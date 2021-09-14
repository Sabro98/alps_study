#include <iostream>
#include <vector>
using namespace std;

#define INF 1e9

int n, m, t, d;
int map[26][26];
long long floyd[676][676];
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

int getHeight(char ch)
{
    if(ch >= 65 && ch <=90) return ch - 65;
    return ch - 71;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m >> t >> d;

    int size = n * m;
    
    char ch;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> ch;
            map[i][j] = getHeight(ch);
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            floyd[i][j] = (i == j? 0 : INF);
        }
    }
    
    // init adj mat
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                int nx = i + dx[k], ny = j + dy[k];
                if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;

                int heightGap = map[nx][ny] - map[i][j];
                if(abs(heightGap) > t) continue;

                if(heightGap > 0)
                    floyd[i * m + j][nx * m + ny] = heightGap * heightGap;
                else
                    floyd[i * m + j][nx * m + ny] = 1;
            }
        }
    }

    // floyd
    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                floyd[i][j] = min(floyd[i][j], floyd[i][k] + floyd[k][j]);
            }
        }
    }

    // for (int i = 0; i < size; i++)
    // {
    //     for (int j = 0; j < size; j++)
    //     {
    //         cout << (floyd[i][j] == INF? -1 : floyd[i][j]) << " ";
    //     }
    //     cout << "\n";
    // }

    int ans = map[0][0];
    for (int j = 1; j < size; j++)
    {
        if(floyd[0][j] + floyd[j][0] <= d) ans = max(ans, map[j / m][j % m]);
    }

    cout << ans << "\n";
}