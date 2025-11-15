// Rucode C/D 2025, A (Математика, римские числа)
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vll = vector<ll>;
using vb = vector<bool>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vvll = vector<vll>;
template<typename T>
using PQLess= priority_queue<T, vector<T>, greater<T>>;

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound

#define F first
#define S second
#define all(x) x.begin(), x.end()
#define rall(x) (x).rbegin(), (x).rend()

#define rep(i,n) for (ll i = 0; i < (ll)(n); ++i)
#define rng(i,l,r) for (ll i = (ll)(l); i < (ll)(r); ++i)

class RomulNum {
    vector<vector<string>> romul_nums = {
        {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
        {"X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
        {"C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
        {"M", "MM", "MMM"}
    };
public:
    RomulNum() = default;
    ~RomulNum() = default;

    string operator()(ll n) {
        string res = "";
        for (ll i=0; n>0; ++i) {
            if (n%10!=0) {
                res = romul_nums[i][n%10-1] + res;
            }
            n/=10;
        }
        return res;
    }
};

ll binpow(ll x, ll n, ll m) {
    if (n == 0) return 1 % m;
    ll u = binpow(x, n/2, m);
    u = (u*u)%m;
    if ((n%2) == 1) u = (u*x)%m;
    return u;
}

ll phi(ll n) {
    ll res = 1, p;
    for (ll d=2; d*d<=n; ++d) {
        p = 0;
        while (n%d==0) {
            ++p;
            n/=d;
        }
        if (p>0) 
            res *= pow(d, p-1) * (d-1);
    }
    if (n>1)
        res *= (n-1);
    return res;
}

ll inv(ll x, ll m) {
    return binpow(x, phi(m)-1, m);
}

/*
I - 0
V - 1
X - 2
L - 3
C - 4
D - 5
M - 6
*/

void solve() {
    RomulNum rn;
    vector next(4000, vll(7));
    map<string, ll> exist;
    rng(i, 1, 4000) {
        exist[rn(i)] = i;
    }

    vector ssuff = {"I", "V", "X", "L", "C", "D", "M"};
    rng(i, 1, 4000) {
        rep(j, 7) {
            if (exist.count(rn(i)+ssuff[j])==1) {
                next[i][j] = exist[rn(i)+ssuff[j]];
            } else {
                string s = rn(i) + ssuff[j];
                for (ll k=0; k<s.size(); ++k) {
                    if (exist.count(s.substr(k))) {
                        next[i][j] = exist[s.substr(k)];
                        break;
                    }
                }
            }
        }
    }

    vector dp(1000, vector<vll>(16, vll(4000, 0)));

    ll N, p, inv_q, m=998'244'353;
    cin>>N;

    for (ll n=2; n<=N; ++n) {
        for (ll lastMax=1; lastMax<=15; ++lastMax) {
            for (ll suff=1; suff<=3999; ++suff)
            for (ll digit=0; digit<7; ++digit) {
                ll currSuff = next[suff][digit];
                ll currMax = max(lastMax, (ll)rn(currSuff).size());
                //cout << currSuff << endl;
                
                dp[n][currMax][currSuff] += dp[n-1][lastMax][suff];
            }
        }
    }

    for (ll i=1; i<=15; ++i) {
        ll si = 0;
        for (ll j=1; j<=3999; ++j) {
            si += dp[N][i][j];
        }
        p += i*si;
    }
    inv_q = inv(binpow(7, N, m), m);

    cout << (p*inv_q)%m << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
