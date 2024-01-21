# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

void swap_greater(vector <int>& arr, int ind1, int ind2){
    if(arr[ind1] > arr[ind2]){
        swap(arr[ind1], arr[ind2]);
    }
}

// It is a basis of shell sort with time-complexity of O(nlogn) and an inplace algorithm.

void Merge(vector <int>& arr, int n){
    int gap = (n/2) + (n%2);
    while(gap > 0){
        int left = 0;
        int right = left + gap;
        while(right < n){
            swap_greater(arr, left, right);
            left++;
            right++;      
        }
        if(gap == 1) break;
        gap = (gap/2) + (gap%2);
    }
}

int main(){
    ifstream inputFile("input_Q3.txt");
    if(!inputFile.is_open()){
        cerr<<"Error opening the input file"<<endl;
    }
    ofstream outputFile("output_Q3.txt");
    if(!outputFile.is_open()){
        cerr<<"Error opening the output file"<<endl;
    }

    long long int n;
    inputFile>>n;
    vector <int> arr(n);
    for(int i=0; i<n; i++){
        inputFile>>arr[i];
    }
    inputFile.close();

    // Sorting the array.
    auto start1 = high_resolution_clock::now();

    Merge(arr, n);

    auto stop1 = high_resolution_clock::now();
    outputFile<<"The time taken by sorting the unsorted array is: "<<duration_cast<microseconds>(stop1 - start1).count()<<" micro-seconds."<<endl;


    outputFile<<"The sorted array is: ";
    for(int i=0; i<n; i++){
        outputFile<<arr[i]<<" ";
    }
    outputFile<<endl;

return 0;
}