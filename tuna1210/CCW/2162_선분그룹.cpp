// Unionfind & CCW
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

typedef struct
{
    pair<int, int> p1, p2;
}line;

vector<line> seg;
vector<int> uf(3001, -1);

int find(int u)
{
    if(uf[u] < 0) return u;
    uf[u] = find(uf[u]);
    return uf[u];
}

bool merge(int u, int v)
{
    u = find(u);
    v = find(v);
    if(u == v) return false;
    uf[u] += uf[v];
    uf[v] = u;
    return true;
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
    
    int n;
    cin >> n;

    int x1, y1, x2, y2;
    for (int i = 0; i < n; i++)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        seg.push_back({{x1, y1}, {x2, y2}});
    }
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(i == j) continue;
            if(hasIntersection(seg[i], seg[j])) merge(i, j);
        }
    }

    int cnt = 0, min = 1e9;
    for (int i = 0; i < n; i++)
    {
        if(min > uf[i]) min = uf[i];
        if(uf[i] < 0) cnt++;
    }
    
    cout << cnt << "\n";
    cout << min * (-1) << "\n";
}