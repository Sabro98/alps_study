#include <iostream>
using namespace std;

int n;
int dp[10][101][1 << 10];

int dfs(int cur, int depth, int path)
{
    // cout << cur << ", " << depth << ", " << bitset<10>(path) << "\n";
    if(depth == n)
    {
        if((path & ((1 << 10) - 1)) == ((1 << 10) - 1))
        {
            return 1;
        }
        return 0;
    }
    int& ret = dp[cur][depth][path];
    if(ret != 0) return ret;

    if(cur > 0) ret += dfs(cur - 1, depth + 1, path | (1 << (cur - 1))) % 1000000000;
    if(cur < 9) ret += dfs(cur + 1, depth + 1, path | (1 << (cur + 1))) % 1000000000;

    return ret % 1000000000;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;

    long long ans = 0;
    for (int i = 1; i <= 9; i++)
    {
        ans += dfs(i, 1, 1 << i);
    }
    cout << ans % 1000000000 << "\n";
}