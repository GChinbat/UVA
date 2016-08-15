#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e9
#define nmax 4004


map<string, int> has;
int n;

vector<pair<int, pair<int, int> > > graph[nmax];
vector<int > dist[30], vis[30];


void solve(int s, int t) {
    
    for(int i = 0; i < 30; i++) {
        dist[i].assign(nmax, inf);
        vis[i].assign(nmax, 0);
    }

    dist[28][s] = 0;
    priority_queue<pair<int, pair<int, char> > > Q;
    Q.push(mp(-dist[28][s], mp(s, 28)));
    
    while(Q.size()) {
           pair<int, pair<int, int> > u = Q.top();
                                           Q.pop(); 
           int uu = u.second.first;
           int uch = u.second.second;
           int uw = -u.first;
           vis[uch][uu] = true;
            
           if(dist[uch][uu] < uw) continue;

           for(int i = 0; i < graph[uu].size(); i++) {
                pair<int, pair<int, char> > v = graph[uu][i];
                int vv = v.first;
                int vw = v.second.first;
                int vch = v.second.second;

                if(uch == vch || vis[vch][vv]) continue; 

                if(dist[vch][vv] > dist[uch][uu] + vw) {

                    dist[vch][vv] = dist[uch][uu] + vw;
                    Q.push(mp(-dist[vch][vv], mp(vv, vch)));

                }

           }

    }

    int ans = inf;
    for(int i = 0; i < 29; i++) {
        ans = min(ans, dist[i][t]);
    } 
    if(ans == inf) {
        cout << "impossivel" << endl;
    }else cout << ans << endl;
   
    for(int i = 1; i <= n; i++) graph[i].clear();

    return ;
}



int main() {

    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif

    int m;
    while(true) {
        cin >> m;
        if(m == 0) break;
        n = 0;
        has.clear();
        string ss, st;
        cin >> ss >> st;
        if(has[ss] == 0) has[ss] = ++ n;
        if(has[st] == 0) has[st] = ++ n;
        int s, t;
        s = has[ss]; t = has[st];

        while(m -- ) {
            string su, sv, sw;
            cin >> su >> sv >> sw;
            if(has[su] == 0) has[su] = ++ n;
            if(has[sv] == 0) has[sv] = ++ n;
            int u = has[su];
            int v = has[sv];
            graph[u].pb(mp(v, mp(sw.size(), sw[0] - 'a')));
            graph[v].pb(mp(u, mp(sw.size(), sw[0] - 'a')));
        }
        
        solve(s, t);

    }


    return 0;
}