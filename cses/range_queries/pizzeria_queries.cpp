#include <bits/stdc++.h>

using namespace std;

#define br '\n'

struct node{
    int val,left,right,sz;

    node(){}

    node(int v) {
        val = v;
        left = v;
        right = v;
        sz = 1;
    }

};


node comb(node l, node r)
{
    node temp;

    temp.val = min(l.val, r.val); // acho que nem usa isso
    temp.left = min(l.left, r.left + l.sz);
    temp.right = min(r.right, l.right + r.sz);
    temp.sz = l.sz + r.sz;

    return temp;
}


int n;
const int MAXN = 2e5+5;
const int inf = 2e9+9;
node t[4*MAXN];


void build(vector<node>& a, int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = comb(t[v*2], t[v*2+1]);
    }
}

int query(int v, int tl, int tr, int pos) {
    int res = inf;

    // próprio nó
    if (tl == tr && tl == pos) {
        return t[v].val;
    }

    // não é ancestral
    if (tl > pos) {
        return t[v].left + tl - pos;
    }
    if (tr < pos)    {
        return t[v].right + pos - tr;
    }

    // é ancestral
    int tm = (tl + tr) / 2;
    return min( query(v*2, tl, tm, pos), 
                query(v*2+1, tm+1, tr, pos) );
}

void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v] = node(new_val);
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = comb(t[v*2], t[v*2+1]);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int q,pos,val,ans;

    cin>>n>>q;

    vector<node> a(n);
    for (int i = 0,k; i < n; i++) {
        cin>>k;
        a[i] = node(k);
    }

    build(a,1,0,n-1);

    for (int i = 0, k; i<q; i++){
        cin>>k;
        if (k == 1)
        {
            cin>>pos>>val; pos--;
            update(1,0,n-1,pos,val);
        }
        else
        {
            cin>>pos; pos--;
            ans = query(1,0,n-1, pos);
            cout << ans << br;
        }
    }



}
