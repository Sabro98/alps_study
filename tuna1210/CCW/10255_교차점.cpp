#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef struct
{
    pair<int, int> p1, p2;
}line;

vector<line> rect;

int ccw(pair<int, int> a, pair<int, int> b, pair<int, int> c)
{
    long long temp = 1l * a.first * b.second + 1l * b.first * c.second + 1l * c.first * a.second;
    temp -= 1l * b.first * a.second + 1l * c.first * b.second + 1l * a.first * c.second;
    if(temp > 0) return 1;
    else if(temp < 0) return -1;
    return 0;
}

int findIntersection(line l1, line l2)
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
            if(a2 < b1 || b2 < a1) return -1;
            //선분의 끝과 접할때 (접점 수 1개)
            else if(a2 == b1 || b2 == a1) return 0;
            // 선분이 겹쳐질 때 (접점 수 무한대)
            else return 3;
        }
        // 선분의 중간과 접할때 (직사각형 한 변에 선분이 접함)
        if(bba1 == 0 || bba2 == 0)
        {
            return 1;
        }
        if(aab1 == 0 || aab2 == 0)
        {
            return 0;
        }
        // 교차할때
        return 2;
    }
    // 안 만남
    return -1;
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

        cin >> x1 >> y1 >> x3 >> y3 >> a.first >> a.second >> b.first >> b.second;
        seg = {a, b};
        if(x1 == x3 && y1 == y3)
        {
            cout << 1 << "\n";
            continue;
        }

        // init Rectangle
        x2 = x3; y2 = y1;
        x4 = x1; y4 = y3;
        rect.push_back({{x1, y1}, {x2, y2}});
        rect.push_back({{x2, y2}, {x3, y3}});
        rect.push_back({{x3, y3}, {x4, y4}});
        rect.push_back({{x4, y4}, {x1, y1}});
        
        int intersection[4];
        int inf = 0, cross = 0, midTangent = 0, endTangent = 0, nointer = 0;
        for (int i = 0; i < 4; i++)
        {
            intersection[i] = findIntersection(rect[i], seg);
            switch(intersection[i])
            {
                case 3:
                inf++;
                break;
                case 2:
                cross++;
                break;
                case 1:
                midTangent++;
                break;
                case 0:
                endTangent++;
                break;
                case -1:
                nointer++;
                break;
            }
        }

        // 겹치는 변이 있을때  => 무한개
        if(inf > 0)
        {
            cout << "4\n";
        }
        // 교차점도, 접점도 없을 때 => 교점이 0개
        else if(cross + midTangent + endTangent == 0)
        {
            cout << "0\n";
        }
        // 점 하나 짜리
        else if((cross == 1 && midTangent + endTangent == 0) ||
                (cross == 0 && midTangent == 2 && endTangent != 1) ||
                (cross == 0 && midTangent <= 1 && endTangent == 1))
        {
            cout << "1\n";
        }
        else
        {
            cout << "2\n";
        }
    }
    
}