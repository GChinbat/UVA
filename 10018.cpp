#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e9


vector<int > add(vector<int > a, vector<int > b) {

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    vector<int > c;
    int sansan = 0;
    for(int i = 0; i < min(a.size(), b.size()); i ++ ){ 
        int num = a[i] + b[i] + sansan;
        c.pb(num % 10);
        sansan = num /= 10;
    }   
    for(int i = a.size(); i < b.size(); i ++ ) {
        int num = b[i] + sansan;
        c.pb(num % 10);
        sansan = num /= 10;
    }    
    for(int i = b.size(); i < a.size(); i ++ ) {
        int num = a[i] + sansan;
        c.pb(num % 10);
        sansan = num /= 10;
    }    
    if(sansan > 0) c.pb(sansan);
    reverse(c.begin(), c.end());

    return c;
}

bool ispal(vector<int > a) {
    int n = a.size();
    //012 345
    //012 3 456
    for(int i = 0; i < n / 2; i ++ ){
        if(a[i] != a[n - i - 1]) return false;
    }
    return true;
}
vector<int > ans;
int solve(vector<int > a) {
    if(ispal(a)){ans = a; return 0;}
    vector<int > b = a;
    reverse(b.begin(), b.end());
    a = add(a, b);
    return 1 + solve(a);
}


int main() {
    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif

    int n;
    cin >> n;
    while(n -- ) {
        string s;
        cin >> s;
        vector<int > a;
        for(int i = 0; i < s.size(); i ++ ) {
            a.pb(s[i] - '0');
        }
        int res = solve(a);
        cout << res << " ";
        for(int i = 0; i < ans.size(); i ++ ) {
            cout << ans[i];
        } cout << endl;
    }


    return 0;
}