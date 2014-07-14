#include "quick_sort.hh"

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

static void test_quick_sort_helper(vector<int>& a) {
    vector<int> cp = a;
    quick_sort(a);
    stable_sort(cp.begin(), cp.end());
    assert(a.size() == cp.size());
    for (size_t i = 0; i < a.size(); ++i) {
        assert(a[i] == cp[i]);
    }
}
static void test_quick_sort() {
    cout << "// Begin Testing for quick_sort" << endl;
    int array[] = {7, 6, 9, 10, 5, 5, 7, 3 };
    size_t size = sizeof(array)/sizeof(int);
    vector<int> a(array, array + size);
    test_quick_sort_helper(a);

    vector<int> empty;
    test_quick_sort_helper(empty);
    cout << "//~ End Testing for quick_sort" << endl;
}

int main(int argc, char**argv) {
    test_quick_sort();
    return 0;
}
