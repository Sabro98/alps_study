```cpp
for(int k=1; k<=N; k++){
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(dist[i][j] > dist[i][k] + dist[k][j]){
                dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}
```
