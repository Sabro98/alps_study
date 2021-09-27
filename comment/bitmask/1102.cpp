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
//발전소
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
int N, M, T, K, P;
//const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

vector<vector<int>> dist(MAXSIZE, vector<int>(MAXSIZE));
vector<int> dp(1 << MAXSIZE, -1); //dp[방문상태] 방문상태에서 순회할때 최소값

int travel(int status)
{
    if (P == __builtin_popcount(status)) //P개방문
    {
        return 0;
    }

    int &ret = dp[status]; //가독성을위해 해당 dp값 ret으로 부름
    if (ret != -1)         //재사용
        return ret;

    ret = INF;
    for (int start = 0; start < N; start++) // 모든 Y에서 모든 N으로 가봄
    {
        if (((1 << start) & status) == 0)
        {
            continue; //안켜진곳 스킵
        }
        for (int i = 0; i < N; i++)
        {
            if (((1 << i) & status) != 0)
            {
                continue; //켜진곳스킵
            }
            ret = min(travel((1 << i) | status) + dist[start][i], ret);
        }
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
    string bits;
    cin >> bits;
    int initstat = 0;
    ffor(i, bits.size())
    {
        if (bits[i] == 'Y')
        {
            initstat = (1 << i) | initstat;
        }
    }
    cin >> P;
    if (P <= __builtin_popcount(initstat))
    {
        cout << 0;
    }
    else if (initstat == 0)
    {
        cout << -1;
    }
    else
        cout << travel(initstat);
}