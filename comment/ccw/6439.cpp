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
//교차
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X first
#define Y second
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
bool intersected(plli p1, plli p2, plli other1, plli other2)
{

    if (p2 < p1)
    {
        swap(p1, p2);
    }
    if (other2 < other1)
    {
        swap(other1, other2);
    }
    int flag1 = ccw(p1, p2, other1) * ccw(p1, p2, other2);
    int flag2 = ccw(other1, other2, p1) * ccw(other1, other2, p2);
    if (flag1 == 0 && flag2 == 0) //일직선
    {
        if (p1 <= other2 && other1 <= p2) //일직선으로 겹침
        {
            return true;
        }
    }
    else if (flag1 <= 0 && flag2 <= 0) //ㄱ이나ㄴ같은 교차포함
    {
        return true;
    }
    return false;
}
bool inner(plli p1, plli p2, plli l1, plli l2)
{ //직사각형 선분내부판별
    lli minX, minY, maxX, maxY;

    //이거 뭔가 멍청하게 푸는듯한?
    minX = min(p1.X, p2.X);
    minY = min(p1.Y, p2.Y);
    maxX = max(p1.X, p2.X);
    maxY = max(p1.Y, p2.Y);
    if (minX < l1.X && l1.X < maxX &&
        minX < l2.X && l2.X < maxX &&
        minY < l1.Y && l1.Y < maxY &&
        minY < l2.Y && l2.Y < maxY)
        return true;

    return false;
}

int main()
{
    fastio;

    cin >> N;
    plli p1, p2, other1, other2, l1, l2;

    vector<pair<plli, plli>> lines; //직사각형의 선분4개
    while (N--)
    {
        lines.clear();

        cin >> l1.X >> l1.Y >> l2.X >> l2.Y; //선분

        cin >> p1.X >> p1.Y >> p2.X >> p2.Y; //직사각형
        //o1 p2
        //p1 o2 형태의 직사각형

        if (inner(p1, p2, l1, l2))
        { //선분의 두 점이 사각형 내부에 있을 때
            cout << 'T' << endl;
            continue;
        }
        other1.X = p1.X;
        other1.Y = p2.Y;
        other2.X = p2.X;
        other2.Y = p1.Y;
        lines.push_back({p1, other1});
        lines.push_back({p1, other2});
        lines.push_back({other1, p2});
        lines.push_back({other2, p2});

        bool flag = false;
        for (auto line : lines)
        {
            if (intersected(line.first, line.second, l1, l2))
            {
                flag = true;
            }
        }
        if (flag)
            cout << 'T' << endl;
        else
            cout << 'F' << endl;
    }
}