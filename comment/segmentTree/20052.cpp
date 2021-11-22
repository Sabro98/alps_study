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
//괄호 문자열
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 100001
#define MOD 1000000000ll
#define INF 0x7FFFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K, Q;

string arr;                       //()()()()()
pair<int, int> tree[4 * MAXSIZE]; // first는( second는) 의 남은개수

//1.트리의 왼쪽노드의( 오른쪽노드의 )의 개수는 합쳐져서 사라진다 //뺄셈한뒤 남는쪽에 더해주면됨
//2.트리의 왼쪽노드의) 오른쪽노드의 (의 개수는 그대로 부모노드로 더해져서 올라간다
pii init(int start, int end, int node) //세그트리생성
{
    if (start == end)
    {
        if (arr[start] == '(')
        {
            return tree[node] = {1, 0};
        }
        return tree[node] = {0, 1};
    }
    int mid = (start + end) / 2;
    pii right = init(mid + 1, end, node * 2 + 1);
    pii left = init(start, mid, node * 2);

    //1.트리의 왼쪽노드의( 오른쪽노드의 )의 개수는 합쳐져서 사라진다 //뺄셈한뒤 남는쪽에 더해주면됨
    int diff = left.first - right.second;
    if (diff > 0)
    {
        tree[node].first += diff;
    }
    else
    {
        tree[node].second += -diff;
    }

    //2.트리의 왼쪽노드의) 오른쪽노드의 (의 개수는 그대로 부모노드로 더해져서 올라간다
    tree[node].second += left.second;
    tree[node].first += right.first;

    return tree[node];
}

pii sum(int start, int end, int node, int l, int r)
{
    if (end < l || r < start) //범위밖
    {
        return {0, 0};
    }
    if (l <= start && end <= r) //범위안이라면 자신을 리턴
    {
        return tree[node];
    }
    //범위에 걸치면
    int mid = (start + end) / 2;
    pii left = sum(start, mid, node * 2, l, r);
    pii right = sum(mid + 1, end, node * 2 + 1, l, r);
    pii ret = {0, 0};
    int diff = left.first - right.second;
    if (diff > 0)
    {
        ret.first += diff;
    }
    else
    {
        ret.second += -diff;
    }
    ret.second += left.second;
    ret.first += right.first;
    return ret;
}

int main()
{
    fastio;
    cin >> arr;
    cin >> N;
    memset(tree, 0, sizeof(tree));

    init(0, arr.size() - 1, 1);
    // pii temp = sum(0, arr.size() - 1, 1, 0, 1);
    // cout << "test===\n";
    // cout << temp.first << temp.second << endl;
    // cout << "======\n";
    int l, r;
    lli up;
    int ans = 0;
    ffor(i, N)
    {
        cin >> l >> r;
        l--;
        r--;
        pii temp = sum(0, arr.size() - 1, 1, l, r);
        if (temp.first == 0 && temp.second == 0)
        {
            ans++;
        }
        // cout << temp.first << temp.second << endl;
    }
    cout << ans;
}