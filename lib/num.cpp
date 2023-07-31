#include <bits/stdc++.h>

#define ll long long

using namespace std;

// mdc
ll gcd(ll a, ll b)
{
  if (!b) return a;
  return gcd(b,a%b);
}

// mmc
ll lcm(ll a, ll b)
{
  return (a / gcd(a,b) ) * b;
}


// fast exp
ll fexp(ll a, ll b)
{
  ll ans = 1;
  while(b)
  {
    if (b&1) ans *= a;
    a *= a;
    b >>= 1;
  }
  return ans;
}

// euclidiano extendido
ll exgcd(ll a, ll b, ll& x, ll& y)
{
  if (!b) {
    x = 1;
    y = 0;
    return a;
  }
  int x1, y1, g;
  g = exgcd(b,a%b,x1,y1);
  x = y1;
  y = x1-((a/b)*y1);
  return g;
}

// diofantina ---------------------



// inverso modular:


  // p primo: pequeno teorema de fermat
  ll minv(ll a, ll m)
  {
    ll ans = fexp(a,m-2);
    ans %= m;
    return ans;
  }

  // geral (a,b primos entre si)
  ll 


// n escolhe k

  // triangulo de pascal: n k pequenos, intermediários sem overflow
  const int mx = 50;
  ll nck[mx+1][mx+1];
  nck[0][0] = 1;
  for (int i = 1; i <= mx; i++)
    for (int j = 1; j <= mx; j++)
      nck[i][j] = nck[i-1][j] + nck[i-1][j-1];

  // usando double, precisão boa
  ll nck(ll n, ll k)
  {
    double a = 1;
    for (double i = 1; i <= k; i++) {
      a *= (n-i+1)/i;
    }
    return (ll)(a+0.01);
  }

  // combinações mod m:












