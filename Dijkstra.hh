#ifndef Dijkstra_hh_include
#define Dijkstra_hh_include

#include <climits>
#include <vector>

class Graph { // un-directional graph
public:
    typedef std::size_t NodeId;
    typedef int EdgeVal;
    static const EdgeVal INVALID_EDGE_VAL = INT_MAX;
    static const NodeId INVALID_NODEID = (NodeId)(-1);

    // init a Graph with n nodes
    // NodeId is in range [0, n - 1]
    explicit Graph(std::size_t n);

    ~Graph();

    std::size_t getNodeNum() const { return size; }

    // add edge between n0 and n1
    void addEdge(NodeId n0, NodeId n1, EdgeVal val);

    // rm edge between n0 and n1
    void rmEdge(NodeId n0, NodeId n1);

    // return true if there is an edge between n0 and n1
    bool hasEdge(NodeId n0, NodeId n1) const;

    // return edge value between n0 and n1
    // return INVALID_EDGE_VAL if there is no edge between them
    EdgeVal getEdgeVal(NodeId n0, NodeId n1) const;

private:
    // uncopyable
    Graph();
    Graph(const Graph&);
    Graph& operator=(const Graph&);

    EdgeVal& edge(NodeId n0, NodeId n1);

    std::size_t size;
    EdgeVal *edges;
};

class Dijkstra {
public:
    typedef Graph::NodeId NodeId;
    typedef Graph::EdgeVal EdgeVal;

    Dijkstra();
    ~Dijkstra();

    void run(const Graph& g, NodeId src);

    void reset();

    EdgeVal *distances;
    NodeId *previous;
};

#endif // Dijkstra_hh_include
