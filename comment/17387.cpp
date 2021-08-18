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
//선분 교차 2
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 100001
#define INF 0x7FFFFFFF
typedef long long int lli;
typedef pair<lli, lli> plli;
int N, M, T, K;
//const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

int ccw(pair<lli, lli> a, pair<lli, lli> b, pair<lli, lli> c)
{
    long long int op = a.first * b.second + b.first * c.second + c.first * a.second;
    op -= (a.second * b.first + b.second * c.first + c.second * a.first);
    if (op > 0)
        return 1; // 양수라면 반시계 방향
    else if (op == 0)
        return 0; // 0이라면 평행
    else
        return -1; // 음수라면 시계 방향
}

int main()
{
    fastio;

    plli a1, a2, b1, b2;
    cin >> a1.first >> a1.second >> a2.first >> a2.second;
    cin >> b1.first >> b1.second >> b2.first >> b2.second;
    if (a2 < a1)
        swap(a1, a2);
    if (b2 < b1)
        swap(b1, b2);
    int aab, bba;
    aab = ccw(a1, a2, b1) * ccw(a1, a2, b2);
    bba = ccw(b1, b2, a1) * ccw(b1, b2, a2);
    if (aab == 0 && bba == 0)
    {
        if (a1 <= b2 && b1 <= a2)
        {
            cout << 1;
        }
        else
        {
            cout << 0;
        }
    }
    else if (aab <= 0 && bba <= 0)
    {
        cout << 1;
    }
    else
    {
        cout << 0;
    }
}