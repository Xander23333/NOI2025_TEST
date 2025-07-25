#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;

long long calculateF(const vector<int>& arr, const vector<int>& B) {
    long long result = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == 0) {
            result += B[i];
        }
    }
    return result;
}

long long calculateG(const vector<int>& arr, const vector<int>& C) {
    long long result = 1;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == 0) {
            result = (result * C[i]) % MOD;
        }
    }
    return result;
}

pair<long long, long long> solve(vector<int> A, vector<int> B, vector<int> C) {
    int n = A.size();
    set<vector<int>> visited;
    queue<vector<int>> q;
    
    q.push(A);
    visited.insert(A);
    
    long long maxF = 0;
    long long sumG = 0;
    
    while (!q.empty()) {
        vector<int> current = q.front();
        q.pop();
        
        // Calculate f and g for current state
        long long f = calculateF(current, B);
        long long g = calculateG(current, C);
        
        maxF = max(maxF, f);
        sumG = (sumG + g) % MOD;
        
        // Try all possible operations
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (abs(i - j) == 1 && current[i] <= current[j] && current[i] > 0) {
                    vector<int> next = current;
                    next[j] -= next[i];
                    next[i] = 0;
                    
                    if (visited.find(next) == visited.end()) {
                        visited.insert(next);
                        q.push(next);
                    }
                }
            }
        }
    }
    
    return {maxF, sumG};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int c, t;
    cin >> c >> t;
    
    for (int test = 0; test < t; test++) {
        int n;
        cin >> n;
        
        vector<int> A(n), B(n), C(n);
        
        for (int i = 0; i < n; i++) {
            cin >> A[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> B[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> C[i];
        }
        
        auto result = solve(A, B, C);
        cout << result.first << " " << result.second << "\n";
    }
    
    return 0;
}