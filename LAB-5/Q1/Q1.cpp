# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

typedef long long int li;
li n,m;

bool check(vector <vector<li>>& graph, vector <vector<bool>>& visited, li x, li y){
    if(x >= n || y >= m || x < 0 || y<0) return false;
    if(visited[x][y]) return false;
    return true;
}

li dfs(vector <vector<li>>& graph, vector <vector<bool>>& visited, li x, li y, li area){
    li ans = 0;
    if(!visited[x][y] && graph[x][y] == 1){
        ans++;
    }
    visited[x][y] = 1;
    if(check(graph, visited, x-1, y) && graph[x-1][y] == 1){
        ans += dfs(graph, visited, x-1, y, 0);
    }
    if(check(graph, visited, x+1, y) && graph[x+1][y] == 1){
        ans += dfs(graph, visited, x+1, y, 0);
    }
    if(check(graph, visited, x, y-1) && graph[x][y-1] == 1){
        ans += dfs(graph, visited, x, y-1, 0);
    }
    if(check(graph, visited, x, y+1) && graph[x][y+1] == 1){
        ans += dfs(graph, visited, x, y+1, 0);
    }
    if(check(graph, visited, x-1, y-1) && graph[x-1][y-1] == 1){
        ans += dfs(graph, visited, x-1, y-1, 0);
    }
    if(check(graph, visited, x+1, y-1) && graph[x+1][y-1] == 1){
        ans += dfs(graph, visited, x+1, y-1, 0);
    }
    if(check(graph, visited, x-1, y+1) && graph[x-1][y+1] == 1){
        ans += dfs(graph, visited, x-1, y+1, 0);
    }
    if(check(graph, visited, x+1, y+1) && graph[x+1][y+1] == 1){
        ans += dfs(graph, visited, x+1, y+1, 0);
    }
    return ans;
}

int main(){
    freopen("input_Q1.txt", "r", stdin);
    freopen("output_Q1.txt", "w", stdout);
    cin>>n>>m;
    vector<vector<li>> graph(n, vector<li>(m));
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    for(li i=0;i<n;i++){
        for(li j=0;j<m;j++){
            cin>>graph[i][j];
            visited[i][j] = false;
        }
    }

    li res = 0;

    auto start1 = high_resolution_clock::now(); // Start time
    for(li i=0;i<n;i++){
        for(li j=0; j<m; j++){
            if(!visited[i][j] && graph[i][j]){
                res = max(res, dfs(graph, visited, i, j, 0));
            }
        }
    }
    auto stop1 = high_resolution_clock::now(); // Stop time
    auto duration = duration_cast<microseconds>(stop1 - start1);
    
    cout<<"The size of the largest region is: "<<res<<"."<<endl;
    cout<<"The time taken by this function is: "<<duration.count()<<" microseconds."<<endl;

    fclose(stdin);
    fclose(stdout);
return 0;
}