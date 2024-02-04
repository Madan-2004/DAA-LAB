# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

typedef long long int li;

li merge(li arr[], li l, li mid, li h){     // O(n) time-complexity.
    li i=l, j=mid+1, inv_count=0;
    
    while(i <= mid && j <= h){
        if(arr[i] <= arr[j]){
            i++;
        }
        else{
            inv_count += (mid-i+1);
            j++;
        }
    }
    return inv_count;
}

li merge_count(li arr[], li l, li h){     // Merge-sort => O(nlogn) time-complexity.
    li mid=0, inv_count=0;
    if(h > l){
        mid = (l+h)/2;
        inv_count += merge_count(arr, l, mid);
        inv_count += merge_count(arr, mid+1, h);
        inv_count += merge(arr, l, mid, h);
    }
    return inv_count;
}

int main(){
    freopen("input_Q1.txt", "r", stdin);
    freopen("output_Q1.txt", "w", stdout);
    li t;
    cin>>t;
    for(li z=0; z<t; z++){
        li n;
        cin>>n;
        li arr[n];
        for(li i=0; i<n; i++){
            cin>>arr[i];
        }

        auto start1 = high_resolution_clock::now(); // Start time
        li ans = merge_count(arr, 0, n-1);
        auto stop1 = high_resolution_clock::now(); // Stop time
        auto duration = duration_cast<microseconds>(stop1 - start1);

        cout<<"The total number of inversions in the given array is: "<<ans<<"."<<endl;
        cout<<"The time taken by this function is: "<<duration.count()<<" microseconds."<<endl;
    }
    
    fclose(stdin);
    fclose(stdout);
return 0;
}