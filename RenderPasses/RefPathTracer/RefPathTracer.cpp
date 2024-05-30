#include "RefPathTracer.h"

extern "C" FALCOR_API_EXPORT void registerPlugin(Falcor::PluginRegistry& registry)
{
    registry.registerClass<RenderPass, RefPathTracer>();
}

RefPathTracer::RefPathTracer(ref<Device> pDevice, const Properties& props) : RenderPass(pDevice) {}

Properties RefPathTracer::getProperties() const
{
    return {};
}

RenderPassReflection RefPathTracer::reflect(const CompileData& compileData)
{
    // Define the required resources here
    RenderPassReflection reflector;
    // reflector.addOutput("dst");
    // reflector.addInput("src");
    return reflector;
}

void RefPathTracer::execute(RenderContext* pRenderContext, const RenderData& renderData)
{
    // renderData holds the requested resources
    // auto& pTexture = renderData.getTexture("src");
}

void RefPathTracer::renderUI(Gui::Widgets& widget) {}
