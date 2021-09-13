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
//등산
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 26
#define INF 0x7FFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, D, K;
const int dx[] = {-1, 0, 1, 0, -1, 1, 1, -1};
const int dy[] = {0, 1, 0, -1, 1, 1, -1, -1};
vector<vector<int>> map2d(MAXSIZE, vector<int>(MAXSIZE));
//vector<vector<int>> dist(MAXSIZE, vector<int>(MAXSIZE, INF));
vector<vector<vector<vector<int>>>> dist(MAXSIZE, vector<vector<vector<int>>>(MAXSIZE, vector<vector<int>>(MAXSIZE, vector<int>(MAXSIZE, INF)))); //4차원배열

void floyd()
{
    int nx, ny, diff;

    ffor(y, N) ffor(x, M)
    {
        ffor(i, 4)
        {
            nx = x + dx[i];
            ny = y + dy[i];
            if (0 <= nx && nx < M && 0 <= ny && ny < N)
            {
                diff = map2d[ny][nx] - map2d[y][x];
                if (0 < diff)
                { //올라가기
                    if (T < diff)
                        continue;
                    dist[y][x][ny][nx] = diff * diff;
                }
                else
                { //내려가기
                    if (T < -diff)
                        continue;
                    dist[y][x][ny][nx] = 1;
                }
            }
        }
    }
    ffor(i, N) ffor(j, M) { dist[i][j][i][j] = 0; }

    ffor(ky, N) ffor(kx, M) ffor(y, N) ffor(x, M) ffor(ny, N) ffor(nx, M)
    {
        if (dist[y][x][ny][nx] > dist[y][x][ky][kx] + dist[ky][kx][ny][nx])
        {
            dist[y][x][ny][nx] = dist[y][x][ky][kx] + dist[ky][kx][ny][nx];
        }
    }
}

void showmap()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << map2d[i][j] << "   ";
        }
        cout << endl;
    }
}
void showdmap()
{
    ffor(y, N)
    {
        ffor(x, M)
        {
            if (dist[0][0][y][x] + dist[y][x][0][0] > INF)
            {
                cout << "?  ";
            }
            else
                cout << dist[0][0][y][x] << "+" << dist[y][x][0][0] << "  ";
        }
        cout << endl;
    }
}
int main()
{
    fastio;
    int u, v, w;
    cin >> N >> M >> T >> D;

    int lowerdiff = -'a' + 26;
    string str;
    ffor(y, N)
    {
        cin >> str;
        ffor(x, M)
        {
            if ('a' <= str[x])
            { //소문자
                map2d[y][x] = str[x] + lowerdiff;
            }
            else
            { //대문자
                map2d[y][x] = str[x] - 'A';
            }
        }
    }
    //showmap();
    floyd();
    int maxheight = map2d[0][0]; //호텔에서 막혔을떄가 있는듯?
    //showdmap();

    ffor(y, N) ffor(x, M)
    {
        if (dist[0][0][y][x] + dist[y][x][0][0] <= D)
        {
            if (maxheight < map2d[y][x])
            {
                maxheight = map2d[y][x];
            }
        }
    }
    cout << maxheight;
}