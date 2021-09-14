#include <iostream>
#include <vector>
using namespace std;

#define INF 1e9

int dp[16][1<<16];
int n;
int weight[16][16];

int solve(int cur, int status)
{
    if(status == (1 << n) - 1)
    {
        if(weight[cur][0] == 0) return INF;
        else return weight[cur][0];
    }

    int& ret = dp[cur][status];

    if(ret != 0) return ret;
    ret = INF;
    
    for (int i = 0; i < n; i++)
    {
        if(weight[cur][i] == 0 || (status & (1 << i)) == (1 << i)) continue;
        ret = min(ret, solve(i, status | (1 << i)) + weight[cur][i]);
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> weight[i][j];
        }
    }
    
    cout << solve(0, (1 << 0)) << "\n";
}
