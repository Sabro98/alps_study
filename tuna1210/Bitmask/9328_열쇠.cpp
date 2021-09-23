/*
삽질
달이 차오른다랑 똑같은 문제인줄 알고 visited[100][100][1 << 26] 했다가 컴퓨터 강제 재부팅함
달이 차오른다는 알파벳의 개수가 6개로 제한이 되어있었기 때문에 방문배열을 3차원으로 설정해도 문제 없었음

해결법
1. 주어진 입력 주변을 '.' 으로 감싼다. n과 m을 1씩 더하고 테두리는 .을 집어넣는다. 시작은 (0, 0)으로 고정
2. bfs를 주어진 열쇠를 가지고 돌린다. 따라서 현재 열쇠에서 갈 수 있는 곳 까지만 간다. 
3. 문서를 만나면 문서를 . 으로 바꾸어서 다음번 bfs 에서 중복으로 세지 않도록 했다.
4. aAbBcCdD 같은 최악의 상황을 방지하기 위해 인자로 받은 열쇠를 열쇠를 찾을 때 마다 갱신해준다.
    (안하면 총 4번의 bfs를 돌려야 함)
5. 함수 리턴값으로 이번에 찾은 문서의 개수와 열쇠가 갱신되었는지를 리턴함.
6. 만약 열쇠가 갱신되지 않았다면 다음번에 돌려봤자 똑같은 결과가 나오므로 그만 돌림.
*/

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
