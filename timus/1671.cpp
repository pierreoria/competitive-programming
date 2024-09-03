#include <bits/stdc++.h>

using namespace std;
#define br '\n'

typedef tuple<int,int,int> iii;
typedef tuple<int,int> ii;


const int mx = 1e5+5;
bitset<mx> rem; 
int par[mx],sz[mx];

void init(int n)
{
    for (int i = 0; i < n; i++) par[i] = i, sz[i] = 1;
}

int find(int a)
{
    if (par[a] == a) return a;
    return par[a] = find(par[a]);
}

void join(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a==b) return;
    if (sz[a] < sz[b]) swap(a,b);
    par[b] = a;
    sz[a] += sz[b];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n,m,u,v,q,cnt,x;
    stack<int> ans,stk;
    
    cin>>n>>m;
    
    vector<ii> edges(m);
    init(n);

    for (int i = 0; i < m; i++)
    {
        cin>>u>>v; u--; v--;
        edges[i] = {u,v};
    }

    cin>>q;
    for (int i = 0; i < q; i++)
    {
        cin>>x; x--;
        stk.push(x);
        rem[x] = 1;
    }

    // grafo sem destruídos
    for (int i = 0; i < m; i++) {
        if (!rem[i]) {
            tie(u,v) = edges[i];
            join(u,v);
        }
    }

    cnt = 0;
    for (int i = 0; i < n; i++){
        if (par[i] == i) cnt++;
    }

    ans.push(cnt);


    while(!stk.empty())
    {
        tie(u,v) = edges[stk.top()]; stk.pop();
        if (find(u) != find(v)){
            cnt--;
            join(u,v);
        }
        if (!stk.empty()) ans.push(cnt);
    }

    while(!ans.empty())
    {
        cout << ans.top();
        ans.pop();
        cout << (ans.empty() ? '\n' : ' ');
    }


    // grafo inicial contém todas as arestas não destruídas
    // conto componentes em O(n): primeira resposta. boto no stack
    // coloco próxima aresta, componentes-- caso junte duas; componenentes no stack.
    // print stack


}
