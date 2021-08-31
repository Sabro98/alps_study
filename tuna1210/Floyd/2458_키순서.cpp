#include <iostream>
#include <vector>
using namespace std;

#define INF 1e9

int n, m;
vector<pair<int, int>> G[501];
int floyd[501][501];

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

int findStudent()
{
    int ans = 0;
    bool right = true;
    for (int i = 1; i <= n; i++)
    {
        right = true;
        for (int j = 1; j <= n; j++)
        {
            if(i == j) continue;
            if((floyd[i][j] == 0 || floyd[i][j] == INF) && (floyd[j][i] == 0 || floyd[j][i] == INF))
            {
                right = false;
                break;
            }
        }
        if(right) ans++;
    }
    
    return ans;
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
        cin >> u >> v;
        G[u].push_back({v, 1});
    }

    initFloyd();
    
    cout << findStudent() << "\n";
}