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
//세금
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 1001
#define INF 0x7FFFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
typedef pair<int, lli> pili;
typedef pair<lli, lli> plli;
int N, M, T, K, S, D;
//const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

vector<pili> G[MAXSIZE];
// vector<int> previous(MAXSIZE);
vector<vector<lli>> dist(MAXSIZE, vector<lli>(MAXSIZE, INF)); //[N][i] n번정점에 i개의 간선을 거쳐 도착하는 최단거리
vector<int> pathlength(MAXSIZE, -1);                          //최소비용일때의 간선갯수
vector<lli> mindist(MAXSIZE, INF);                            //최소비용만저장

int maxsize = 0;
struct node
{
    int at, k;
    lli w;
    node(int _at, lli _w, int _k)
    {
        at = _at;
        w = _w;
        k = _k;
    }
    bool operator<(const node &rhs) const { return w > rhs.w; }
};

void dijkstra(int starting)
{
    // priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    priority_queue<node> pq;
    mindist[starting] = 0;
    dist[starting][0] = 0;
    pq.push({starting, dist[starting][0], 0});
    pathlength[starting] = 0;
    while (!pq.empty())
    {

        lli ccost = pq.top().w;
        int cindex = pq.top().at;
        int nodeCount = pq.top().k;
        pq.pop();

        if (dist[cindex][nodeCount] < ccost)
            continue;

        for (auto next : G[cindex])
        {
            int ncost = next.second;
            int nindex = next.first;

            if (mindist[nindex] > ccost + ncost)
            { //그냥 최소비용을 구하는 다익스트라
                mindist[nindex] = ccost + ncost;
                dist[nindex][nodeCount + 1] = ccost + ncost;
                pathlength[nindex] = nodeCount + 1;
                pq.push({nindex, mindist[nindex], nodeCount + 1});
            }
            else if (pathlength[nindex] > nodeCount + 1 && dist[nindex][nodeCount + 1] > ccost + ncost)
            { //코스트는 높지만 간선갯수가 적은 경로일때
                dist[nindex][nodeCount + 1] = ccost + ncost;
                pq.push({nindex, dist[nindex][nodeCount + 1], nodeCount + 1});
            }
        }
    }
}
int main()
{
    fastio;
    cin >> N >> M >> K;
    cin >> S >> D;
    int u, v;
    lli w;

    ffor(i, M)
    {
        cin >> u >> v >> w;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }

    dijkstra(S);

    int maxCount = -1;
    int thatCount;
    f1for(i, N)
    {
        if (mindist[D] == dist[D][i])
        {
            maxCount = i;
            break;
        }
    }
    cout << mindist[D] << endl;

    ffor(i, K)
    {
        int tax;
        cin >> tax;
        int minCost = INF;
        f1for(count, maxCount)
        {
            if (dist[D][count] != INF)
            {
                dist[D][count] = tax * count + dist[D][count];
                if (minCost > dist[D][count])
                {
                    minCost = dist[D][count];
                    thatCount = count;
                }
            }
        }
        maxCount = thatCount; //현재 최소비용경로가 간선n개를 거쳐서 왔다면 다음세금을 올릴때 n이하의 경로를 거쳐야함
        cout << minCost << endl;
    }
}