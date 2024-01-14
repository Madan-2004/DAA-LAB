#include <bits/stdc++.h>
using namespace std;

int vertices;
// Time complexity for Travelling Salesman Problem(brute force) is O(n!).
// Time complexity for Travelling Salesman Problem using DP is O(2^n*n^2).

vector<vector<int>> edges;
vector<vector<int>> memo;

int solve(int vertex, int subset){ 
    if(memo[vertex][subset] != 0)
        return memo[vertex][subset];
    
    if(__builtin_popcount(subset) == 2)
        return memo[vertex][subset] = edges[0][vertex];
    
    int result = INT_MAX;
    for(int mask = 1; mask < vertices; mask++)
        if((subset & (1 << mask)) && mask != vertex)
            result = min(result, solve(mask, subset ^ (1 << vertex)) + edges[mask][vertex]);
    return memo[vertex][subset] = result;
}

int main(){
    freopen("input_Q3.txt","r",stdin);
    freopen("output_Q3.txt","w",stdout);
    cin>>vertices;
    memo.resize(vertices);
    edges.resize(vertices);
    for(int i=0; i<vertices; i++){
        edges[i].resize(vertices);
        for(int j=0; j<vertices; j++)
            cin >> edges[i][j];
        memo[i].resize(1 << vertices);
    }
    int answer = INT_MAX;
    for(int j=1; j<vertices; j++){
        answer = min(answer, solve(j, (1 << vertices)-1) + edges[j][0]);
    }
    cout<<"The shortest possible route cost that visits each city exactly once and returns to the original city is: "<<answer<<endl;

    fclose(stdin);
    fclose(stdout);
return 0;    
}
