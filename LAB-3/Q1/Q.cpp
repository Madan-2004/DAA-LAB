# include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// Naive implementation => O(n^3).
vector <vector<int>> multiplyMatrix(vector <vector<int>> arr1, vector <vector<int>> arr2, int n){
    vector <vector<int>> ans(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            ans[i][j] = 0;
            for(int k=0; k<n; k++){
                ans[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
    return ans;
}

//  Divide and Conquer Implementation => O(n^3).
// vector <vector<int>> matrixMultiplyDivideConquer(const vector<vector<int>>& A, const vector<vector<int>>& B){
//     int n = A.size();
//     vector<vector<int>> C(n, vector<int>(n, 0));

//     if(n == 1){
//         C[0][0] = A[0][0] * B[0][0];
//     } 
//     else{
//         vector<vector<int>> A11(n/2, vector<int>(n/2, 0));
//         vector<vector<int>> A12(n/2, vector<int>(n/2, 0));
//         vector<vector<int>> A21(n/2, vector<int>(n/2, 0));
//         vector<vector<int>> A22(n/2, vector<int>(n/2, 0));

//         vector<vector<int>> B11(n/2, vector<int>(n/2, 0));
//         vector<vector<int>> B12(n/2, vector<int>(n/2, 0));
//         vector<vector<int>> B21(n/2, vector<int>(n/2, 0));
//         vector<vector<int>> B22(n/2, vector<int>(n/2, 0));

//         // Dividing matrices into sub-matrices
//         for (int i = 0; i < n/2; ++i) {
//             for (int j = 0; j < n/2; ++j) {
//                 A11[i][j] = A[i][j];
//                 A12[i][j] = A[i][j + n/2];
//                 A21[i][j] = A[i + n/2][j];
//                 A22[i][j] = A[i + n/2][j + n/2];

//                 B11[i][j] = B[i][j];
//                 B12[i][j] = B[i][j + n/2];
//                 B21[i][j] = B[i + n/2][j];
//                 B22[i][j] = B[i + n/2][j + n/2];
//             }
//         }

//         // Matrix multiplication using Divide and Conquer
//         vector<vector<int>> C11 = matrixMultiplyDivideConquer(A11, B11) + matrixMultiplyDivideConquer(A12, B21);
//         vector<vector<int>> C12 = matrixMultiplyDivideConquer(A11, B12) + matrixMultiplyDivideConquer(A12, B22);
//         vector<vector<int>> C21 = matrixMultiplyDivideConquer(A21, B11) + matrixMultiplyDivideConquer(A22, B21);
//         vector<vector<int>> C22 = matrixMultiplyDivideConquer(A21, B12) + matrixMultiplyDivideConquer(A22, B22);

//         for(int i = 0; i < n/2; ++i){
//             for(int j = 0; j < n/2; ++j){
//                 C[i][j] = C11[i][j];
//                 C[i][j + n/2] = C12[i][j];
//                 C[i + n/2][j] = C21[i][j];
//                 C[i + n/2][j + n/2] = C22[i][j];
//             }
//         }
//     }
//     return C;
// }

// Function to add two matrices
vector<vector<int>> addMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}

// Function to subtract two matrices
vector<vector<int>> subtractMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    return C;
}

// Strassen's algorithm.
vector<vector<int>> matrixMultiplyStrassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else {
        vector<vector<int>> A11(n/2, vector<int>(n/2, 0));
        vector<vector<int>> A12(n/2, vector<int>(n/2, 0));
        vector<vector<int>> A21(n/2, vector<int>(n/2, 0));
        vector<vector<int>> A22(n/2, vector<int>(n/2, 0));

        vector<vector<int>> B11(n/2, vector<int>(n/2, 0));
        vector<vector<int>> B12(n/2, vector<int>(n/2, 0));
        vector<vector<int>> B21(n/2, vector<int>(n/2, 0));
        vector<vector<int>> B22(n/2, vector<int>(n/2, 0));

        // Dividing matrices into sub-matrices
        for (int i = 0; i < n/2; ++i) {
            for (int j = 0; j < n/2; ++j) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + n/2];
                A21[i][j] = A[i + n/2][j];
                A22[i][j] = A[i + n/2][j + n/2];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + n/2];
                B21[i][j] = B[i + n/2][j];
                B22[i][j] = B[i + n/2][j + n/2];
            }
        }

        // Intermediate matrices
        vector<vector<int>> M1 = matrixMultiplyStrassen(addMatrices(A11, A22), addMatrices(B11, B22));
        vector<vector<int>> M2 = matrixMultiplyStrassen(addMatrices(A21, A22), B11);
        vector<vector<int>> M3 = matrixMultiplyStrassen(A11, subtractMatrices(B12, B22));
        vector<vector<int>> M4 = matrixMultiplyStrassen(A22, subtractMatrices(B21, B11));
        vector<vector<int>> M5 = matrixMultiplyStrassen(addMatrices(A11, A12), B22);
        vector<vector<int>> M6 = matrixMultiplyStrassen(subtractMatrices(A21, A11), addMatrices(B11, B12));
        vector<vector<int>> M7 = matrixMultiplyStrassen(subtractMatrices(A12, A22), addMatrices(B21, B22));

        // Combining results
        vector<vector<int>> C11 = addMatrices(subtractMatrices(addMatrices(M1, M4), M5), M7);
        vector<vector<int>> C12 = addMatrices(M3, M5);
        vector<vector<int>> C21 = addMatrices(M2, M4);
        vector<vector<int>> C22 = addMatrices(subtractMatrices(addMatrices(M1, M3), M2), M6);

        // Combining results
        for (int i = 0; i < n/2; ++i) {
            for (int j = 0; j < n/2; ++j) {
                C[i][j] = C11[i][j];
                C[i][j + n/2] = C12[i][j];
                C[i + n/2][j] = C21[i][j];
                C[i + n/2][j + n/2] = C22[i][j];
            }
        }
    }
    return C;
}

// Function to print a matrix
void printMatrix(const vector<vector<int>>& matrix){
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}


int main(){
    // freopen("input_Q1.txt", "r", stdin);
    // freopen("output_Q1.txt", "w", stdout);
    long long int n;
    cin>>n;
    vector <vector<int>> arr1(n), arr2(n);

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin>>arr1[i][j];
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin>>arr2[i][j];
        }
    }
    
    vector <vector<int>> ans1 = multiplyMatrix(arr1, arr2, n);
    // vector <vector<int>> ans2 = matrixMultiplyDivideConquer(arr1, arr2);
    vector <vector<int>> ans3 = matrixMultiplyStrassen(arr1, arr2);
    printMatrix(ans1);
    printMatrix(ans3);
    // fclose(stdin);
    // fclose(stdout);

return 0;
}