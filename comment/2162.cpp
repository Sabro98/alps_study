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
//선분 그룹
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 3001
#define INF 0x7FFFFFFF
typedef long long int lli;
typedef pair<lli, lli> plli;
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

vector<pair<plli, plli>> lines(MAXSIZE);
int main()
{
    fastio;
    memset(uf, -1, sizeof(uf));
    cin >> N;
    plli p1, p2, other1, other2;
    int flag1, flag2;
    ffor(i, N)
    {
        cin >> p1.first >> p1.second >> p2.first >> p2.second;
        if (p2 < p1)
        {
            swap(p1, p2);
        }

        if (i >= 1)
        {
            ffor(j, i)
            { //현재까지 입력받은 모든점과 교차하는지 판별 하나라도 교차하면 union
                other1 = lines[j].first;
                other2 = lines[j].second;

                flag1 = ccw(p1, p2, other1) * ccw(p1, p2, other2);
                flag2 = ccw(other1, other2, p1) * ccw(other1, other2, p2);
                if (flag1 == 0 && flag2 == 0) //일직선
                {
                    if (p1 <= other2 && other1 <= p2) //일직선으로 겹침
                    {
                        merge(i, j);
                    }
                }
                else if (flag1 <= 0 && flag2 <= 0) //ㄱ이나ㄴ같은 교차포함
                {
                    merge(i, j);
                }
            }
        }
        lines[i] = {p1, p2};
    }
    int groupCount = 0;
    int lineCount = 0;
    ffor(i, N)
    {
        if (uf[i] < 0)
        {
            groupCount++;
            lineCount = min(lineCount, uf[i]);
        }
    }
    cout << groupCount << endl
         << -lineCount;
}