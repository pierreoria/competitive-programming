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
