#include "BipartiteGraphHandler.hpp"
#include <queue>
#include <iostream>

using namespace dai;
using namespace std;

BipartiteGraphHandler::BipartiteGraphHandler()
{
    vector<Edge> edges = {
        Edge(0, 0), Edge(1, 0), Edge(2, 0),
        Edge(1, 1), Edge(2, 1), Edge(3, 1), Edge(4, 2)};

    graph = BipartiteGraph(5, 3, edges.begin(), edges.end());
}

void BipartiteGraphHandler::operator()()
{
    this->doSomething();
}

void BipartiteGraphHandler::addEdge(size_t node1, size_t node2)
{
    if (node1 < graph.nrNodes1() && node2 < graph.nrNodes2() && !graph.hasEdge(node1, node2))
    {
        graph.addEdge(node1, node2);
    }
}

void BipartiteGraphHandler::removeEdge(size_t node1, size_t node2)
{
    if (graph.hasEdge(node1, node2))
    {
        graph.eraseEdge(node1, node2);
    }
}

void BipartiteGraphHandler::addNode(size_t nodeType)
{
    if (nodeType == 1)
    {
        graph.addNode1();
    }
    else if (nodeType == 2)
    {
        graph.addNode2();
    }
}

void BipartiteGraphHandler::removeNode(size_t node, size_t nodeType)
{
    if (nodeType == 1 && node < graph.nrNodes1())
    {
        graph.eraseNode1(node);
    }
    else if (nodeType == 2 && node < graph.nrNodes2())
    {
        graph.eraseNode2(node);
    }
}

bool BipartiteGraphHandler::isConnected(size_t node1, size_t node2)
{
    vector<bool> visited(graph.nrNodes1() + graph.nrNodes2(), false);
    queue<size_t> q;
    q.push(node1);
    visited[node1] = true;

    while (!q.empty())
    {
        size_t n = q.front();
        q.pop();
        const auto &neighbors = (n < graph.nrNodes1() ? graph.nb1(n) : graph.nb2(n - graph.nrNodes1()));
        for (const Neighbor &neighbor : neighbors)
        {
            size_t adjacent = neighbor.node;
            if (adjacent == node2)
            {
                return true;
            }
            if (!visited[adjacent])
            {
                visited[adjacent] = true;
                q.push(adjacent);
            }
        }
    }
    return false;
}

void BipartiteGraphHandler::displayConnectivity()
{
    cout << "Connectivity between nodes:" << endl;
    for (size_t i = 0; i < graph.nrNodes1(); ++i)
    {
        cout << "Node Type 1, Index " << i << ":";
        for (const Neighbor &n : graph.nb1(i))
        {
            cout << " connected to Node Type 2, Index " << n.node << ";";
        }
        cout << endl;
    }
    for (size_t i = 0; i < graph.nrNodes2(); ++i)
    {
        cout << "Node Type 2, Index " << i << ":";
        for (const Neighbor &n : graph.nb2(i))
        {
            cout << " connected to Node Type 1, Index " << n.node << ";";
        }
        cout << endl;
    }
}

void BipartiteGraphHandler::displayGraphInfo()
{
    cout << "Graph has " << graph.nrNodes1() << " nodes of type 1 and "
         << graph.nrNodes2() << " nodes of type 2." << endl
         << "Total edges: " << graph.nrEdges() << endl;
}

