# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

typedef long long int li;

li pivot(li arr[], li l, li h){     // O(n) time-complexity.
    li p = arr[h];
    li i = l-1;
    li j = l;
    while(j < h){
        if(arr[j] <= p){
            i++;
            swap(arr[i], arr[j]);
        }
        j++;
    }
    i++;
    swap(arr[i], arr[j]);
    return i;
}

li partition(li arr[], li k, li l, li h){   // Quick Sort => O(nlogn) time-complexity.
    // if(l >= h) return -1;
    li val = pivot(arr, l, h);
    if(val == k){
        return arr[k];
    }
    if(val < k){
        return partition(arr, k, val+1, h);
    }
    else{
        return partition(arr, k, l, val-1);
    }
    return -1;
}

int main(){
    freopen("input_Q3.txt", "r", stdin);
    freopen("output_Q3.txt", "w", stdout);
    li t;
    cin>>t;
    while(t--){
        li n, j;
        cin>>n>>j;
        li arr[n];

        for(li i=0; i<n; i++){
            cin>>arr[i];
        }

        auto start1 = high_resolution_clock::now(); // Start time
        li ans = partition(arr, n-j, 0, n-1);
        auto stop1 = high_resolution_clock::now(); // Stop time
        auto duration = duration_cast<microseconds>(stop1 - start1);

        cout<<"The "<<j<<"th largest element is: "<<ans<<"."<<endl;
        cout<<"The time taken by this function is: "<<duration.count()<<" microseconds."<<endl;
    }
    fclose(stdin);
    fclose(stdout);
return 0;
}