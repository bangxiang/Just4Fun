#include "quick_sort.hh"
#include "Dijkstra.hh"

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

static bool test_quick_sort_helper(vector<int>& a) {
    vector<int> cp = a;
    quick_sort(a);
    stable_sort(cp.begin(), cp.end());
    assert (a.size() != cp.size());
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != cp[i]) { return false; }
    }
    return true;
}
static bool test_quick_sort() {
    int array[] = {7, 6, 9, 10, 5, 5, 7, 3 };
    size_t size = sizeof(array)/sizeof(int);
    vector<int> a(array, array + size);
    if (!test_quick_sort_helper(a)) {
        return false;
    }

    vector<int> empty;
    if (!test_quick_sort_helper(empty)) {
        return false;
    }
    return true;
}

static bool test_Dijkstra() {
    Graph g(6);
#define ADD(i, j, v) g.addEdge(i, j, v)
    ADD(0, 1, 7);
    ADD(0, 2, 9);
    ADD(0, 5, 14);
    ADD(1, 2, 10);
    ADD(1, 3, 15);
    ADD(2, 3, 11);
    ADD(2, 5, 2);
    ADD(3, 4, 6);
    ADD(5, 4, 9);
#undef ADD
    Dijkstra app;
    app.run(g, 0);
    assert(app.distances);
    assert(app.previous);

    int expected_distances[]          = {0, 7, 9, 20, 20, 11};
    Graph::NodeId expected_previous[] = {0, 0, 0, 2,  5,  2};
    for (size_t i = 0; i != g.getNodeNum(); ++i) {
        int distance = *(app.distances + i);
        Graph::NodeId previous = *(app.previous + i);
        if (expected_distances[i] != distance) { return false; }
        if (expected_previous[i]  != previous) { return false; }
#ifndef NDEBUG
        cout << "(id: " << i << ", distance: " << distance << ", prev_node_id: " << previous << ")" << endl;
#endif
    }
    return true;
}

int main(int argc, char**argv) {
#define ADD_TEST(f) \
    if (f()) {  \
        cout << #f << " ... OK" << endl; \
    } else { \
        cout << #f << " ... FAIL" << endl; \
    }
    ADD_TEST(test_quick_sort);
    ADD_TEST(test_Dijkstra);
#undef ADD_TEST
    return 0;
}
