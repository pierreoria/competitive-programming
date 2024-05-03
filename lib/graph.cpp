#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define br '\n'
#define pb push_back


typedef long long ll;
typedef pair<long long, long long> pii;


// dijkstra

const ll mx = 1e5;
ll dist[mx];
bitset<mx> vis;

void dijkstra(vector<vector<pii>>& g)
{
    ll u,v,d,w;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    d = 0;
    pq.push({d,0});
    
    while(!pq.empty())
    {

        d = pq.top().ff; u = pq.top().ss; pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (pii p : g[u])
        {
            w = p.ff; v = p.ss;

            if (d + w < dist[v]){
                dist[v] = d + w;
                pq.push({d+w,v});
            }
        }
    }
}


// kosaraju



const int mx = 1e6;

bitset<mx> vis,repvis;

void dfs(vector<vector<int>>& adj, stack<int>& ord, int u)
{
    vis[u] = 1;
    for (int v : adj[u]) {
        if (!vis[v]) {
            dfs(adj,ord,v);
        }
    }
    ord.push(u);
}

// s (source) eh representante do scc
void dfs2(vector<vector<int>>& scc, vector<vector<int>>& adjT, vector<int>& rep, int s, int u) 
{
    vis[u] = 1;
    rep[u] = s;
    scc[s].pb(u);

    for (int v : adjT[u]) {
        if (!vis[v]) {
            dfs2(scc,adjT,rep,s,v);
        }
    }
}

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t,n,u,g,v,r,sz,repcnt;
    char p;

    cin>>t;

    while(t--)
    {
        cin>>n;

        vis.reset();
        repvis.reset();
        vector<vector<int>> adj(n);
        vector<vector<int>> adjT(n);
        vector<vector<int>> scc(n);
        vector<int> rep(n);
        stack<int> ord;
        repcnt = 0;
        string gp; // numero:

        ord.push(-1); // evitar verificacao empty


        for (int i = 0; i < n; i++)
        {
            cin>>u>>gp;

            gp.pop_back(); // dois pontos

            g = stoi(gp);

            for (int j = 0; j < g; j++)
            {
                cin>>v;
                adj[u].pb(v);
                adjT[v].pb(u);
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (!vis[i]) {
                dfs(adj,ord,i);
            }
        }

        vis.reset();

        while (ord.top() != -1)
        {
            u = ord.top(); ord.pop();
            if (!vis[u]) {
                repcnt++;
                dfs2(scc,adjT,rep,u,u);
            }
        }

        cout << repcnt << br;
        for (int i = 0; i < n; i++)
        {
            r = rep[i];
            if (!repvis[r])
            {
                repvis[r] = 1;
                sz = scc[r].size();
                sort(scc[r].begin(), scc[r].end());
                for (int j = 0; j < sz; j++){
                    cout << scc[r][j] << (j == sz-1 ? '\n' : ' ');
                }
            }
        }
        cout << br;
    }


    return 0;
}

