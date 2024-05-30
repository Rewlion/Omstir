add_plugin(RefPathTracer)

target_sources(RefPathTracer PRIVATE
    RefPathTracer.cpp
    RefPathTracer.h
)

target_source_group(RefPathTracer "RenderPasses")
