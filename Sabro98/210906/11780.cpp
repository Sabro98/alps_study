#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> P;

const int INF = 0x3f3f3f3f;
int N, M, dist[101][101], nextNode[101][101];
vector<P> G[101];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 0, u, v, w; i < M; i++)
    {
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
    }

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            dist[i][j] = INF;
        }
    }

    for (int i = 1; i <= N; i++)
        dist[i][i] = 0;

    for (int i = 1; i <= N; i++)
    {
        for (P g : G[i])
        {
            if (dist[i][g.first] > g.second)
            {
                dist[i][g.first] = g.second;
                nextNode[i][g.first] = g.first;
            }
        }
    }

    for (int k = 1; k <= N; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nextNode[i][j] = nextNode[i][k];
                }
            }
        }
    }

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cout << (dist[i][j] == INF ? 0 : dist[i][j]) << ' ';
        }
        cout << '\n';
    }

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            queue<int> q;
            q.push(i);
            if (i == j)
                cout << 0 << '\n';
            else
            {
                int next = nextNode[i][j];
                while (next != 0)
                {
                    q.push(next);
                    next = nextNode[next][j];
                }
                if (q.size() == 1)
                {
                    cout << 0 << '\n';
                }
                else
                {
                    cout << q.size() << ' ';
                    while (!q.empty())
                    {
                        cout << q.front() << ' ';
                        q.pop();
                    }
                    cout << '\n';
                }
            }
        }
    }

    return 0;
}