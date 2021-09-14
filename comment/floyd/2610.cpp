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
//회의준비
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 101
#define INF 0x7FFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K;
//const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };
int uf[MAXSIZE]; // <- memset(uf, -1, sizeof(uf)); 등의 연산을 사용해 음수로 초기화 필요

// 경로 압축을 하면서 부모를 find
int find(int a)
{
    if (uf[a] < 0)
        return a;
    uf[a] = find(uf[a]);
    return uf[a];
}

bool merge(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a == b)
        return false;
    uf[a] += uf[b]; //<- uf가 음수일 때, -|uf|를 집합의 크기로 봐도 무방, 합치는 경우에는 둘의 크기를 더해줌
    uf[b] = a;
    return true;
}

vector<vector<int>> dist(MAXSIZE, vector<int>(MAXSIZE, INF));
vector<vector<int>> nextpath(MAXSIZE, vector<int>(MAXSIZE, 0));
vector<pii> G[MAXSIZE];
void floyd()
{
    //1-pass
    for (int i = 1; i <= N; i++)
    {
        for (auto g : G[i])
        {
            dist[i][g.first] = min(dist[i][g.first], g.second);
            nextpath[i][g.first] = g.first;
        }
    }
    for (int i = 1; i <= N; i++)
        dist[i][i] = 0;

    //n-pass if {i -> k -> j} < {i -> j}, update
    for (int k = 1; k <= N; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nextpath[i][j] = nextpath[i][k];
                }
            }
        }
    }
}
int main()
{
    fastio;
    int u, v, w;
    memset(uf, -1, sizeof(uf));
    cin >> N >> M;
    ffor(i, M)
    {
        cin >> u >> v;
        G[u].push_back({v, 1});
        G[v].push_back({u, 1});
        merge(u, v);
    }
    floyd();

    vector<pii> timesum;
    f1for(i, N)
    {
        int maxval = 0;

        f1for(j, N)
        {

            if (dist[i][j] != INF)
            {
                // cout << dist[i][j] << " ";
                maxval = max(maxval, dist[i][j]);
            }
            else
            {
                // cout << 0 << " ";
            }
        }
        // cout << maxval << endl;
        timesum.push_back({maxval, i});
    }
    sort(timesum.begin(), timesum.end());

    vector<bool> visited(MAXSIZE, false);
    vector<int> answer;
    for (pii t : timesum)
    {
        auto [sum, index] = t;
        if (visited[find(index)])
        {
            continue;
        }
        else
        {
            visited[find(index)] = true;
            answer.push_back(index);
        }
    }
    cout << answer.size() << endl;
    sort(answer.begin(), answer.end());
    for (int i : answer)
    {
        cout << i << endl;
    }
}