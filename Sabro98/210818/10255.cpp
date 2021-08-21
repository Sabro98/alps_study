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

bool isCrossOver(pair<P, P> A, pair<P, P> B){
    P a, b, c, d;
    a = A.first, b = A.second, c = B.first, d = B.second;
    int first = ccw(a, b, c);
    int second = ccw(a, b, d);
    int third= ccw(c, d, a);
    int fourth = ccw(c, d, b);

    if(first == 0 && second == 0 && third == 0 && fourth == 0){
        if(a > b) swap(a, b);
        if(c > d) swap(c, d);
        if(a > c){
            swap(a, c);
            swap(b, d);
        }
        if(a < d && c < b) return true;
        if(a == c) return true;
        if(b == d) return true;
    }
    return false;
}

int isCrossed(pair<P, P> A, pair<P, P> B){
    P a, b, c, d;
    a = A.first, b = A.second, c = B.first, d = B.second;
    int first = ccw(a, b, c) * ccw(a, b, d);
    int second = ccw(c, d, a) * ccw(c, d, b);

    if(first == 0 && second == 0){
        if(a > b) swap(a, b);
        if(c > d) swap(c, d);
        return (a <= d && c <= b); // 무한 교차
    }

    return first <= 0 && second <= 0; //평범하게 교차
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while(T--){
        int xmin, xmax, ymin, ymax;
        pair<P, P> a;
        vector<pair<P, P>> lines;

        cin >> xmin >> ymin >> xmax >> ymax;
        cin >> a.first.first >> a.first.second >> a.second.first >> a.second.second;
        lines.push_back({{xmin, ymin}, {xmin, ymax}});
        lines.push_back({{xmin, ymin}, {xmax, ymin}});
        lines.push_back({{xmax, ymax}, {xmin, ymax}});
        lines.push_back({{xmax, ymax}, {xmax, ymin}});

        int ans = 0;
        bool tmp = false;
        for(auto line : lines){
            tmp |= isCrossOver(a, line);
        }
        if(tmp){
            cout << 4 << '\n';
            continue;
        }
        //두 선분 동시에 교차 먼저 탐색

        bool flag[4] = {false, };
        if(a.first > a.second) swap(a.first, a.second);
        if(ccw(a.first, a.second, {xmin, ymin}) == 0){
            auto c = pair<int, int>(xmin, ymin);
            if(a.first <= c && c <= a.second){
                ans++;
                flag[0] = true;
                flag[1] = true;
            }
        }
        if(ccw(a.first, a.second, {xmin, ymax}) == 0){
            auto c = pair<int, int>(xmin, ymax);
            if(a.first <= c && c <= a.second){
                ans++;
                flag[0] = true;
                flag[2] = true;
            }
        }
        if(ccw(a.first, a.second, {xmax, ymin}) == 0){
            auto c = pair<int, int>(xmax, ymin);
            if(a.first <= c && c <= a.second){
                ans++;
                flag[1] = true;
                flag[3] = true;
            }
        }
        if(ccw(a.first, a.second, {xmax, ymax}) == 0){
            auto c = pair<int, int>(xmax, ymax);
            if(a.first <= c && c <= a.second){
                ans++;
                flag[2] = true;
                flag[3] = true;
            }
        }

        for(int i=0; i<4; i++){
            auto line = lines[i];
            if(flag[i]) continue;
            if(isCrossed(a, line)) ans++;
        }
        cout << ans << '\n';
    }

    return 0;
}