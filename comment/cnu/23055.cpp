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
//공사장 표지판
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

vector<vector<char>> arr(MAXSIZE, vector<char>(MAXSIZE, ' '));
int main()
{
    fastio;
    cin >> N;
    ffor(i, N) //모서리
    {
        arr[0][i] = '*';
        arr[N - 1][i] = '*';
        arr[i][0] = '*';
        arr[i][N - 1] = '*';
    }
    ffor(i, N)
    { // 대각
        arr[i][i] = '*';
        arr[i][N - 1 - i] = '*';
    }

    ffor(y, N)
    {
        ffor(x, N)
        {
            cout << arr[y][x];
        }
        cout << endl;
    }
}