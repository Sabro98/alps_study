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
//참가자 명단
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 21
#define INF 0x7FFFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K;
//const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

vector<string> arr[11];
int main()
{
    fastio;
    cin >> N >> M;
    string name;
    int c;
    int maxregister = 501;
    while (maxregister--)
    {
        cin >> c >> name;
        if (c == 0)
            break;
        if (arr[c].size() < M)
        {
            arr[c].push_back(name);
        }
    }
    f1for(i, N)
    {
        sort(arr[i].begin(), arr[i].end());
    }
    for (int i = 1; i <= N; i += 2)
    {
        for (string s : arr[i])
        {
            cout << i << " " << s << endl;
        }
    }
    for (int i = 2; i <= N; i += 2)
    {
        for (string s : arr[i])
        {
            cout << i << " " << s << endl;
        }
    }
}