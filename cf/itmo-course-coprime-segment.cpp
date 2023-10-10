/*
  segmento l,r tal que todos o MMC de todos os elementos no segmento == 1
  implementação O(n) com two pointers

  https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/G
*/

#include <bits/stdc++.h>

using namespace std;

#define forn(i,n) for (int i = 0; i< n; i++)
#define br '\n'
#define fastio ios::sync_with_stdio(false); cin.tie(NULL)
#define ll long long

const int MX = 1e5+5;
const ll inf = 1e18+1;

ll a[MX];

ll GCD(ll a, ll b){
        if (b > a) swap(a,b);
        if (!b) return a;
        return GCD(b,a%b);
}

struct Stack
{
    stack<ll> s;
    stack<ll> g;

    ll gcd(ll i){
        if (g.empty()) return i;
        else return GCD(g.top(), i);
    }

    void push(ll i){
        s.push(i);
        g.push(gcd(i));
    }

    ll s_top(){
        return s.top();
    }

    ll g_top(){
        return g.top();
    }

    bool empty(){
        return s.empty();
    }

    void pop(){
        s.pop();
        g.pop();
    }
};

struct Queue
{
    Stack front;
    Stack back;

    void remove()
    {
        if (back.empty())
        {
            while(!front.empty()){
                back.push(front.s_top());
                front.pop();
            }
        }
        back.pop();
    }

    void push(ll i){
        front.push(i);
    }

    ll gcd(){
        if (front.empty()) return back.g_top();
        else if (back.empty()) return front.g_top();
        else return GCD(back.g_top(), front.g_top());
    }

    bool good(){
        if (gcd() == 1) return true;
        return false;
    }
};

int main()
{
    fastio;
    Queue q;
    ll n,ans,l,gl,gr;
    cin>>n;
    ans = inf;
    forn(i,n) cin>>a[i];

    l = 0; gl = gr = inf;
    for (ll r = 0; r < n; r++)
    {
        if (a[r] == 1){
            ans = 1; break;
        }
        q.push(a[r]);
        while(q.good() && l < r){
            gl = l;
            gr = r;
            q.remove();
            l++;
        }
        if (gr == r)
            ans = min(ans, gr-gl+1);
    }

    if (ans == inf) cout << -1 << br;
    else cout << ans << br;

}
