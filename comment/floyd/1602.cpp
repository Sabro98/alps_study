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
//도망자원숭이
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 501
#define INF 0x7FFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K, S, Q;
//const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

vector<vector<int>> dist(MAXSIZE, vector<int>(MAXSIZE, INF));
vector<int> extraTime(MAXSIZE);                                      //노드별 원숭이가 괴롭혀서발생하는 추가시간
vector<vector<int>> pathExtraTime(MAXSIZE, vector<int>(MAXSIZE, 0)); //pathExtraTime[i][j] == i>j경로를 이루는 노드들의 extraTime중 최대값
vector<pii> G[MAXSIZE];

/*
1.경로(dist)의 비용을 계산할때 경로중 노드의 비용(extraTime)의 최댓값(pathExtraTime)을 저장한다
2.비교할때는 둘을 합친 값을 비교하지만 갱신할때는 둘을 따로 갱신해야함
*/
void floyd()
{
    //1-pass
    for (int i = 1; i <= N; i++)
    {
        for (auto g : G[i])
        {
            dist[i][g.first] = min(dist[i][g.first], g.second);
            pathExtraTime[i][g.first] = max(extraTime[i], extraTime[g.first]);
        }
    }
    for (int i = 1; i <= N; i++)
    {
        dist[i][i] = 0;
        pathExtraTime[i][i] = extraTime[i];
    }

    //n-pass if {i -> k -> j} < {i -> j}, update
    for (int k = 1; k <= N; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                if (dist[i][j] + pathExtraTime[i][j] > dist[i][k] + dist[k][j] + max(pathExtraTime[i][k], pathExtraTime[k][j]))
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pathExtraTime[i][j] = max(pathExtraTime[i][k], pathExtraTime[k][j]);
                }
            }
        }
    }
}
int main()
{
    fastio;
    int u, v, w;

    cin >> N >> M >> Q;
    f1for(i, N)
    {
        cin >> extraTime[i];
    }
    ffor(i, M)
    {
        cin >> u >> v >> w;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    floyd();
    // f1for(i, N)//debug
    // {
    //     f1for(j, N)
    //     {
    //         if (dist[i][j] != INF)
    //         {
    //             cout << dist[i][j] << " ";
    //         }
    //         else
    //         {
    //             cout << "? ";
    //         }
    //     }
    //     cout << endl;
    // }
    ffor(i, Q)
    {
        cin >> S >> T;
        if (dist[S][T] != INF)
        {
            cout << dist[S][T] << " " << pathExtraTime[S][T];
            // cout << dist[S][T] + pathExtraTime[S][T];
        }
        else
        {
            cout << -1;
        }
        cout << endl;
    }
}