#include "Dijkstra.hh"

#include <list>
#include <cassert>

using std::size_t;

Graph::Graph(size_t n) : size(n) {
    const size_t matrix_size = ((n - 1) * n)/2 + 1;
    edges = new EdgeVal[matrix_size];
    *edges = 0; // edges[0] means self-edge whose value is always 0
    for (size_t i = 1; i != matrix_size; ++i) {
        *(edges + i) = INVALID_EDGE_VAL;
    }
}

Graph::~Graph() {
    delete [] edges;
}

Graph::EdgeVal& Graph::edge(NodeId i, NodeId j) {
    assert(i < size && j < size);
    if (i < j) {
        std::swap(i, j);
    }
    return i == j ? *edges : *(edges + ((i-1)*i)/2 + j + 1);
}

bool Graph::hasEdge(NodeId n0, NodeId n1) const {
    return getEdgeVal(n0, n1) != INVALID_EDGE_VAL;
}

Graph::EdgeVal Graph::getEdgeVal(NodeId n0, NodeId n1) const {
    return (const_cast<Graph*>(this))->edge(n0, n1);
}

void Graph::addEdge(NodeId n0, NodeId n1, EdgeVal val) {
    assert(n0 != n1 || val == 0);
    edge(n0, n1) = val;
}

void Graph::rmEdge(NodeId n0, NodeId n1) {
    assert(n0 != n1);
    edge(n0, n1) = INVALID_EDGE_VAL;
}

Dijkstra::Dijkstra() : distances(0), previous(0) {
}

Dijkstra::~Dijkstra() {
    reset();
}

void Dijkstra::reset() {
    delete [] distances;
    delete [] previous;
}

void Dijkstra::run(const Graph& g, NodeId src_node) {
    reset();
    assert(src_node < g->getNodeNum());
    size_t size = g.getNodeNum();
    distances = new EdgeVal[size];
    previous = new NodeId[size];
    typedef std::list<NodeId> SortedList;
    SortedList set; // sort according to distances[*it]
    set.push_back(src_node);
    for (size_t i = 0; i != size; ++i) {
        distances[i] = Graph::INVALID_EDGE_VAL;
        previous[i] = Graph::INVALID_NODEID;
        if (i != src_node) {
            set.push_back(i);
        }
    }
    assert(set.size() == size);
    distances[src_node] = 0;
    previous[src_node] = src_node;
    while(!set.empty()) {
        // extract_min
        NodeId u = *set.begin();
        set.pop_front();

        // update distances and previous
        // , and move updated nodes into updated_nodes
        std::vector<NodeId> updated_nodes;
        for (SortedList::iterator it = set.begin(); it != set.end();) {
            NodeId i = *it;
            if (!g.hasEdge(u, i)) { ++it; continue; }
            EdgeVal d = distances[u] + g.getEdgeVal(u, i);
            if (distances[i] > d) {
                distances[i] = d;
                previous[i] = u;
                updated_nodes.push_back(i);
                it = set.erase(it);
            } else {
                ++it;
            }
        }

        // insert updated nodes back to the set and keep it sorted
        for (size_t i = 0; i != updated_nodes.size(); ++i) {
            NodeId id = updated_nodes[i];
            SortedList::iterator it = set.begin();
            for (; it != set.end(); ++it) {
                if(distances[id] < distances[*it]) {
                    set.insert(it, id);
                    break;
                }
            }
            if (it == set.end()) {
                set.insert(it, id);
            }
        }
    }
}
