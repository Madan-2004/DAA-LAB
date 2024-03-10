# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct Graph{
    int size;
    list <int>* arr;

    Graph(int v){
        this->size = v;
        arr = new list<int> [v];
    }

    void addEdge(int x, int y){
        arr[x].push_back(y);
    }

};

// void DFS(Graph *g, vector <bool> visited, int src, stack <int>& s){
//     visited[src] = true;

//     for(auto u:g->arr[src]){
//         if(!visited[u]){
//             DFS(g, visited, u, s);
//         }
//     }
//     s.push(src);
// }

// void TopoSortDFS(Graph *g){
//     stack <int> s;
//     int n = g->size;
//     vector <bool> visited(n, false);
    
//     for(int i=0; i<n; i++){
//         if(!visited[i]){
//             DFS(g, visited, i, s);
//         }
//     }

//     while(!s.empty()){
//         cout<<" "<<s.top();
//         s.pop();
//     }
//     cout<<"."<<endl;
// }

void TopoSort(Graph &g){        // Kahn's algorithm => O(V+E) time complexity.
    int n = g.size;
    vector <int> indegree(n, 0);
    for(int i=0; i<n; i++){
        for(auto it:g.arr[i]){
            indegree[it]++;
        }
    }

    queue <int> q;
    for(int i=0; i<n; i++){
        if(indegree[i] == 0){
            q.push(i);
        }
    }

    cout<<"The topological sorting of the given graph is:";

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto v:g.arr[u]){
            indegree[v]--;
            if(indegree[v] == 0){
                q.push(v);
            }
        }
        cout<<" "<<u;
    }  
    cout<<"."<<endl;     
}


int main(){
    freopen("input_Q1.txt", "r", stdin);
    freopen("output_Q1.txt", "w", stdout);
    int t;
    cin>>t;
    while(t--){
        int n, edge;
        cin>>n>>edge;
        
        Graph g(n);
        int u, v;
        for(int i=0; i<edge; i++){
            cin>>u>>v;
            u--;
            v--;
            g.addEdge(u, v);
        }

        // Graph g(5);
        // g.addEdge(0, 1);
        // g.addEdge(1, 3);
        // g.addEdge(3, 4);
        // g.addEdge(2, 3);
        // g.addEdge(2, 4);

        auto start1 = high_resolution_clock::now(); // Start time
        TopoSort(g);
        auto stop1 = high_resolution_clock::now(); // Stop time
        auto duration = duration_cast<microseconds>(stop1 - start1);

        cout<<"The time taken by Topological Sorting is: "<<duration.count()<<" microseconds."<<endl;  
    }  
        
    fclose(stdin);
    fclose(stdout);  
return 0;
}