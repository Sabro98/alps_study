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
#include <unordered_set>
#include <string.h>
#include <random>
#include <queue>
//도전 숫자왕
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 21
#define INF 0x7FFFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K;
//const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
//const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

vector<int> arr(20);
unordered_set<int> hset;
int main()
{
    fastio;
    cin >> N;
    int sum = 0;
    ffor(i, N)
    {
        cin >> arr[i];
        sum += arr[i];
    }
    int all = 1 << N;

    for (int num = 1; num < all; num++)
    {
        int tempsum = 0;
        int c = num;
        for (int i = 0; i < N; i++)
        {
            if ((c & 1) == 1)
            {
                tempsum += arr[i];
            }
            c = c >> 1;
        }
        hset.insert(tempsum);
    }
    cout << sum - hset.size();
}