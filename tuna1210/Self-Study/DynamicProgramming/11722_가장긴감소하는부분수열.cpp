#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
int A[1001];
int dp[1001];

int LIS()
{
    int ans = 1;
    dp[0] = 1;
    for (int i = 1; i < n; i++)
    {
        int lessMax = 0;
        for (int j = 0; j < i; j++)
        {
            if(A[i] < A[j])
            {
                if(lessMax < dp[j])
                {
                    lessMax = dp[j];
                }
            }
        }
        dp[i] = lessMax + 1;
        if(dp[i] > ans) ans = dp[i];
    }
    
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
    }
    
    cout << LIS() << "\n";
}