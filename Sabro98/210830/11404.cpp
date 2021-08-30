#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;
typedef pair<int, int> P;
typedef long long ll;

const int INF = 0x3f3f3f3f;
int N, M, dist[101][101];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            dist[i][j] = INF;
        }
    }
    for (int i = 1; i <= N; i++)
        dist[i][i] = 0;

    for (int i = 0, u, v, w; i < M; i++)
    {
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
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

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (dist[i][j] == INF)
                cout << 0 << ' ';
            else
                cout << dist[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}
