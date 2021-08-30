#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <cstring>

using namespace std;
typedef pair<int, int> P;
typedef long long ll;

const int dx[] = {0, 0, -1, 1}, dy[] = {-1, 1, 0, 0};
const ll INF = 1e16;
int N, M, A[31][31];
ll dist[31][31];
vector<pair<P, int>> G[31][31];

void solve() {
    int repeat = N * M - 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dist[i][j] = INF;
        }
    }

    dist[0][0] = 0;
    
    while (repeat--) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (dist[i][j] == INF) continue;
                if (P(i, j) == P(N - 1, M - 1)) continue;
                for (pair<P, int> g : G[i][j]) {
                    int nx = g.first.first, ny = g.first.second, w = g.second;
                    dist[nx][ny] = min(dist[nx][ny], dist[i][j] + w * 1l);
                }
            }
        }
    }

    bool flag = true;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (dist[i][j] == INF) continue;
            if (P(i, j) == P(N - 1, M - 1)) continue;
            for (pair<P, int> g : G[i][j]) {
                int nx = g.first.first, ny = g.first.second, w = g.second;
                flag &= (dist[nx][ny] <= dist[i][j] + w * 1l);
            }

        }
    }

    if (!flag) cout << "Never\n";
    else if (dist[N - 1][M - 1] == INF) cout << "Impossible\n";
    else cout << dist[N - 1][M - 1] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while (true) {
        cin >> N >> M;
        memset(A, 0, sizeof(A));
        int g, E, u, v, w, u2, v2;
        if (N == 0 && M == 0) break;
        cin >> g;
        while (g--) {
            cin >> u >> v;
            A[u][v] = -1;
        }
        cin >> E;
        while (E--) {
            cin >> u >> v >> u2 >> v2 >> w;
            G[u][v].push_back({{u2, v2}, w});
        }
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                if(!G[i][j].empty()) continue;
                if(P(i, j) == P(N-1, M-1)) continue;

                for(int k=0; k<4; k++){
                    int nx = i + dx[k], ny = j + dy[k];
                    if(!(0 <= nx && nx < N && 0 <= ny && ny < M)) continue;
                    if(A[nx][ny] == -1) continue;
                    G[i][j].push_back({{nx, ny}, 1});
                }
            }
        }

        solve();

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                G[i][j].clear();
            }
        }
        memset(A, 0, sizeof(A));
    }

    return 0;
}