void BipartiteGraphHandler::doSomething()
{
    // Step 1: Display initial graph info
    std::cout << "Initial Graph Information:" << std::endl;
    displayGraphInfo();
    displayGraphWithGraphviz();

    // Step 2: Add nodes and edges to the graph
    std::cout << "\nAdding initial nodes and edges to the graph..." << std::endl;
    addNode(1);                                   // Adding a new Type 1 node
    addNode(2);                                   // Adding a new Type 2 node
    size_t firstType1Node = graph.nrNodes1() - 1; // Assuming last node index for Type 1
    size_t firstType2Node = graph.nrNodes2() - 1; // Assuming last node index for Type 2
    addEdge(firstType1Node, firstType2Node);      // Connecting the newly added nodes

    // Step 3: Add more nodes
    std::cout << "\nAdding more nodes to demonstrate dynamic additions..." << std::endl;
    addNode(1);                                    // Adding another Type 1 node
    addNode(1);                                    // And one more Type 1 node
    size_t secondType1Node = graph.nrNodes1() - 2; // Second last Type 1 node index
    size_t thirdType1Node = graph.nrNodes1() - 1;  // Last Type 1 node index
    addEdge(secondType1Node, firstType2Node);      // Connect second new Type 1 to the first Type 2
    addEdge(thirdType1Node, firstType2Node);       // Connect third new Type 1 to the first Type 2

    // Step 4: Display updated graph info
    std::cout << "\nUpdated Graph Information after adding more nodes and edges:" << std::endl;
    displayGraphInfo();
    displayGraphWithGraphviz();

    // Step 5: Remove some nodes
    std::cout << "\nRemoving the second newly added Type 1 node..." << std::endl;
    removeNode(secondType1Node, 1); // Removing this Type 1 node

    // Step 6: Check connectivity
    std::cout << "\nChecking connectivity after node removals:" << std::endl;
    if (isConnected(firstType1Node, firstType2Node))
    {
        std::cout << "Node Type1_" << firstType1Node << " and Node Type2_" << firstType2Node << " are still connected." << std::endl;
    }
    else
    {
        std::cout << "Node Type1_" << firstType1Node << " and Node Type2_" << firstType2Node << " are not connected." << std::endl;
    }

    // Step 7: Display connectivity information
    std::cout << "\nConnectivity Information after modifications:" << std::endl;
    displayConnectivity();

    // Step 8: Visualize the graph using Graphviz
    std::cout << "\nVisualizing the graph with Graphviz after all modifications..." << std::endl;
    displayGraphWithGraphviz();
    std::cout << "Graph visualization saved as 'bipartite_graph.png'." << std::endl;

    // Step 9: Display final graph info
    std::cout << "\nFinal Graph Information after all modifications:" << std::endl;
    displayGraphInfo();
}

void BipartiteGraphHandler::displayGraphWithGraphviz()
{
    GVC_t *gvc;
    Agraph_t *g;
    Agnode_t *node1, *node2;
    Agedge_t *edge;
    char buffer[1024];

    // Initialize a Graphviz context
    gvc = gvContext();

    // Create a new graph
    g = agopen("bipartite_graph", Agstrictundirected, nullptr);

    // Add nodes and label them according to their type
    for (size_t i = 0; i < graph.nrNodes1(); i++)
    {
        sprintf(buffer, "Type1_%zu", i);
        node1 = agnode(g, buffer, true);
        agsafeset(node1, "color", "red", "");
        agsafeset(node1, "shape", "circle", "");
    }

    for (size_t i = 0; i < graph.nrNodes2(); i++)
    {
        sprintf(buffer, "Type2_%zu", i);
        node2 = agnode(g, buffer, true);
        agsafeset(node2, "color", "blue", "");
        agsafeset(node2, "shape", "square", "");
    }

    // Add edges between nodes
    for (size_t n1 = 0; n1 < graph.nrNodes1(); n1++)
    {
        for (const Neighbor &n : graph.nb1(n1))
        {
            sprintf(buffer, "Type1_%zu", n1);
            node1 = agnode(g, buffer, false);
            sprintf(buffer, "Type2_%zu", n.node);
            node2 = agnode(g, buffer, false);
            edge = agedge(g, node1, node2, nullptr, true);
            agsafeset(edge, "color", "gray", "");
        }
    }

    // Set graph attributes
    agsafeset(g, "splines", "ortho", ""); // Use orthogonal edges
    agsafeset(g, "rankdir", "LR", "");    // Left to right directed graph

    // Layout the graph using the DOT algorithm
    gvLayout(gvc, g, "dot");

    // Render the graph to a file
    std::string filename = std::string(Settings::bp_graphviz) + std::to_string(BipartiteGraphHandler::counter++) + ".png";
    const char *filename_c_str = filename.c_str();
    gvRenderFilename(gvc, g, "png", filename_c_str);

    // Clean up
    gvFreeLayout(gvc, g);

    // Close the graph
    agclose(g);

    // Free graphviz context
    gvFreeContext(gvc);

    cout << "Graph visualized and saved as bipartite_graph.png" << endl;
}