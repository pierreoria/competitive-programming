/*
  Canadian Computing Competition: 2020 Stage 1, Senior #3
  https://dmoj.ca/problem/ccc20s3
*/

#include <bits/stdc++.h>

using namespace std;

#define br '\n'

typedef long long ll;

class Hash{
public:
  int n;
  const __int128_t M = (1ll << 61) - 1;
  mt19937 rng;
  __int128_t A;
  vector<__int128_t> h,p;
  string s;

  Hash(string str) {
    s = str;
    n = str.size();
    h.resize(n);
    p.resize(n);
    rng.seed((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
    A = uniform_int_distribution<ll>(M/2,M-1)(rng);

    calc();
  }

  void calc()
  {
    h[0] = s[0]-'a';
    for (int i = 1; i < n; i++){
      h[i] = ((((h[i-1]*A) % M + (s[i]-'a'))%M) + M) % M;
    }
    p[0] = 1;
    for (int i = 1; i < n; i++){
      p[i] = (((p[i-1]*A)%M) + M ) %M;
    }
  }

  ll qry(int l, int r)
  {
    if (l) return ((h[r]-((h[l-1]*p[r-l+1])%M)%M) + M) % M;
    return h[r];
  }

};

const int MXN = 2e5+5;
int sig[26];
int ps[26][MXN];

bool match(int I, int m)
{
  for (int i = 0; i < 26; i++){
    if (I == m-1){
      if (ps[i][I] != sig[i]) return false;
    }
    else{
      if (ps[i][I] - ps[i][I-m] != sig[i]) return false;
    }
  }
  return true;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  string t; cin>>t;
  string s; cin>>s;
  int n = s.size();
  int m = t.size();

  Hash s_hashed(s);

  set<ll> st;

  // sig
  for (int i = 0; i < m; i++){
    sig[t[i]-'a']++;
  }

  // ps
  for (int i = 0; i < n; i++){
    if (i) for (int j = 0; j < 26; j++) ps[j][i] = ps[j][i-1];

    ps[s[i]-'a'][i]++;
  }

  // matches
  for (int i = m-1; i < n; i++){
    if (match(i, m)) {
      st.insert(s_hashed.qry(i-m+1,i));
    }
  }

  cout << st.size() << br;

  
}
