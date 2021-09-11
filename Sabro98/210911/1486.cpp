#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <cstring>

using namespace std;
typedef pair<int, int> P;
typedef long long ll;

const int dx[] = {0, 0, -1, 1}, dy[] = {-1, 1, 0, 0}, INF = 0x3f3f3f3f;
int N, M, T, D, dist[625][625];
char A[25][25];
unordered_map<char, int> dict;
vector<P> G[625];

int pos(int x, int y) {
    return x * M + y;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    for(char c = 'A'; c <= 'Z'; c++) dict[c] = c - 'A';
    for(char c = 'a'; c <= 'z'; c++) dict[c] = c - 'a' + 26;

    cin >> N >> M >> T >> D;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> A[i][j];
        }
    }

    for (int i = 0; i < 625; i++) {
        for (int j = 0; j < 625; j++) {
            dist[i][j] = (i == j ? 0 : INF);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < 4; k++) {
                int nx = i + dx[k], ny = j + dy[k];
                if (!(0 <= nx && nx < N && 0 <= ny && ny < M)) continue;
                if(abs(dict[A[i][j]] - dict[A[nx][ny]]) > T) continue;
                int diff = 1;
                if(A[i][j] < A[nx][ny]){
                    diff = dict[A[nx][ny]] - dict[A[i][j]];
                }
                int weight = (int) pow(diff, 2);
                G[pos(i, j)].emplace_back(pos(nx, ny), weight);
                int &d = dist[pos(i, j)][pos(nx, ny)];
                d = min(d, weight);
            }
        }
    }

    for (int k = 0; k < N * M; k++) {
        for (int i = 0; i < N * M; i++) {
            for (int j = 0; j < N * M; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    int ans = dict[A[0][0]];
    for (int i = 0; i < N * M; i++) {
        int val = dist[0][i] + dist[i][0];
        if (val > D) continue;
        ans = max(ans, dict[A[i/M][i%M]]);
    }

    cout << ans;

    return 0;
}

