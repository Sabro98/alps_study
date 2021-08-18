#include <iostream>
using namespace std;

int ccw(pair<int, int> a, pair<int, int> b, pair<int, int> c)
{
    long long temp = 1l * a.first * b.second + 1l * b.first * c.second + 1l * c.first * a.second;
    temp -= 1l * b.first * a.second + 1l * c.first * b.second + 1l * a.first * c.second;
    if(temp > 0) return 1;
    else if(temp < 0) return -1;
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    pair<int, int> a1, b1, a2, b2;
    a1 = {x1, y1};
    a2 = {x2, y2};
    b1 = {x3, y3};
    b2 = {x4, y4};

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
            if(a2 < b1 || b2 < a1)
            {
                cout << 0 << "\n";
                return 0;
            }
        }
        cout << 1 << "\n";
    }
    else cout << 0 << "\n";
}