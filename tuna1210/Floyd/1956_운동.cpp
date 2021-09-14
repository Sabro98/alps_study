#include <iostream>
#include <vector>
using namespace std;

#define INF 1e9

int n, m;
vector<pair<int, int>> G[401];
int floyd[401][401];

void initFloyd()
{
    for (int i = 1; i <= n; i++)
    {
        for(const auto& next : G[i])
        {
            floyd[i][next.first] = min(floyd[i][next.first], next.second);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        floyd[i][i] = 0;
    }

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                floyd[i][j] = min(floyd[i][j], floyd[i][k] + floyd[k][j]);
            }
        }
    }
}

int findCycle()
{
    int ans = INF;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if(i == j || floyd[i][j] == INF || floyd[i][j] == INF) continue;
            ans = min(ans, floyd[i][j] + floyd[j][i]);
        }
    }
    
    return (ans == INF ? -1 : ans);
}

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
            floyd[i][j] = INF;
        }
    }
    
    int u, v, w;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        G[u].push_back({v, w});
    }

    initFloyd();
    
    cout << findCycle() << "\n";
}