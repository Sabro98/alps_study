```cpp
//1-pass
for(int i=1; i<=N; i++){
    for(auto g : G[i]){
        dist[i][g.first] = min(dist[i][g.first], g.second);
    }
}
for(int i=1; i<=N; i++) dist[i][i] = 0;

//n-pass if {i -> k -> j} < {i -> j}, update
for(int k=1; k<=N; k++){
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
    }
}

```
