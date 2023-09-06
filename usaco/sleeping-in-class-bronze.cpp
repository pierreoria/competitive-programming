/*
  1. como provar complexidade de número de divisores de N (não só divisores primos)?
  2. essa solução não para quando encontra o melhor caso. tem como diminuir operações no caso médio, mesmo que pior caso seja igual
*/

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

const int N = 1e5+5;
const ll inf = 1e18;

ll a[N];

int main()
{
    fastio;
    int t,n,l; cin>>t;
    ll mx,s,k,sq,ans,lans,ps; // mx element, soma total
    bool ok,eq;
    while(t--)
    {
        mx = 0;
        cin>>n;
        ans = n-1; // resposta nunca vai ser pior que n-1
        a[0] = 0;
        s = 0;
        eq = true;
        for (int i = 1; i <= n; i++) {
            cin>>a[i];
            s += a[i];
            if (a[i] > mx) mx = a[i];
        }
        for (int i = 1; i <= n; i++) {
            if (a[i] != mx) {
                eq = false; 
                break;
            }
        }
        if (eq) cout << 0 << br;
            else{
            // divisores
            sq = sqrt(s);
            vector<ll> divs;
            for (ll i = 1; i <= sq; i++){
                if (s%i == 0) {
                    divs.pb(i);
                    if ((s/i) != i) divs.pb(s/i);
                };
            }
            divs.pb(s);

            for (ll x : divs)
            {
                k = s/x;
                // tentar chegar na soma k em cada grupo
                ok = true; l = 0; lans = 0; ps = 0;
                for (int i = 1; i <= n; i++){

                    if (ps + a[i] < k) // menor: continua
                    {
                        ps += a[i];
                    }
                    else if (ps + a[i] == k) // igual: vê tamanho t do trecho cuja soma é k, lans += t-1 operações 
                    {
                        lans += i-(l+1);
                        l = i;
                        ps = 0;
                    }
                    else // passou: esse k não funciona 
                    {
                        ok = false;
                        break; 
                    }
                }
                if (ok) ans = min(ans,lans);
            }
            cout << ans << br;
        }
    }
}
