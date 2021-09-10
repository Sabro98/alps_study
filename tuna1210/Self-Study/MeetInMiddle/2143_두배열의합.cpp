#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int t;
int aSize, bSize;
vector<int> A, B;
vector<int> pSumA, pSumB;
vector<int> subArrA, subArrB;

int getPartSum(int from, int to, vector<int>& pSum)
{
    return pSum[to] - pSum[from - 1];
}

void setSumOfSubArr(int size, vector<int> &subArr, vector<int> &pSum)
{
    for (int i = 1; i <= size; i++)
    {
        for (int j = i; j <= size; j++)
        {
            subArr.push_back(getPartSum(i, j, pSum));
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> t;

    cin >> aSize;
    A.resize(aSize + 1);
    pSumA.resize(aSize + 1);
    for(int i = 1; i <= aSize; i++)
    {
        cin >> A[i];
        pSumA[i] = pSumA[i - 1] + A[i];
    }

    cin >> bSize;
    B.resize(bSize + 1);
    pSumB.resize(bSize + 1);
    for (int i = 1; i <= bSize; i++)
    {
        cin >> B[i];
        pSumB[i] = pSumB[i - 1] + B[i];
    }
    
    setSumOfSubArr(aSize, subArrA, pSumA);
    setSumOfSubArr(bSize, subArrB, pSumB);
   
    sort(subArrB.begin(), subArrB.end());

    long long ans = 0;
    for(const auto& i : subArrA)
    {
        auto range = equal_range(subArrB.begin(), subArrB.end(), t - i);
        ans += range.second - range.first;
    }

    cout << ans << "\n";
}