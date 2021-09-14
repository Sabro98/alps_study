#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

#define INF 1e9

int n, m;
int map[101][101];
bool visited[101];
vector<vector<int>> connectedComponent;

int initConnectedComponent()
{
    memset(visited, false, sizeof(visited));

    for (int i = 1; i <= n; i++)
    {
        if(visited[i]) continue;
        vector<int> tmp;
        tmp.push_back(i);
        for (int j = 1; j <= n; j++)
        {
            if(i == j || map[i][j] == INF) continue;
            visited[j] = true;
            tmp.push_back(j);
        }
        connectedComponent.push_back(tmp);
    }
    
    return connectedComponent.size();
}

int getMax(int s)
{
    int ret = 0;
    for (int i = 1; i <= n; i++)
    {
        if(s == i || map[s][i] == INF) continue;
        ret = max(ret, map[s][i]);
    }
    return ret;
}

void floyd()
{
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if(map[i][j] > map[i][k] + map[k][j])
                {
                    map[i][j] = map[i][k] + map[k][j];
                }
            }
        }
    }

    cout << initConnectedComponent() << "\n";

    vector<int> ans;
    for(const auto& cc : connectedComponent)
    {
        int min = INF, minInd = cc.front(), tmp;
        for(const auto& it : cc)
        {
            tmp = getMax(it);
            if(min > tmp)
            {
                min = tmp;
                minInd = it;
            }
        }
        ans.push_back(minInd);
    }

    sort(ans.begin(), ans.end());
    for(const auto& i : ans)
    {
        cout << i << "\n";
    }
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
            map[i][j] = (i == j ? 0 : INF);
        }
    }

    int u, v, w;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        map[u][v] = 1;
        map[v][u] = 1;
    }
    
    floyd();
}