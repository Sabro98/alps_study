#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

#define INF 1e9

vector<pair<int, int>> G[1001];
// 부모, {부모로부터의 cost, 부모 경로 길이}
map<int, pair<int, int>> parent[1001];
// cost, 그 cost의 경로 길이
pair<int, int> dist[1001];
set<pair<int, int>> path[1001];
vector<int> tax;
int n, m, k, s, d;

void bellmanFord()
{
    for (int i = 1; i <= n; i++) dist[i] = {INF, 0};
    dist[s] = {0, 0};

    for (int tc = 0; tc < n - 1; tc++)
    {
        for (int i = 1; i <= n; i++)
        {
            if(dist[i].first == INF) continue;
            for(const auto& next : G[i])
            {
                if(dist[next.second].first > dist[i].first + next.first)
                {
                    dist[next.second].first = dist[i].first + next.first;
                    dist[next.second].second = dist[i].second + 1;
                    parent[next.second][i] = {dist[i].first + next.first, dist[i].second + 1};
                }
                path[i].insert({dist[i].first + next.first, dist[i].second + 1});
            }
        }
    }
}

void increaseTax()
{
    bellmanFord();

    cout << "1번째\n";
    cout << dist[d].first << "\n";

    int curTax = 0;
    for (int i = 0; i < k; i++)
    {
        cout << i + 2 << "번째\n";
        cout << "tax : " << tax[i] << "\n";
        int min = INF;
        curTax += tax[i];

        for(const auto& iit : parent[d])
        {
            cout << "cur : " << iit.first << "\n";
            for(const auto& iter : iit.second)
            {
                cout << iter.first << " " << iter.second << "\n";
                if(min > iter.first + iter.second * curTax)
                {
                    min = iter.first + iter.second * curTax;
                    cout << "min is Updated to " << min << "\n"; 
                }
            }
        }
        
        cout << "min : " << min << "\n";
        cout << "--------------------------------------\n";
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
    
    increaseTax();
}