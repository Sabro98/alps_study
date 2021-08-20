#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef pair<int, int> P;

const int INF = 0x3f3f3f3f;

int N, M;
vector<P> G[501];

void solve(int src){
    vector<long long> dist(501, INF);
    dist[src]  = 0;
    
    int count = N - 1;
    while(count--){
        for(int i=1; i<=N; i++){
            if(dist[i] == INF) continue;
            for(P g : G[i]){
                int next = g.first, weight = g.second;
                dist[next] = min(dist[next], dist[i] + weight);
            }
        }
    }

    for(int i=1; i<=N; i++){
        if(dist[i] == INF) continue;
        for(P g : G[i]){
            int next = g.first, weight = g.second;
            if(dist[next] > dist[i] + weight){
                cout << -1;
                return;
            }
        }
    }

    for(int i=2; i<=N; i++){
        cout << (dist[i] == INF ? -1 : dist[i]) << '\n';
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for(int i=0, u, v, w; i<M; i++){
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
    }

    solve(1);

    return 0;
}