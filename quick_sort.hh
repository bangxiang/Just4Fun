#include <vector>
#include <stack>
#include <cassert>

/*
 * Purpose: play quick sort algorithm
 */

void quick_sort(std::vector<int>& a) {
    typedef std::pair<std::size_t, std::size_t> Range;
    std::stack<Range> st;
    st.push(Range(0, a.size()));
    while(!st.empty()) {
        std::size_t start = st.top().first;
        std::size_t end = st.top().second;
        st.pop();

        if (start + 1 > end) { continue ; } // elem# <= 1, already sorted

        assert(start < a.size() && end <= a.size());

        int v = a[start];
        // i: point to the first elem which is greater than or equal to v (a[i] >= v);
        // j: point to the first elem which is less than v (a[j] < v)
        std::size_t i = start;
        std::size_t j = start + 1;
        for(; j != end; ++j) {
            if (a[j] < v) {
                std::swap(a[j], a[i]);
                ++i;
            }
        }
        assert(i < end);

        if (i > start) {
            st.push(Range(start, i));
            st.push(Range(i, end));
        } else {
            st.push(Range(start + 1, end));
        }
    }
}
