# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

vector <int> Merge(int a[], int b[], int m, int n){
    vector <int> c(m+n);
    int i = 0;
    int j = 0;
    int k = 0;
    while(i<m && j<n){
        if(a[i] <= b[j]){
            c[k] = a[i];
            i++;
            k++;
        }
        else{
            c[k] = b[j];
            j++;
            k++;
        }
    }
    while(i<m){
        c[k] = a[i];
        i++;
        k++;
    }
    while(j<n){
        c[k] = b[j];
        j++;
        k++;
    }
    return c;
} 

vector <int> Union(int a[], int b[], int m, int n){
    vector <int> c(m+n);
    int i=0, j=0, k=0;
    while(i<m && j<n){
            if(k>0 && c[k-1] == a[i]){
                i++;
                continue;
            }
            if(k>0 && c[k-1] == b[j]){
                j++;
                continue;
            }
            if(a[i] <= b[j]){
                c[k] = a[i];
                i++;
                k++;
                continue;
            }
            if(a[i] > b[j]){
                c[k] = b[j];
                j++;
                k++;
                continue;
            }
        }
        while(i<m){
            if(k>0 && c[k-1] == a[i]){
                i++;
                continue;
            }
            c[k] = a[i];
            k++;
            i++;
        }
        while(j<n){
            if(k>0 && c[k-1] == b[j]){
                j++;
                continue;
            }
            c[k] = b[j];
            j++;
            k++;
        }
        c.resize(k);
    return c;
}

vector <int> Intersection(int a[], int b[], int m, int n){
    vector <int> c(m+n);
    int i=0, j=0, k=0;
    while (i < m && j < n){
        if(a[i] < b[j]){
            i++;
        } 
        else if(a[i] > b[j]){
            j++;
        } 
        else{
            if(k == 0 || (k > 0 && c[k - 1] != a[i])){
                c[k] = a[i];
                k++;
            }
            i++;
            j++;
        }
    }
    c.resize(k);
    return c;
}

int main(){
    ifstream inputFile("input_Q1.txt");
    if(!inputFile.is_open()){
        cerr<<"Error opening the input file"<<endl;
        return 1;
    }
    ofstream outputFile("output_Q1.txt");
    if(!outputFile.is_open()){
        cerr<<"Error opening the output file"<<endl;
    }

    long long int m,n;
    //Receiving the inputs from the input file
    inputFile>>m>>n;
    int a[m], b[n];
    vector <int> c(m+n), d(m+n), e(m+n);
    for(long long int i=0; i<m; i++){
       inputFile>>a[i];
    }
    for(long long int i=0; i<n; i++){
        inputFile>>b[i];
    }
    inputFile.close();

    auto start1 = high_resolution_clock::now();

    // Merging of A and B.
    c = Merge(a, b, m, n);
    outputFile<<"The array by merging A and B is: "<<endl;
    for(int i=0; i<m+n; i++){
        outputFile<<c[i]<<" ";
    }
    outputFile<<endl;

    // Union of A and B.
    d = Union(a, b, m, n);
    outputFile<<"The array by union of A and B is: "<<endl; 
    for(long long int i=0; i<d.size(); i++){
        outputFile<<d[i]<<" ";
    }
    outputFile<<endl;

    // Intersection of A and B.
    e = Intersection(a, b, m, n);

    outputFile<<"The array by intersection of A and B is: "<<endl;
    for(long long int i=0; i<e.size(); i++){
        outputFile<<e[i]<<" ";
    }
    outputFile<<endl;
    auto stop1 = high_resolution_clock::now();
    outputFile<<"The time taken for all the three functions is: "<<duration_cast<milliseconds>(stop1 - start1).count()<<" milli-seconds."<<endl;
    outputFile.close();
return 0;
}