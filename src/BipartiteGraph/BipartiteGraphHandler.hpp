#ifndef BIPARTITE_GRAPH_HANDLER_HPP
#define BIPARTITE_GRAPH_HANDLER_HPP

#include <dai/bipgraph.h>
#include <vector>
#include <gvc.h>
#include <cgraph.h>

class BipartiteGraphHandler
{
public:
    BipartiteGraphHandler();
    void operator()()
    {
        this->displayGraphInfo();
        this->drawGraph();
    }

private:
    dai::BipartiteGraph graph;
    void displayGraphInfo();
    void drawGraph();
};

#endif // BIPARTITE_GRAPH_HANDLER_HPP