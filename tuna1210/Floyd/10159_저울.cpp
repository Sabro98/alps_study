#include <iostream>
using namespace std;

#define INF 1e9

int dist[101][101];
int n, m;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if(i != j) dist[i][j] = INF;
            else dist[i][j] = 0;
        }
    }

    int a, b;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        dist[a][b] = 1;
    }
    
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    
    int cnt;
    for (int i = 1; i <= n; i++)
    {
        cnt = 0;
        for (int j = 1; j <= n; j++)
        {
            if(dist[i][j] == INF && dist[j][i] == INF) cnt++;
        }
        cout << cnt << "\n";
    }
}