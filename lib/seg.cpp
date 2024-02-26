/*
  seg mínimo
*/

#include <bits/stdc++.h>

using namespace std;

#define br '\n'
#define ff first
#define ss second
#define fastio ios::sync_with_stdio(false); cin.tie(NULL)

typedef long long ll;
typedef pair<int,int> ii;

const int mx = 8e5+ 5; // tamanho maximo do array de entrada int seg [4*ms];
int n; // tamanho do array de entrada
const int inf = 2e9;

int seg[mx];

void build(vector<int> &v, int l=0, int r = n-1, int idx=0)
{
    if(l == r) {
        seg[idx] = v[l];
        return;
    }
    int m = (l+r)/2;
    int left = 2*idx +1;
    int right = 2*idx +2;
    build(v, l, m, left), build (v, m+1, r, right);
    seg[idx] = min(seg[left], seg[right]);
}

void update(int pos, int num, int l=0, int r =n-1, int idx=0)
{ 
    if(l == r) {
        seg[idx] = num;
        return;
    }

    int m = (l + r)/2;
    int left = 2*idx + 1;
    int right = 2*idx + 2;
    if(pos <= m) {
        update(pos, num, l, m, left);
    }
    else update(pos, num, m+1, r, right);
    seg[idx] = min(seg[left], seg[right]);
}

int query(int L, int R, int l=0, int r=n-1, int idx=0)
{ 
    if (R < l || L > r) return inf; // Valor que nao atrapalhe

    if(L <= l && r <= R) return seg[idx];
    int m = (l + r)/2;
    int left = 2*idx + 1;
    int right = 2*idx + 2;
    return min(query(L, R, l, m, left) ,query(L, R, m+1, r, right));
}


int main()
{
    fastio;

    int q,x,a,b,ans;

    cin>>n>>q;
    vector<int> v(n);
    for (int i = 0 ; i < n; i++) cin>>v[i];
    build(v);
    for (int i = 0; i < q; i++)
    {
        cin>>x>>a>>b;
        if (x == 1)
        {
            a--;
            update(a,b);
        }
        else
        {
            a--; b--;
            ans = query(a,b);
            cout << ans << br;
        }
    }


    return 0;
}
