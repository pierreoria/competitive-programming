/*
CEOI 2017, day 2
Palindromic Partitions
*/

#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll;

#define br '\n'

class HashedString{
public:
  vector<ll> h,p;
  const ll A = 19937;
  const ll M = 1e9+9;
  int n;

  HashedString(string& s){
    n = s.size();

    h.resize(n);
    p.resize(n+1);

    h[0] = s[0]-'a'+1;
    for (int i = 1; i < n; i++){
      h[i] = (((h[i-1]*A)%M) + s[i]-'a'+1)%M;
      h[i] = (h[i]+M)%M;
    }

    p[0] = 1;
    for (int i = 1; i <= n; i++){
      p[i] = (p[i-1]*A)%M;
      p[i] = (p[i]+M)%M;
    }
  }

  ll qry(int l, int r){
    if (l){
      ll res = (h[r]-((h[l-1]*p[r-l+1])%M))%M;
      res = (res+M)%M;
      return res;
    }
    return h[r];
  }

};


 
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int t; cin>>t;

  while(t--){
    string s; cin>>s;
    int n = s.size();
    HashedString H(s);
    int cnt = 0;
    int l = 0;
    for (int i = 0; i < n/2; i++){
      if (H.qry(l,i) == H.qry(n-1-i,n-1-l)){
        l = i+1;
        cnt++;
      }
    }

    if (l == n/2 && (n&1) == 0){
      cout << 2*cnt << br;
    } 
    else{
      cout << 2*cnt + 1 << br;
    }
  }




  return 0;
}
