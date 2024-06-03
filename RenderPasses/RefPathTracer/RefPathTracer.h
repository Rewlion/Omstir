#pragma once
#include "Falcor.h"
#include "RenderGraph/RenderPass.h"

using namespace Falcor;

class RefPathTracer : public RenderPass
{
public:
    FALCOR_PLUGIN_CLASS(RefPathTracer, "RefPathTracer", "Insert pass description here.");

    static ref<RefPathTracer> create(ref<Device> pDevice, const Properties& props)
    {
        return make_ref<RefPathTracer>(pDevice, props);
    }

    RefPathTracer(ref<Device> pDevice, const Properties& props);

    virtual Properties getProperties() const override;
    virtual RenderPassReflection reflect(const CompileData& compileData) override;
    virtual void compile(RenderContext* pRenderContext, const CompileData& compileData) override {}
    virtual void execute(RenderContext* pRenderContext, const RenderData& renderData) override;
    virtual void renderUI(Gui::Widgets& widget) override;
    virtual void setScene(RenderContext* pRenderContext, const ref<Scene>& pScene) override;
    virtual bool onMouseEvent(const MouseEvent& mouseEvent) override { return false; }
    virtual bool onKeyEvent(const KeyboardEvent& keyEvent) override { return false; }

private:
    ref<Program> mpProgram;
    ref<Scene> mpScene;
    ref<RtBindingTable> mpBindingTable;
    ref<RtProgramVars> mpVars;
};
