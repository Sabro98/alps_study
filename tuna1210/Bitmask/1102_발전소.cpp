#include <iostream>
#include <cstring>
using namespace std;

int repairCost[16][16];
int dist[1 << 16];
int n, p;

int repairGen(int activeStat, int activeCnt)
{
    // 켜져있는 발전소의 개수가 P에 도달하면 재귀호출 종료
    if(activeCnt == p) return 0;

    int& ret = dist[activeStat];
    if(ret != -1) return ret;

    ret = 1e9;
    for (int i = 0; i < n; i++)
    {
        // 다음이 이미 켜져 있는 발전소면 Pass
        if((activeStat & (1 << i)) == (1 << i)) continue;

        // 다음 발전소를 킬 수 있는 가장 적은 비용을 찾아냄
        int minCost = 1e9;
        for (int j = 0; j < n; j++)
        {
            // 다음 발전소를 키려면 이미 켜져있어야 하므로 꺼져있는 발전소는 Pass
            if((activeStat & (1 << j)) != (1 << j)) continue;
            minCost = min(minCost, repairCost[j][i]);
        }
         
        ret = min(ret, repairGen((activeStat | (1 << i)), activeCnt + 1) + minCost);
    }
    if(ret == 1e9) ret = 0;
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    memset(dist, -1, sizeof(dist));
    
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> repairCost[i][j];
        }
    }
    
    int startStat = 0, startCnt = 0;
    for (int i = 0; i < n; i++)
    {
        char stat;
        cin >> stat;
        if(stat == 'Y')
        {
            startStat |= (1 << i);
            startCnt++;
        }
    }

    cin >> p;
    
    if(p <= startCnt) cout << 0 << "\n";
    else if(startCnt != 0) cout << repairGen(startStat, startCnt) << "\n";
    else cout << -1 << "\n";
} 