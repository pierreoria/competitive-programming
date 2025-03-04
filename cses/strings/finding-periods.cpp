#include <bits/stdc++.h>
 
using namespace std;
 
#pragma GCC optimize("O3")
 
#define br '\n'
 
typedef long long ll;
 
class HashedString{
public:
  int n;
  vector<ll> h,p;
  const ll M = 1e9+9;
  const ll A = 19937;
 
  HashedString(string s){
    n = s.size();
    p.resize(n);
    h.resize(n);
    
    h[0] = s[0]-'a';
    for (int i = 1; i < n; i++){
      h[i] = ((h[i-1]*A)%M + s[i]-'a') %M;
      h[i] = (h[i]+M) % M;
    }
 
    p[0] = 1;
    for (int i = 1; i < n; i++){
      p[i] = (p[i-1]*A)%M;
      p[i] = (p[i]+M)%M;
    }
  }
 
  ll qry(int l, int r){
    if (l) return ( ( (h[r]- (h[l-1]*p[r-l+1]%M) ) % M ) + M) % M;
    else return h[r];
  }
};
 
bool solve(HashedString& H, int k)
{
  int n = H.n;
  ll hash = H.qry(0, k-1);
  // piso
  for (int i = 0; i < n/k; i++){
    if (H.qry(i*k,(i+1)*k-1) != hash) return false;
  }
 
  // sobra
  if (n%k){
    ll part = H.qry(0,n % k - 1);
 
    if (H.qry((n/k)*k, n-1) != part) return false; 
  }
 
  return true;
  
}
 
 
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
 
  string s; cin>>s;
  HashedString H(s);
  int n = H.n;
  vector<int> ans;
 
  for (int i = 1; i <= n; i++){
    if (solve(H,i)) ans.push_back(i);   
  }
 
  for (int i = 0; i < ans.size(); i++){
    cout << ans[i] << (i == ans.size()-1 ? '\n' : ' ');
  }
 
}

