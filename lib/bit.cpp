#include <bits/stdc++.h>

using namespace std;

#define br '\n'
#define ff first
#define ss second
#define fastio ios::sync_with_stdio(false); cin.tie(NULL)

typedef long long ll;
typedef pair<int,int> ii;

const ll mx = 2e5+5;
ll n;
ll bit[mx], nums[mx];

void update(int idx, ll v) 
{ 
    while(idx <= n) {
        bit[idx] += v;
        idx += idx & -idx;
    }
}

ll query (int idx) 
{ 
    ll ans = 0;
    while(idx > 0) {
        ans += bit[idx];
        idx -= idx & -idx;
    }

    return ans;
}

int main()
{
    fastio;

    ll q,x,k,a,b,ans;

    cin>>n>>q;

    for (int i = 1; i <= n; i++) {
        cin>>x;
        nums[i] = x;
        update(i,x);
    }

    //for (int i = 1; i<= n; i++) cout << bit[i] << " "; cout << br;

    for (int i = 0; i < q; i++)
    {
        cin>>x>>a>>b;
        if (x==1)
        {
            k = b-nums[a]; // k passado não é b, é b - o que tava originalmente. precisa de array original pq bit não tem todos os intervalos[i,i] como seg
            nums[a] = b;  // lembrar de atualizar array original
            update(a,k);
        }
        else
        {
            ans = query(b) - query(a-1);
            cout << ans << br;
        }
    }

    //for (int i = 1; i<= n; i++) cout << bit[i] <<" "; cout << br;


    return 0;
}
