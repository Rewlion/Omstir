#include "Utils/Math/MathConstants.slangh"

import Scene.Raytracing;

#define is_valid(name) (is_valid_##name != 0)

cbuffer CB
{
    uint gFrameCount;
};

RWTexture2D<float4> gOutputColor;

struct Payload
{
    float3 color;
};

static const float kRayTMax = FLT_MAX;

[shader("raygeneration")]
void RayGen()
{
    uint2 rayId = DispatchRaysIndex().xy;
    uint2 rayDim = DispatchRaysDimensions().xy;

    float3 rayOrigin = gScene.camera.getPosition();
    float3 rayDir = gScene.camera.computeRayPinhole(rayId, rayDim).dir;

    RayDesc ray;
    ray.Direction = rayDir;
    ray.Origin = rayOrigin;
    ray.TMin = 0;
    ray.TMax = kRayTMax;

    Payload payload = { 0.0.xxx };
    TraceRay(gScene.rtAccel, 0, 0xFF, 0, 0, 0, ray, payload);

    gOutputColor[rayId] = float4(payload.color, 1);
}

[shader("closesthit")]
void ClosestHit(inout Payload payload, BuiltInTriangleIntersectionAttributes attribs)
{
    TriangleHit hit;
    hit.instanceID = getGeometryInstanceID();
    hit.primitiveIndex = PrimitiveIndex();
    hit.barycentrics = attribs.barycentrics;

    VertexData v = gScene.getVertexData(hit);
    uint materialID = gScene.getMaterialID(hit.instanceID);

    let lod = ExplicitLodTextureSampler(0.f);
    ShadingData sd = gScene.materials.prepareShadingData(v, materialID, -WorldRayDirection(), lod);

    let mi = gScene.materials.getMaterialInstance(sd, lod);
    let bsdfProperty = mi.getProperties(sd);

    payload.color = bsdfProperty.diffuseReflectionAlbedo;
}

[shader("miss")]
void Miss(inout Payload payload)
{
    payload.color = float3(1, 0, 0);
}
