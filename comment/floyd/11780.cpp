#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <set>
#include <cmath>
#include <map>
#include <deque>
#include <limits.h>
#include <utility>
#include <list>
#include <unordered_map>
#include <string.h>
#include <random>
#include <queue>
//플로이드 2
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 101
#define INF 0x7FFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K;
//const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

vector<vector<int>> dist(MAXSIZE, vector<int>(MAXSIZE, INF));
vector<vector<int>> nextpath(MAXSIZE, vector<int>(MAXSIZE, 0));
vector<pii> G[MAXSIZE];
void floyd()
{
    //1-pass
    for (int i = 1; i <= N; i++)
    {
        for (auto g : G[i])
        {
            dist[i][g.first] = min(dist[i][g.first], g.second);
            nextpath[i][g.first] = g.first;
        }
    }
    for (int i = 1; i <= N; i++)
        dist[i][i] = 0;

    //n-pass if {i -> k -> j} < {i -> j}, update
    for (int k = 1; k <= N; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nextpath[i][j] = nextpath[i][k];
                }
            }
        }
    }
}
int main()
{
    fastio;
    int u, v, w;
    cin >> N >> M;
    ffor(i, M)
    {
        cin >> u >> v >> w;
        G[u].push_back({v, w});
    }
    floyd();

    f1for(i, N)
    {
        f1for(j, N)
        {
            if (dist[i][j] != INF)
            {
                cout << dist[i][j] << " ";
            }
            else
            {
                cout << 0 << " ";
            }
        }
        cout << endl;
    }

    f1for(start, N)
    {
        f1for(end, N)
        {
            queue<int> q;
            q.push(start);
            int nextS = nextpath[start][end];
            while (nextS != 0)
            {
                q.push(nextS);
                nextS = nextpath[nextS][end];
            }
            if (q.size() == 1)
            { // no path from start to end
                cout << 0 << endl;
            }
            else
            {
                cout << q.size() << ' ';
                while (!q.empty())
                {
                    cout << q.front() << ' ';
                    q.pop();
                }
                cout << endl;
            }
        }
    }
}