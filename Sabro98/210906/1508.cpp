#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

typedef pair<int, int> P;

int N, dist[21][21], floyd[21][21];
bool edge[21][21];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cin >> dist[i][j];
            floyd[i][j] = dist[i][j];
        }
    }

    memset(edge, true, sizeof(edge));
    for (int i = 1; i <= N; i++)
        edge[i][i] = false;
    for (int k = 1; k <= N; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                if (!edge[i][k] || !edge[k][j] || !edge[i][j])
                    continue;
                if (dist[i][j] == dist[i][k] + dist[k][j])
                    edge[i][j] = false;
                floyd[i][j] = min(floyd[i][j], floyd[i][k] + floyd[k][j]);
            }
        }
    }

    bool flag = false;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            flag |= dist[i][j] != floyd[i][j];
        }
    }

    if (flag)
    {
        cout << -1;
        return 0;
    }

    int ans = 0;

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (edge[i][j])
            {
                ans += dist[i][j];
            }
        }
    }

    cout << ans / 2;

    return 0;
}