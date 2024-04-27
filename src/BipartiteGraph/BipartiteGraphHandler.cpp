#include "BipartiteGraphHandler.hpp"
#include <iostream>

using namespace dai;
using namespace std;

BipartiteGraphHandler::BipartiteGraphHandler()
{
    // Create a list of edges
    vector<Edge> edges;
    edges.reserve(5);
    edges.push_back(Edge(0, 0));
    edges.push_back(Edge(1, 0));
    edges.push_back(Edge(2, 0));
    edges.push_back(Edge(1, 1));
    edges.push_back(Edge(2, 1));

    // Initialize bipartite graph
    graph = BipartiteGraph(3, 2, edges.begin(), edges.end());
}

void BipartiteGraphHandler::displayGraphInfo()
{
    cout << "G has " << graph.nrNodes1() << " nodes of type 1, "
         << graph.nrNodes2() << " nodes of type 2 and " << graph.nrEdges() << " edges." << endl
         << endl;
}

void BipartiteGraphHandler::drawGraph()
{
    GVC_t *gvc;
    Agraph_t *g;
    Agnode_t *node;
    Agedge_t *edge;

    // Initialize a Graphviz context
    gvc = gvContext();

    // Create a new graph
    g = agopen("bipartite", Agstrictundirected, NULL);

    // Add nodes and edges from the bipartite graph
    for (size_t n1 = 0; n1 < graph.nrNodes1(); ++n1)
    {
        string node1_name = "Type1_" + to_string(n1);
        node = agnode(g, const_cast<char *>(node1_name.c_str()), true);

        bforeach(const Neighbor &n2, graph.nb1(n1))
        {
            string node2_name = "Type2_" + to_string(n2);
            Agnode_t *node2 = agnode(g, const_cast<char *>(node2_name.c_str()), true);
            edge = agedge(g, node, node2, 0, true);
        }
    }

    // Set some attributes (optional)
    agsafeset(g, "rankdir", "LR", "");
    agsafeset(g, "splines", "true", "");

    // Layout the graph
    gvLayout(gvc, g, "dot");

    // Render the graph to an output file
    gvRenderFilename(gvc, g, "png", "bipartite_graph.png");

    // Free layout data
    gvFreeLayout(gvc, g);

    // Close the graph
    agclose(g);

    // Free graphviz context
    gvFreeContext(gvc);

    cout << "Graph drawn and saved as bipartite_graph.png" << endl;
}