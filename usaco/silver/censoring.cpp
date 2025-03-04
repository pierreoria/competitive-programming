#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;
 
typedef long long ll;

class CustomHash{
public:
  vector<ll> h,p;
  string ans;
  const ll A = 19937;
  const ll M = 1e9+9;
  ll THASH; // hash of t (patterns)
  int n,m,sz = 0;

  CustomHash(string& s, string& t){
    n = s.size();
    m = t.size();
    p.resize(n+1);
    p[0] = 1;
    for (int i = 1; i <= n; i++){
      p[i] = (p[i-1]*A) % M;
      p[i] = (p[i] + M) % M;
    }

    THASH = t[0]-'a';
    for (int i = 1; i < m; i++)
    {
      THASH = (THASH*A%M) + (t[i]-'a');
      THASH = (THASH+M)%M;
    }

  }

  // add
  void add(char c){
    if (sz){
      ans.push_back(c);
      ll val = h[sz-1];
      val = ((val*A)%M) + (c-'a') % M;
      val = (val+M) % M;
      h.push_back(val);
    }
    else{
      ans.push_back(c);
      h.push_back(c-'a');
    }
    sz++;


    // check
    if (sz >= m)
    {
      if (qry() == THASH){
        del();
      }
    }


  }

  // query last m characters
  ll qry(){
    ll res;
    if (sz > m){
      res = h[sz-1]-(h[sz-1-m]*p[m]%M) % M;
    }
    else if (sz == m){
      res = h[sz-1];
    }
    else {
      return -1;
    }

    res = (res+M)%M;
    return res;
  }


  // delete last m characters
  void del(){
    for (int i = 0; i < m; i++){
      h.pop_back();
      ans.pop_back();
    }
    sz -= m;
  }

};

 
int main()
{
  freopen("censor.in","r", stdin);
  freopen("censor.out","w", stdout);

  string s,t; cin>>s>>t;
  int n; n = s.size();

  CustomHash H(s,t);
  
  for (int i = 0; i < n; i++){
    H.add(s[i]);
  }

  cout << H.ans << endl;

  return 0;
}
