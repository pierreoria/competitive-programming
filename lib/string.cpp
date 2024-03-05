// z-function
vector<int> z_funct(string& s)
{
    int n,l,r;
    n = s.size();
    vector<int> z(n,0);
    l = r = 0;
    for (int i = 1; i < n; i++)
    {
        if (i < r) z[i] = min(r-i, z[i-l]);
        
        // while
        while(i + z[i] < n && s[z[i]] == s[i+z[i]]) {
            z[i]++;
        }

        // atualiza l,r
        if (z[i] + i > r){
            r = z[i]+i;
            l = i;
        }
    }
    
    return z;
}


// manacher
// só funciona para palíndromos de tamanho ímpar. transformar string a priori
vector<int> manacher(string& s)
{
    int n = s.size();
    s = '%' + s + '#';
    vector<int> p(n+2,0); // 1-based
    int l,r; l = r = 1;
    for (int i = 1; i <= n; i++)
    {
        p[i] = max(0,min(p[l+(r-i)], r-i));
        while (s[i + p[i]] == s[i - p[i]]) p[i]++;
        if (i + p[i] > r)
        {
            l = i - p[i];
            r = i + p[i];
        }
    }
    return p;
}
