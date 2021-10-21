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
//기업투자
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

vector<vector<int>> value(21, vector<int>(301, 0)); //[M][N] N만원 M번째기업이익
vector<vector<int>> dp(21, vector<int>(301, 0));    //[c][j] 1~c기업에서 j만원으로할수있는 최선
vector<vector<pii>> parent(21, vector<pii>(301));
int main()
{
    fastio;
    cin >> N >> M;

    f1for(i, N)
    {
        cin >> i;
        f1for(j, M)
        {
            cin >> value[j][i];
        }
    }

    //1번째기업부터 1만원~N만원까지 최대이익을채워나감
    //j만원일때 j만원을 c기업에투자+dp[c-1][남은돈] 과
    //
    f1for(c, M) for (int i = 1; i <= N; i++) for (int cur = 0; cur <= i; cur++)
    {
        if (dp[c][i] < value[c][cur] + dp[c - 1][i - cur])
        {
            dp[c][i] = value[c][cur] + dp[c - 1][i - cur];
            parent[c][i] = {cur, i - cur};
        }
    }
    cout << dp[M][N] << endl;
    int p = M;
    int c = N;
    deque<int> st;
    while (p > 0)
    {
        auto [selected, remain] = parent[p][c];
        c = remain;
        st.push_back(selected);
        p--;
    }
    while (!st.empty())
    {
        cout << st.back() << " ";
        st.pop_back();
    }
}