#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (int)a; i <= (int)b;  ++ i)
#define repd(i, a, b) for(int i = (int)a; i >= (int)b; -- i)
#define inf (int)1e9
#define mod 1000000007
const int nmax = (int)1e6;
#define north 0
#define south 1
#define east 2
#define west 3

int n, m, a[55][55];
int begx, begy, finx, finy;

struct robot {

    vector<pair<int, int> > pos;
    int dir;
    int get_hash() {
       return (pos[0].first * 1007  + pos[0].second   + dir * 10007);
    }

};

int main() {

     #ifndef ONLINE_JUDGE 
        freopen("in", "r", stdin); 
       // freopen("out", "w", stdout); 
    #endif  
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
   

    while(1) {
        
        cin >> n >> m;
        if(n == 0 && m == 0) break;

        rep(i, 0, n - 1) {
            rep(j, 0, m - 1) {
                cin >> a[i][j];
            }
        }

        cin >> begx >> begy >> finx >> finy;
        begx --;
        begy --;
        finx --;
        finy --;
        string dir;
        int ddir;
        cin >> dir;
        

        robot rob;
        rob.pos.push_back(make_pair(begx, begy));
        rob.pos.push_back(make_pair(begx, begy + 1));
        rob.pos.push_back(make_pair(begx + 1, begy));
        rob.pos.push_back(make_pair(begx + 1, begy + 1));
        
        if(dir == "east") {
            ddir = east;
        }
        if(dir == "west") {
            ddir = west;
        }
        if(dir == "north") {
            ddir = north;
        }
        if(dir == "south") {
            ddir = south;
        }
        rob.dir = ddir;

        queue<robot > Q;

        Q.push(rob);   
        
        map<int, bool> vis;
        vector<int > dist(500000, -1);
        vis[rob.get_hash()] = true;
        dist[rob.get_hash()] = 0;


        int ans = -1;
        while(Q.size()) {

            rob = Q.front();
                  Q.pop();
            
            
            if(rob.pos[0].first == finx && rob.pos[0].second == finy) {
                ans = dist[rob.get_hash()];
                break;
            }

            if(rob.dir == south) {
                                        
                for(int step = 1; step <= 3; step ++) {     
                    robot bb;                               
                    bool ok = true;                             
                    
                    rep(i, 0, rob.pos.size() - 1) {             
                        int xx = rob.pos[i].first + step;       
                        int yy = rob.pos[i].second; 
                        
                        if(xx >= n) ok = false;
                        else {
                            for(int k = step - 1; k >= 0; k --) {
                                if(a[xx - k][yy] == 1) ok = false;
                            }
                        }
                        bb.pos.push_back(make_pair(xx, yy));     
                    }
                    
                    if(ok) {                                    
                        bb.dir = south;
                        if(!vis[bb.get_hash()]){ 
                            Q.push(bb);
                            vis[bb.get_hash()] = true;
                            dist[bb.get_hash()] = dist[rob.get_hash()] + 1;
                        }
                    } 
                }                                           

                robot bb;
                bb = rob;
                bb.dir = west;
                if(!vis[bb.get_hash()]) {
                    Q.push(bb);
                    vis[bb.get_hash()] = true;
                    dist[bb.get_hash()] = dist[rob.get_hash()] + 1;   
                } 
               
                bb.dir = east;
                if(!vis[bb.get_hash()]) {
                    Q.push(bb);
                    vis[bb.get_hash()] = true; 
                    dist[bb.get_hash()] = dist[rob.get_hash()] + 1;  
                } 
            }

            if(rob.dir == north) {
                
                for(int step = 1; step <= 3; step ++) {
                    
                    robot bb;
                    bool ok = true;

                    rep(i, 0, rob.pos.size() - 1) {
                        int xx = rob.pos[i].first - step;
                        int yy = rob.pos[i].second;
                        if(xx < 0) ok = false;
                        else {
                            for(int k = step - 1; k >= 0; k --) {
                                if(a[xx + k][yy] == 1) ok = false;
                            }
                        }
                        bb.pos.push_back(make_pair(xx, yy));
                    } 
                    
                    if(ok) {
                        bb.dir = north;
                        if(!vis[bb.get_hash()]){
                            Q.push(bb);
                            vis[bb.get_hash()] = true;
                            dist[bb.get_hash()] = dist[rob.get_hash()] + 1;   
                        }  
                    } 

                }

                robot bb;
                bb = rob;
                bb.dir = west;
                if(!vis[bb.get_hash()]) {
                    Q.push(bb);
                    vis[bb.get_hash()] = true;
                    dist[bb.get_hash()] = dist[rob.get_hash()] + 1;   
                } 

                bb.dir = east;
                if(!vis[bb.get_hash()]){
                    Q.push(bb);
                    vis[bb.get_hash()] = true;   
                    dist[bb.get_hash()] = dist[rob.get_hash()] + 1;
                } 
            }
            if(rob.dir == west) {

                for(int step = 1; step <= 3; step ++) {
                    
                    robot bb;
                    bool ok = true;

                    rep(i, 0, rob.pos.size() - 1) {
                        int xx = rob.pos[i].first;
                        int yy = rob.pos[i].second - step;                    
                        if(yy < 0) ok = false;
                        else {
                            for(int k = step - 1; k >= 0; k --) {
                                if(a[xx][yy + k] == 1) ok = false;
                            }
                        }
                        bb.pos.push_back(make_pair(xx, yy));
                    } 
                    
                    if(ok) {
                        bb.dir = west; 
                        if(!vis[bb.get_hash()]) {
                            Q.push(bb);
                            vis[bb.get_hash()] = true;
                            dist[bb.get_hash()] = dist[rob.get_hash()] + 1;   
                        } 
                    }

                }

                robot bb;
                bb = rob;
                bb.dir = north;
                if(!vis[bb.get_hash()]) {
                    Q.push(bb);
                    vis[bb.get_hash()] = true;
                    dist[bb.get_hash()] = dist[rob.get_hash()] + 1;   
                } 
                bb.dir = south;
                if(!vis[bb.get_hash()]) {
                    Q.push(bb);
                    vis[bb.get_hash()] = true;
                    dist[bb.get_hash()] = dist[rob.get_hash()] + 1;   
                } 

            }
            if(rob.dir == east) {

                for(int step = 1; step <= 3; step ++) {
                    robot bb;
                    bool ok = true;
                    

                    rep(i, 0, rob.pos.size() - 1) {
                        int xx = rob.pos[i].first;
                        int yy = rob.pos[i].second + step;
                        if(yy >= m) ok = false;
                        else {
                            for(int k = step - 1; k >= 0; k --) {
                                if(a[xx][yy - k] == 1) ok = false;
                            }
                        }
                        bb.pos.push_back(make_pair(xx, yy));
                    }


                    if(ok) {
                        bb.dir = east;
                        if(!vis[bb.get_hash()]) {
                            Q.push(bb);
                            vis[bb.get_hash()] = true;
                            dist[bb.get_hash()] = dist[rob.get_hash()] + 1;   
                        } 
                    }

                }

                robot bb; 
                bb = rob; 
                bb.dir = north;   
                if(!vis[bb.get_hash()]) {
                    Q.push(bb);
                    vis[bb.get_hash()] = true;   
                    dist[bb.get_hash()] = dist[rob.get_hash()] + 1;
                } 
                bb.dir = south;  
                if(!vis[bb.get_hash()]) {
                    Q.push(bb);
                    vis[bb.get_hash()] = true;   
                    dist[bb.get_hash()] = dist[rob.get_hash()] + 1;
                } 

            }

        }

        cout << ans << endl;

    }
    
    return 0;
}