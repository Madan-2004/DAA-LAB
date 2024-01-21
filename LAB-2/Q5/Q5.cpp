#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;


void findMinima(vector <int> arr, int n, int &first_min, int &second_min) {
    first_min = INT_MAX;
    second_min = INT_MAX;

    for (int i = 0; i < n; ++i) {
        if (arr[i] < first_min) {
            second_min = first_min;
            first_min = arr[i];
        }
        // If the current element is greater than or equal to the first minimum and smaller than the second minimum, update only the second minimum.
        else if (arr[i] < second_min && arr[i] != first_min) {
            second_min = arr[i];
        }
    }
}

int main(){
    ifstream inputFile("input_Q5.txt");
    if(!inputFile.is_open()){
        cerr<<"Error opening the input file"<<endl;
    }
    ofstream outputFile("output_Q5.txt");
    if(!outputFile.is_open()){
        cerr<<"Error opening the output file"<<endl;
    }
    long long int n;
    inputFile>>n;
    vector <int> arr(n);
    // Taking input array.
    for(int i=0; i<n; i++){
        inputFile>>arr[i];
    }
    inputFile.close();
    int first_min = INT32_MAX;
    int second_min = INT32_MAX;

    // We can find the first two min-elements in two ways.
    // 1) Maintain two variables and compare with the elements of the array => O(n) time.

    auto start1 = high_resolution_clock::now();

    findMinima(arr, n, first_min, second_min);

    auto stop1 = high_resolution_clock::now();
    outputFile<<"The first and second minimum elements by comparing is: "<<first_min<<" and "<<second_min<<"."<<endl;
    outputFile<<"The time taken by comparing is: "<<duration_cast<microseconds>(stop1 - start1).count()<<" micro-seconds."<<endl;
    // 2) Sort the array and take the first two entries => O(nlogn) time.
    // This will work correctly even when all elements are same as they will be sorted together.
    auto start2 = high_resolution_clock::now();

    sort(arr.begin(), arr.end());

    auto stop2 = high_resolution_clock::now();
    outputFile<<"The first and second minimum elements after sorting is: "<<arr[0]<<" and "<<arr[1]<<"."<<endl;
    outputFile<<"The time taken by sorting is: "<<duration_cast<microseconds>(stop2 - start2).count()<<" micro-seconds."<<endl;

return 0;
}
