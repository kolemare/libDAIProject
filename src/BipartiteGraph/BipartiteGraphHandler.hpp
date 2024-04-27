#ifndef BIPARTITE_GRAPH_HANDLER_HPP
#define BIPARTITE_GRAPH_HANDLER_HPP

#include <dai/bipgraph.h>
#include <vector>
#include <gvc.h>

class BipartiteGraphHandler
{
public:
    BipartiteGraphHandler();
    void operator()()
    {
        this->displayGraphInfo();
    }

private:
    dai::BipartiteGraph graph;
    void displayGraphInfo();
};

#endif // BIPARTITE_GRAPH_HANDLER_HPP