#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

#define INF 1e14

priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, greater<pair<long long, pair<int, int>>>> pq;
vector<pair<long long, int>> G[1001];
long long dist[1001][1001];
vector<int> tax;
int n, m, k, s, d;

void dijk()
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            dist[i][j] = INF;
        }
    }
    dist[s][0] = 0;
    pq.push({0, {s, 0}});

    pair<long long, pair<int, int>> cur;
    long long nextMove, curMove, curCost, nextCost;
    int curInd, nextInd, qSize;
    while(!pq.empty())
    {
        cur = pq.top();
        pq.pop();

        curCost = cur.first; curInd = cur.second.first; curMove = cur.second.second;

        if(curCost > dist[curInd][curMove]) continue;

        for(const auto& next : G[curInd])
        {
            nextCost = next.first;
            nextInd = next.second;
            nextMove = curMove + 1;
            if(nextMove == 1000) continue;
            if(dist[nextInd][nextMove] > curCost + nextCost)
            {
                dist[nextInd][nextMove] = curCost + nextCost;
                pq.push({dist[nextInd][nextMove], {nextInd, nextMove}});
            }
        }
    }

    long long min = INF;
    for (int i = 0; i <= n; i++)
    {
        if(dist[d][i] == INF) continue;
        if(min > dist[d][i]) min = dist[d][i];
    }
    cout << min << "\n";

    int tmp;
    for (const auto& curTax : tax)
    {
        min = INF;
        for (int i = 0; i <= n; i++)
        {
            if(dist[d][i] == INF) continue;
            tmp = curTax * i;
            if(min > dist[d][i] + tmp) min = dist[d][i] + tmp;
            dist[d][i] += tmp;
        }
        cout << min << "\n";
    }
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m >> k >> s >> d;

    int a, b, w, p;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> w;
        G[a].push_back({w, b});
        G[b].push_back({w, a});
    }

    for (int i = 0; i < k; i++)
    {
        cin >> p;
        tax.push_back(p);
    }

    dijk();
}