//Longest Common Sequence
#include <string.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

int comparisonCounter=0;

string generateRandomString(int length) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis('A', 'Z');

    string randomString;
    for (int i = 0; i < length; ++i) {
        randomString += static_cast<char>(dis(gen));
    }

    return randomString;
}

int LCS(string a, string b) {
    int m = a.length();
    int n = b.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Obliczanie LCS
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            comparisonCounter++;
            if (a[i - 1] == b[j - 1]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else if(dp[i-1][j]<dp[i][j-1]){
                comparisonCounter++;
                dp[i][j] =  dp[i][j - 1];
            }
            else{
                comparisonCounter++;
                dp[i][j] =  dp[i-1][j];
            }
    }
    }

    return dp[m][n];
}

int main(){
    cout<<"Wpisz dwa wyrazy:"<<endl;
    string a;
    string b;

    cin >> a;
    cin >> b;


    cout<<LCS(a,b)<<endl;
    return 0; 
}