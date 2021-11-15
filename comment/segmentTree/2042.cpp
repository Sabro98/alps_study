#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <set>
#include <cmath>
#include <map>
#include <deque>
#include <limits.h>
#include <utility>
#include <list>
#include <unordered_map>
#include <string.h>
#include <random>
#include <queue>
//구간합구하기
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 1000001
#define MOD 1000000000ll
#define INF 0x7FFFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K, Q;

// vector<int> arr(MAXSIZE);
lli arr[MAXSIZE];
lli tree[4 * MAXSIZE];
// vector<int> tree(MAXSIZE, 0);

lli init(int start, int end, int node) //세그트리생성
{
    if (start == end)
    {
        return tree[node] = arr[start];
    }
    int mid = (start + end) / 2;

    return tree[node] = init(start, mid, node * 2) + init(mid + 1, end, node * 2 + 1);
}

lli sum(int start, int end, int node, int left, int right)
{
    if (end < left || right < start) //범위밖
    {
        return 0;
    }
    if (left <= start && end <= right) //범위안이라면 자신을 리턴
    {
        return tree[node];
    }
    //범위에 걸치면
    int mid = (start + end) / 2;
    return sum(start, mid, node * 2, left, right) + sum(mid + 1, end, node * 2 + 1, left, right);
}

void update(int start, int end, int node, int idx, lli diff)
{
    if (!(start <= idx && idx <= end))
        return;

    tree[node] += diff;
    if (start == end)
        return; //트리의 밑바닥

    int mid = (start + end) / 2;
    update(start, mid, node * 2, idx, diff);
    update(mid + 1, end, node * 2 + 1, idx, diff);
}
int main()
{
    fastio;

    cin >> N >> M >> K;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
    init(0, N - 1, 1);
    // cout << sum(0, N - 1, 1, 1, 3);
    // update(0, N - 1, 1, 2, 100);
    // cout << sum(0, N - 1, 1, 1, 4);
    int l, r, idx;
    lli up;
    ffor(i, M + K)
    {
        cin >> Q;
        if (Q == 1)
        { //변경
            cin >> idx >> up;
            idx--;
            update(0, N - 1, 1, idx, up - arr[idx]);
            arr[idx] = up;
            // cout << sum(0, N - 1, 1, 0, N - 1) << endl;
        }
        else
        { //합
            cin >> l >> r;
            l--;
            r--;
            cout << sum(0, N - 1, 1, l, r) << endl;
        }
    }
}