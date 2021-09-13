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
//ignition
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 201
#define INF 0x7FFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K;
//const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

vector<vector<int>> dist(MAXSIZE, vector<int>(MAXSIZE, INF));
vector<vector<int>> distMAX(MAXSIZE, vector<int>(MAXSIZE, -1)); //직접 연결된 간선중 최대 간선길이 저장

vector<pii> G[MAXSIZE];
void floyd()
{
    //1-pass
    for (int i = 1; i <= N; i++)
    {
        for (auto g : G[i])
        {
            dist[i][g.first] = min(dist[i][g.first], g.second);
            distMAX[i][g.first] = max(distMAX[i][g.first], g.second);
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
                }
            }
        }
    }
}

int main()
{
    fastio;
    int u, v;
    int w;
    cin >> N >> M;
    ffor(i, M)
    {
        cin >> u >> v >> w;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    floyd();

    //cout << "===============\n";
    // for (int i = 1; i <= N; i++) //debug
    // {
    //     for (int j = 1; j <= N; j++)
    //     {
    //         if (dist[i][j] == INF)
    //             cout << "INF ";
    //         else
    //             cout << dist[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "===============\n";
    // for (int i = 1; i <= N; i++) //debug
    // {
    //     for (int j = 1; j <= N; j++)
    //     {
    //         if (dist[i][j] == -1)
    //             cout << "N ";
    //         else
    //             cout << distMAX[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    double answer = 1E+300; //아무튼 존나큰 double값
    //k에 불을 붙였을때 i노드에서j노드사이의 간선중 가장 마지막에 타는 간선의 시간을 구한다.
    for (int k = 1; k <= N; k++) //불 붙이는 곳
    {
        double maxtime = 0; //마지막 간선이 타기까지의시간
        for (int i = 1; i <= N; i++)
        {
            maxtime = max(maxtime, (double)dist[k][i]); //혹시라도 중복된 간선이 없을경우 dist값이라도 저장
        }
        for (int i = 1; i <= N; i++) //]dist[k][i] == k에 불을 붙였을때 i에서 불이 시작할때까지의 시간
        {
            for (int j = 1; j <= N; j++) //distMAX[i][j] i에서 j로 연결된 간선중 가장 긴 간선
            {
                if (dist[k][i] + distMAX[i][j] > dist[k][j])
                {
                    double extra = ((double)dist[k][i] + distMAX[i][j] - dist[k][j]) / 2;
                    maxtime = max(maxtime, extra + dist[k][j]);
                }
            }
        }
        answer = min(answer, maxtime);
    }

    cout << fixed;
    cout.precision(1);
    cout << answer;
}