<p align="center">
<a href=https://solved.ac/tuna1210>
<img src="http://mazassumnida.wtf/api/v2/generate_badge?boj=tuna1210" alt="text" width="70%"/>
</a>
</p>

***  

# 알고리즘 정리

## CCW
Counter Clock Wise, 세 점이 순서대로 시계방향인지 아닌지 검사하는 방법.  
아래 신발끈공식(외적)을 이용. S가 ``음수라면 시계, 0이면 직선, 양수면 반시계방향``이다.  
* 신발끈 공식   
![신발끈](https://mblogthumb-phinf.pstatic.net/20160530_226/10baba_14645967148306TPeY_PNG/%BB%E7%BC%B1%BD%C4.png?type=w2)


* 예제 : **중간에 더해가는 과정에서 OVFL가 일어날 수 있음을 주의**
```
int ccw(pair<int, int> a, pair<int, int> b, pair<int, int> c)
{
    long long temp = 1l * a.first * b.second + 1l * b.first * c.second + 1l * c.first * a.second;
    temp -= 1l * b.first * a.second + 1l * c.first * b.second + 1l * a.first * c.second;
    if(temp > 0) return 1;
    else if(temp < 0) return -1;
    return 0;
}
```
***
## Bellman Ford
시간복잡도는 $O(VE)$이다. 최단 경로를 찾아내는 알고리즘으로, 다익스트라와는 달리 음의 가중치를 지닌 간선을 가질 수 있지만 ``음의 사이클(사이클 가중치의 합이 음수)은 가질 수 없다``. 만약 음의 사이클이 존재하지 않는다면 노드의 개수를 $N$이라 하였을 때 $N-1$번 모든 간선에 대해 Relaxation을 수행하여 정해를 구할 수 있다. 이떄 만약 음의 사이클이 존재한다면 $N$번째 수행 시 Relaxation이 발생한다. 이를 이용하여 음의 사이클의 존재여부를 판단할 수 있다.  


* 유의할 점 ([할로윈 묘지](https://www.acmicpc.net/problem/3860))  
<img src = "https://i.ibb.co/s3GzWWk/IMG-50-EE9614-E6-F9-1.jpg" width="60%">  
이와같은 상황일때 노드를 순회하면서 $dist[n] ≠ \infty$ 을 검사하지 않는다면 파란색 웜홀에 도달할 수 있는 방법이 존재하지 않음에도 불구하고 웜홀 스스로 relaxation이 발생하여 경로 상에 음의 사이클이 있다고 판단함. 따라서 dist가 INF가 아닌 노드에 대해서는 relaxation이 가능하더라도 그것을 수행해서는 안된다.

***
## Dijkstra
* [세금](https://www.acmicpc.net/problem/13907) : 
$dist$ 배열을 \[노드]\[거쳐온 노드 수]로 2차원으로 선언, 문제의 input이 $N ≤ 1000$ 이므로 거친 노드의 최대값은 1000이다. 따라서 다익스트라를 실행할때 거친노드가 1000을 넘어간다면 무시하도록 예외 처리를 해주어야 한다. 
```
if(nextMove == 1000) continue;
```
또 다른 풀이 : 더 높은 비용을 가지고 더 많은 노드를 거쳐온 경로는 최적해가 되지 않으므로 큐에 집어 넣지 않아도 됨

***
## 소수판정

에라토스테네스의 체를 이용하여 $n$까지의 소수를 구해야 할 때 $\sqrt{n}$까지의 배수만 제거해도 정답이 보장된다.
