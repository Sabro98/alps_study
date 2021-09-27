#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <set>
#include <cmath>
#include <map>
#include <deque>
#include <limits.h>
#include <utility>
#include <list>
#include <unordered_map>
#include <string.h>
#include <random>
#include <queue>
//계단 수
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 101
#define INF 123456789
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K;
#define MOD 1000000000ll

//dp[i][num][status] 길이가i면서 num으로 시작하고 status인 계단수 숫자
//쉬운 계단수에서 status가 11 1111 1111 인것만 세준다
vector<vector<vector<lli>>> dp(MAXSIZE, vector<vector<lli>>(11, vector<lli>(1 << 10, -1)));

// void showmap()
// {
//     ffor(i, N)
//     {
//         ffor(j, M)
//         {
//             cout << arr[i][j] << " ";
//         }
//         cout << '\n';
//     }
//     cout << "==================\n";
// }
lli dfs(int len, int cur, int status)
{
    if (len == N - 1)
    {
        if (status == (1 << 10) - 1)
            return 1;
        else
            return 0;
    }

    lli &ret = dp[len][cur][status]; //가독성을위해 해당 dp값 ret으로 부름
    if (ret != -1)                   //재사용
        return ret;

    ret = 0;
    for (int next : {cur + 1, cur - 1})
    {
        if (0 <= next && next <= 9)
        {
            ret = (ret + dfs(len + 1, next, status | (1 << next))) % MOD;
        }
    }

    return ret;
}
int main()
{
    fastio;

    cin >> N;
    // auto initdp = dp;
    long long int sum = 0;
    // N = 10;
    // lli lsum = 0;
    // while (N <= 40)
    // {
    // dp = initdp;
    // sum = 0;
    for (int i = 1; i < 10; i++)
    {
        sum = (sum + dfs(0, i, 1 << i)) % MOD;
    }
    cout << sum << endl;
    // lsum += sum;
    // N++;
    // }
    // cout << lsum;
}