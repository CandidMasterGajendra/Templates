
// Mint structure for modular arithmetic
struct Mint {
    static const int MOD = 1e9 + 7;
    int value;

    Mint(int v = 0) : value(v % MOD) {
        if (value < 0) value += MOD;
    }

    Mint operator*(Mint other) const {
        return Mint(1LL * value * other.value % MOD);
    }

    Mint operator*(int other) const {
        return Mint(1LL * value * other % MOD);
    }

    Mint inv() const {
        return power(MOD - 2);
    }

    Mint power(int exp) const {
        Mint base = *this, result = 1;
        while (exp) {
            if (exp & 1) result = result * base;
            base = base * base;
            exp >>= 1;
        }
        return result;
    }

    friend ostream &operator<<(ostream &os, const Mint &m) {
        return os << m.value;
    }
};

// Namespace for combinatorics
namespace comb {
    int n = 0;
    vector<Mint> _fac{1}, _invfac{1}, _inv{0};

    void init(int m) {
        m = min(m, Mint::MOD - 1); // Modular arithmetic limit
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i++) _fac[i] = _fac[i - 1] * i;
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }

    Mint fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }

    Mint invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }

    Mint inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }

    Mint ncr(int n, int r) {
        if (n < r || r < 0) return 0;
        return fac(n) * invfac(r) * invfac(n - r);
    }
} // namespace comb

using comb::fac, comb::invfac, comb::inv, comb::ncr;
