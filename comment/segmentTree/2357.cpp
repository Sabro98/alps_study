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
//최솟값과 최댓값
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 100001
#define MOD 1000000007ll
#define INF 0x7FFFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K, Q;

lli arr[MAXSIZE];
lli tree[4 * MAXSIZE];

lli init(int start, int end, int node) //세그트리생성
{
    if (start == end)
    {
        return tree[node] = arr[start];
    }
    int mid = (start + end) / 2;

    return tree[node] = max(init(start, mid, node * 2), init(mid + 1, end, node * 2 + 1));
}

lli getmax(int start, int end, int node, int left, int right)
{
    if (end < left || right < start) //범위밖
    {
        return -1;
    }
    if (left <= start && end <= right) //범위안이라면 자신을 리턴
    {
        return tree[node];
    }
    //범위에 걸치면
    int mid = (start + end) / 2;
    return max(getmax(start, mid, node * 2, left, right), getmax(mid + 1, end, node * 2 + 1, left, right));
}

lli mtree[4 * MAXSIZE];

lli minit(int start, int end, int node) //세그트리생성
{
    if (start == end)
    {
        return mtree[node] = arr[start];
    }
    int mid = (start + end) / 2;

    return mtree[node] = min(minit(start, mid, node * 2), minit(mid + 1, end, node * 2 + 1));
}

lli getmin(int start, int end, int node, int left, int right)
{
    if (end < left || right < start) //범위밖
    {
        return INF;
    }
    if (left <= start && end <= right) //범위안이라면 자신을 리턴
    {
        return mtree[node];
    }
    //범위에 걸치면
    int mid = (start + end) / 2;
    return min(getmin(start, mid, node * 2, left, right), getmin(mid + 1, end, node * 2 + 1, left, right));
}

int main()
{
    fastio;

    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
    init(0, N - 1, 1);
    minit(0, N - 1, 1);
    int l, r;
    ffor(i, M)
    {
        cin >> l >> r;
        l--;
        r--;
        //cout << "ans: ";
        cout << getmin(0, N - 1, 1, l, r) << " ";
        cout << getmax(0, N - 1, 1, l, r) << endl;
    }
}