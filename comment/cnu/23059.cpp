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
//리그 오브 레게노
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 400000
#define INF 123456789
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K;
const int dx[] = {-1, 0, 1, 0, -1, 1, 1, -1};
const int dy[] = {0, 1, 0, -1, 1, 1, -1, -1};

vector<int> G[MAXSIZE];
vector<int> deg(MAXSIZE, 0);
deque<string> Q;
priority_queue<string, vector<string>, greater<string>> pq;
unordered_map<int, string> smap;
unordered_map<string, int> imap;
vector<string> ans;
void bfs()
{
    while (!Q.empty())
    {
        int qsize = Q.size();
        ffor(i, qsize)
        {

            string cur = Q.front();
            Q.pop_front();
            pq.push(cur);

            for (int next : G[imap[cur]])
            {
                deg[next]--;
                if (!deg[next])
                {
                    Q.push_back(smap[next]);
                }
            }
        }
        while (!pq.empty())
        {
            ans.push_back(pq.top());
            pq.pop();
        }
    }
}

int main()
{
    fastio;
    cin >> N;
    int u, v;
    string str1, str2;
    int num = 0;
    ffor(i, N)
    {
        cin >> str1 >> str2;
        if (imap.find(str1) != imap.end())
        {
            u = imap[str1];
        }
        else
        {
            u = num;
            imap[str1] = u;
            smap[u] = str1;
            num++;
        }

        if (imap.find(str2) != imap.end())
        {
            v = imap[str2];
        }
        else
        {
            v = num;
            imap[str2] = v;
            smap[v] = str2;
            num++;
        }

        G[u].push_back(v);
        deg[v]++;
    }
    ffor(i, num)
    {
        if (!deg[i])
        {
            Q.push_back(smap[i]);
        }
    }
    bfs();
    if (ans.size() == num)
    {
        for (string s : ans)
        {
            cout << s << endl;
        }
    }
    else
        cout << -1;
}