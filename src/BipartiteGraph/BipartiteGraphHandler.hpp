#ifndef BIPARTITE_GRAPH_HANDLER_HPP
#define BIPARTITE_GRAPH_HANDLER_HPP

#include "Settings.hpp"
#include <dai/bipgraph.h>
#include <iostream>
#include <vector>
#include <gvc.h>
#include <cgraph.h>

/**
 * @class BipartiteGraphHandler
 * @brief Handles operations and visualizations for a bipartite graph.
 *
 * This class manages a bipartite graph and provides functionalities for adding and removing nodes and edges,
 * checking connectivity, and visualizing the graph using Graphviz. It supports various operations to manipulate
 * the graph structure and provides detailed visual feedback on the graph's current state.
 */
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