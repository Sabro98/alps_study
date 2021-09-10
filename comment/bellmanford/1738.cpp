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
//골목길
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X first
#define Y second
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 101
#define INF 0x7FFFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
typedef pair<int, lli> pili;
typedef pair<lli, lli> plli;
int N, M, T, K, W, S;

vector<pili> G[MAXSIZE];
vector<lli> dist(MAXSIZE, INF);
vector<int> previous(MAXSIZE, 0);
bool Bellman_Ford(int src)
{
    dist[src] = 0;

    int update = N - 1;

    //update
    while (update--)
    {
        for (int i = 1; i <= N; i++)
        {
            if (dist[i] != INF)
            {
                for (const auto &g : G[i])
                {
                    if (dist[g.first] > dist[i] + g.second)
                    {
                        dist[g.first] = dist[i] + g.second;
                        previous[g.first] = i;
                    }
                }
            }
        }
    }

    //check negative cycle
    for (int i = 1; i <= N; i++)
    {
        if (dist[i] != INF)
        {
            for (const auto &g : G[i])
            {
                if (dist[g.first] > dist[i] + g.second)
                {
                    return true;
                }
            }
        }
    }

    return false;
}
bool bfs()
{
    vector<bool> visited(MAXSIZE, false);
    deque<int> Q;
    for (int i = 0; i < N; i++)
    {
        if (dist[i] != INF)
        {
            for (const auto &g : G[i])
            {
                if (dist[g.first] > dist[i] + g.second)
                {
                    if (!visited[i])
                    {
                        Q.push_back(i);
                        visited[i] = true;
                    }
                }
            }
        }
    }
    while (!Q.empty())
    {
        int cur = Q.front();
        Q.pop_front();
        for (auto i : G[cur])
        {
            if (!visited[i.first])
            {
                Q.push_back(i.first);
                visited[i.first] = true;
            }
        }
    }
    return visited[N];
}
int main()
{
    fastio;

    cin >> N >> M;
    int u, v;
    lli w;
    ffor(i, M)
    {
        cin >> u >> v >> w;
        G[u].push_back({v, -w});
    }

    bool hasnega = Bellman_Ford(1);
    if (dist[N] == INF)
    {
        cout << -1;
        exit(0);
    }
    else if (hasnega)
    {
        if (bfs())
        {
            cout << -1;
            exit(0);
        }
    }
    int parent = N;
    deque<int> stack;
    stack.push_back(N);
    while (parent != 1)
    {
        parent = previous[parent];
        stack.push_back(parent);
    }
    while (!stack.empty())
    {
        cout << stack.back() << " ";
        stack.pop_back();
    }
}