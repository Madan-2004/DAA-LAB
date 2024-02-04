# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

typedef long long int li;
typedef double ld;

ld median(li a1[], li a2[], li m, li n){        // O(m+n) time-complexity.
    li k=0, i=0, j=0;
    li m1 = (m+n)/2;
    li m2 = m1 - 1;
    li m1e = 0, m2e = 0;
    
    while(i < m && j < n && k < m+n){
        if(a1[i] <= a2[j]){
            if(k == m1) m1e = a1[i];
            if(k == m2) m2e = a1[i];
            i++;
            k++;
        }
        else{
            if(k == m1) m1e = a2[j];
            if(k == m2) m2e = a2[j];
            j++;
            k++;
        }
    }

    while(k < m+n && i < m){
        if(k == m1) m1e = a1[i];
        if(k == m2) m2e = a1[i];
        i++;
        k++;
    }

    while(k < m+n && j < n){
        if(k == m1) m1e = a2[j];
        if(k == m2) m2e = a2[j];
        j++;
        k++;
    }

    if((m+n)%2 == 0){
        return double(double(m1e+m2e)/2);
    }
    return m1e;
}

int main(){
    freopen("input_Q2.txt", "r", stdin);
    freopen("output_Q2.txt", "w", stdout);
    li t;
    cin>>t;
    while(t--){
        li n, m;
        cin>>m>>n;
        li a1[m], a2[n];
        for(li i=0; i<m; i++){
            cin>>a1[i];
        }

        for(li i=0; i<n; i++){
            cin>>a2[i];
        }

        auto start1 = high_resolution_clock::now(); // Start time
        ld mid = median(a1, a2, m, n);
        auto stop1 = high_resolution_clock::now(); // Stop time
        auto duration = duration_cast<microseconds>(stop1 - start1);
        cout<<"The median of the two arrays is: "<<mid<<"."<<endl;
        cout<<"The time taken by two pointers approach is: "<<duration.count()<<" microseconds."<<endl;

    }
    fclose(stdin);
    fclose(stdout);
return 0;
}