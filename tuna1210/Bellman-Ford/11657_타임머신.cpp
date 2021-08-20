#include <iostream>
#include <vector>
using namespace std;

#define INF 1e9

int n, m;
long long dist[501];
vector<pair<int, int>> G[501];

bool bf()
{
    for (int i = 2; i <= n; i++) dist[i] = INF;
    dist[1] = 0;

    bool cycle = false;

    for (int tc = 0; tc < n - 1; tc++)
    {
        for (int i = 1; i <= n; i++)
        {
            if(dist[i] != INF)
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m;
    int a, b, c;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        G[a].push_back({c, b});
    }

    if(bf()) cout << -1 << "\n";
    else
    {
        for (int i = 2; i <= n; i++)
        {
            cout << (dist[i] == INF ? -1 : dist[i])  << "\n";
        }
    }
}