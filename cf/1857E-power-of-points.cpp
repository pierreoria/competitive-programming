#include <bits/stdc++.h>

using namespace std;

#define forn(i,n) for (int i = 0; i< n; i++)
#define br '\n'
#define fastio ios::sync_with_stdio(false); cin.tie(NULL)
#define pii pair<int,int>
#define ppi pair<int,pii>
#define ll long long
#define pb push_back
#define ull long long
#define vi vector<int>
#define ff first
#define ss second
#define mp make_pair
#define debug(x) cout << (#x) << ": " << x << br;

bool srt(pair<ll,int> a, pair<ll,int> b)
{
    if (a.ss < b.ss) return true;
    return false;
}


int main()
{
    fastio;

    int t,n; cin>>t;

    while(t--)
    {
        cin>>n;
        vector<ll> ps(n);
        ll x,v;
        vector<pair<ll,int>> a(n),ans(n); // v,i

        forn(i,n){
            cin>>x;
            a[i] = {x,i};
        }
        sort(a.begin(),a.end());
        ps[0] = a[0].ff;
        for (int i = 1; i < n; i++){
            ps[i] = ps[i-1]+a[i].ff;
        }
        
        forn(i,n){
            v = a[i].ff;
            ans[i].ff = ps[n-1]-(2*ps[i])+(v*(2*i + 2 - n))+n;
            ans[i].ss = a[i].ss;
        }

        sort(ans.begin(), ans.end(), srt);
        forn(i,n) cout << ans[i].ff << " ";
        cout << br;

    }

}
