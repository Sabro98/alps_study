#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> P;

const int INF = 0x3f3f3f3f;
int N, M, dist[101][101], label[101];
vector<int> G[101];
bool visited[101];

void dfs(int x, int l)
{
    label[x] = l;
    visited[x] = true;
    for (int g : G[x])
    {
        if (visited[g])
            continue;
        dfs(g, l);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            dist[i][j] = INF;
        }
    }

    for (int i = 0, u, v; i < M; i++)
    {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
        dist[u][v] = 1;
        dist[v][u] = 1;
    }

    for (int i = 1; i <= N; i++)
        dist[i][i] = 0;

    for (int k = 1; k <= N; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    int l = 1;
    for (int i = 1; i <= N; i++)
    {
        if (visited[i])
            continue;
        dfs(i, l++);
    }

    vector<int> answer;
    for (int k = 1; k < l; k++)
    {
        int minVal = 1e9, ans = -1;

        for (int i = 1; i <= N; i++)
        {
            if (label[i] != k)
                continue;
            int val = 0;

            for (int j = 1; j <= N; j++)
            {
                if (i == j)
                    continue;
                if (label[j] != k)
                    continue;
                val = max(val, dist[i][j]);
            }

            if (minVal > val)
            {
                minVal = val;
                ans = i;
            }
        }
        answer.push_back(ans);
    }

    sort(answer.begin(), answer.end());
    cout << answer.size() << '\n';
    for (int a : answer)
        cout << a << '\n';

    return 0;
}