![header](https://capsule-render.vercel.app/api?type=waving&height=200&text=ALPS%20Algorithm%20Study&color=50bcdf&animation=scaleIn&fontColor=FFFFFF&fontSize=35&fontAlignY=30&desc=tuna1210&descAlign=66&descAlignY=48)  


<p align="center">
<a href=https://solved.ac/tuna1210>
<img src="http://mazassumnida.wtf/api/v2/generate_badge?boj=tuna1210" alt="text" width="number"/>
</a>
</p>

***  

# 알고리즘 정리

## CCW
Counter Clock Wise, 세 점이 순서대로 시계방향인지 아닌지 검사하는 방법.  
아래 신발끈공식(외적)을 이용. S가 음수라면 시계, 0이면 직선, 양수면 반시계방향이다.  
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