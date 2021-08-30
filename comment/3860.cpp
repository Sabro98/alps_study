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
//할로윈 묘지
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X first
#define Y second
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 31
#define INF 0x7FFFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
typedef pair<int, lli> pili;
typedef pair<lli, lli> plli;
int N, M, T, K, W, S, H, E;
const int dx[] = {-1, 0, 1, 0, -1, 1, 1, -1};
const int dy[] = {0, 1, 0, -1, 1, 1, -1, -1};
vector<vector<lli>> dist(MAXSIZE, vector<lli>(MAXSIZE, INF));
vector<vector<char>> map2d(MAXSIZE, vector<char>(MAXSIZE, 'o'));
class node
{
public:
    int x, y;
    lli w;
    node()
    {
        x = 0;
        y = 0;
        w = 0;
    }
    node(int _x, int _y, lli weight)
    {
        x = _x;
        y = _y;
        w = weight;
    }
};
node hole[MAXSIZE][MAXSIZE];
bool Bellman_Ford()
{
    int nx, ny;

    dist[0][0] = 0;
    int update = W * H - 1;

    //update
    while (update--)
    {
        ffor(x, W) ffor(y, H)
        {
            if (dist[x][y] != INF)
            {
                if (map2d[x][y] == 'o')
                { //평범한땅
                    //4방향이동

                    for (int k = 0; k < 4; k++)
                    {
                        nx = x + dx[k];
                        ny = y + dy[k];
                        if (0 <= nx && nx < W && 0 <= ny && ny < H && map2d[nx][ny] != 'x')
                        {
                            if (dist[nx][ny] > dist[x][y] + 1)
                            {
                                dist[nx][ny] = dist[x][y] + 1;
                            }
                        }
                    }
                }
                else if (map2d[x][y] == 'h')
                { //구멍
                    node nextNode = hole[x][y];
                    if (dist[nextNode.x][nextNode.y] > dist[x][y] + nextNode.w)
                    {
                        dist[nextNode.x][nextNode.y] = dist[x][y] + nextNode.w;
                    }
                }
            }
        }
    }

    //check negative cycle
    ffor(x, W) ffor(y, H)
    {
        if (dist[x][y] != INF)
        {
            if (map2d[x][y] == 'o')
            { //평범한땅
                //4방향이동
                for (int k = 0; k < 4; k++)
                {
                    nx = x + dx[k];
                    ny = y + dy[k];
                    if (0 <= nx && nx < W && 0 <= ny && ny < H && map2d[nx][ny] != 'x')
                    {
                        if (dist[nx][ny] > dist[x][y] + 1)
                        {
                            return true;
                        }
                    }
                }
            }
            else if (map2d[x][y] == 'h')
            { //구멍
                node nextNode = hole[x][y];
                if (dist[nextNode.x][nextNode.y] > dist[x][y] + nextNode.w)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
// bool bfs()
// {
//     vector<vector<bool>> visited(MAXSIZE, vector<bool>(MAXSIZE, false));
//     deque<pii> Q;
//     ffor(x, W) ffor(y, H)
//     {
//         if (dist[x][y] != INF)
//         {
//             if (map2d[x][y] == 'o')
//             { //평범한땅
//                 //4방향이동
//                 for (int k = 0; k < 4; k++)
//                 {
//                     int nx = x + dx[k];
//                     int ny = y + dy[k];
//                     if (0 <= nx && nx < W && 0 <= ny && ny < H && map2d[nx][ny] != 'x')
//                     {
//                         if (dist[nx][ny] > dist[x][y] + 1)
//                         {
//                             if (!visited[nx][ny])
//                             {
//                                 visited[nx][ny] = true;
//                                 Q.push_back({nx, ny});
//                             }
//                         }
//                     }
//                 }
//             }
//             else if (map2d[x][y] == 'h')
//             { //구멍
//                 node nextNode = hole[x][y];
//                 if (dist[nextNode.x][nextNode.y] > dist[x][y] + nextNode.w)
//                 {
//                     if (!visited[nextNode.x][nextNode.y])
//                     {
//                         visited[nextNode.x][nextNode.y] = true;
//                         Q.push_back({nextNode.x, nextNode.y});
//                     }
//                 }
//             }
//         }
//     }

//     while (!Q.empty())
//     {
//         auto cur = Q.front();
//         Q.pop_front();
//         int x = cur.X;
//         int y = cur.Y;
//         if (map2d[x][y] == 'o')
//         {
//             for (int k = 0; k < 4; k++)
//             {
//                 int nx = x + dx[k];
//                 int ny = y + dy[k];
//                 if (0 <= nx && nx < W && 0 <= ny && ny < H && map2d[nx][ny] != 'x')
//                 {
//                     if (!visited[nx][ny])
//                     {
//                         visited[nx][ny] = true;
//                         Q.push_back({nx, ny});
//                     }
//                 }
//             }
//         }
//         else if (map2d[x][y] == 'h')
//         { //구멍
//             node nextNode = hole[x][y];
//             if (!visited[nextNode.x][nextNode.y])
//             {
//                 visited[nextNode.x][nextNode.y] = true;
//                 Q.push_back({nextNode.x, nextNode.y});
//             }
//         }
//     }
//     return visited[W - 1][H - 1];
// }
void init()
{
    ffor(i, W) ffor(j, H)
    {
        map2d[i][j] = 'o';
        dist[i][j] = INF;
        hole[i][j] = {0, 0, 0};
    }
    map2d[W - 1][H - 1] = 'e';
}
int main()
{ //[x][y]순서임
    fastio;
    while (true)
    {
        cin >> W >> H;
        if (W == 0 && H == 0)
        {
            break;
        }
        init();
        int x, y, fromX, fromY, toX, toY, graves;
        lli w;
        cin >> graves;
        ffor(i, graves)
        { //묘비
            cin >> x >> y;
            map2d[x][y] = 'x';
        }
        cin >> E;
        ffor(i, E)
        { //귀신구멍
            cin >> fromX >> fromY >> toX >> toY >> w;
            map2d[fromX][fromY] = 'h';
            hole[fromX][fromY] = {toX, toY, w};
        }
        bool hasnega = Bellman_Ford();

        if (hasnega)
        {
            // if (bfs())
            // {아니 번역을 개같이 해놨는데 다른문제와달리 음의사이클에서 bfs로 찾으면안됨+ 무조건 음의사이클있으면 이거부터 출력
            cout << "Never" << endl;
            continue;
            // }
        }
        else if (dist[W - 1][H - 1] == INF)
        {
            cout << "Impossible" << endl;
            continue;
        }
        cout << dist[W - 1][H - 1] << endl;
        continue;
    }
}