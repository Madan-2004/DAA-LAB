# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct DS{
    int* parent, * rank;
    int n;
    DS(int n){
        this->parent = new int[n];
        this->rank = new int[n];
        this->n = n;
        for(int i=0; i<n; i++){
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int find(int s){
        if(s == parent[s]) return s;
        return parent[s] = find(parent[s]);
    }

    void merge(int s1, int s2){
        int ps1 = find(s1);
        int ps2 = find(s2);
        if(ps1 == ps2) return;
        if(rank[ps1] > rank[ps2]){
            parent[ps2] = ps1;
        }
        else if(rank[ps1] < rank[ps2]){
            parent[ps1] = ps2;
        }
        else{
            parent[ps2] = ps1;
            rank[ps1]++;
        }
    }
};

bool myCmp(vector<int> v1, vector<int> v2){
    return v1[2] < v2[2];
}

void Kruskals(vector<vector<int>> &arr, int n){
    int count = 0;
    int edges = arr.size();
    sort(arr.begin(), arr.end(), myCmp);
    int indx = 0;
    DS mst(n);
    int total_weight = 0;

    while(indx < edges && count < n-1){
        int u = arr[indx][0];
        int v = arr[indx][1];
        int w = arr[indx][2];
        if(mst.find(u) == mst.find(v)){
            arr[indx][3] = 0;
        }
        else{
            mst.merge(u, v);
            arr[indx][3] = 1;
            total_weight += w;
            count++;
        } 
        indx++;       
    }
    cout<<"Total weight: "<<total_weight<<endl;
}

int main(){
    freopen("input_Q1.txt","r",stdin);
    freopen("output_Q1.txt","w",stdout);
    int n, edges;
    cin>>n>>edges;
    vector <vector<int>> arr(edges, vector<int>(4, 0));
    for(int i=0; i<edges; i++){
        cin>>arr[i][0]>>arr[i][1]>>arr[i][2];
    }

    auto start1 = high_resolution_clock::now(); // Start time

    Kruskals(arr, n);

    auto stop1 = high_resolution_clock::now(); // Stop time
    auto duration1 = duration_cast<microseconds>(stop1 - start1);

    for(int i=0; i<edges; i++){
        if(arr[i][3] == 1){
            cout<<'('<<arr[i][0]<<','<<arr[i][1]<<')'<<" -- "<<arr[i][2]<<endl;
        }
    }

    cout<<"The time taken by Kruskal's algorithm is: "<<duration1.count()<<" microseconds."<<endl;  
return 0;
}