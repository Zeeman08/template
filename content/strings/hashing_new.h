long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
ll inv(ll x, ll m) {
    return binpow(x, m-2, m);
}

typedef pair<ll, ll> pll;
ostream& operator<<(ostream& os, pll hash) {
    return os<<"("<<hash.first<<", "<<hash.second<<")";
}
pll operator + (const pll &a, const pll &b) {
    return {a.first + b.first, a.second + b.second};
}
pll operator - (const pll &a, const pll &b) {
    return {a.first - b.first, a.second - b.second};
}
pll operator * (const pll &a, const pll &b) {
    return {a.first * b.first, a.second * b.second};
}
pll operator % (const pll &a, const pll &b) {
    return {a.first % b.first, a.second % b.second};
}
pll operator * (const pll &a, const ll b) {
    return {a.first * b, a.second * b};
}
const pll _primes={773,709};
const pll _mods = {281559881,398805713};
const int MAXLEN = 1e6 + 10;
pll p_pow[MAXLEN], pinv_pow[MAXLEN];
pll inv(pll x) {
    return {inv(x.first, _mods.first), inv(x.second, _mods.second)};
}
void calc_pow() {
    p_pow[0] = {1, 1};
    for(int j = 1;j < MAXLEN; j++) {
        p_pow[j] = (p_pow[j-1] * _primes) % _mods;
    }
    pinv_pow[0] = {1, 1};
    pinv_pow[1] = inv(_primes);
    for(int j = 2; j < MAXLEN; j++) {
        pinv_pow[j] = (pinv_pow[j-1] * pinv_pow[1]) % _mods;
    }
}


class hashing {
    public:
    int n, limit;
    string s;
    vector<pll>pref, suff;
    hashing() {}
    hashing(int _n, string _s) {
        this->s = _s; //1 indexed
        this->n = _n;
        pref.resize(n+2);
        suff.resize(n+2);
        precompute();
    }   
    void precompute() {
        pll hash_value = {0, 0};
        pref[0] = {0, 0};
        for(int i = 1; i <= n; i++) {
            hash_value = (hash_value + p_pow[i-1] * (s[i]-'a'+1)) % _mods;
            pref[i] = hash_value;
        }
        suff[n+1] = {0, 0};
        hash_value = {0, 0};
        for(int i = n; i >= 1; i--) {
            hash_value = (hash_value + p_pow[n-i] * (s[i]-'a'+1)) % _mods;
            suff[i] = hash_value;
        }
    }   
    pll get_pref(int l, int r) {
        return ((pref[r]-pref[l-1]+_mods) * pinv_pow[l-1]) % _mods;
    }
    pll get_suff(int l, int r) {
        return ((suff[l]-suff[r+1]+_mods) * pinv_pow[n-r]) % _mods;
    }

    pll get(int l, int r){
        return get_pref(l, r);
    }
};
