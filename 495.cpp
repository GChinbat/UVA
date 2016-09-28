#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e9

vector<int > add(vector<int> a, vector<int > b) {
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    vector<int > c; 
    int sansan = 0;
    for(int i = 0; i < min(a.size(), b.size()); i ++ ){
        int sum = a[i] + b[i] + sansan;
        c.pb(sum % 10);
        sansan = sum / 10;
    }
    for(int i = a.size(); i < b.size(); i ++ ) {
        int sum = b[i] + sansan;
        c.pb(sum % 10);
        sansan = sum / 10;    
    }
    for(int i = b.size(); i < a.size(); i ++ ) {
        int sum = a[i] + sansan;
        c.pb(sum % 10);
        sansan = sum / 10;    
    }
    if(sansan > 0) c.pb(sansan);
    reverse(c.begin(), c.end());
    return c;
}

vector<int > fib[5005];

int main() {

    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif

    fib[0].pb(0);
    fib[1].pb(1);

    for(int i = 2; i <= 5000; i ++ ){
        fib[i] = add(fib[i - 1], fib[i - 2]);
    }

    int n;
    while(cin >> n) {
        cout << "The Fibonacci number for " << n << " is ";
        for(int i = 0; i < fib[n].size(); i ++ ) {
            cout << fib[n][i];
        } cout << endl;
    }

    return 0;
}