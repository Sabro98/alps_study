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
//앱
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 100001
#define INF 0x7FFFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K;
//const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

vector<int> mem(101, 0);
vector<int> value(101, 0);
vector<int> dp(MAXSIZE, 0);
// vector<vector<int>> dp(MAXSIZE, vector<int>(MAXSIZE, 0));
int main()
{
    fastio;
    cin >> N >> M;
    f1for(i, N)
    {
        cin >> mem[i];
    }
    f1for(i, N)
    {
        cin >> value[i];
    }

    f1for(i, N) for (int j = 10000; j >= value[i]; j--)
    {
        dp[j] = max(dp[j], dp[j - value[i]] + mem[i]);
    }

        int i = 0;
    while (true)
    {
        if (dp[i] >= M)
        {
            cout << i;
            break;
        }
        i++;
    }
}