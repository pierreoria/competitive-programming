#include <bits/stdc++.h>

using namespace std;

#define br '\n'
#define fastio ios::sync_with_stdio(false); cin.tie(NULL)
#define pb push_back
#define ff first
#define ss second

typedef long long ll;
typedef pair<long long, long long> ii;
typedef tuple<long long, long long, long long> iii;

const int mx = 1e5+1;

int dp[mx][3][21]; // idx, hsp, k (1-based)
int a[mx];
int pm3[3] = {1,2,0};
int mm3[3] = {2,0,1};
int kmax;

int win(int a, int b)
{
    if (a == 0) {
        if (b == 1) return 1;
    }
    else if (a == 1){
      if (b == 2) return 1;  
    } 
    else if (a == 2) {
        if (b == 0) return 1;
    }
    return 0;
}

int solve(int i, int j, int k)
{
    int w,op1,op2,op3;
    if (i == 0 || k < 0) return 0;

    if (dp[i][j][k] != -1) return dp[i][j][k];

    w = win(j,a[i]);
 
    op1 = solve(i-1,j,k);
    op2 = solve(i-1,mm3[j],k-1);
    op3 = solve(i-1,pm3[j],k-1);

    op1 = max(op1,op2);
    op1 = max(op1,op3);

    return dp[i][j][k] = op1 + w;
}

int main()
{
    fastio;

    freopen("hps.in","r",stdin);
    freopen("hps.out","w",stdout);

    int n;
    int ans = 0;
    char c;

    memset(dp,-1,sizeof(dp));

    cin>>n>>kmax;

    for (int i = 1; i <= n; i++)
    {
        cin>>c;
        if (c == 'H') a[i] = 0;
        else if (c == 'S') a[i] = 1;
        else a[i] = 2;
    }

    for (int i = 0; i <= kmax; i++) for (int j = 0; j < 3; j++) ans = max(ans, solve(n,j,i));

    cout << ans << br;
}

