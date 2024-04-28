#ifndef BIPARTITE_GRAPH_HANDLER_HPP
#define BIPARTITE_GRAPH_HANDLER_HPP

#include "Settings.hpp"
#include <dai/bipgraph.h>
#include <iostream>
#include <vector>
#include <gvc.h>
#include <cgraph.h>

class BipartiteGraphHandler
{
public:
    BipartiteGraphHandler();
    void operator()();
    void addEdge(size_t node1, size_t node2);
    void removeEdge(size_t node1, size_t node2);
    void addNode(size_t nodeType);
    void removeNode(size_t node, size_t nodeType);
    bool isConnected(size_t node1, size_t node2);
    void displayGraphInfo();
    void displayConnectivity();
    void displayGraphWithGraphviz();

private:
    dai::BipartiteGraph graph;
    std::vector<dai::Neighbor> nodesType1;
    std::vector<dai::Neighbor> nodesType2;
    void doSomething();
    static inline int counter = 0;
};

#endif // BIPARTITE_GRAPH_HANDLER_HPP