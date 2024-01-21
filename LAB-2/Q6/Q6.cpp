# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

 // CUTOFF is used to reduce the time-complexity by switching the mode to insertion sort when the length is small than the desired value.
const int CUTOFF = 12;

// Insertion sort used for CUTOFF
void insertionSort(int* arr, int low, int high) {
    for (int i = high; i > low; --i) {
        if (arr[i] < arr[i - 1])
            swap(arr[i], arr[i - 1]);
    }
    for (int i = low + 2; i <= high; ++i) {
        int j = i;
        int value = arr[i];
        while (value < arr[j - 1]) {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = value;
    }
}

// Function to perform the partition for quicksort
int partition(int* arr, int low, int high) {
    int i = low, j = high + 1;
    int pivot = arr[low];
    while (true) {
        while (arr[++i] < pivot) {
            if (i == high) break;
        }
        while (pivot < arr[--j]) {
            if (j == low) break;
        }
        if (i >= j) break;
        swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;
}

// Function to find the median of three elements.
int medianOfThree(int* arr, int low, int high){
    int mid = low + (high - low) / 2;
    if (arr[high] < arr[low]) swap(arr[low], arr[high]);
    if (arr[mid] < arr[low]) swap(arr[low], arr[mid]);
    if (arr[high] < arr[mid]) swap(arr[mid], arr[high]);
    return mid;
}

// Quicksort implementation using CUTOFF and pivot with Median of 3.
void quickSort(int* arr, int low, int high) {
    if (high <= low + CUTOFF - 1) {
        insertionSort(arr, low, high);
        return;
    }
    int median = medianOfThree(arr, low, high);
    swap(arr[low], arr[median]);
    int partitionIndex = partition(arr, low, high);
    quickSort(arr, low, partitionIndex - 1);
    quickSort(arr, partitionIndex + 1, high);
}

int main(){
    ifstream inputFile("input_Q6.txt");
    if(!inputFile.is_open()){
        cerr<<"Error opening the input file"<<endl;
    }
    ofstream outputFile("output_Q6.txt");
    if(!outputFile.is_open()){
        cerr<<"Error opening the output file"<<endl;
    }
    long long int n;
    inputFile>>n;
    int arr[n];
    for(int i=0; i<n; i++){
        inputFile>>arr[i];
    }
    // Sorting array using quicksort algorithm where the pivot is almost the median of the array.

    auto start1 = high_resolution_clock::now();

    quickSort(arr, 0, n-1);

    auto stop1 = high_resolution_clock::now();
    outputFile<<"The time taken for sorting is: "<<duration_cast<microseconds>(stop1 - start1).count()<<" micro-seconds."<<endl;

    outputFile<<"The sorted array is: ";
    for (int i=0; i<n; i++){
        outputFile<<arr[i]<<" ";
    }
    outputFile<<endl;

return 0;
}
