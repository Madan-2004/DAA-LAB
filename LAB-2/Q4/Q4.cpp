# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

int main(){
    ifstream inputFile("input_Q4.txt");
    if(!inputFile.is_open()){
        cerr<<"Error opening the input file"<<endl;
    }
    ofstream outputFile("output_Q4.txt");
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
    
    auto start1 = high_resolution_clock::now();

    sort(arr.begin(), arr.end());  //sorting the array using the inbuilt sort function.
    // The C++ sort() function uses introsort, which is a hybrid algorithm. It is a combination of quicksort and heapsort.
    // The median element after sorting will be just a constant time operation which is just accessing the middle element of the sorted array.
    if(n%2 == 0){
        outputFile<<"The median is: "<<double(arr[n/2] + arr[(n/2)-1])/2<<endl;
    }
    else if(n%2 == 1){
        outputFile<<"The median is: "<<arr[n/2]<<endl;
    }

    auto stop1 = high_resolution_clock::now();
    outputFile<<"The time taken is: "<<duration_cast<microseconds>(stop1 - start1).count()<<" micro-seconds."<<endl;
return 0;
}