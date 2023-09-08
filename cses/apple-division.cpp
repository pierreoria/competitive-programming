/*
  busca completa, bitset
*/

#include<bits/stdc++.h>

using namespace std;

#define forn(i,n) for(int i = 0; i < n; i++)
#define fastio ios::sync_with_stdio(false); cin.tie(NULL)
#define pii pair<int,int>
#define ll long long
#define vi vector<int>
#define br '\n'
#define pb push_back
#define ff first
#define ss second
#define debug(x) cout << (#x) << ": " << (x) << '\n'

const ll inf = 1e18;

int main()
{
    fastio;

    ll ans,ls,la,n,s,k,j,u;

    cin>>n;
    ll a[n];
    s = 0;
    ans = inf;
    forn(i,n) cin>>a[i], s+=a[i];
    k = (1<<n);
    for (ll i = 1; i < k; i++){
        ls = 0;
        j = (1<<(n-1));
        u = 0;
        while(j){
            if (j&i) ls += a[u];
            j>>=1;
            u++;
        }
        la = abs(ls-abs(s-ls));
        ans = min(ans,la);
    }
    cout << ans << br;


    return 0;
}
