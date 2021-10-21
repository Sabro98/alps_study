#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <set>
#include <cmath>
#include <map>
#include <deque>
#include <utility>
#include <list>
#include <unordered_map>
#include <string.h>
#include <random>
#include <queue>
//백남이의 여행 준비
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 101
#define INF 0x7FFFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K;
//const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

vector<int> dp(1000001, 0);
vector<int> weight(MAXSIZE, 0);
vector<int> value(MAXSIZE, 0);
vector<int> knapsack(MAXSIZE);
int main()
{
    fastio;

    cin >> N >> M;

    f1for(i, N)
    {
        cin >> weight[i] >> value[i];
    }
    K = 0;
    f1for(i, M)
    {
        cin >> knapsack[i];
        K = max(K, knapsack[i]);
    }

    f1for(i, N) for (int j = K; j > 0; j--)
    {
        if (weight[i] <= j)
        { // 넣을 수 있다면?
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
            // 그 물건을 넣었을 때와 넣지 않았을 때 중 더 큰 값으로 초기화
        }
    }
    double effi = 0;
    double maxEffi = 0;
    int ans = 1;
    f1for(i, M)
    {
        effi = dp[knapsack[i]] / ((double)knapsack[i]);
        if (maxEffi < effi)
        {
            maxEffi = effi;
            ans = i;
        }
    }

    cout << ans;
}