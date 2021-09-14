#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INF 1e9

priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
int n;
int answer[21][21];
int floyd[21][21];

void runFloyd()
{
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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;
    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> answer[i][j];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            pq.push({answer[i][j], {i, j}});
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            floyd[i][j] = (i == j? 0 : INF);
        }
    }

    int sum = 0;
    while(!pq.empty())
    {
        pair<int, pair<int, int>> cur = pq.top();
        pq.pop();

        int cost = cur.first;
        int x = cur.second.first, y = cur.second.second;
        if(floyd[x][y] <= cost) continue;
        
        sum += cost;

        floyd[x][y] = cost;
        floyd[y][x] = cost;

        runFloyd();
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if(answer[i][j] != floyd[i][j]) 
            {
                cout << -1 << "\n";
                return 0;
            }
        }
    }

    cout << sum << "\n";
}