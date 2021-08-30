#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;
typedef pair<int, int> P;
typedef long long ll;

const int INF = 0x3f3f3f3f;
int N, M;
bool A[501][501];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 0, u, v; i < M; i++)
    {
        cin >> u >> v;
        A[u][v] = true;
    }

    for (int i = 1; i <= N; i++)
        A[i][i] = true;

    for (int k = 1; k <= N; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                A[i][j] |= A[i][k] & A[k][j];
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= N; i++)
    {
        bool flag = true;
        for (int j = 1; j <= N; j++)
        {
            flag &= (A[i][j] || A[j][i]);
        }
        if (flag)
            ans++;
    }

    cout << ans;

    return 0;
}
