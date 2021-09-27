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
//열쇠
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 102
#define INF 123456789
#define notvisit 1073741824 // 1 <<30
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K;
const int dx[] = {-1, 0, 1, 0, -1, 1, 1, -1};
const int dy[] = {0, 1, 0, -1, 1, 1, -1, -1};

vector<vector<char>> map2d(MAXSIZE, vector<char>(MAXSIZE));
vector<vector<int>> visited(MAXSIZE, vector<int>(MAXSIZE)); //visited[y][x]==status
/*비트마스킹+bfs

status로 갖고있는 열쇠표현
T만큼 다먹거나 q가 비면 종료.
$먹으면 .으로 바꿔버려 중복먹기방지.
visited배열에 status를 저장하고 이 값과 현재status의 |연산이 다르면 큐에삽입
문제가 지나간 거리가아닌 얼마나 먹은지가 중요하며 한번 도달한곳은 또 도달가능한 곳이므로
모든 탐색중인 원소들은 status는 curkey변수하나를 공유함

근데 백조의 호수랑 비슷한 비효율이 있는데 굳이 비트마스킹+bfs를 써야하나는 생각이드는데 귀찮으니 이거로품
예: FeDcBa..............AbCdEf
*/
void showmap()
{
    cout << "\n";
    ffor(i, N + 2)
    {
        ffor(j, M + 2)
        {
            cout << map2d[i][j];
        }
        cout << endl;
    }
    cout << "\n";
}
int bfs(int stat) //비트마스킹 bfs
{
    int curkey = stat;
    deque<pii> Q; //y,x

    visited[0][0] = stat;
    Q.push_back({0, 0});
    int ans = 0;

    while (!Q.empty())
    {
        if (T == ans)
            break; //최대 개수에 도달

        auto [y, x] = Q.front();
        Q.pop_front();

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (0 <= nx && nx <= M + 1 && 0 <= ny && ny <= N + 1)
            {
                if (visited[ny][nx] == notvisit || ((visited[ny][nx] | curkey) != visited[ny][nx]))
                { //새로 지나가야하는 자리
                    if (map2d[ny][nx] == '.')
                    { //빈공간
                        visited[ny][nx] = curkey;
                        Q.push_back({ny, nx});
                    }
                    else if ('a' <= map2d[ny][nx] && map2d[ny][nx] <= 'z')
                    { //열쇠휙득
                        curkey |= (1 << (map2d[ny][nx] - 'a'));
                        map2d[ny][nx] = '.';
                        visited[ny][nx] = curkey;
                        Q.push_back({ny, nx});
                    }
                    else if ('A' <= map2d[ny][nx] && map2d[ny][nx] <= 'Z')
                    {                                                     //금고
                        if ((curkey & (1 << (map2d[ny][nx] - 'A'))) != 0) //열쇠있으면
                        {
                            visited[ny][nx] = curkey;
                            map2d[ny][nx] = '.';
                            Q.push_back({ny, nx});
                        }
                    }
                    else if (map2d[ny][nx] == '$')
                    { //돈
                        map2d[ny][nx] = '.';
                        ans++;
                        visited[ny][nx] = curkey;
                        Q.push_back({ny, nx});
                    }
                }
            }
        }
    }

    return ans;
}

void init()
{

    for (int i = 0; i <= N + 1; i++)
    {
        map2d[i][0] = '.';
        visited[i][0] = notvisit;
        map2d[i][M + 1] = '.';
        visited[i][M + 1] = notvisit;
    }
    for (int i = 0; i <= M + 1; i++)
    {
        map2d[0][i] = '.';
        map2d[N + 1][i] = '.';
        visited[0][i] = notvisit;
        visited[N + 1][i] = notvisit;
    }
}
int main()
{
    fastio;
    string keys;
    int testcase;
    cin >> testcase;

    while (testcase--)
    {
        cin >> N >> M;

        int status = 0;
        T = 0;
        init();

        f1for(i, N) f1for(j, M)
        {
            cin >> map2d[i][j];
            visited[i][j] = notvisit;
            if (map2d[i][j] == '$')
            {
                T++;
            }
        }

        cin >> keys;
        if (keys[0] != '0')
        {
            for (char k : keys)
            {
                status = status | 1 << (k - 'a');
            }
        }

        // showmap();
        cout << bfs(status) << endl;
    }
}