#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef pair<int, int> P;

int ccw(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
    long long op = 1l * a.first * b.second + 1l * b.first * c.second + 1l * c.first * a.second;
    op -= (1l * a.second * b.first + 1l * b.second * c.first + 1l * c.second * a.first);
    if (op > 0) return 1; // 양수라면 반시계 방향
    else if (op == 0) return 0; // 0이라면 평행
    else return -1; // 음수라면 시계 방향
}

int isCrossed(pair<P, P> A, pair<P, P> B){ //A -> 주어진 선분, B -> 사각형의 한 변
    P a, b, c, d;
    a = A.first, b = A.second, c = B.first, d = B.second;
    int first = ccw(a, b, c) * ccw(a, b, d);
    int second = ccw(c, d, a) * ccw(c, d, b);


    if(first == 0 && second == 0){
        if(a > b) swap(a, b);
        if(c > d) swap(c, d);
        if(a < d && c < b) return 4; // 무한 교차
        else if(a == d || b == c) return -1; // 모서리에 교차   __/
        else return 0;
    }

    if(first == 0 && second < 0) return -1; // 모서리에 교차  /--

    if(first < 0 && second <= 0) return 1; //평범하게 교차

    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while(T--){
        int xmin, xmax, ymin, ymax;
        pair<P, P> a, b;
        vector<pair<P, P>> lines;
        
        cin >> xmin >> ymin >> xmax >> ymax;
        cin >> a.first.first >> a.first.second >> a.second.first >> a.second.second;
        lines.push_back({{xmin, ymin}, {xmin, ymax}});
        lines.push_back({{xmin, ymin}, {xmax, ymin}});
        lines.push_back({{xmax, ymax}, {xmin, ymax}});
        lines.push_back({{xmax, ymax}, {xmax, ymin}});
        
        int ans = 0;
        for (auto line : lines){
            int res = isCrossed(a, line);
            cout << res << ' ';
            if(res == -1) {
                ans = 1;
                break;
            }

            if(res == 4) {
                ans = 4;
                break;
            }
            
            ans += res;
            
        }
        cout << '\n' << ans << '\n';
    }

    return 0;
}