#include <iostream>
using namespace std;

int ccw(pair<int, int> a, pair<int, int> b, pair<int, int> c)
{
    long long temp = a.first * b.second + b.first * c.second + c.first * a.second;
    temp -= b.first * a.second + c.first * b.second + a.first * c.second;
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

    // 두개 각각 다른 clock wise (선이 맞닿아 있는 경우는 제외)
    if(aab1 * aab2 < 0 && bba1 * bba2 < 0) cout << 1 << "\n";
    else cout << 0 << "\n";
}