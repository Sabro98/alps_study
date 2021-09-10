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
//교차점
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
int intersected(plli p1, plli p2, plli other1, plli other2)
{

    if (p2 < p1)
    {
        swap(p1, p2);
    }
    if (other2 < other1)
    {
        swap(other1, other2);
    }
    int ppo1 = ccw(p1, p2, other1);
    int ppo2 = ccw(p1, p2, other2);
    int flag1 = ppo1 * ppo2;
    int oop1 = ccw(other1, other2, p1);
    int oop2 = ccw(other1, other2, p2);
    int flag2 = oop1 * oop2;
    if (oop1 == 0 && oop2 == 0 && ppo1 == 0 && ppo2 == 0) //일직선
    {
        if (p1 < other2 && other1 < p2) //일직선으로 겹침
        {
            return 4;
        }
    }
    else if (flag1 <= 0 && flag2 <= 0) //ㄱ이나ㄴ같은 교차포함,일직선으로 연결되는 교차 포함
    {
        return 1;
    }
    return 0;
}

int main()
{
    fastio;

    cin >> N;

    plli l1, l2, topleft, botright, botleft, topright;
    vector<pair<plli, plli>> lines; //직사각형의 선분4개
    vector<pair<lli, lli>> points;  //직사각형의 점4개
    while (N--)
    {
        lines.clear();
        points.clear();
        cin >> botleft.X >> botleft.Y >> topright.X >> topright.Y;
        cin >> l1.X >> l1.Y >> l2.X >> l2.Y;

        topleft.X = botleft.X;
        topleft.Y = topright.Y;
        botright.X = topright.X;
        botright.Y = botleft.Y;
        lines.push_back({botleft, botright});
        lines.push_back({topleft, topright});
        lines.push_back({botleft, topleft});
        lines.push_back({botright, topright});
        points.push_back(botleft);
        points.push_back(botright);
        points.push_back(topleft);
        points.push_back(topright);

        bool flag = false;
        bool one = false;
        int sum = 0;
        //교점이 0개면 sum==0
        //교점이 1개면 sum이1또는2
        //교점이 2개면 sum이2이상 //sum이 2일때 검증필요
        //일직선은 ret에서 검출

        for (auto line : lines)
        {
            int ret = intersected(line.first, line.second, l1, l2);
            // cout << ret << " ";
            if (ret == 1)
            {
                sum++;
            }
            if (ret == 4)
            { //일직선인경우
                flag = true;
            }
        }
        if (flag)
        {
            cout << 4 << endl;
            continue;
        }
        if (sum == 0)
        {
            cout << 0 << endl;
        }
        else if (sum == 1)
        {
            cout << 1 << endl;
        }
        else if (sum >= 3)
        {
            cout << 2 << endl;
        }
        else
        { //sum==2
            for (auto point : points)
            {
                if (ccw(l1, l2, point) == 0)
                { //꼭지점에서 교점이 발생하는지 확인
                    one = true;
                }
            }
            if (one)
                cout << 1 << endl;
            else
            {
                cout << 2 << endl;
            }
        }
    }
}