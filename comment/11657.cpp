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
//타임머신
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X first
#define Y second
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 501
#define INF 0x7FFFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
typedef pair<lli, lli> plli;
int N, M, T, K;
//const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

vector<pii> G[MAXSIZE];
// vector<int> previous(MAXSIZE);
vector<lli> Bellman_Ford(int src)
{
    vector<lli> dist(N, INF);
    dist[src] = 0;

    int update = N - 1;

    //update
    while (update--)
    {
        for (int i = 0; i < N; i++)
        {
            if (dist[i] != INF)
            {
                for (const auto &g : G[i])
                {
                    if (dist[g.first] > dist[i] + g.second)
                    {
                        dist[g.first] = dist[i] + g.second;
                        // previous[g.first] = i;
                    }
                }
            }
        }
    }

    //check negative cycle
    for (int i = 0; i < N; i++)
    {
        if (dist[i] != INF)
        {
            for (const auto &g : G[i])
            {
                if (dist[g.first] > dist[i] + g.second)
                {
                    dist[g.first] > dist[i] + g.second;
                    cout << "-1";
                    exit(0);
                }
            }
        }
    }

    return dist;
}
int main()
{
    fastio;

    cin >> N >> M;

    int u, v, w;

    ffor(i, M)
    {
        cin >> u >> v >> w;
        u--;
        v--;
        G[u].push_back({v, w});
    }

    auto answer = Bellman_Ford(0);
    f1for(i, N - 1)
    {
        if (answer[i] == INF)
            cout << -1 << endl;
        else
            cout << answer[i] << endl;
    }
}