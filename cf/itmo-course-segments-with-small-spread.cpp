/* 
  problema two pointers com implementação O(n) para determinar máximos e mínimos em cada segmento
  usa pilhas pra fazer isso - ao invés de estrutura como set que deixaria o código O(n*log(n))

  ficaria mais limpo usando struct - aqui teve que pôr muito código repetido para prevenir acesso a stack vazia

  link:
  https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/F

  mais explicações na parte teórica desse mesmo curso
*/

#include <bits/stdc++.h>

using namespace std;

#define forn(i,n) for (int i = 0; i< n; i++)
#define br '\n'
#define fastio ios::sync_with_stdio(false); cin.tie(NULL)
#define ll long long

const int MX = 1e5+5;
const ll inf =  1e18+5;

ll a[MX];
stack<ll> f,b,mnf,mxf,mnb,mxb;

bool chk(ll k){

    ll mn,mx,mn1,mn2,mx1,mx2;
    if (f.empty()){
        mn1 = inf;
        mx1 = 0;
    }
    else {
        mn1 = mnf.top();
        mx1 = mxf.top();
    }
    if (b.empty()){
        mn2 = inf;
        mx2 = 0;
    }
    else{
        mn2 = mnb.top();
        mx2 = mxb.top();
    }
    mn = min(mn1,mn2);
    mx = max(mx1,mx2);
    return ((mx-mn) <= k);
}

void add(ll i){
    ll mn,mx;
    
    if (mnf.empty()) mn = inf;
    else mn = mnf.top();

    if (mxf.empty()) mx = 0;
    else mx = mxf.top();
    
    mn = min(mn, i);
    mx = max(mx, i);

    f.push(i);
    mnf.push(mn);
    mxf.push(mx);
}

void rem(){
    ll top,mn,mx,mnbt,mxbt;
    if (b.empty()){
        while (!f.empty()){

            top = f.top();
            mn = mnf.top();
            mx = mxf.top();

            if (b.empty()) {
                mnbt = inf;
                mxbt = 0;
            }
            else{
                mnbt = mnb.top();
                mxbt = mxb.top();
            }

            b.push(top);
            mnb.push(min(top, mnbt));
            mxb.push(max(top, mxbt));

            f.pop();
            mnf.pop();
            mxf.pop();
        }
    }

    b.pop();
    mnb.pop();
    mxb.pop();
}


int main()
{
    fastio;
    ll n,k,ans,l; cin>>n>>k;
    forn(i,n) cin>>a[i];
    ans = l = 0;
    forn(r,n){
        add(a[r]);
        while (!chk(k)){
            rem();
            l++;
        }
        ans += (r-l+1);
    }
    cout << ans << br;
}
