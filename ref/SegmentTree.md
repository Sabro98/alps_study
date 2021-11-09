```cpp
ll init(int start, int end, int node) {
    if (start == end) return tree[node] = A[start];
    int mid = (start + end) / 2;

    return tree[node] = init(start, mid, LEFT(node)) + init(mid + 1, end, RIGHT(node));
}

ll calc(int start, int end, int node, int left, int right) {
    if (left > end || right < start) return 0;
    if (left <= start && end <= right) return tree[node];
    int mid = (start + end) / 2;
    return calc(start, mid, LEFT(node), left, right) + calc(mid + 1, end, RIGHT(node), left, right);
}

void update(int start, int end, int node, int idx, ll diff) {
    if (start > idx || end < idx) return;
    tree[node] += diff;
    if (start == end) return;
    int mid = (start + end) / 2;
    update(start, mid, LEFT(node), idx, diff);
    update(mid + 1, end, RIGHT(node), idx, diff);
}
```
