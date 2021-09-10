#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
int A[1001];
int dp[1001];
int ldsDp[1001];

void LIS()
{
    dp[0] = 1;
    for (int i = 1; i < n; i++)
    {
        int lessMax = 0;
        for (int j = 0; j < i; j++)
        {
            if(A[i] > A[j])
            {
                if(lessMax < dp[j])
                {
                    lessMax = dp[j];
                }
            }
        }
        dp[i] = lessMax + 1;
    }
}

void LDS()
{
    ldsDp[n - 1] = 1;
    for (int i = n - 1; i >= 0; i--)
    {
        int bigMax = 0;
        // cout << "i : " << i << "\n";
        for (int j = n - 1; j >= i; j--)
        {
            if(A[i] > A[j])
            {
                if(bigMax < ldsDp[j])
                {
                    // cout << i << " " << j << " \n";
                    bigMax = ldsDp[j];
                }
            }
        }
        ldsDp[i] = bigMax + 1;
        // cout << "bigMax : " << bigMax << ", dp : " << ldsDp[i] << "\n";
    }
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
    

    LIS();
    LDS();

    int lbs = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if(A[i] == A[j]) continue;
            lbs = max(lbs, dp[i] + ldsDp[j]);
        }
    }
    
    cout << lbs << "\n";
}