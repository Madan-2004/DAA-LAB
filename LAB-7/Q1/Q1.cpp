# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

bool myCmp(pair <int, int> a, pair <int, int> b){
    return (double)a.second/a.first > (double)b.second/b.first;
}

int Greedy(pair <int, int> arr[], int n, int k){
    sort(arr, arr+n, myCmp);

    int cap = 0;
    int profit = 0;
    int indx = 0;
    while(indx <= n){
        if(cap + arr[indx].first <= k){
            cap += arr[indx].first;
            profit += arr[indx].second;
        }
        if(cap == k) break;
        indx++;
    }

    return profit;
}

int Optimal(vector<int> val, vector<int> wt, int n, int k){
    vector <vector<int>> dp(n+1, vector<int>(k+1));
    
    for(int i=0; i<=n; i++){
        
        for(int w=0; w<=k; w++){
            if(i == 0 || w == 0){
                dp[i][w] = 0;
            }

            else if(wt[i-1] <= w){
                dp[i][w] = max(dp[i-1][w], val[i-1] + dp[i-1][w-wt[i-1]]);
            }

            else{
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    return dp[n][k];
}

int main(){
    freopen("input_Q1.txt","r",stdin);
    freopen("output_Q1.txt","w",stdout);
    int t;
    cin>>t;
    while(t--){
        int n, k;
        cin>>n>>k;
        vector<int> wt(n);
        vector<int> val(n);

        for(int i=0; i<n; i++){
            cin>>wt[i];
        }

        for(int i=0; i<n; i++){
            cin>>val[i];
        }

        pair <int, int> arr[n];
        for(int i=0; i<n; i++){
            arr[i] = {wt[i], val[i]};
        }

        auto start1 = high_resolution_clock::now(); // Start time

        int profit_greedy = Greedy(arr, n, k);

        auto stop1 = high_resolution_clock::now(); // Stop time
        auto duration1 = duration_cast<microseconds>(stop1 - start1);

        cout<<"Greedy approach: "<<profit_greedy<<endl;
        cout<<"The time taken by greedy approach is: "<<duration1.count()<<" microseconds."<<endl;  

        auto start2 = high_resolution_clock::now(); // Start time

        int profit_optimal = Optimal(val, wt, n, k);

        auto stop2 = high_resolution_clock::now(); // Stop time
        auto duration2 = duration_cast<microseconds>(stop2 - start2);

        cout<<"Optimal approach: "<<profit_optimal<<endl;
        cout<<"The time taken by optimal approach is: "<<duration2.count()<<" microseconds."<<endl;  

    }
    
return 0;
}