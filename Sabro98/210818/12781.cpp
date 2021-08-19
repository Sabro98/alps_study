#include <algorithm>
#include <iostream>

using namespace std;
typedef pair<int, int> P;

int ccw(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
    long long op = 1l * a.first * b.second + 1l * b.first * c.second + 1l * c.first * a.second;
    op -= (1l * a.second * b.first + 1l * b.second * c.first + 1l * c.second * a.first);
    if (op > 0) return 1; // 양수라면 반시계 방향
    else if (op == 0) return 0; // 0이라면 평행
    else return -1; // 음수라면 시계 방향
}

bool isCrossed(pair<P, P> A, pair<P, P> B){
    P a, b, c, d;
    a = A.first, b = A.second, c = B.first, d = B.second;
    int first = ccw(a, b, c) * ccw(a, b, d);
    int second = ccw(c, d, a) * ccw(c, d, b);

    return first < 0 && second < 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    pair<P, P> a, b;

    cin >> a.first.first >> a.first.second >> a.second.first >> a.second.second;
    cin >> b.first.first >> b.first.second >> b.second.first >> b.second.second;

    cout << isCrossed(a, b);

    return 0;
}