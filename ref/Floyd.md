```cpp
void floyd(){
    //1-pass
    for(int i=1; i<=N; i++){
        for(auto g : G[i]){
            dist[i][g.first] = min(dist[i][g.first], g.second);
            previous[i][g.first] = g.first;
        }
    }
    for(int i=1; i<=N; i++) dist[i][i] = 0;

    //n-pass if {i -> k -> j} < {i -> j}, update
    for(int k=1; k<=N; k++){
        for(int i=1; i<=N; i++){
            for(int j=1; j<=N; j++){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                    previous[i][j] = previous[i][k];
                }
            }
        }
    }

    //find shortest path from 3 to 2
    int start = 3, end = 2;
    queue<int> q;
    q.push(3);
    int next = previous[start][end];
    while(next != 0){
        q.push(next);
        next = previous[next][end];
    }
    if(q.size() == 1){// no path from start to end
        exit(0);
    }else{
        while(!q.empty()){
            cout << q.front() << ' ';
            q.pop();
        }
    }
}

```
