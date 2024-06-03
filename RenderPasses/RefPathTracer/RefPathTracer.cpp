#include "RefPathTracer.h"
#include "Core/Program/ProgramVars.h"
#include "Core/Program/RtBindingTable.h"

extern "C" FALCOR_API_EXPORT void registerPlugin(Falcor::PluginRegistry& registry)
{
    registry.registerClass<RenderPass, RefPathTracer>();
}

namespace
{
    const char kShaderFile[] = "RenderPasses/RefPathTracer/RefPathTracer.rt.slang";
    // Ray tracing settings that affect the traversal stack size.
    // These should be set as small as possible.
    const uint32_t kMaxPayloadSizeBytes = 16u;
    const uint32_t kMaxRecursionDepth = 2u;
}

RefPathTracer::RefPathTracer(ref<Device> pDevice, const Properties& props)
    : RenderPass(pDevice)
{
}

Properties RefPathTracer::getProperties() const
{
    return {};
}

RenderPassReflection RefPathTracer::reflect(const CompileData& compileData)
{
    // Define the required resources here
    RenderPassReflection reflector;
    reflector.addOutput("output", "output")
             .texture2D()
             .format(ResourceFormat::RGBA32Float)
             .bindFlags(ResourceBindFlags::UnorderedAccess);
    return reflector;
}

void RefPathTracer::execute(RenderContext* pRenderContext, const RenderData& renderData)
{
    if (!mpScene)
    {
        Texture* pDst = renderData.getTexture("output").get();
        if (pDst)
            pRenderContext->clearTexture(pDst);
        return;
    }

    if (!mpProgram)
    {

        ProgramDesc desc;
        desc.addShaderModules(mpScene->getShaderModules());
        desc.addShaderLibrary(kShaderFile);
        desc.setMaxPayloadSize(kMaxPayloadSizeBytes);
        desc.setMaxAttributeSize(mpScene->getRaytracingMaxAttributeSize());
        desc.setMaxTraceRecursionDepth(kMaxRecursionDepth);

        mpBindingTable = RtBindingTable::create(1, 1, mpScene->getGeometryCount());
        auto& sbt = mpBindingTable;

        sbt->setRayGen(desc.addRayGen("RayGen"));
        sbt->setMiss(0, desc.addMiss("Miss"));

        if (mpScene->hasGeometryType(Scene::GeometryType::TriangleMesh))
        {
            sbt->setHitGroup(0,
            mpScene->getGeometryIDs(Scene::GeometryType::TriangleMesh),
            desc.addHitGroup("ClosestHit"));
        }

        mpProgram = Program::create(mpDevice, desc, mpScene->getSceneDefines());
        mpProgram->setTypeConformances(mpScene->getTypeConformances());

        mpVars = RtProgramVars::create(mpDevice, mpProgram, sbt);
    }

    if (is_set(mpScene->getUpdates(), Scene::UpdateFlags::RecompileNeeded) ||
        is_set(mpScene->getUpdates(), Scene::UpdateFlags::GeometryChanged))
    {
        FALCOR_THROW("This render pass does not support scene changes that require shader recompilation.");
    }

    ShaderVar var = mpVars->getRootVar();

    static uint frameCount = 0;
    var["CB"]["gFrameCount"] = frameCount++;
    var["gOutputColor"] = renderData.getTexture("output");

     // Get dimensions of ray dispatch.
    const uint2 targetDim = renderData.getDefaultTextureDims();
    FALCOR_ASSERT(targetDim.x > 0 && targetDim.y > 0);

    mpScene->raytrace(pRenderContext, mpProgram.get(), mpVars, uint3(targetDim, 1));
}

void RefPathTracer::setScene(RenderContext* pRenderContext, const ref<Scene>& pScene)
{
    mpScene = pScene;
    mpProgram = nullptr;
    mpBindingTable = nullptr;
    mpVars = nullptr;
}

void RefPathTracer::renderUI(Gui::Widgets& widget) {}
