#include <iostream>
#include <queue>
using namespace std;

#define INF 1e9

int n, m;
int map[101][101];
int nextNode[101][101];

void printPath(int s, int d)
{
    queue<int> q;
    q.push(s);
    int daum = nextNode[s][d];
    while(daum != 0)
    {
        q.push(daum);
        daum = nextNode[daum][d];
    }
    if(q.size() == 1)
    {
        cout << 0 << "\n";
        return;
    }
    cout << q.size() << " ";
    while(!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << "\n";
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
                    nextNode[i][j] = nextNode[i][k];
                }
            }
        }
    }
    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << (map[i][j] == INF ? 0 : map[i][j]) << " ";
        }
        cout << "\n";
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printPath(i, j);
        }
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
            nextNode[i][j] = 0;
        }
    }

    int u, v, w;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        map[u][v] = min(map[u][v], w);
        nextNode[u][v] = v;
    }
    
    floyd();
}