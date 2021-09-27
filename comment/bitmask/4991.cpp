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
//로봇청소기
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 20
#define INF 123456789
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K;
const int dx[] = {-1, 0, 1, 0, -1, 1, 1, -1};
const int dy[] = {0, 1, 0, -1, 1, 1, -1, -1};

vector<vector<char>> map2d(MAXSIZE, vector<char>(MAXSIZE));

int bfs(pii start, int targets) //비트마스킹 bfs
{
    vector<vector<vector<bool>>> visited(MAXSIZE, vector<vector<bool>>(MAXSIZE, vector<bool>(1 << targets, false))); //visited[y][x][status]
    int y, x, status;
    tie(y, x) = start;
    /*auto [y, x] = start;*/
    deque<tuple<int, int, int>> Q; //y,x,status
    visited[y][x][0] = true;
    Q.push_back({y, x, 0});

    int day = 0;
    while (!Q.empty())
    {
        int qsize = Q.size();
        ffor(i, qsize)
        {
            /*auto [y,x,status]*/ tie(y, x, status) = Q.front();
            Q.pop_front();
            if (status == ((1 << targets) - 1))
                return day;

            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (0 <= nx && nx < M && 0 <= ny && ny < N)
                {
                    if (visited[ny][nx][status])
                        continue;
                    if (0 <= map2d[ny][nx] && map2d[ny][nx] <= targets)
                    {
                        visited[ny][nx][status] = true;
                        Q.push_back({ny, nx, status | (1 << map2d[ny][nx])});
                    }
                    else if (map2d[ny][nx] != 'x')
                    {
                        visited[ny][nx][status] = true;
                        Q.push_back({ny, nx, status});
                    }
                }
            }
        }
        day++;
    }

    return -1;
}
int main()
{
    fastio;
    pii start;
    while (true)
    {
        cin >> M >> N;
        if (N == 0 && M == 0)
            break;
        int target = 0;
        ffor(i, N) ffor(j, M)
        {
            cin >> map2d[i][j];
            if (map2d[i][j] == 'o')
            {
                start = {i, j};
            }
            else if (map2d[i][j] == '*')
            {
                map2d[i][j] = target;
                target++;
            }
        }
        cout << bfs(start, target) << endl;
    }
}