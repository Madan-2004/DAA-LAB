# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

typedef long long int li;

bool isBipartiteCheck(vector <vector<li>>& arr, vector <li>& color, li src, li n){
    queue <li> q;
    q.push(src);
    color[src] = 1;

    while(!q.empty()){
        li u = q.front();
        q.pop();
        for(li v=0; v<n; v++){
            if(arr[u][v] != 0 && color[v] == -1){
                color[v] = 1-color[u];
                q.push(v);
            }

            else if(arr[u][v] && color[v] == color[u]){
                return false;
            }
        }
    }
    return true;
}

bool isBipartite(vector <vector<li>>& arr, li n){
    vector <li> color(n, -1);

    for(li i=0; i<n; i++){
        if(color[i] == -1){
            if(isBipartiteCheck(arr, color, i, n) == false){
                return false;
            }
        }
    }
    return true;
}

bool twoCliques(vector <vector<li>>& graph, li n){
    vector <vector<li>> reverse(n, vector<li>(n,0));
    for(int i=0; i<n; i++){
        for(int j=0; j<n && i != j; j++){
            reverse[i][j] = 1-graph[i][j]; // Reversing the edge direction
        }
    }
    return isBipartite(reverse, n);
}

int main(){
    freopen("input_Q3.txt", "r", stdin);
    freopen("output_Q3.txt", "w", stdout);
    // li t;
    // cin>>t;
    // while(t--){
        li n;
        cin>>n;
        vector <vector<li>> graph(n, vector<li>(n,0));
        for(li i=0; i<n; i++){
            for(li j=0; j<n; j++){
                cin>>graph[i][j];
            }
        }

        auto start1 = high_resolution_clock::now(); // Start time
        bool ans = twoCliques(graph, n);
        auto stop1 = high_resolution_clock::now(); // Stop time
        auto duration = duration_cast<microseconds>(stop1 - start1);

        if(ans) cout<<"The given graph can be divided into two cliques."<<endl;
        else cout<<"The given graph cannot be divided into two cliques."<<endl;

        cout<<"The time taken by this function is: "<<duration.count()<<" microseconds."<<endl;      
    // }
    
    fclose(stdin);
    fclose(stdout);
return 0;
}