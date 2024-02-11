# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

int main(){
    freopen("input_Q2.txt", "r", stdin);
    freopen("output_Q2.txt", "w", stdout);
    int nums;
    cin>>nums;
    while(nums--){
        int n = 30;
        // cin>>n;
        int ladders; 
        cin>>ladders;
        unordered_map<int,int> lad;
        for(int i=0; i<ladders; i++){
            int a, b;
            cin>>a>>b;
            lad[a] = b;
        }

        int snakes;
        cin>>snakes;
        unordered_map<int,int> snk;
        for(int i=0; i<snakes; i++){
            int a, b;
            cin>>a>>b;
            snk[a] = b;
        }

        auto start1 = high_resolution_clock::now(); // Start time
        queue<int> q;
        q.push(1);
        bool found = false;
        vector <int> visited(n+1, 0);
        int moves = 0;

        while(!q.empty() && !found){
            int sz = q.size();
            while(sz--){
                int t = q.front();
                q.pop();
                for(int die=1; die<=6; die++){
                    if(t+die == n){
                        found = true;
                    }
                    if(t+die <= n && lad[t+die] && !visited[lad[t+die]]){
                        visited[lad[t+die]] = 1;
                        if(lad[t+die] == n){
                            found = true;
                        }
                        q.push(lad[t+die]);
                    }
                    if(t+die <= n && snk[t+die] && !visited[snk[t+die]]){
                        visited[snk[t+die]] = 1;
                        if(snk[t+die] == n){
                            found = true;
                        }
                        q.push(snk[t+die]);
                    }
                    if(t+die <= n && !snk[t+die] && !lad[t+die] && !visited[t+die]){
                        visited[t+die] = 1;
                        if(t+die == n){
                            found = true;
                        }
                        q.push(t+die);
                    }
                }
            }
        moves++;  
        }
        auto stop1 = high_resolution_clock::now(); // Stop time
        auto duration = duration_cast<microseconds>(stop1 - start1);
        
        if(found){
            cout<<"The minimum number of moves are: "<<moves<<"."<<endl;
        }
        else{
            cout<<"It is not possible."<<endl;
        }
        cout<<"The time taken by this function is: "<<duration.count()<<" microseconds."<<endl;
    }
    fclose(stdin);
    fclose(stdout);
return 0;
}