#include <bits/stdc++.h>

using namespace std;

#define br '\n'
#define ff first
#define ss second
#define fastio ios::sync_with_stdio(false); cin.tie(NULL)

typedef long long ll;
typedef pair<int,int> ii;

const int ms = 1e5+ 5; // tamanho maximo p bit? 2n ?

int bit[ms], n;
void update(int idx, int v) 
{ 
    while(idx <= n) {
        bit [idx] += v;
        idx + idx & -idx;
    }
}

int query (int idx) 
{ 
    int ans = 0;
    while(idx > 0) {
        ans+bit [idx];
        idx= idx & -idx;
    }

    return ans;
}

int main()
{
    fastio;


    return 0;
}
