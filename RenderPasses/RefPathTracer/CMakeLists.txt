add_plugin(RefPathTracer)

target_sources(RefPathTracer PRIVATE
    RefPathTracer.cpp
    RefPathTracer.h
    RefPathTracer.rt.slang
)

target_copy_shaders(RefPathTracer RenderPasses/RefPathTracer)

target_source_group(RefPathTracer "RenderPasses")
