/*
  bitmasks, complete search
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
#define ull unsigned long long

int main()
{
    fastio;
    freopen("cownomics.in","r",stdin);
    freopen("cownomics.out","w",stdout);
    map<char,int> code; code['A'] = 0; code['T'] = 1; code['C'] = 2; code['G'] = 3;
    int n,m,cnt; cin>>n>>m; cnt = 0;
    char spotted[n][m],plain[n][m];
    forn(i,n) forn(j,m) cin>>spotted[i][j];
    forn(i,n) forn(j,m) cin>>plain[i][j];
    ull pmsk,smsk,x,y,z,t,one; one = 1;
    bool eq;
    for (int i = 0; i < m; i++){
        for (int j = i+1; j < m; j++){
            for (int k = j+1; k < m; k++){
                smsk = pmsk = 0;
                eq = false;
                for (int c = 0; c < n; c++){
                    x = code[spotted[c][i]]; x = (x<<4);
                    y = code[spotted[c][j]]; y = (y<<2);
                    z = code[spotted[c][k]];
                    t = x+y+z;
                    smsk |= (one<<t); // com literal '1' dá problema pra t maior que 32 - one é constante ull
                }
                for (int c = 0; c < n; c++){
                    x = code[plain[c][i]]; x<<=4;
                    y = code[plain[c][j]]; y<<=2;
                    z = code[plain[c][k]];
                    t = x+y+z;
                    pmsk |= (one<<t);
                    if (pmsk&smsk){eq = true; break;}
                }
                if (!eq) cnt++;
            }
        }
    }
    cout << cnt << br;
}
