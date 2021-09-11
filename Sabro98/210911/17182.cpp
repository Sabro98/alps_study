#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <cstring>

using namespace std;
typedef pair<int, int> P;
typedef long long ll;

int N, S;
P dist[10][10];
int dp[10][1<<10];

int solve(int x, int status){
    if((1 << N) - 1 == status) return 0;
    int& ret = dp[x][status];
    if(ret != -1) return ret;

    ret = 1e9;
    for(int i=0; i<N; i++){
        if(status & (1 << i)) continue;
        if(x == i) continue;
        ret = min(ret, solve(i, status | dist[x][i].second) + dist[x][i].first);
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> S;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> dist[i][j].first;
            dist[i][j].second = (1 << j) | (1 << i);
        }
    }

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int tmp = dist[i][k].first + dist[k][j].first;
                if(dist[i][j].first > tmp){
                    dist[i][j].first = tmp;
                    dist[i][j].second = dist[i][k].second | dist[k][j].second;
                }
            }
        }
    }

    memset(dp, -1, sizeof(dp));

    cout << solve(S, 1 << S);

    return 0;
}

