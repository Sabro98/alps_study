#include <iostream>
#include <vector>
#include <cstring>
#include <map>
using namespace std;

#define INF 1e14

const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

enum stat
{
    grass,
    stone,
    hole
};

stat graveYard[31][31];
long long dist[31][31];
int w, h, g, e;

//  from {x1, y1}  ->  to {cost, {x2, y2}}
map<pair<int, int>, pair<int, pair<int, int>>> destination;

void bellmanFord();

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int x1, y1, x2, y2, t;

    while(true)
    {
        cin >> w >> h;
        if(w == 0 && h == 0) break;
        
        destination.clear();
        //init graveYard
        for (int i = 0; i < w; i++)
        {
            for (int j = 0; j < h; j++)
            {
                graveYard[i][j] = grass;
            }
        }
        
        //init stones
        cin >> g;
        for (int i = 0; i < g; i++)
        {
            cin >> x1 >> y1;
            graveYard[x1][y1] = stone;
        }

        //init ghosthole
        cin >> e;
        for (int i = 0; i < e; i++)
        {
            cin >> x1 >> y1 >> x2 >> y2 >> t;
            graveYard[x1][y1] = hole;
            destination[{x1, y1}] = {t, {x2, y2}};
        }
        
        bellmanFord();
    }
}

void bellmanFord()
{
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            dist[i][j] = INF;
        }
    }
    dist[0][0] = 0;
    
    int nx, ny, cost, repeat = w * h - 1;
    pair<int, pair<int, int>> dest;
    while(repeat--)
    {
        for (int i = 0; i < w; i++)
        {
            for (int j = 0; j < h; j++)
            {
                if(dist[i][j] != INF)
                {
                    if(i == w - 1 && j == h - 1) continue;
                    if(graveYard[i][j] == stone) continue;
                    else if(graveYard[i][j] == hole)
                    {
                        dest = destination[{i, j}];
                        cost = dest.first; nx = dest.second.first; ny = dest.second.second;
                        if(dist[nx][ny] > dist[i][j] + cost)
                        {
                            dist[nx][ny] = dist[i][j] + cost;
                        }
                    }
                    else 
                    {
                        for (int k = 0; k < 4; k++)
                        {
                            nx = i + dx[k]; ny = j + dy[k];
                            if(nx < 0 || ny < 0 || nx >= w || ny >= h || graveYard[nx][ny] == stone) continue;
                            if(dist[nx][ny] > dist[i][j] + 1)
                            {
                                dist[nx][ny] = dist[i][j] + 1;
                            }
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if(dist[i][j] != INF)
            {
                if(i == w - 1 && j == h - 1) continue;
                if(graveYard[i][j] == stone) continue;
                else if(graveYard[i][j] == hole)
                {
                    dest = destination[{i, j}];
                    cost = dest.first; nx = dest.second.first; ny = dest.second.second;
                    if(dist[nx][ny] > dist[i][j] + cost && dist[nx][ny] != INF)
                    {
                        cout << "Never\n";
                        return;
                    }
                }
                else 
                {
                    for (int k = 0; k < 4; k++)
                    {
                        nx = i + dx[k]; ny = j + dy[k];
                        if(nx < 0 || ny < 0 || nx >= w || ny >= h || graveYard[nx][ny] == stone) continue;
                        if(dist[nx][ny] > dist[i][j] + 1 && dist[nx][ny] != INF)
                        {
                            cout << "Never\n";
                            return;
                        }
                    }
                }
            }
        }
    }

    if(dist[w - 1][h - 1] == INF)
    {
        cout << "Impossible\n";
        return;
    }

    cout << dist[w - 1][h - 1] << "\n";
}