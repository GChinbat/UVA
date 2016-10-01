#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int )1e9

int too[10];
int main() {

    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif

    int T;
    cin >> T;
    for(int test = 1; test <= T; test ++ ){
        string s;
        cin >> s;
        memset(too, 0, sizeof too);
        for(int i = 0; i < s.size(); i ++ ){
            too[s[i] - '0'] ++;
        } 
        int sum = 0;
        for(int i = 0; i < 10; i ++ ){
            sum += too[i] * i;
        }
        bool S = 0;
        int three = too[0] + too[3] + too[6] + too[9];

        for(int i = 1; i < 10; i ++ ) {
            if(too[i] > 0) {
                
                if((sum - i) % 3 == 0) {
                    if(i % 3 == 0) {
                        if((three - 1) % 2 == 0) {
                            S |= true;
                        }
                    }else if(three % 2 == 0) {
                        S |= true;
                    }
                }
            }
        }
        cout << "Case " << test << ": ";
        if(S) cout << "S" << endl;
        else cout << "T" << endl;

    }



    return 0;
}