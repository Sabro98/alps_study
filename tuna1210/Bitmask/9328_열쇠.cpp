#include <iostream>
#include <cstring>
#include <string>
#include <queue>

using namespace std;

const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

char map[102][102];
bool visited[102][102];
int n, m;

inline bool isKey(char ch)
{
    return (ch >= 'a' && ch <= 'z');
}

inline bool isDoor(char ch)
{
    return (ch >= 'A' && ch <= 'Z');
}

pair<bool, int> bfs(int& startKey)
{
    memset(visited, false, sizeof(visited));

    queue<pair<int, int>> q;
    q.push({0, 0});
    visited[0][0] = true;
    
    int cnt = 0;
    bool keyChg = false;
    while(!q.empty())
    {
        pair<int, int> cur = q.front();
        q.pop();

        int cx = cur.first, cy = cur.second;

        if(map[cx][cy] == '$')
        {
            map[cx][cy] = '.';
            cnt++;
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = cx + dx[i], ny = cy + dy[i];
            char nType = map[nx][ny];

            if(nx < 0 || ny < 0 || nx > n || ny > m || nType == '*' || visited[nx][ny]) continue;

            visited[nx][ny] = true;

            if(isKey(nType) && (startKey & (1 << (nType - 'a'))) != (1 << (nType - 'a')))
            {
                keyChg = true;
                startKey = (startKey | (1 << (nType - 'a')));
            }

            if(isDoor(nType))
            {
                if((startKey & (1 << (nType - 'A'))) != (1 << (nType - 'A'))) continue;
                q.push({nx, ny});
            }
            else
            {
                q.push({nx, ny});
            }
        }
    }
    
    return {keyChg, cnt};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int tc;
    cin >> tc;

    while (tc--)
    {
        cin >> n >> m;

        n++;
        m++;

        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= m; j++)
            {
                if(i == 0 || j == 0 || i == n || j == m) map[i][j] = '.';
                else cin >> map[i][j];
            }
        }

        string strStartKey;
        cin >> strStartKey;

        int startKey = 0;
        if(strStartKey.compare("0") != 0)
        {
            for(const auto& key : strStartKey)
            {
                startKey |= (1 << (key - 'a'));
            }
        }
        
        int totalDocs = 0;
        while(true)
        {
            pair<bool, int> docs = bfs(startKey);
            totalDocs += docs.second;
            if(!docs.first) break;
        }
        
        cout << totalDocs << "\n";
    }
}
