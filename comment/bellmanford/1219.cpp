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
//오민식의 고민
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
typedef pair<lli, lli> plli;
int N, M, T, K, W, S;
//const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

vector<pii> G[MAXSIZE];
// vector<int> previous(MAXSIZE);
vector<lli> cost(MAXSIZE);
bool hasNegativeCycle = false;
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
                    hasNegativeCycle = true;
                }
            }
        }
    }

    return dist;
}

int main()
{
    fastio;

    cin >> N >> S >> T >> M;

    tuple<int, int, lli> tempG[MAXSIZE];

    int u, v;
    lli w;
    ffor(i, M)
    {
        cin >> u >> v >> w;
        tempG[i] = {u, v, w};
    }

    ffor(i, N)
    {
        cin >> cost[i];
    }
    ffor(i, M)
    {
        G[get<0>(tempG[i])].push_back({get<1>(tempG[i]), get<2>(tempG[i]) - cost[get<1>(tempG[i])]});
        //u->v의 w를 cost[v]의 값만큼 감소시킨 값으로 그래프만들기
    }
    auto answerCost = Bellman_Ford(S);

    if (answerCost[T] == INF)
    {
        cout << "gg";
        exit(0);
    }
    else if (hasNegativeCycle)
    { //음의사이클이 T로가는 길에 존재하는지 확인

        vector<bool> visited(N, false);
        deque<int> Q;
        for (int i = 0; i < N; i++)
        {
            if (answerCost[i] != INF)
            {
                for (const auto &g : G[i])
                {
                    if (answerCost[g.first] > answerCost[i] + g.second)
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

        if (visited[T] == true)
        {
            cout << "Gee";
            exit(0);
        }
    }
    cout << -answerCost[T] + cost[S];
}