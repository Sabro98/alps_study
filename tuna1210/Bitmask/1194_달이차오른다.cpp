#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

char map[50][50];
bool visited[50][50][(1 << 6) + 1];
int n, m, sx, sy;

inline bool isKey(char ch)
{
    return (ch >= 'a' && ch <= 'f');
}

inline bool isDoor(char ch)
{
    return (ch >= 'A' && ch <= 'F');
}

int bfs()
{
    memset(visited, false, sizeof(visited));

    queue<pair<pair<int, int>, int>> q;

    q.push({{sx, sy}, 0});
    visited[sx][sy][0] = true;

    int cnt = 0;
    while(!q.empty())
    {
        int qsize = q.size();
        for (int qs = 0; qs < qsize; qs++)
        {
            pair<pair<int, int>, int> cur = q.front();
            q.pop();

            int cx = cur.first.first, cy = cur.first.second, cKey = cur.second;

            // cout << cx << ", " << cy << ", " << bitset<6>(cKey) << ", " << cType << "\n";

            if(map[cx][cy] == '1') return cnt;

            for (int i = 0; i < 4; i++)
            {
                int nx = cx + dx[i], ny = cy + dy[i];
                char nType = map[nx][ny];
                // cout << nType << "\n";
                int nKey = cKey;

                if(nx < 0 || ny < 0 || nx >= n || ny >= m || nType == '#') continue;

                if(isKey(nType))
                {
                    nKey = (cKey | (1 << (nType - 'a')));
                }
                
                if(visited[nx][ny][nKey]) continue;
                visited[nx][ny][nKey] = true;

                if(isDoor(nType))
                {
                    if((nKey & (1 << (nType - 'A'))) != (1 << (nType - 'A'))) continue;
                    q.push({{nx, ny}, nKey});
                }
                else
                {
                    q.push({{nx, ny}, nKey});
                }
            }
        }
        cnt++;
    }
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
            if(map[i][j] == '0')
            {
                sx = i;
                sy = j;
            }
        }
    }
    
    cout << bfs() << "\n";
}
