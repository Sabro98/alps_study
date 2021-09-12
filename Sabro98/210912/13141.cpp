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
int N, M;
vector<pair<P, int>> edges;
int dist[201][201];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed;
    cout.precision(1);

    for (int i = 0; i < 201; i++)
    {
        for (int j = 0; j < 201; j++)
        {
            dist[i][j] = (i == j ? 0 : INF);
        }
    }

    cin >> N >> M;
    for (int i = 0, u, v, w; i < M; i++)
    {
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
        edges.push_back({{u, v}, w});
        edges.push_back({{v, u}, w});
    }

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

    double ans = INF;

    for (int k = 1; k <= N; k++)
    { //try ignition
        double tmp = 0;
        for (auto edge : edges)
        {
            int t1 = dist[k][edge.first.first], t2 = dist[k][edge.first.second], c = edge.second;
            if (t1 + c <= t2)
                tmp = max(tmp, (double)t1 + c);
            else
                tmp = max(tmp, t2 + ((c - (t2 - t1)) / 2.));
        }
        ans = min(ans, tmp);
    }

    cout << ans;

    return 0;
}