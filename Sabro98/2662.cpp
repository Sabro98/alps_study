#include <iostream>
#include <vector>

using namespace std;
typedef pair<int, int> P;

int N, M, value[301][21];
int dp[21][301];
vector<int> ans[21][301];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 0; i <= M; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            ans[i][j] = vector<int>(M + 1);
        }
    }

    for (int i = 1, j; i <= N; i++)
    {
        cin >> j;
        for (int k = 1; k <= M; k++)
        {
            cin >> value[j][k];
        }
    }

    for (int i = 1; i <= M; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            //0원 투자
            dp[i][j] = dp[i - 1][j];
            ans[i][j] = ans[i - 1][j];
            //1원 ~ N원 투자
            for (int k = 1; k <= N; k++)
            {
                if (j - k < 0)
                    break;
                int v = value[k][i];
                if (dp[i - 1][j - k] + v > dp[i][j])
                {
                    dp[i][j] = dp[i - 1][j - k] + v;
                    ans[i][j] = ans[i - 1][j - k];
                    ans[i][j][i] += k;
                }
            }
        }
    }

    cout << dp[M][N] << '\n';
    for (int i = 1; i <= M; i++)
        cout << ans[M][N][i] << ' ';

    return 0;
}