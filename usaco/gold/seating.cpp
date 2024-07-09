#include <bits/stdc++.h>

using namespace std;

#define br '\n'

struct node{
    int pref,suff,sum,best,sz;

    node(int x = 1){
        pref = suff = best = max(x,0);
        sum = x;
        sz = 1;
    }
};

const int mx = 5e5+5;
int marked[4*mx]; // marca atualização lazy a ser feita
node t[4*mx];
int n;

// comb é usado pra calcular pai a partir de filhos
node comb(node a, node b) {
    node temp;

    if (a.sum == a.sz) temp.pref = max(a.pref, a.sum + b.pref);
    else temp.pref = a.pref;

    if (b.sum == b.sz) temp.suff = max(b.suff, b.sum + a.suff);
    else temp.suff = b.suff;

    temp.best = max(max(a.best, b.best), a.suff + b.pref);
    temp.sum = a.sum + b.sum;
    temp.sz = a.sz + b.sz; 
    return temp;
}

void setnode(node& a, bool one)
{
    if (one) a.sum = a.best = a.pref = a.suff = a.sz;
    else a.sum = a.best = a.pref = a.suff = 0;
    
}

void build(vector<node>& a, int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = comb(t[v*2] , t[v*2+1]);
    }
}

// propaga atualização lazy
void push(int v) {
    if (marked[v]) {
        setnode(t[v*2],(t[v].sum != 0));
        setnode(t[v*2+1],(t[v].sum != 0));
        marked[v*2] = marked[v*2+1] = true;
        marked[v] = false;
    }
}

// range assignment
void update(int v, int tl, int tr, int l, int r, int new_val) {
    if (l > r) 
        return;
    if (l == tl && tr == r) {
        setnode(t[v], (bool)new_val);
        marked[v] = true;
    } else {
        push(v);
        int tm = (tl + tr) / 2;
        update(v*2, tl, tm, l, min(r, tm), new_val);
        update(v*2+1, tm+1, tr, max(l, tm+1), r, new_val);
        t[v] = comb(t[2*v], t[2*v+1]);
    }
}

// point query
node get(int v, int tl, int tr, int pos) {
    if (tl == tr) {
        return t[v];
    }
    push(v);
    int tm = (tl + tr) / 2;
    if (pos <= tm) 
        return get(v*2, tl, tm, pos);
    else
        return get(v*2+1, tm+1, tr, pos);
}

// retorna índice do início de subarray de tamanho x t.q. todo elemento do subarray é 1
int bb(int v, int tl, int tr, int x)
{
    if (t[v].best < x) return -1;
    if (tl == tr) return t[v].best;
    
    push(v); // só chamado para pais (tl != tr)
    int tm = (tl+tr)/2;
    int subl = bb(v*2, tl, tm, x); // busca resposta na sub-árvore esquerda
    
    if (subl != -1) return subl;

    // busca resposta na intersessão da sub-árvore esquerda e direita
    if (t[v*2].suff + t[v*2+1].pref >= x){
        return tm - t[v*2].suff + 1; // funciona porque sufixo é formado por 1s
    }

    return bb(v*2+1, tm+1, tr, x); // busca resposta na sub-árvore direita
}


int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL);

    ///*
    freopen("seating.in","r", stdin);
    freopen("seating.out","w", stdout);
    //*/

    int q,x,l,r,idx,ans;
    char ch;
    cin>>n>>q;

    vector<node> a(n);
    build(a,1,0,n-1);

    ans = 0;
    while(q--)
    {
        cin>>ch;
        if (ch == 'A')
        {
            cin>>x;
            idx = bb(1,0,n-1,x); 
            if (idx != -1){
                update(1,0,n-1,idx,idx+x-1,0);
            } 
            else ans++;
        }
        else
        {
            cin>>l>>r; l--; r--;
            update(1,0,n-1,l,r,1);
        }
    }

    cout << ans << br;
}
