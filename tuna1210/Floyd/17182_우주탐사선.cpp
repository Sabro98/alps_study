#include <iostream>

using namespace std;

#define INF 1e9

int n, s;
int floyd[10][10];
int dp[10][1 << 10];

int ana(int cur, int path)
{
    if(path == (1 << n) - 1)
    {
        return 0;
    }
    int& ret = dp[cur][path];
    if(ret != 0) return ret;

    ret = INF;
    for (int i = 0; i < n; i++)
    {
        if((path & (1 << i)) == (1 << i)) continue;
        ret = min(ret, ana(i, (path | (1 << i))) + floyd[cur][i]);
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> s;
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> floyd[i][j];
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                floyd[i][j] = min(floyd[i][j], floyd[i][k] + floyd[k][j]);
            }
            
        }
        
    }
    

    cout << ana(s, (1 << s)) << "\n";
}