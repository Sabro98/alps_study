#include <iostream>
#include <cstring>
#include <vector>
#include <deque>
using namespace std;

#define INF 1e14

vector<pair<int, int>> G[101];
int parent[101];
bool visited[101];
bool tvisited[101];
long long dist[101];
int n, m;

// s -> negative cycle 경로 있는지 확인용
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
    for (int i = 1; i <= n; i++) dist[i] = -1e14;
    dist[1] = 0;
    parent[1] = -1;
    visited[1] = true;

    int update = n - 1;
    while(update--)
    {
        for (int i = 1; i <= n; i++)
        {
            for(const auto& next : G[i])
            {
                if(dist[next.second] < dist[i] + next.first)
                {
                    dist[next.second] = dist[i] + next.first;
                    if(parent[next.second] != -1) parent[next.second] = i;
                }
            }
        }
    }

    dfs(1);
    if(!visited[n])
    {
        cout << "-1\n";
        return;
    }

    for (int i = 1; i <= n; i++)
    {
        for(const auto& next : G[i])
        {
            if(dist[next.second] < dist[i] + next.first && visited[next.second])
            {
                memset(tvisited, false, sizeof(tvisited));
                fdfs(next.second);
                if(tvisited[n])
                {
                    cout << "-1\n";
                    return;
                }
            }
        }
    }

    int it = n, cnt = m;
    deque<int> ans;
    while(parent[it] != -1)
    {
        ans.push_front(parent[it]);
        it = parent[it];
        cnt--;
        if(cnt == 0)
        {
            cout << "-1\n";
            return;
        }
    }
    ans.push_back(n);
    for(const auto& i : ans)
    {
        cout << i << " ";
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    memset(visited, false, sizeof(visited));
    
    cin >> n >> m;
    int a, b, c;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        G[a].push_back({c, b});
    }
    
    bellmanFord();
}