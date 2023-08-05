/*
implementação com busca ternária
(não precisava - busca completa resolve)
*/

#include <bits/stdc++.h>

using namespace std;

#define forn(i,n) for (int i = 0; i< n; i++)
#define br '\n'
#define fastio ios::sync_with_stdio(false); cin.tie(NULL)
#define ll long long
#define ld long double


ll m,b;
ld mx = 0;
ld mxx;

// último y discreto válido para determinado x
ll gety(ll x)
{
  ll dy = x/m;
  if (x%m) dy++;
  ll y = b - dy;
  y = max((ll)0,y);
  return y;
}

// função discreta: só coordenadas válidas (valor exato)
ll f(ll x)
{
  ll ans = 0;
  ll y = gety(x);
  ans += (x+1)*(((y+1)*y)/2);
  ll xc = (y+1)*(((x+1)*x)/2); 
  ans += xc;
  return ans;
}

// função contínua: valor aproximado
ld f_db(ld x)
{
  ld ans;
  ld y = b-(x/m);
  ans = (x+1)*(((y+1)*y)/2) + (y+1)*(((x+1)*x)/2);
  return ans;
}

// busca ternária com double: valores são aproximados
// único jeito de garantir propriedade unimodal para rodar a busca ternária
ld bt(ld l, ld r)
{
  if ((r-l)<0.1) return f_db(l);
  ld x1,x2,f1,f2,step;
  step = ((r-l)/3);
  x1 = l+step;
  x2 = x1+step;
  f1 = f_db(x1);
  f2 = f_db(x2);
  if (f1>mx) {mx = f1; mxx = x1;}
  if (f2>mx) {mx = f2; mxx = x2;}
  if (f1 <= f2) return bt(x1,r);
  else return bt(l,x2);
}

int main()
{
  fastio;

  cin>>m>>b;
  double r0 = (m*b);
  bt(0,r0);

  ll mxval = 0;
  ll v,fv;

  // a partir do valor teoricamente máximo, itera pelos pontos (x_teorico - 450) até (x_teorico + 450) 
  for(ll i = -450; i < 450; i++) {
    v = mxx+i;
    if ((v) >= 0 && v <= (ll)r0) {
      fv = f(v);
      if (fv > mxval) {
        mxval = fv;
      }
    }
  }
  // resposta correta sem aproximações (desde que resposta esteja na margem de 450 valores à esquerda ou direita - é o caso nessa questão)
  cout << mxval << br; 

  return 0;
}
