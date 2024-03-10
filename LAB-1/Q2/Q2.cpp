# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// 0/1 KnapSack Problem.

int knapSack1(int W, int wt[], int val[], int n){        // Recursive approach, we have exponential time complexity. 
    // O(n) stack space is required for recursion.
    // Base Case 
    if (n == 0 || W == 0) 
        return 0; 
  
    if (wt[n - 1] > W) 
        return knapSack1(W, wt, val, n - 1); 
  
    else
        return max(val[n - 1] + knapSack1(W - wt[n - 1], wt, val, n - 1), knapSack1(W, wt, val, n - 1)); 
} 

int knapSack(int W, int wt[], int val[], int n){    // DP approach, we have O(n*W) time complexity and O(n*W) space complexity.
    int dp[n+1][W+1];
    for(int i=0; i<=n; i++){
        dp[i][0] = 0;
    }
    for(int j=0; j<=W; j++){
        dp[0][j] = 0;
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=W; j++){
            if(wt[i-1] > j){
                dp[i][j] = dp[i-1][j];
            }
            else{
                dp[i][j] = max(dp[i-1][j], val[i-1] + dp[i-1][j-wt[i-1]]);
            }
        }
    }
    return dp[n][W];
}

int main(){
    freopen("input_Q2.txt", "r", stdin);
    freopen("output_Q2.txt", "w", stdout);
    int n;
    cin>>n;
    int W;
    cin>>W;
    int val[n];
    int wt[n];
    for(int i=0; i<n; i++){
        cin>>wt[i];
    }
    for(int i=0; i<n; i++){
        cin>>val[i];
    }
    
    // Recursive Approach.
    // auto start1 = high_resolution_clock::now();
    // cout<<"The maximum value that can be put in the knapsack(Recursive) is: "<<knapSack1(W, wt, val, n)<<endl;
    // auto stop1 = high_resolution_clock::now();
    // cout<<"The time taken by recursive approach is: "<<duration_cast<microseconds>(stop1 - start1).count()<<" micro-seconds."<<endl;

    // DP approach.
    auto start2 = high_resolution_clock::now();
    cout<<"The maximum value that can be put in the knapsack(DP) is: "<<knapSack(W, wt, val, n)<<endl;
    auto stop2 = high_resolution_clock::now();
    cout<<"The time taken by DP approach is: "<<duration_cast<microseconds>(stop2 - start2).count()<<" micro-seconds."<<endl;
    fclose(stdin);
    fclose(stdout);
return 0;
}