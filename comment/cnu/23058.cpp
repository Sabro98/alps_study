#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <set>
#include <cmath>
#include <map>
#include <deque>
#include <utility>
#include <list>
#include <unordered_map>
#include <string.h>
#include <random>
#include <queue>
//뒤집기게임
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 8
#define INF 0x7FFFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K;
//const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

vector<vector<int>> originalMap(MAXSIZE, vector<int>(MAXSIZE));

int mapCount[2];
//1~8행 1~8열 총 16라인 뒤집기연산 2^16
//일단 뭘 뒤집을지 정했으면 그뒤는 한번뒤집기만 사용하므로 0의갯수 또는 1의갯수를 세면됨

int main()
{
    fastio;

    cin >> N;

    ffor(i, N) ffor(j, N)
    {
        cin >> originalMap[i][j];
    }

    int sz = 1 << N;
    int ans = INF;
    ffor(flipX, sz) ffor(flipY, sz)
    {

        auto mapCopy = originalMap;
        int flipCount = __builtin_popcount(flipX) + __builtin_popcount(flipY);

        for (int i = flipY, y = 0; i > 0; i = i >> 1, y++)
        {
            if (i & 1) //가장 오른쪽 비트가1이면
            {
                ffor(x, N)
                { //뒤집기
                    mapCopy[y][x] = !mapCopy[y][x];
                }
            }
        }
        for (int i = flipX, x = 0; i > 0; i = i >> 1, x++)
        {
            if (i & 1) //가장 오른쪽 비트가1이면
            {
                ffor(y, N)
                { //뒤집기
                    mapCopy[y][x] = !mapCopy[y][x];
                }
            }
        }
        mapCount[0] = 0;
        mapCount[1] = 0;
        ffor(x, N) ffor(y, N)
        {
            mapCount[mapCopy[y][x]]++;
        }

        ans = min(ans, flipCount + min(mapCount[0], mapCount[1])); //뒤집기횟수+남은 숫자중 적은것
    }
    cout << ans;
}