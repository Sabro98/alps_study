#include <iostream>
#include <cstring>
#include <queue>
#include <map>
using namespace std;

int w, h, sx, sy;
bool visited[20][20][1 << 10];
char room[20][20];
int dustCnt;
map<pair<int, int>, int> dustNum;
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

int bfs()
{
    memset(visited, false, sizeof(visited));

    queue<pair<pair<int, int>, int>> q;
    q.push({{sx, sy}, 0});
    visited[sx][sy][0] = true;
    
    // cout << w << ", " << h << "\n";
    int cnt = 0;
    while(!q.empty())
    {
        int qsize = q.size();
        for (int qs = 0; qs < qsize; qs++)
        {
            pair<pair<int, int>, int> cur = q.front();
            q.pop();

            int cx = cur.first.first, cy = cur.first.second, cPath = cur.second;
            // cout << cx << ", " << cy << ", " << bitset<3>(cPath) << "\n";

            if((cPath & ((1 << dustCnt) - 1)) == ((1 << dustCnt) - 1)) return cnt;

            for (int i = 0; i < 4; i++)
            {
                int nx = cx + dx[i], ny = cy + dy[i], nPath = cPath;
                // cout << nx << ", " << ny << "\n";
                if(nx < 0 || ny < 0 || nx >= h || ny >= w || room[nx][ny] == 'x') continue;
                // cout << "dasdasdad\n";
                if(room[nx][ny] == '*')
                {
                    int nNum = dustNum[{nx, ny}];
                    nPath = (cPath | (1 << nNum));
                }
                
                if(visited[nx][ny][nPath]) continue;
                visited[nx][ny][nPath] = true;
                q.push({{nx, ny}, nPath});
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
    
    while(true)
    {
        cin >> w >> h;
        if(w == 0 && h == 0) break;

        dustCnt = 0;
        dustNum.clear();

        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                cin >> room[i][j];
                if(room[i][j] == 'o')
                {
                    sx = i;
                    sy = j;
                    continue;
                }
                if(room[i][j] == '*')
                {
                    dustNum[{i, j}] = dustCnt;
                    dustCnt++;
                }
            }
        }

        cout << bfs() << "\n";
    }
    
}