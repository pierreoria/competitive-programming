// lca with euler tour and seg tree

#include <bits/stdc++.h>

using namespace std;

#define br '\n'

typedef tuple<int,int> ii;

const int inf = 1e9;
const int N = 1003;
int n;
vector<ii> t(4 * N);
int first[N], indeg[N];
vector<int> euler,h;

// t armazena (h, indice).
// faço query na seg, pego indice e descubro o  vertice indo pra first[idx]

void build() {  // build the tree
  for (int i = n - 1; i > 0; --i) {  
    if (get<0>(t[i<<1]) < get<0>(t[i<<1|1])){
        t[i] = t[i<<1];
    }
    else t[i] = t[i<<1|1];
  }
}

int query(int l, int r) {  // retorna indice do menor do intervalo [l, r)
  int mn = inf;
  int ans;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) {
        if (get<0>(t[l]) < mn){
            mn = get<0>(t[l]);
            ans = get<1>(t[l]);
        }
        l++;
    }
    if (r&1) 
    {
        r--;
        if (get<0>(t[r]) < mn){
            mn = get<0>(t[r]);
            ans = get<1>(t[r]);
        }
    }
  }
  return ans;
}

void dfs(vector<vector<int>>& adj, int u, int d)
{
    euler.push_back(u);
    h.push_back(d);

    for (int v: adj[u]){
        dfs(adj,v,d+1);
        euler.push_back(u);
        h.push_back(d);
    } 
}



int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL);

    int T,q,u,v,m,locn;

    cin>>T;

    for (int y = 1; y <= T; y++)
    {
        cin>>locn;

        vector<vector<int>> adj(locn);
        for (int i = 0; i < locn; i++) indeg[i] = 0, first[i] = -1;

        for (int i = 0; i < locn; i++){
            cin>>m;
            for (int j = 0; j < m; j++){
                cin>>v; v--;
                adj[i].push_back(v);
                indeg[v]++;
            } 
        }

        for (int i = 0; i < locn; i++){
            if (!indeg[i]){
                dfs(adj,i,0);
                break;
            }
        }

        n = euler.size();

        for (int i = 0; i < n; i++){
            if (first[euler[i]] == -1){
                first[euler[i]] = i;
            }
        }

        

    
        for (int i = 0; i < n; i++){
            t[n+i] = {h[i],i};
            //cout << h[i] << "," << i << br;
        }

        build();

        cin>>q;        
        
        cout << "Case " << y << ":\n";
        for (int i = 0; i < q; i++)
        {
            cin>>u>>v; u--; v--;
            u = first[u];
            v = first[v];

            if (u > v) swap(u,v);

            v++;

            int idx = query(u,v);

            int ans = euler[idx]+1;

            cout << ans << br;
        }



    }

    
}
