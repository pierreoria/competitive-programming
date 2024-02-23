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
  ll inv(ll a, ll m)
  {
    ll ans = fexp(a,m-2); // fexp com mod pra não dar overflow
    ans %= m;
    return ans;
  }

  // geral (a,m primos entre si)
  ll inv(ll a, ll m)
{
  int x,y;
  ll g = exgcd(a,m,x,y);
  if (g != 1) {
    x %= m; 
    x = (x+m) % m; // x entre 0 e m-1
    return x;
  }
  else return -1; // ou outro valor: a,m não primos entre si
}


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
  
      // 1. triangulo de pascal é uma opção, se complexidade de tempo e memória O(n²) passar

      // 2. calcular fatoriais mod m em O(n) depois usar inverso modular
      ll fat[mx];
      fat[0] = 1;
      for (int i = 1; i <= mx; i++)
          fat[i] = i * fat[i-1]%m;

      ll nck(ll n, ll k){
        return (fat[n] * inv(fat[k] * fat[n-k] % m)) % m;
      }

// matriz:
﻿

const int m = 2; // tamanho
const int MOD = 1e9 + 7;


class Matrix{
public:
    ll mat [m][m] = {{0, 0}, {0, 0}};
    Matrix operator * (const Matrix &p){
        Matrix ans;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            for(int k = ans.mat[i][j] = 0; k < m; k++)
                ans.mat[i][j] = (ans.mat[i][j] + 1LL * (mat[i][k] % MOD) * (p.mat[k][j] % MOD)) % MOD;
    return ans;
    }
};






