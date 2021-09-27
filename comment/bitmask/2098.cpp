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
//외판원 순회
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 16
#define INF 123456789
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K;
//const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

vector<vector<int>> dist(MAXSIZE, vector<int>(MAXSIZE));
vector<vector<int>> dp(MAXSIZE, vector<int>(1 << MAXSIZE, -1)); //dp[x][방문상태] 방문상태에서 x를갈때의 비용

int travel(int x, int status)
{
    if (status == (1 << N) - 1) //모두방문
    {
        if (dist[x][0] == 0)
        {
            return INF; //0을 시작으로 둘꺼임
        }
        return dist[x][0]; //문제에서 0인길이 있음
    }

    int &ret = dp[x][status]; //가독성을위해 해당 dp값 ret으로 부름
    if (ret != -1)            //재사용
        return ret;
    ret = INF;
    for (int i = 0; i < N; i++)
    {
        if (dist[x][i] == 0 || ((1 << i) & status) != 0) //i방문
            continue;

        ret = min(travel(i, (1 << i) | status) + dist[x][i], ret);
    }

    return ret;
}
int main()
{
    fastio;
    cin >> N;
    ffor(i, N) ffor(j, N)
    {
        cin >> dist[i][j];
    }

    cout << travel(0, 1);
}