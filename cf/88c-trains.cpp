/*
Codeforces 88c - Trains

ver link para mais informações
https://codeforces.com/blog/entry/54182

solução mais rápida existe: ver editorial
*/

#include <bits/stdc++.h>

using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(NULL)
#define forn(i,n) for (int i = 0; i < n ; i++)
#define br '\n'
#define ll long long


ll gcd(ll a, ll b)
{
if (a < b) swap(a,b);
if (!b) return a;
return gcd(b, a%b);
}

int main()
{
  fastio;

  ll a,b,nb,na,ita,itb,g,k,lim,lcm;

  cin>>a>>b;

  if (a == b) {cout << "Equal" << br; return 0;}

  bool inv = false;

  if (a > b) {swap(a,b); inv = true;}

  ita = itb = nb = 0;

  g = gcd(a,b);
  lcm = a * (b / g);

  k = b/a;

  // vê comprimentos de segmentos correspondentes a cada namorada por intervalos múltiplos de b
  // i estritamente menor que a/g pq no último intervalo vai add nb += a (critério de adicionar 
  for (ll i = 1; i < a/g; i++)
  {
      itb = i * b;
      ita += (k*a);
      if (ita+a < itb) ita += a;
      nb += itb-ita;
  }

  nb += a;
  na = lcm - nb;

  if (nb == na) {
      cout << "Equal" << br;
  }
  else if (nb > na) {
      if (inv) cout << "Dasha" << br;
      else cout << "Masha" << br;
  }
  else {
      if (inv) cout << "Masha" << br;
      else cout << "Dasha" << br;
  }


  return 0;
}
