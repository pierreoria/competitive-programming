
// continua errada

#include <bits/stdc++.h>
 
using namespace std;

#define br '\n'

const int mx = 1e5+5;

int factorsum(int x)
{
    if (x == 1) return 0;
    int lim = sqrt(x);
    int res = 0;
    for (int i = 2; i <= lim && x > 1; i++)
    {
        while (!(x%i)){
            res += i;
            x /= i;
        }
    }

    if (x > 1) res += x;

    return res;
}

int greatestfactor(int x)
{
    if (x == 1) return 1;
    int lim = sqrt(x);
    int ans = 1;
    for (int i = 2; i <= lim; i++){
        while (!(x%i)) ans = max(ans,i), x /= i;
    }
    ans = max(ans,x);
    return ans;
}

struct segTree{
    int n;
    vector<int> val, sum, lazy;

    segTree(int nn)
    {
        n = nn;
        val.resize(n<<2);
        sum.resize(n<<2);
        lazy.resize(n<<2);
    }

    void build(vector<int>& a, int node, int l, int r)
    {
        if (l == r) {
            val[node] = a[l];
            sum[node] = factorsum(a[l]);
        }
        else {
            int m = (l+r)>>1;
            build(a, node<<1, l, m);
            build(a, (node<<1)|1, m+1 ,r);
            val[node] = val[node<<1] + val[(node<<1)|1];
            sum[node] = sum[node<<1] + sum[(node<<1)|1];
        }
    }

    void update_lazy(int node, int l, int r)
    {
        if (!lazy[node]) return;
        int v = lazy[node];
        val[node] = v;
        sum[node] = factorsum(v) * (r-l+1);
        lazy[node] = 0;
    }

    void push(int node, int l, int r)
    {
        if (lazy[node])
        {
            lazy[node<<1] = lazy[(node<<1)|1] = lazy[node];
            update_lazy(node, l, r);

            int m = (l+r)>>1;
            update_lazy(node<<1, l, m);
            update_lazy((node<<1)|1, m+1, r);
        }
    }

    void assign_range(int node, int tl, int tr, int l, int r, int v)
    {
        if (l > r) return;
        if (tl == l && tr == r) {
            lazy[node] = v;
            cout << "lazy[" << node << "]: " << v << br;
        }
        else {
            push(node, tl, tr);
            int tm = (tl + tr)>>1;
            assign_range(node<<1, tl, tm, l, min(tm,r), v);
            assign_range((node<<1)|1, tm+1, tr, max(tm+1,l), r, v);

            sum[node] = sum[node<<1] + sum[(node<<1)|1];
            cout << "sum[" << node << "] = " << sum[node] << br;
        }
    }

    int sumquery(int node, int tl, int tr, int l, int r)
    {
        //cout << node << " " << tl << " " << tr << " " << l << " " << r  << endl;
        if (l > r) return 0;
        if (tl == l && tr == r) {
            update_lazy(node, tl, tr);
            return sum[node];
        }
        push(node, tl, tr);
        int tm = (tl + tr)>>1;
        return sumquery(node<<1, tl, tm, l, min(r,tm)) +
               sumquery((node<<1)|1, tm+1, tr, max(tm+1,l), r);
    }

    int valquery(int node, int tl, int tr, int pos)
    {
        if (tl > tr) return 0;
        if (tl == pos && tr == pos){
            //cout << "val[node]: " << val[node] << br;
            update_lazy(node, tl, tr);
            //cout << "'val[node]: " << val[node] << br;
            return val[node];
        }
        push(node, tl, tr);
        int tm = (tl + tr)>>1;
        if (pos <= tm)
            return valquery(node<<1, tl, tm, pos);
        return valquery((node<<1)|1, tm+1, tr, pos);
    }

};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n,q,x,op,l,r,pos,sum,val;

    cin>>n;
    vector<int> a(n);
    
    segTree seg(n);

    for (int i = 0; i < n; i++) {
        cin>>a[i];
    }

    seg.build(a,1,0,n-1);

    cin>>q;

    for (int i = 0 ; i < q; i++)
    {
        cin>>op;
        if (op == 1)
        {
            cin>>pos; pos--;
            val = seg.valquery(1,0,n-1,pos);
            if (greatestfactor(val) > 1) val /= greatestfactor(val);
            //cout << "val["<<pos<<"]: " << val << br;
            seg.assign_range(1,0,n-1,pos,pos,val); // caso especial de range assign: só folha
        }
        else if (op == 2)
        {
            cin>>l>>r; l--; r--;
            cout << seg.sumquery(1,0,n-1,l,r) << br;
        }
        else
        {
            cin>>l>>r>>x; l--; r--;
            seg.assign_range(1,0,n-1,l,r,x);
        }
    }


    return 0;
}
