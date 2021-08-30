#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;
typedef pair<int, int> P;
typedef long long ll;

const int INF = 0x3f3f3f3f;
int N, M, dist[401][401];

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

    int ans = INF;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            ans = min(ans, dist[i][j] + dist[j][i]);
        }
    }
    cout << (ans == INF ? -1 : ans);

    return 0;
}
