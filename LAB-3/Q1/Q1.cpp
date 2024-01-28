#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
using namespace std::chrono;

typedef vector<vector<int>> Matrix; // Matrix
typedef vector<int> vi; 

Matrix matrixAddition(const Matrix &A, const Matrix &B){
    int n = A.size(), m = A[0].size() ;
    Matrix result(n, vi(m));
    rep(i,0,n){
        rep(j,0,m){
            result[i][j] = A[i][j] + B[i][j]; 
        }
    }
    return result;
}

Matrix matrixSubtraction(const Matrix &A, const Matrix &B){
    int n = A.size(), m = A[0].size() ;
    Matrix result(n, vi(m));
    rep(i,0,n){
        rep(j,0,m){
            result[i][j] = A[i][j] - B[i][j]; 
        }
    }
    return result;
}

// Naive Implementation => O(n^3).

Matrix naiveMatrixMultiplication(const Matrix &A, const Matrix &B) {
    int n1 = A.size();
    int n2 = B.size();

    if (n1 != n2) {
        cerr << "\nError: Enter valid matrices.\n";
        return {};
    }

    int n = n1;
    Matrix C(n, vi(n,0));

    rep(i,0,n) {
        rep(j,0,n) {
            rep(k,0,n) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

// Divide And Conquer Implementation.
// T(n) = 8T(n/2) + O(n^2)  => O(n^3) same as the naive method and taking extra space.

Matrix divideAndConquerMatrixMultiplication(const Matrix &A,const Matrix &B)
{
    int n1 = A.size();
    int n2 = B.size();

    if (n1 != n2)
    {
        cerr << "\nError: enter vaild Matrices\n ";
        return {};
    }

    Matrix c(n1, vi(n1,0));

    if (n1 == 1) { c[0][0] = A[0][0] * B[0][0]; return c;} // base case

    int v = log2(n1);
    if (pow(2,v) != n1 ) { n1 = pow(2,v+1); } // padding for matrix of size other than 2 powers


    int si = n1 / 2;

    Matrix a00(si, vi(si,0)), a01(si, vi(si,0)), a10(si, vi(si,0)), a11(si, vi(si,0));
    Matrix b00(si, vi(si,0)), b01(si, vi(si,0)), b10(si, vi(si,0)), b11(si, vi(si,0));

    rep(i, 0, si)
    {
        rep(j, 0, si)
        {
            a00[i][j] = A[i][j];
            b00[i][j] = B[i][j];
            if(j + si < n2) {
               a01[i][j] = A[i][j + si];
               b01[i][j] = B[i][j + si];
            }
            if(i + si < n2) {
               a10[i][j] = A[si + i][j];
               b10[i][j] = B[si + i][j];
            }
            if(j + si < n2 && i + si < n2){
               a11[i][j] = A[i + si][j + si];
               b11[i][j] = B[i + si][j + si];
            }
        }
    }

    Matrix c_00 = matrixAddition(divideAndConquerMatrixMultiplication(a00, b00),divideAndConquerMatrixMultiplication(a01, b10));
    Matrix c_01 = matrixAddition(divideAndConquerMatrixMultiplication(a00, b01),divideAndConquerMatrixMultiplication(a01, b11));
    Matrix c_10 = matrixAddition(divideAndConquerMatrixMultiplication(a10, b00),divideAndConquerMatrixMultiplication(a11, b10));
    Matrix c_11 = matrixAddition(divideAndConquerMatrixMultiplication(a10, b01),divideAndConquerMatrixMultiplication(a11, b11));

    rep(i, 0, si)
    {
        rep(j, 0, si)
        {
            c[i][j] = c_00[i][j];
            if(j + si < n2) {
               c[i][j + si] = c_01[i][j];
            }
            if(i + si < n2) {
               c[si + i][j] = c_10[i][j];
            }
            if(j + si < n2 && i + si < n2){
               c[i + si][j + si] = c_11[i][j];
            }
        }
    }

    c_00.clear(); c_01.clear(); c_10.clear(); c_11.clear();
    a00.clear(); a01.clear(); a10.clear(); a11.clear(); b00.clear(); b01.clear(); b10.clear(); b11.clear();
    
    return c;
}


// Divide and Conquer with Strassen's Algorithm.
// T(n) = 7T(n/2) + O(n^2) => O(n^2.81) better than naive but not practical.

Matrix strassenMatrixMultiplication(const Matrix &A,const Matrix &B) {
    int n1 = A.size();
    int n2 = B.size();

    if (n1 != n2) {
        cerr << "\nError: Enter valid matrices.\n";
        return {};
    }

    int n = n1;
    Matrix C(n, vi(n,0));

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int v = log2(n);
    if (pow(2,v) != n) {
        n = pow(2,v+1);
    }

    int si = n / 2;

    Matrix a00(si, vi(si,0)), a01(si, vi(si,0)), a10(si, vi(si,0)), a11(si, vi(si,0));
    Matrix b00(si, vi(si,0)), b01(si, vi(si,0)), b10(si, vi(si,0)), b11(si, vi(si,0));

    rep(i, 0, si) {
        rep(j, 0, si) {
            a00[i][j] = A[i][j];
            b00[i][j] = B[i][j];
            if(j + si < n2) {
               a01[i][j] = A[i][j + si];
               b01[i][j] = B[i][j + si];
            }
            if(i + si < n2) {
               a10[i][j] = A[si + i][j];
               b10[i][j] = B[si + i][j];
            }
            if(j + si < n2 && i + si < n2) {
               a11[i][j] = A[i + si][j + si];
               b11[i][j] = B[i + si][j + si];
            }
        }
    }

    Matrix p1 = strassenMatrixMultiplication(a00, matrixSubtraction(b01,b11));
    Matrix p2 = strassenMatrixMultiplication(matrixAddition(a00,a01), b11);
    Matrix p3 = strassenMatrixMultiplication(matrixAddition(a10,a11), b00);
    Matrix p4 = strassenMatrixMultiplication(a11, matrixSubtraction(b10,b00));
    Matrix p5 = strassenMatrixMultiplication(matrixAddition(a00,a11), matrixAddition(b00,b11));
    Matrix p6 = strassenMatrixMultiplication(matrixSubtraction(a01,a11), matrixAddition(b10,b11));
    Matrix p7 = strassenMatrixMultiplication(matrixSubtraction(a00,a10), matrixAddition(b00,b01));

    Matrix c_00 = matrixSubtraction(matrixAddition(matrixAddition(p5,p4),p6),p6);
    Matrix c_01 = matrixAddition(p1,p2);
    Matrix c_10 = matrixAddition(p3,p4);
    Matrix c_11 = matrixSubtraction(matrixAddition(p1,p5),matrixAddition(p3,p7));

    rep(i, 0, si) {
        rep(j, 0, si) {
            C[i][j] = c_00[i][j];
            if(j + si < n2) {
               C[i][j + si] = c_01[i][j];
            }
            if(i + si < n2) {
               C[si + i][j] = c_10[i][j];
            }
            if(j + si < n2 && i + si < n2) {
               C[i + si][j + si] = c_11[i][j];
            }
        }
    }

    return C;
}

int main(){

    freopen("input_Q1.txt","r",stdin);
    freopen("output_Q1.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tt;
    cin >> tt; 
    while(tt--) {
        int n; 
        cin >> n;
        Matrix A(n,vi(n)), B(n,vi(n));
        rep(i,0,n){
            rep(j,0,n){
                cin >> A[i][j];
            }
        }
        rep(i,0,n){
            rep(j,0,n){
                cin >> B[i][j];
            }
        }
        
        auto start1 = high_resolution_clock::now(); // Start time
        Matrix C_naive = naiveMatrixMultiplication(A,B);
        auto stop1 = high_resolution_clock::now(); // Stop time
        auto duration = duration_cast<microseconds>(stop1 - start1);
        cout<<"The time taken by naive method: "<<duration.count()<<" microseconds."<<endl;

        auto start2 = high_resolution_clock::now();
        Matrix C_DC = divideAndConquerMatrixMultiplication(A,B);
        auto stop2 = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop2 - start2);
        cout<<"The time taken by Divide And Conquer method: "<<duration.count()<<" microseconds."<<endl;


        cout<<"The resultant matrix through naive method is: "<<endl;
        rep(i,0,n){
            rep(j,0,n){
                cout << C_naive[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        cout<<"The resultant matrix through divide and conquer method is: "<<endl;
        rep(i,0,n){
            rep(j,0,n){
                cout << C_DC[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

return 0;
}
