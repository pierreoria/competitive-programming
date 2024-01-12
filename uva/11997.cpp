#include <bits/stdc++.h>

using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(NULL)
#define br '\n'
#define forn(i,n) for (int i = 0; i < n; i++)
#define pb push_back
#define ff first
#define ss second

typedef long long ll;
typedef pair<long long, long long> pll;

const ll mx = 760;

ll a[mx],b[mx],k;

void k_pairs()
{
	priority_queue<pll, vector<pll>, greater<pll>> pq; // sum, j
	ll cnt,t,j; cnt = 0;

	for (int i = 0; i < k; i++)
	{
		pq.push({a[i] + b[0], 0 });
	}

	while(cnt < k)
	{
		t = pq.top().ff; j = pq.top().ss; pq.pop(); 
		a[cnt++] = t; 
		if (j < k-1) pq.push({t + b[j+1] - b[j], j+1});
	}
}


int main()
{
	fastio;
	
	while(cin>>k)
	{
		forn(i,k) cin>>a[i]; 

		sort(a,a+k);
		
		forn(i,k-1)
		{
			forn(j,k) cin>>b[j];
			sort(b,b+k);
			k_pairs();
		}

		cout << a[0];
		for (int i = 1; i < k; i++) cout << " " << a[i];
		cout << br;
	}

}

