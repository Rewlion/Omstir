#include "Utils/Math/MathConstants.slangh"

import Scene.Raytracing;
// import Utils.Sampling.SampleGenerator;
import Utils.Sampling.UniformSampleGenerator;
typedef UniformSampleGenerator SampleGenerator;

cbuffer CB
{
    uint gFrameCount;
    uint gMaxBounces;
};

RWTexture2D<float4> gOutputColor;

struct Payload
{
    TriangleHit hit;
    uint hasHit;

    __init()
    {
        hasHit = 0;
    }
};

static const float kRayTMax = FLT_MAX;

[shader("raygeneration")]
void RayGen()
{
    uint2 rayId = DispatchRaysIndex().xy;
    uint2 rayDim = DispatchRaysDimensions().xy;

    RayDesc ray = gScene.camera.computeRayPinhole(rayId, rayDim).toRayDesc();

    float3 radiance = 0.0.xxx;
    float3 throughouput = 1.0.xxx;

    SampleGenerator sg = SampleGenerator(rayId, gFrameCount);

    for (uint bounce = 0; bounce <= gMaxBounces; ++bounce)
    {
        Payload payload;
        TraceRay(gScene.rtAccel, 0, 0xFF, 0, 0, 0, ray, payload);

        if (payload.hasHit == 0)
            break;

        let hit = payload.hit;

        VertexData v = gScene.getVertexData(hit);
        uint materialID = gScene.getMaterialID(hit.instanceID);

        let lod = ExplicitLodTextureSampler(0.f);
        ShadingData sd = gScene.materials.prepareShadingData(v, materialID, -ray.Direction, lod);
        let mi = gScene.materials.getMaterialInstance(sd, lod);

        BSDFProperties properties = mi.getProperties(sd);

        if (any(properties.emission > 0))
        {
            radiance += properties.emission * throughouput;
            break;
        }

        BSDFSample lightSample;
        mi.sample(sd, sg, lightSample, true);

        throughouput *= lightSample.weight;
        ray.Origin = sd.computeRayOrigin(true);
        ray.Direction = lightSample.wo;
        ray.TMin = 0.0;
    }

    gOutputColor[rayId] = float4(radiance, 1);
}

[shader("closesthit")]
void ClosestHit(inout Payload payload, BuiltInTriangleIntersectionAttributes attribs)
{
    TriangleHit hit;
    hit.instanceID = getGeometryInstanceID();
    hit.primitiveIndex = PrimitiveIndex();
    hit.barycentrics = attribs.barycentrics;

    payload.hasHit = 1;
    payload.hit = hit;
}

[shader("miss")]
void Miss(inout Payload payload)
{
    payload.hasHit = 0;
}
