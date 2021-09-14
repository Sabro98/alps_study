#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;
typedef pair<int, int> P;

const int INF = 0x3f3f3f3f;
int N, M, Q, cost[501];
P dist[501][501];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    for (auto &i : dist)
    {
        for (auto &j : i)
        {
            j.first = INF;
        }
    }

    cin >> N >> M >> Q;
    for (int i = 1; i <= N; i++)
        cin >> cost[i];
    for (int i = 0, u, v, w; i < M; i++)
    {
        cin >> u >> v >> w;
        dist[u][v].first = min(dist[u][v].first, w);
        dist[u][v].second = max(dist[u][v].second, max(cost[u], cost[v]));
        dist[v][u].first = min(dist[v][u].first, w);
        dist[v][u].second = max(dist[v][u].second, max(cost[u], cost[v]));
    }

    vector<int> order;
    for (int i = 1; i <= N; i++)
        order.push_back(i);
    sort(order.begin(), order.end(), [](int first, int second) -> bool
         { return cost[first] < cost[second]; });

    for (int k : order)
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                int tmp = dist[i][k].first + dist[k][j].first + max(dist[i][k].second, dist[k][j].second);
                if (dist[i][j].first + dist[i][j].second > tmp)
                {
                    dist[i][j].first = dist[i][k].first + dist[k][j].first;
                    dist[i][j].second = max(dist[i][k].second, dist[k][j].second);
                }
            }
        }
    }

    while (Q--)
    {
        int S, D;
        cin >> S >> D;
        int val = dist[S][D].first + dist[S][D].second;
        cout << (val == INF ? -1 : val) << '\n';
    }

    return 0;
}