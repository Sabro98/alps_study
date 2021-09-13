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
//우주 탐사선
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 11
#define INF 0x7FFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K;
int ans;
//const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };
vector<vector<int>> dist(MAXSIZE, vector<int>(MAXSIZE));
vector<bool> visited(MAXSIZE, false);
void floyd()
{

    ffor(k, N) ffor(i, N) ffor(j, N)
    {
        {
            {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

void dfs(int starting, int sum, int depth)
{
    visited[starting] = true;

    ffor(i, N)
    {
        if (!visited[i])
        {
            dfs(i, sum + dist[starting][i], depth + 1);
            visited[i] = false;
        }
    }
    if (depth == N)
    {
        ans = min(ans, sum);
    }
}

int main()
{
    fastio;
    int start;
    cin >> N >> start;
    ffor(i, N) ffor(j, N)
    {
        cin >> dist[i][j];
    }
    floyd();

    // ffor(i, N)
    // {
    //     ffor(j, N)
    //     {
    //         if (dist[i][j] != INF)
    //         {
    //             cout << dist[i][j] << " ";
    //         }
    //         else
    //         {
    //             cout << '?' << " ";
    //         }
    //     }
    //     cout << endl;
    // }
    ans = INF;
    dfs(start, 0, 1); //무지성으로 다해보기
    cout << ans;
}