#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

void union_set(map<int,int>&size, map<int,int>&par, map<int,vector<int>>&mp,int a,int b){
    if(size[par[a]]>size[par[b]]){
        int c=par[b];
        size[par[a]]+=size[par[b]];
        for(auto &x:mp[c]){
            par[x]=par[a];
            mp[par[a]].push_back(x);
        }
    }else{
        int c=par[a];
        size[par[b]]+=size[par[a]];
        for(auto &x:mp[c]){
            par[x]=par[b];
            mp[par[b]].push_back(x);
        }        
    }
}

int half_kruskal(vector<pair<int,pair<int,int>>> v,int n,int m,int j){
    map<int,int> size,par;
    map<int,vector<int>> mp;
    for(int i=1;i<=n;i++){
        size[i]=1;
        par[i]=i;
        mp[i].push_back(i);
    }
    int ans=0;
    for(int i=0;i<m;i++){
        int a=v[i].second.first;
        int b=v[i].second.second;
        if(par[a]!=par[b] && i!=j){
            ans+=v[i].first;
            union_set(size,par,mp,a,b);
        }
    }  
    // cout<<ans<<endl;
    return ans;
}

void print_kruskal(vector<pair<int,pair<int,int>>> v,int n,int m,int j){
    map<int,int> size,par;
    map<int,vector<int>> mp;
    for(int i=1;i<=n;i++){
        size[i]=1;
        par[i]=i;
        mp[i].push_back(i);
    }
    int ans=0;
    for(int i=0;i<m;i++){
        int a = v[i].second.first;
        int b = v[i].second.second;
        int weight = v[i].first;
        if(par[a]!=par[b] && i!=j){
            cout<<'('<<a<<","<<b<<')'<<" -- "<<weight<<endl;
            ans += weight;
            union_set(size,par,mp,a,b);
        }
    }
    cout<<"Total weight: "<<ans<<endl;  
}

void kruskal(vector<pair<int,pair<int,int>>> v,int n,int m){
    map<int,int> size,par;
    map<int,vector<int>> mp;
    for(int i=1;i<=n;i++){
        size[i]=1;
        par[i]=i;
        mp[i].push_back(i);
    }
    sort(v.begin(),v.end());
    int ans=0;
    for(int i=0;i<m;i++){
        int a=v[i].second.first;
        int b=v[i].second.second;
        if(par[a]!=par[b]){
            ans+=v[i].first;
            union_set(size,par,mp,a,b);
        }
    }
    int k=-1;
    int mn=100000;
    for(int i=0;i<m;i++){
        if(half_kruskal(v,n,m,i)>ans && ans-half_kruskal(v,n,m,i)<mn){
            mn=ans-half_kruskal(v,n,m,i);
            k=i;
        }
    }
    print_kruskal(v,n,m,k);
}

int main(){
    freopen("input_Q3.txt","r",stdin);
    freopen("output_Q3.txt","w",stdout);
    int n, m;
    cin>>n>>m;
    vector<pair<int,pair<int,int>>> v;

    for(int i=0;i<m;i++){
        int a,b,w;
        cin>>a>>b>>w;
        pair<int,int> p={a,b};
        v.push_back({w,p});
    }

    auto start1 = high_resolution_clock::now(); // Start time

    kruskal(v,n,m);

    auto stop1 = high_resolution_clock::now(); // Stop time
    auto duration1 = duration_cast<microseconds>(stop1 - start1);

    cout<<"The time taken for finding second best MST is: "<<duration1.count()<<" microseconds."<<endl;  
    return 0;
}