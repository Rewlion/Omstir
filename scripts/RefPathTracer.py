from pathlib import WindowsPath, PosixPath
from falcor import *

def render_graph_RefPTRenderGraph():
    g = RenderGraph('ReferencePathTracer')
    g.create_pass('RefPathTracer', 'RefPathTracer', {})
    g.mark_output('RefPathTracer.output')
    return g

RefPTRenderGraph = render_graph_RefPTRenderGraph()
try: m.addGraph(RefPTRenderGraph)
except NameError: None
