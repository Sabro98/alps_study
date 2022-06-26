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
#include <unordered_map>
#include <string.h>
#include <random>
#include <queue>
//나무 심기
using namespace std;
#define ffor(i, x) for (int(i) = 0; (i) < (x); ++(i))
#define f1for(i, x) for (int(i) = 1; (i) <= (x); ++(i))
#define X second
#define Y first
#define coutln(x) cout << x << '\n'
#define endl '\n'
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define MAXSIZE 200002
#define MOD 1000000007ll
#define INF 0x7FFFFFFF
typedef long long int lli;
typedef pair<int, int> pii;
int N, M, T, K, Q;

lli rankingTree[4 * MAXSIZE]; //합
lli lengthTree[4 * MAXSIZE];  //순위를 위한트리

lli sum(lli *tree, int start, int end, int node, int left, int right)
{
    if (end < left || right < start) //범위밖
    {
        return 0;
    }
    if (left <= start && end <= right) //범위안이라면 자신을 리턴
    {
        return tree[node];
    }
    //범위에 걸치면
    int mid = (start + end) / 2;
    return sum(tree, start, mid, node * 2, left, right) + sum(tree, mid + 1, end, node * 2 + 1, left, right);
}

void update(lli *tree, int start, int end, int node, int idx, lli diff)
{
    if (!(start <= idx && idx <= end))
        return;

    tree[node] += diff;
    if (start == end)
        return; //트리의 밑바닥

    int mid = (start + end) / 2;
    update(tree, start, mid, node * 2, idx, diff);
    update(tree, mid + 1, end, node * 2 + 1, idx, diff);
}

int findRanking(lli *tree, int node, int ranking, int start, int end)
{
    if (start == end) //밑바닥임
        return start;

    int mid = (start + end) / 2;
    if (tree[node * 2] < ranking)
    { //오른쪽에서 찾아야함
        return findRanking(tree, node * 2 + 1, ranking - tree[node * 2], mid + 1, end);
    }
    else
    { //왼쪽으로가야함
        return findRanking(tree, node * 2, ranking, start, mid);
    }
}

// 현재 심을 나무길이가 k일때
// k * (k보다작은나무개수) - (k보다작은나무들의길이합)로서 구할수있다 (k보다큰나무는 부호가 반대)
//k보다작은 나무개수는 rankingArray[길이]+=1 해가며 개수를 저장하여 구한다
//k보다작은 나무들의 길이합은 lengthArray[길이] +=길이를 더해가며 길이*개수를 저장하게한다
//이러면 sum(0,길이-1),sum(길이+1,MAXSIZE)로 작은놈들 큰놈들 길이합을 구할수있다
int main()
{
    fastio;

    cin >> N;
    memset(rankingTree, 0, sizeof(rankingTree));
    memset(lengthTree, 0, sizeof(lengthTree));

    lli k;
    lli answer = 1;
    lli lowerSum, upperSum, lowerCount, upperCount;
    lli cost;
    //첫번째 나무 심기
    cin >> k;
    k++;
    update(lengthTree, 1, MAXSIZE, 1, k, k);
    update(rankingTree, 1, MAXSIZE, 1, k, 1);
    ffor(i, N - 1)
    {
        cin >> k;
        k++;                                                      //index문제 해결
        lowerSum = sum(lengthTree, 1, MAXSIZE, 1, 1, k - 1);      //(k보다작은나무들의길이합)
        upperSum = sum(lengthTree, 1, MAXSIZE, 1, k, MAXSIZE);    //(k보다큰나무들의길이합)
        lowerCount = sum(rankingTree, 1, MAXSIZE, 1, 1, k - 1);   //(k보다작은나무들의개수)
        upperCount = sum(rankingTree, 1, MAXSIZE, 1, k, MAXSIZE); //(k보다큰나무들의개수)
        cost = ((k * lowerCount - lowerSum) + (upperSum - k * upperCount)) % MOD;
        answer = answer * cost % MOD;
        update(lengthTree, 1, MAXSIZE, 1, k, k);
        update(rankingTree, 1, MAXSIZE, 1, k, 1);
    }
    cout << answer;
}