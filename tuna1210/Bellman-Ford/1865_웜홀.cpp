#include <iostream>
#include <vector>
using namespace std;

#define INF 1e9

vector<pair<int, int>> G[501];
int dist[501];
int n, m, w;

bool bellmanford()
{
    for (int i = 1; i <= n; i++) dist[i] = INF;
    
    for (int tc = 0; tc < n - 1; tc++)
    {
        for (int i = 1; i <= n; i++)
        {
            for(const auto& next : G[i])
            {
                if(dist[next.second] > dist[i] + next.first)
                {
                    dist[next.second] = dist[i] + next.first;
                }
            }
        }
    }
    
    for (int i = 1; i <= n; i++)
    {
        if(dist[i] != INF)
        {
            for(const auto& next : G[i])
            {
                if(dist[next.second] > dist[i] + next.first)
                {
                    return true;
                }
            }
        }
    }
    return false;
}


int main()
{
    int tc, s, e, t;

    cin >> tc;
    for (int tk = 0; tk < tc; tk++)
    {
        cin >> n >> m >> w;
        for (int i = 0; i < m; i++)
        {
            cin >> s >> e >> t;
            G[s].push_back({t, e});
            G[e].push_back({t, s});
        }
        for (int i = 0; i < w; i++)
        {
            cin >> s >> e >> t;
            G[s].push_back({(-1) * t, e});
        }

        if(bellmanford()) cout << "YES\n";
        else cout << "NO\n";

        for (int i = 1; i <= n; i++)
        {
            G[i].clear();
        }
    }

}