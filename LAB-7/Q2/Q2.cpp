# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct DS{
    int *parent;
    DS(int n){
        parent = new int[n+1];
        for(int i=0; i<=n; i++){
            parent[i] = i;
        }
    }

    int find(int s){
        if(s == parent[s]) return s;
        return parent[s] = find(parent[s]);
    }

    void merge(int u, int v){
        parent[v] = u;
    }
};

int maxDeadline(vector<pair<int,int>> arr){
    int m = INT_MIN;
    for(int i=0; i<arr.size(); i++){
        m = max(m, arr[i].first);
    }
    return m;
}

bool myCmp(pair<int, int> a, pair<int, int> b){
    return a.second > b.second;
}

int Optimal(vector<pair<int,int>> arr){
    int m = maxDeadline(arr);
    DS slots(m+1);
    sort(arr.begin(), arr.end(), myCmp);
    int profit = 0;

    for(int i=0; i<arr.size(); i++){
        int available = slots.find(arr[i].first);
        if(available > 0){
            profit += arr[i].second;
            slots.merge(slots.find(available-1), available);
        }
    }
    return profit;
}

int Greedy(vector<pair<int,int>> arr){
    sort(arr.begin(), arr.end(), myCmp);
    int limit = 0;
    for(int i=0; i<arr.size(); i++){
        limit = max(limit, arr[i].first);
    }
    vector <bool> visited(limit, false);
    int profit = 0;
    for(int i=0; i<arr.size(); i++){
        int deadline = arr[i].first;
        if(visited[deadline-1] == false){
            visited[deadline-1] = true;
            profit += arr[i].second;
        }
        else{
            int indx = deadline-1;
            while(indx >= 0){
                if(visited[indx] == false){
                    visited[indx] = true;
                    profit += arr[i].second;
                    break;
                }
                indx--;
            }
        }
    }
    return profit;
}

int main(){
    freopen("input_Q2.txt","r",stdin);
    freopen("output_Q2.txt","w",stdout);
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<pair<int, int>> arr(n);
        int deadline, profit;

        for(int i=0; i<n; i++){
            cin>>deadline>>profit;
            arr[i] = {deadline, profit};
        }

        auto start1 = high_resolution_clock::now(); // Start time

        int profit_greedy = Greedy(arr);

        auto stop1 = high_resolution_clock::now(); // Stop time
        auto duration1 = duration_cast<microseconds>(stop1 - start1);

        cout<<"The maximum profit in greedy approach is: "<<profit_greedy<<"."<<endl;
        cout<<"The time taken by greedy approach is: "<<duration1.count()<<" microseconds."<<endl;

        auto start2 = high_resolution_clock::now(); // Start time

        int profit_optimal = Optimal(arr);

        auto stop2 = high_resolution_clock::now(); // Stop time
        auto duration2 = duration_cast<microseconds>(stop2 - start2);

        cout<<"The maximum profit in optimal approach by disjoint set data structure is: "<<profit_optimal<<"."<<endl;
        cout<<"The time taken by optimal approach is: "<<duration2.count()<<" microseconds."<<endl;    

    }
    
return 0;
}