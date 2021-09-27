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
//달이 차오른다,가자
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 50
#define INF 123456789
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K;
const int dx[] = {-1, 0, 1, 0, -1, 1, 1, -1};
const int dy[] = {0, 1, 0, -1, 1, 1, -1, -1};

vector<vector<char>> map2d(MAXSIZE, vector<char>(MAXSIZE));
vector<vector<vector<bool>>> visited(MAXSIZE, vector<vector<bool>>(MAXSIZE, vector<bool>(1 << 6, false))); //visited[y][x][status]

int bfs(pii start) //비트마스킹 bfs
{
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
            if (map2d[y][x] == '1')
                return day;

            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (0 <= nx && nx < M && 0 <= ny && ny < N)
                {
                    if (visited[ny][nx][status])
                        continue;
                    if ('a' <= map2d[ny][nx] && map2d[ny][nx] <= 'f')
                    { //열쇠휙득
                        visited[ny][nx][status] = true;
                        Q.push_back({ny, nx, status | (1 << (map2d[ny][nx] - 'a'))});
                    }
                    else if ('A' <= map2d[ny][nx] && map2d[ny][nx] <= 'F')
                    {
                        if ((status & (1 << (map2d[ny][nx] - 'A'))) != 0)
                        {
                            visited[ny][nx][status] = true;
                            Q.push_back({ny, nx, status});
                        }
                    }
                    else if (map2d[ny][nx] != '#')
                    { //0,1,빈공간
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
    cin >> N >> M;
    pii start;

    ffor(i, N) ffor(j, M)
    {
        cin >> map2d[i][j];
        if (map2d[i][j] == '0')
        {
            start = {i, j};
        }
    }

    cout << bfs(start);
}