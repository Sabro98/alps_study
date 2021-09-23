#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int choice[100001];
bool team[100001];
bool visited[100001];

void dfs(int u, vector<int>& path, int start)
{
    if(visited[u])
    {
        auto pos = find(path.begin(), path.end(), u);
        for (;pos != path.end(); pos++)
        {
            team[*pos] = true;
        }
        return;
    }
    if(team[u]) return;
    visited[u] = true;
    path.push_back(u);
    dfs(choice[u], path, start);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int tc;
    cin >> tc;

    while(tc--)
    {
        int n;
        cin >> n;

        memset(team, false, sizeof(bool) * (n + 1));

        for (int i = 1; i <= n; i++)
        {
            cin >> choice[i];
        }
        
        memset(visited, false, sizeof(bool) * (n + 1));
        for (int i = 1; i <= n; i++)
        {
            if(team[i]) continue;

            vector<int> path;
            path.push_back(i);

            dfs(choice[i], path, i);
        }
        
        int cnt = 0;
        for (int i = 1; i <= n; i++)
        {
            if(!team[i]) cnt++;
        }
        
        cout << cnt << "\n";
    }
}