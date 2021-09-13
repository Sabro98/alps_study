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
//궁금한 민호
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 21
#define INF 0x7FFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K;
//const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

vector<vector<int>> dist(MAXSIZE, vector<int>(MAXSIZE, INF));
vector<vector<bool>> visited(MAXSIZE, vector<bool>(MAXSIZE, false));

int main()
{
    /*다른간선을 이용해 도달 가능하면 그 간선 제거
     제거될 간선을 이용해서 중복 도달하는 경우도 있으므로 bool배열 사용*/
    fastio;
    cin >> N;
    f1for(i, N)
    {
        f1for(j, N)
        {
            cin >> dist[i][j];
        }
    }

    //cout << "===============\n";
    // for (int i = 1; i <= N; i++) //debug
    // {
    //     for (int j = 1; j <= N; j++)
    //     {
    //         if (dist[i][j] == INF)
    //             cout << "INF ";
    //         else
    //             cout << dist[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    for (int start = 1; start <= N; start++)
    {
        for (int end = start + 1; end <= N; end++)
        {
            for (int mid = 1; mid <= N; mid++)
            {
                if (start == mid || mid == end)
                    continue;
                if (dist[start][end] == dist[start][mid] + dist[mid][end])
                {
                    visited[start][end] = true;
                }
                else if (dist[start][end] > dist[start][mid] + dist[mid][end])
                {
                    cout << -1;
                    return 0;
                }
            }
        }
    }
    lli sum = 0;
    for (int i = 1; i <= N; i++)
    {
        for (int j = i + 1; j <= N; j++)
        {
            if (!visited[i][j])
                sum += dist[i][j];
        }
    }
    cout << sum;
}