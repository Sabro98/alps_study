#include <iostream>
#include <vector>
using namespace std;

#define INF 1e9

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int floyd[401][401];
    int n, m, s;
    
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            floyd[i][j] = (i == j? 0 : INF);
        }
    }

    int a, b;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        floyd[a][b] = 1;
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

    cin >> s;
    for (int i = 0; i < s; i++)
    {
        cin >> a >> b;
        if(floyd[a][b] == INF && floyd[b][a] == INF) cout << 0 << "\n";
        else
        {
            if(floyd[a][b] != INF) cout << -1 << "\n";
            else cout << 1 << "\n";
        }
    }
}