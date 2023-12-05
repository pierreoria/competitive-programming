#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

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
