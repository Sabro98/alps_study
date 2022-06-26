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
//사탕상자
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

lli arr[MAXSIZE]; //arr[맛] =갯수
lli tree[4 * MAXSIZE];

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

int findRanking(int node, int ranking, int start, int end)
{
    if (start == end) //밑바닥임
        return start;

    int mid = (start + end) / 2;
    if (tree[node * 2] < ranking)
    { //오른쪽에서 찾아야함
        return findRanking(node * 2 + 1, ranking - tree[node * 2], mid + 1, end);
    }
    else
    { //왼쪽으로가야함
        return findRanking(node * 2, ranking, start, mid);
    }
}
int main()
{
    fastio;

    cin >> N;
    memset(tree, 0, sizeof(tree));
    for (int i = 0; i <= MAXSIZE; i++)
    {
        arr[i] = 0;
    }

    int l, r, ranking, idx;
    lli up;
    ffor(i, N)
    {
        cin >> Q;
        if (Q == 2)
        { //빼거나 더함
            cin >> idx >> up;
            update(1, MAXSIZE, 1, idx, up);
            arr[idx] += up;
            // cout << sum(1, N, 1, 1, 10) << endl;
        }
        else
        { //순위 구하기 , 빼기
            cin >> ranking;
            r = findRanking(1, ranking, 1, MAXSIZE);
            cout << r << endl;
            update(1, MAXSIZE, 1, r, -1);
        }
    }
}