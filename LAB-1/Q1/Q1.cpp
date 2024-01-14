# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

int largestSum(int arr[], int n){       // Brute force => n^2 time complexity.
    int maxSum = INT_MIN;
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            int sum = arr[i] + arr[j];
            if(sum > maxSum){
                maxSum = sum;
            }
        }
    }
    return maxSum;
}

int main(){
    freopen("input_Q1.txt", "r", stdin);
    freopen("output_Q1.txt", "w", stdout);
    long long int n;
        // cout<<"Enter the size of the array: "<<endl;
    cin>>n;

    long long int arr[n];

        // cout<<"Enter the elements of the array: "<<endl;
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }

    sort(arr, arr+n);       // It takes n*logn time complexity.

    cout<<"The maximum sum is: "<<arr[n-2] + arr[n-1]<<endl;

    fclose(stdin);
    fclose(stdout);

return 0;
}