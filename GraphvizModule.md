# Introduction #

[Graphviz](http://www.graphviz.org/) is an open source graph visualization library.

Through different renderers, the Graphviz module can output the graphs to contexts such as Max2D and Cairo. It also includes live graph interaction, with click-able nodes and edges, and built-in zoom capability.

Graphs can either be rendered from _dot_ files/text or be created on-the-fly using a simple object hierarchy.

## Requirements ##

BaH.Graphviz requires the **BaH.Expat** module for support of complex HTML-based node text rendering support.

Applications will also require a specific renderer to be Imported. Currently available is **BaH.GraphvizMax2D**, a Max2D-based renderer.