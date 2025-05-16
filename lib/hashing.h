class H{
public:
    vector<long long> h,p;
    int sz;
    const int A = 19937;
    const int M = 1e9+9;

    H(){}

    H(string& s)
    {
        sz = s.size();
        h.resize(sz+1);
        p.resize(sz+1);

        h[0] = s[0];
        p[0] = 1;
        for (int i = 1; i < sz; i++){
            h[i] = (h[i-1]*A + s[i]) % M;
            p[i] = (p[i-1]*A) % M;
        }
    }

    ll query(int l, int r){
        if (l == 0){
            return h[r];
        }
        else{
            return (h[r] - (h[l-1]*p[r-l+1])%M+ M) % M;
        }
    }
};
