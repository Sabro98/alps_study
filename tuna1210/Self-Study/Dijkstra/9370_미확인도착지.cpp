#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

#define INF 1e9;

int n, m, t;
int s, g, h;
int stodDist[2001];
int nextDist[2001];

void stodDijkstra(vector<pair<int, int>> G[], int start)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    for (int i = 1; i <= n; i++)
    {
        stodDist[i] = INF;
    }
    stodDist[start] = 0;

    while(!pq.empty())
    {
        pair<int, int> cur = pq.top();
        pq.pop();

        int curCost = cur.first, curNode = cur.second;

        for(const auto& next : G[curNode])
        {
            int nextCost = next.first, nextNode = next.second;
            if(stodDist[nextNode] > stodDist[curNode] + nextCost)
            {
                stodDist[nextNode] = stodDist[curNode] + nextCost;
                pq.push({stodDist[nextNode], nextNode});
            }
        }
    }
}

void nextDijkstra(vector<pair<int, int>> G[], int start)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    for (int i = 1; i <= n; i++)
    {
        nextDist[i] = INF;
    }
    nextDist[start] = 0;

    while(!pq.empty())
    {
        pair<int, int> cur = pq.top();
        pq.pop();

        int curCost = cur.first, curNode = cur.second;

        for(const auto& next : G[curNode])
        {
            int nextCost = next.first, nextNode = next.second;
            if(nextDist[nextNode] > nextDist[curNode] + nextCost)
            {
                nextDist[nextNode] = nextDist[curNode] + nextCost;
                pq.push({nextDist[nextNode], nextNode});
            }
        }
    }
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
        cin >> n >> m >> t;
        vector<pair<int, int>> G[n + 1];
        vector<int> candidate(t);

        cin >> s >> g >> h;

        int a, b, d, must;
        for (int i = 0; i < m; i++)
        {
            cin >> a >> b >> d;
            G[a].push_back({d, b});
            G[b].push_back({d, a});
            if((a == g && b == h) || (a == h && b == g))
            {
                must = d;
            }
        }

        for(auto& cand : candidate)
        {
            cin >> cand;
        }
        sort(candidate.begin(), candidate.end());
        
        stodDijkstra(G, s);

        if(stodDist[g] < stodDist[h])
        {
            nextDijkstra(G, h);

            int prev = stodDist[g] + must;
            for(const auto& dest : candidate)
            {
                if(prev + nextDist[dest] <= stodDist[dest]) cout << dest << " ";
            }
        }
        else
        {
            nextDijkstra(G, g);

            int prev = stodDist[h] + must;
            for(const auto& dest : candidate)
            {
                if(prev + nextDist[dest] <= stodDist[dest]) cout << dest << " ";
            }
        }        
        cout << "\n";
    }

}