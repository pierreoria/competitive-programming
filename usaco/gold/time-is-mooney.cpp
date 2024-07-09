#include <bits/stdc++.h>

using namespace std;

#define br '\n'
#define fastio ios::sync_with_stdio(false); cin.tie(NULL)
#define pb push_back
#define ff first
#define ss second
#define forn(i,n) for(int i = 0; i < n; i++)

typedef long long ll;
typedef pair<long long, long long> ii;
typedef tuple<long long, long long, long long> iii;

const ll mx = 1e3+3;

ll dp[mx][mx],val[mx];

int main()
{
    fastio;
    freopen("time.in","r",stdin);
    freopen("time.out","w",stdout);

    memset(dp,200,sizeof(dp));
    ll ninf = dp[0][0];
    dp[0][0] = 0;

    ll a,b,n,m,c,t,cost,u,sz,gain,ans; 

    cin>>n>>m>>c;

    forn(i,n) cin>>val[i];

    vector<vector<ll>> adj(n);

    forn(i,m)
    {
        cin>>a>>b; a--; b--;
        adj[a].pb(b);
    }

    for (int i = 0; i < mx; i++) // dia
    {
        for (int u = 0; u < n; u++) // no
        {
            if (dp[i][u] == ninf) continue; 
            for (ll v : adj[u])
            {
                dp[i+1][v] = max(dp[i+1][v],dp[i][u] + val[v]);
            }
        }
    }
    ans = 0;
    for (int j = 0; j < mx; j++)
    {
        cost = j * j * c;
        ans = max(ans,dp[j][0] - cost);  
    } 

    cout << ans << br;

}

