#include <bits/stdc++.h>
 
using namespace std;

#define br '\n'

const int mx = 1e5+5;
bitset<mx> p;

void gen()
{
    p.set();
    p[0] = p[1] = 0;
    int lim = sqrt(mx);
    for (int i = 2; i <= lim; i++)
    {
        if (p[i])
        {
            int j = i+i;
            while(j < mx)
            {
                p[j] = 0;
                j += i;
            }
        }
    }
}

int factorsum(int x)
{
    if (x == 1) return 0;
    int lim = sqrt(x);
    int res = 0;
    for (int i = 2; i <= lim && x > 1; i++)
    {
        if (p[i]){
            while (!(x%i)){
                if ((x/i) > lim && p[x/i]) {
                    res += x/i;
                    x /= (x/i);
                    
                }
                res += i;
                x /= i;
            }
        }
    }
    return (res ? res : x);
}

int greatestfactor(int x)
{
    if (x == 1) return 1;
    int lim = sqrt(x);
    // fator entre raiz(x) e x
    for (int i = 2; i <= lim; i++)
    {
        if (!(x%i) && p[x/i]){
            return x/i;
        }
    }
    int res = 0;
    // fator entre 2 e raiz x
    for (int i = 2; i <= lim; i++)
    {
        if (p[i] && !(x%i)){
            res = max(res, i);
        }
    }
    // se x for primo, retornar x
    return (res == 0 ? x : res);
}

struct node {
    int val,sum,sz;

    node(){
        sz = 1;
    }

    node(int v){
        val = v;
        sum = factorsum(val);
        sz = 1;
    }
};

node comb(node l, node r)
{
    node res;

    res.sz = l.sz + r.sz;
    res.val = l.val + r.val; // armazena valor lixo pra nós internos não marcados
    res.sum = l.sum + r.sum;

    return res;
}


node t[mx<<2];
bool marked[mx<<2];
int n;

void build(vector<node>& a, int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
        //cout << "1 t[" << v << "].val = " << t[v].val << " t[" << v << "].sum = " << t[v].sum << br;
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = comb(t[v<<1], t[v<<1|1]);
        //cout << "2 t[" << v << "].val = " << t[v].val << " t[" << v << "].sum = " << t[v].sum << br;
    }
}


void push(int v) {
    if (marked[v]) {
        t[v<<1].val = t[v<<1|1].val = t[v].val;
        t[v<<1].sum = t[v<<1|1].sum = t[v].sum;
        marked[v<<1] = marked[v<<1|1] = true;
        marked[v] = false;
    }
}

void update(int v, int tl, int tr, int l, int r, int new_val) {
    if (l > r) 
        return;
    if (l == tl && tr == r) {
        t[v].val = new_val;
        t[v].sum = factorsum(new_val); // sum * sz pra nós marcados
        marked[v] = true;
    } else {
        push(v);
        int tm = (tl + tr)>>1;
        update(v<<1, tl, tm, l, min(r, tm), new_val);
        update(v<<1|1, tm+1, tr, max(l, tm+1), r, new_val);
        t[v] = comb(t[v<<1], t[v<<1|1]);
    }
}

// range query das somas
int sumquery(int v, int tl, int tr, int l, int r)
{
    if (l > r) return 0;
    if (tl == l && tr == r) {
        //cout << "inclui nó " << v << " -> += " << (marked[v] ? t[v].sum * t[v].sz : t[v].sum) << br;
        return (marked[v] ? t[v].sum * t[v].sz : t[v].sum);
    }
    push(v);
    int tm = (tl + tr)>>1;
    return sumquery(v<<1,tl, tm, l, min(r, tm)) + sumquery(v<<1|1, tm+1, tr, max(l,tm+1), r);
}

// point query valor
int getval(int v, int tl, int tr, int pos) {
    if (tl == tr) {
        return t[v].val;
    }
    push(v);
    int tm = (tl + tr)>>1;
    if (pos <= tm) 
        return getval(v<<1, tl, tm, pos);
    else
        return getval(v<<1|1, tm+1, tr, pos);
}



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    gen();

    int q,x,op,l,r,pos,sum,val;

    cin>>n;
    vector<node> a(n);
    for (int i = 0; i < n; i++){
        cin>>a[i].val;
        a[i].sum = factorsum(a[i].val);
        //cout << "factorsum (" << a[i].val << "): " << a[i].sum << br;
    }

    build(a,1,0,n-1);

    cin>>q;

    //cout <<"a "<<  factorsum(1) << br;
    //cout << "q0: " << br;
    //cout << sumquery(1,0,n-1,0,n-1) << br;


    for (int i = 0 ; i < q; i++)
    {
        cin>>op;
        if (op == 1)
        {
            cin>>pos; pos--;
            // aqui tem que ser query pq eu n sei se tem ancestral marcado
            val = getval(1,0,n-1,pos);
            //cout << "op1: " << val << " /= " << greatestfactor(val) << br;
            val /= greatestfactor(val);
            update(1,0,n-1,pos,pos,val);
        }
        else if (op == 2)
        {
            cin>>l>>r; l--; r--;
            //cout << "op2: sumquery(" << l << "," << r << ")" << br;
            cout << sumquery(1,0,n-1,l,r) << br;
        }
        else
        {
            cin>>l>>r>>x; l--; r--;
            //cout << "op3: (" << l << "," << r << ") = " << x << br;
            update(1,0,n-1,l,r,x);
        }
    }


    return 0;
}
