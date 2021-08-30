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
//키 순서
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 501
#define INF 0x7FFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K;
//const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

vector<vector<int>> dist(MAXSIZE, vector<int>(MAXSIZE, INF));

vector<pii> G[MAXSIZE];
void floyd()
{
    //1-pass
    for (int i = 1; i <= N; i++)
    {
        for (auto g : G[i])
        {
            dist[i][g.first] = min(dist[i][g.first], g.second);
        }
    }
    for (int i = 1; i <= N; i++)
        dist[i][i] = 0;

    //n-pass if {i -> k -> j} < {i -> j}, update
    for (int k = 1; k <= N; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}
//자기자신까지 올수있는정점과 자기자신으로부터 갈수있는 정점을 합친게 N개일때
int main()
{
    fastio;
    int u, v, w;
    cin >> N >> M;
    ffor(i, M)
    {
        cin >> u >> v;
        G[u].push_back({v, 1});
    }
    floyd();

    for (int i = 1; i <= N; i++)
    {
        for (int j = i + 1; j <= N; j++)
        {
            if (dist[i][j] != INF)
            {
                dist[j][i] = 1;
            }
            else if (dist[j][i] != INF)
            {
                dist[i][j] = 1;
            }
        }
    }
    int ans = 0;
    f1for(i, N)
    {
        int count = 0;
        f1for(j, N)
        {
            if (dist[i][j] != INF)
            {
                count++;
            }
        }
        if (count == N)
        {
            ans++;
        }
    }
    cout << ans;
}