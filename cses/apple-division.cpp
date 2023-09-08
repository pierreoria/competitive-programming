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
    ans = inf;
    s = 0;
    forn(i,n) cin>>a[i], s+=a[i];
    for (ll msk = 1; msk < (1<<n); msk++){
        ls = 0;
        forn(i,n){
            if (msk&(1<<i)) ls+=a[i];
        }
        la = abs(ls-abs(s-ls));
        ans = min(ans,la);
    }
    cout << ans << br;


    return 0;
}
