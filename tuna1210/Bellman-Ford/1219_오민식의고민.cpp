#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define INF 1e14

vector<pair<int, int>> G[101];
int cost[101];
bool visited[101];
bool tvisited[101];
long long money[101];
long long dist[101];
int n, s, d, m;

// s -> negative 경로 있는지 확인용
void dfs(int u)
{
    for(const auto& next : G[u])
    {
        if(!visited[next.second])
        {
            visited[next.second] = true;
            dfs(next.second);
        }
    }
}

// negative cycle -> d 경로 있는지 확인용
void fdfs(int u)
{
    for(const auto& next : G[u])
    {
        if(!tvisited[next.second])
        {
            tvisited[next.second] = true;
            fdfs(next.second);
        }
    }
}

void bellmanFord()
{
    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[s] = cost[s];
    money[s] = cost[s];
    visited[s] = true;

    int update = n - 1;
    while(update--)
    {
        for (int i = 0; i < n; i++)
        {
            for(const auto& next : G[i])
            {
                if(dist[next.second] > dist[i] + next.first - cost[next.second])
                {
                    dist[next.second] = dist[i] + next.first - cost[next.second];
                    money[next.second] = money[i] - next.first + cost[next.second];
                }
            }
        }
    }

    dfs(s);
    if(!visited[d])
    {
        cout << "gg\n";
        return;
    }

    for (int i = 0; i < n; i++)
    {
        for(const auto& next : G[i])
        {
            if(dist[next.second] > dist[i] + next.first - cost[next.second] && visited[next.second])
            {
                memset(tvisited, false, sizeof(tvisited));
                fdfs(next.second);
                if(tvisited[d])
                {
                    cout << "Gee\n";
                    return;
                }
            }
        }
    }

    cout << money[d] << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    memset(visited, false, sizeof(visited));
    
    cin >> n >> s >> d >> m;
    int a, b, c;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        G[a].push_back({c, b});
    }
    for (int i = 0; i < n; i++)
    {
        cin >> cost[i];
    }
    
    bellmanFord();
}