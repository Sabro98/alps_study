#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef struct
{
    pair<int, int> p1, p2;
}line;

vector<line> rect;

double dist(pair<int, int> a, pair<int, int> b)
{
    return sqrt(pow(a.first - b.first, 2.0) + pow(a.second - b.second, 2.0));
}

int ccw(pair<int, int> a, pair<int, int> b, pair<int, int> c)
{
    long long temp = 1l * a.first * b.second + 1l * b.first * c.second + 1l * c.first * a.second;
    temp -= 1l * b.first * a.second + 1l * c.first * b.second + 1l * a.first * c.second;
    if(temp > 0) return 1;
    else if(temp < 0) return -1;
    return 0;
}

bool hasIntersection(line l1, line l2)
{
    pair<int, int> a1, b1, a2, b2;
    a1 = {l1.p1.first, l1.p1.second};
    a2 = {l1.p2.first, l1.p2.second};
    b1 = {l2.p1.first, l2.p1.second};
    b2 = {l2.p2.first, l2.p2.second};

    int aab1 = ccw(a1, a2, b1), aab2 = ccw(a1, a2, b2), bba1 = ccw(b1, b2, a1), bba2 = ccw(b1, b2, a2);
    
    // 두개 각각 다른 clock wise
    if(aab1 * aab2 <= 0 && bba1 * bba2 <= 0)
    {
        // 둘 다 같은 직선 상에 존재
        if(aab1 == 0 && aab2 == 0)
        {
            if(a1 > a2) swap(a1, a2);
            if(b1 > b2) swap(b1, b2);
            // 직선 a1 ~ a2 가 b1 ~ b2 앞에 있거나 뒤에 있으면 교차 X
            if(a2 < b1 || b2 < a1) return false;
        }
        return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    pair<int, int> a, b;
    int x1, y1, x2, y2, x3, y3, x4, y4;
    int sega[4], segb[4];
    line seg;
    
    for (int tc = 0; tc < t; tc++)
    {
        rect.clear();
        cin >> a.first >> a.second >> b.first >> b.second >> x1 >> y1 >> x3 >> y3;
        seg = {a, b};
        // init Rectangle
        if(x1 > x3 && y1 > y3)
        {
            x2 = x1; y2 = y3;
            x4 = x3; y4 = y1;
        }
        else if(x1 > x3 && y1 < y3)
        {
            x2 = x3; y2 = y1;
            x4 = x1; y4 = y3;
        }
        else if(x1 < x3 && y1 > y3)
        {
            x2 = x3; y2 = y1;
            x4 = x1; y4 = y3;
        }
        else
        {
            x2 = x1; y2 = y3;
            x4 = x3; y4 = y1;
        }

        rect.push_back({{x1, y1}, {x2, y2}});
        rect.push_back({{x2, y2}, {x3, y3}});
        rect.push_back({{x3, y3}, {x4, y4}});
        rect.push_back({{x4, y4}, {x1, y1}});

        for (int i = 0; i < 4; i++)
        {
            sega[i] = ccw(rect[i].p1, rect[i].p2, a);
            segb[i] = ccw(rect[i].p1, rect[i].p2, b);
        }

        // 선분이 아무 직사각형 변과 교차할때
        if(hasIntersection(rect[0], seg) || hasIntersection(rect[1], seg) || hasIntersection(rect[2], seg) || hasIntersection(rect[3], seg))
        {
            cout << "T\n";
        }
        // 선분의 양 끝점이 모두 직사각형 내부에 존재할 때
        else if(sega[0] <= 0 && segb[0] <= 0 && sega[1] <= 0 && segb[1] <= 0 && sega[2] <= 0 && segb[2] <= 0 && sega[3] <= 0 && segb[3] <= 0)
        {
            cout << "T\n";
        }
        else cout << "F\n";
    }
}