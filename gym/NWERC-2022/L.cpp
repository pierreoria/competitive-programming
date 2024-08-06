    #include <bits/stdc++.h>
     
    using namespace std;
    #define br '\n'
     
    struct FlowEdge {
        int v, u;
        long long cap, flow = 0;
        FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
    };
     
    struct Dinic {
        const long long flow_inf = 1e18;
        vector<FlowEdge> edges;
        vector<vector<int>> adj;
        int n, m = 0;
        int s, t;
        vector<int> level, ptr;
        queue<int> q;
     
        Dinic(int n, int s, int t) : n(n), s(s), t(t) {
            adj.resize(n);
            level.resize(n);
            ptr.resize(n);
        }
     
        void add_edge(int v, int u, long long cap) {
            edges.emplace_back(v, u, cap);
            edges.emplace_back(u, v, 0);
            adj[v].push_back(m);
            adj[u].push_back(m + 1);
            m += 2;
        }
     
        bool bfs() {
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (int id : adj[v]) {
                    if (edges[id].cap - edges[id].flow < 1)
                        continue;
                    if (level[edges[id].u] != -1)
                        continue;
                    level[edges[id].u] = level[v] + 1;
                    q.push(edges[id].u);
                }
            }
            return level[t] != -1;
        }
     
        long long dfs(int v, long long pushed) {
            if (pushed == 0)
                return 0;
            if (v == t)
                return pushed;
            for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
                int id = adj[v][cid];
                int u = edges[id].u;
                if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                    continue;
                long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
                if (tr == 0)
                    continue;
                edges[id].flow += tr;
                edges[id ^ 1].flow -= tr;
                return tr;
            }
            return 0;
        }
     
        long long flow() {
            long long f = 0;
            while (true) {
                fill(level.begin(), level.end(), -1);
                level[s] = 0;
                q.push(s);
                if (!bfs())
                    break;
                fill(ptr.begin(), ptr.end(), 0);
                while (long long pushed = dfs(s, flow_inf)) {
                    f += pushed;
                }
            }
            return f;
        }
    };
     
    int lb[26], ub[26], cnt[26], black[26][505], yellow[26][505];
    bitset<26> occurgrey;
    int ans[505];
     
    int main()
    {
        ios::sync_with_stdio(false); cin.tie(NULL);
     
        int g,n;
        cin>>g>>n;
        string s,t;
     
        Dinic graph(26+n+3, 26+n, 26+n+2);
     
        for (int i = 0; i < 26; i++) ub[i] = n;
        // 26+n = s
        // 26+n+1 = s'
        // 26+n+2 = t
     
        memset(ans,-1,sizeof(ans));
     
     
        for (int i = 0; i < g-1; i++)
        {
            cin>>s>>t;
            memset(cnt,0,sizeof(cnt));
            occurgrey.reset();
            for (int j = 0; j < n; j++)
            {
                int letter = (int)(s[j]-'a');
                if (t[j] == 'G'){
                    cnt[letter]++;
                    ans[j] = letter;
                }
                else if (t[j] == 'B'){
                    black[letter][j] = 1;
                    occurgrey[letter] = 1;
                }
                else{
                    cnt[letter]++;
                    yellow[letter][j] = 1;
                }
            }
            for (int j = 0; j < 26; j++){
                if (occurgrey[j]){
                    ub[j] = cnt[j];
                }
                lb[j] = max(lb[j],cnt[j]);
            }
        }
     
        // s -> s'
        long long sumlb = 0;
        for (int i = 0; i < 26; i++){
            sumlb += lb[i];
        }
        graph.add_edge(26+n,26+n+1,n-sumlb);
     
        /*
        for (int i = 0; i < 26; i++){
            cout << (char)(i+'a') << ": " << lb[i] << "," << ub[i] << br;
        }
        */
     
        // s -> l
        for (int i = 0; i < 26; i++)
        {
            graph.add_edge(26+n, i, lb[i]);
        }
     
        // s' -> l
        for (int i = 0; i < 26; i++){
            graph.add_edge(26+n+1, i, ub[i]-lb[i]);
        }
     
        // l -> i
        for (int i = 0; i < n; i++)
        {
            if (ans[i] != -1){
                graph.add_edge(ans[i], i+26, 1);
            }
            else{
                for (int j = 0; j < 26; j++){
                    if (!black[j][i] && !yellow[j][i]){
                        graph.add_edge(j,26+i,1);
                    }
                }
            }
        }
     
        // i -> t
        for (int i = 0; i < n; i++){
            graph.add_edge(26+i, 26+n+2, 1);
        }
     
        graph.flow();
     
        for (FlowEdge fe : graph.edges){
            //if (fe.flow > 0) cout << fe.v << "->" << fe.u << ": " << fe.flow << br;
            if (0 <= fe.v && fe.v < 26 && 26 <= fe.u && fe.u < 26+n && fe.flow == fe.cap && fe.flow > 0){
                ans[fe.u-26] = fe.v;
            }
        }
     
        /*
        for (int i = 0; i < n; i++){
            cout << ans[i] << " ";
        }cout << br;
        */
     
        for (int i = 0; i < n; i++){
            cout << (char)(ans[i]+'a');
        }
        cout << br;
     
     
     
     
    }
