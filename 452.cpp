#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e9

vector<int > graph[30];
int day[30], in[30];
void convert(string s) {
    s += " ";
    int u = s[0] - 'A';
    in[u] = 0;
    int beg = 2;
    for(int i = 2; i < s.size(); i ++) {
        if(s[i] == ' ') {
            beg = i - 1;
            break;
        }
    }
    int val = 0;
    int num = 1;
    for(int i = beg; i >= 2; i -- ) {
        val += (s[i] - '0') * num;
        num *= 10;
    }
    for(int i = beg + 2; i < s.size() - 1; i ++ ){
        graph[s[i] - 'A'].pb(u);
        in[u] ++;
    }
    day[u] = val;
    return ;
}

bool vis[30];
int dp[30];
void dfs(int u) {
    vis[u] = true;

    if(graph[u].size() == 0) {
        dp[u] = day[u];
        return ;
    }

    for(int i = 0; i < graph[u].size(); i ++ ){
        int v = graph[u][i];
        if(!vis[v]) dfs(v);
        dp[u] = max(dp[u], day[u] + dp[v]);
    }

}


int main() {

    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif  
    ios_base :: sync_with_stdio(false);
    cin.tie(0); cout.tie(0);


    int T;
    cin >> T;
    string s;
    getline(cin, s);   
    getline(cin, s); 
    while(T -- ) {
        for(int i = 0; i < 26;  i++) graph[i].resize(0);
        memset(day, 0, sizeof day);
        memset(in, -1, sizeof in);
        memset(vis, false, sizeof vis);
        memset(dp, 0, sizeof dp);
       
        while(getline(cin, s)){
            if(s == "") break;
            convert(s);
        }
        
        int root = 26;
        for(int i = 0; i < 26; i ++) {
            if(in[i] == 0) {
                graph[root].pb(i);
            }
        }
        dfs(root);
        cout << dp[root] << endl;
        if(T > 0) cout << endl;
    }

    return 0;
}