#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;
typedef pair<int, int> P;
typedef long long ll;

const ll INF = 1e16;
ll N, M, K, S, D, dist[1001][1000], inc[30000];
vector<P> G[1001];


void solve(){
    for(int i=0; i<1001; i++){
        for(int j=0; j<1000; j++){
            dist[i][j] = INF;
        }
    }

    priority_queue<pair<int, P>> pq;
    dist[S][0] = 0;
    pq.push({0, {S, 0}});

    while(!pq.empty()){
        int cost = -pq.top().first, curr = pq.top().second.first, count = pq.top().second.second;
        pq.pop();

        if(dist[curr][count] < cost) continue;

        for(auto g : G[curr]){
            int next = g.first, nextCost = cost + g.second, nextCount = count + 1;
            if(nextCount == 1000) continue;
            if(dist[next][nextCount] > nextCost){
                dist[next][nextCount] = nextCost;
                pq.push({-nextCost, {next, nextCount}});
            }
        }
    }

    for(int k=0; k<=K; k++){
        ll ans = INF;
        for(int i=1; i<1000; i++) {
            ans = min(ans, dist[D][i]);
            if(k < K && dist[D][i] != INF) dist[D][i] += 1l * inc[k] * i;
        }
        cout << ans << '\n';
    }

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> K;
    cin >> S >> D;
    for(int i=0, u, v, w; i<M; i++){
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    for(int i=0; i<K; i++) cin >> inc[i];

    solve();

    return 0;
}