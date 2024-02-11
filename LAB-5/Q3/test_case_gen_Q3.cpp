#include<bits/stdc++.h>
using namespace std;

const int n = 1e3; 
const int m = 1e5; 

int matrix[n][n]; 

int main()
{
    freopen("input_Q3.txt", "w", stdout); 
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<> distrib1(0,1); 
    vector<int> groups[2]; 
    for(int i = 0; i < n; i++)
    {
        groups[distrib1(rng)].push_back(i); 
    }    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i==j) matrix[i][j] = 0; 
            else matrix[i][j] = 1; 
        }
    }
    uniform_int_distribution<> distrib2(0,groups[0].size()-1); 
    uniform_int_distribution<> distrib3(0,groups[1].size()-1); 
    for(int i = 0; i < m; i++)
    {
        int u = groups[0][distrib2(rng)];
        int v = groups[1][distrib3(rng)]; 
        matrix[u][v] = 0; 
        matrix[v][u] = 0; 
    }
    cout<<n<<"\n"; 
    // uncomment to generate output which gives no 
    // int u = groups[0][0]; 
    // int v = groups[0][1]; 
    // int w = groups[0][2]; 
    // matrix[u][v] = 0; 
    // matrix[v][u] = 0;
    // matrix[v][w] = 0; 
    // matrix[w][v] = 0; 
    // matrix[w][u] = 0; 
    // matrix[w][v] = 0; 
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout<<matrix[i][j]<<" "; 
        }
        cout<<"\n"; 
    }
}