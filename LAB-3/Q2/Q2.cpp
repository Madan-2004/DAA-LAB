# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

long long int Kadanes_algo(vector <long long int> arr, long long int n){       // In O(n) time-complexity.
    
    long long int curr = 0, max_sum = INT_MIN;

    for(long long int i=0; i<n; i++){
        if(curr+arr[i] > 0){
            curr += arr[i];
            max_sum = max(curr, max_sum);
        }
        else{
            curr = 0;
            max_sum = max(arr[i], max_sum);
        }
    }
return max_sum;
}

long long int max(long long int a, long long int b, long long int c){
    return max(max(a,b), c);
}

long long int crossSum(vector <long long int> arr, long long int l, long long int m, long long int h){
    long long int left_sum = INT_MIN;
    long long int right_sum = INT_MIN;
    long long int sum = 0;
    for(long long int i=m; i>=l; i--){
        sum += arr[i];
        left_sum = max(sum, left_sum);
    }
    sum = 0;
    for(long long int i=m; i<=h; i++){
        sum += arr[i];
        right_sum = max(right_sum, sum);
    }

    return max(left_sum+right_sum-arr[m], left_sum, right_sum);
}

long long int maxSumDC(vector <long long int> arr, long long int l, long long int h){  // It takes O(nlogn) time-com[plexity.]
    if(l > h) return INT_MIN;
    if(l == h) return arr[l];

    long long int m = l + (h-l)/2;

    return max(maxSumDC(arr, l , m-1), maxSumDC(arr, m+1, h), crossSum(arr, l, m, h));
}

// O(n) time-complexity Divide and Conquer method.
struct Node{
    long long int max_val;
    long long int prefix_sum;
    long long int suffix_sum;
    long long int total_sum;
};

Node getNode(long long int x){
    Node a;
    a.max_val = x;
    a.prefix_sum = x;
    a.suffix_sum = x;
    a.total_sum = x;
    return a;
}

Node mergeNodes(const Node &left, const Node &right){
    Node merged_node;
    merged_node.max_val = max({left.max_val, right.max_val, left.suffix_sum + right.prefix_sum});
    merged_node.prefix_sum = max(left.prefix_sum, left.total_sum + right.prefix_sum);
    merged_node.suffix_sum = max(right.suffix_sum, right.total_sum + left.suffix_sum);
    merged_node.total_sum = left.total_sum + right.total_sum;
    return merged_node;
}

Node getMaxSubArraySum(int left, int right, vector<long long int> &arr) {
    if (left == right)
        return getNode(arr[left]);

    int mid = (left + right) >> 1;
    Node left_node = getMaxSubArraySum(left, mid, arr);
    Node right_node = getMaxSubArraySum(mid + 1, right, arr);
    return mergeNodes(left_node, right_node);
}


int main(){
    freopen("input_Q2.txt", "r", stdin);
    freopen("output_Q2.txt", "w", stdout);
    long long int n;
    cin>>n;
    vector <long long int> arr(n);
    for(long long int i=0; i<n; i++){
        cin>>arr[i];
    }

    auto start1 = high_resolution_clock::now();

    int max_sum = Kadanes_algo(arr, n);

    auto stop1 = high_resolution_clock::now();
    cout<<"The time taken by Kadane's algorithm is: "<<duration_cast<microseconds>(stop1 - start1).count()<<" micro-seconds."<<endl;

    cout<<"The maximum sum using Kadane's algorithm is: "<<max_sum<<"."<<endl;

    // Divide and Conquer => O(nlogn) time-complexity.

    // auto start2 = high_resolution_clock::now();

    // int max_sumDC = maxSumDC(arr, 0, n-1);

    // auto stop2 = high_resolution_clock::now();
    // cout<<"The time taken by divide and conquer in O(nlogn) time-complexity is: "<<duration_cast<microseconds>(stop2 - start2).count()<<" micro-seconds."<<endl;

    // cout<<"The maximum sum using divide and conquer in O(nlogn) time-complexity is: "<<max_sumDC<<endl;

    // Divide and Conquer => O(n) time-complexity approach.

    auto start3 = high_resolution_clock::now();

    Node result = getMaxSubArraySum(0, n - 1, arr);

    auto stop3 = high_resolution_clock::now();
    cout<<"The time taken by divide and conquer in O(n) time-complexity is: "<<duration_cast<microseconds>(stop3 - start3).count()<<" micro-seconds."<<endl;

    cout<<"The maximum sum using divide and conquer in O(n) time-complexity is: "<<result.max_val<<"."<<endl;

    fclose(stdin);
    fclose(stdout);

return 0;
}