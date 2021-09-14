#include <iostream>
#include <queue>
#include <unordered_set>
#include <string>
using namespace std;

typedef struct
{
    int board[3][3];
} puzzle;

const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
const int correct[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
unordered_set<string> visited;

bool isCorrect(puzzle& cur)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(cur.board[i][j] != correct[i][j]) return false;
        }
    }
    return true;
}

pair<int, int> getZeroPos(puzzle& cur)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (cur.board[i][j] == 0) return {i, j};
        }
    }
    return {-1, -1};
}

void setNextPuzzle(pair<int, int> zeroPos, pair<int, int> nextZeroPos, puzzle cur, puzzle& next)
{
    next = cur;
    next.board[zeroPos.first][zeroPos.second] = cur.board[nextZeroPos.first][nextZeroPos.second];
    next.board[nextZeroPos.first][nextZeroPos.second] = cur.board[zeroPos.first][zeroPos.second];
}

string puzzleToString(puzzle& cur)
{
    string ret = "";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ret += cur.board[i][j];
        }
    }
    return ret;
}

int bfs(puzzle& start)
{
    queue<puzzle> q;
    q.push(start);
    visited.insert(puzzleToString(start));
    
    int move = 0;
    while(!q.empty())
    {
        int size = q.size();
        for (int qs = 0; qs < size; qs++)
        {
            puzzle cur = q.front();
            q.pop();
            
            if(isCorrect(cur)) return move;

            pair<int, int> zeroPos = getZeroPos(cur);
            for (int i = 0; i < 4; i++)
            {
                int nx = zeroPos.first + dx[i], ny = zeroPos.second + dy[i];
                if(nx < 0 || ny < 0 || nx >= 3 || ny >= 3) continue;

                puzzle next;
                setNextPuzzle(zeroPos, {nx, ny}, cur, next);
                string nextStr = puzzleToString(next);
                if(visited.find(nextStr) != visited.end()) continue;
                visited.insert(nextStr);
                q.push(next);
            }
        }
        move++;
    }
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    puzzle start;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> start.board[i][j];
        }
    }
    
    cout << bfs(start) << "\n";
}