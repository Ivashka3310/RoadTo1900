// ICPC 2025, квалификация, H (bfs, римские числа)
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vll = vector<ll>;
using vb = vector<bool>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
template<typename T>
using PQLess= priority_queue<T, vector<T>, greater<T>>;

#define F first
#define S second

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

    string translate(ll n) {
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

void mins(ll& a, ll b) {
    a = min(a,b);
}

void solve() {
    RomulNum rn;
    map<string, ll> nums;
    vector<vpll> adj(4000);
    vector weight(4000, vll(2));

    for (ll i=1; i<4000; ++i) {
        nums[rn.translate(i)] = i;
        weight[i][0] = weight[i][1] = i;
    }

    ll n, x, add, del; 
    cin>>n;
    for (ll i=0; i<n; ++i) {
        cin>>x>>add>>del;

        mins(weight[x][0], add);
        mins(weight[x][1], del);
    }

    ll u, v;
    string currentRomulNum;
    for (ll i=1; i<4000; ++i) {
        currentRomulNum = rn.translate(i);
        x = nums[currentRomulNum];
        u = nums[currentRomulNum.substr(1)];
        v = nums[currentRomulNum.substr(0, currentRomulNum.size()-1)];

        adj[u].push_back({x, weight[u][0]});
        adj[x].push_back({u, weight[x][1]});
        adj[v].push_back({x, weight[v][0]});
        adj[x].push_back({v, weight[x][1]});
    }

    // Граф adj не зависит от RomulNum => можно запустить bfs от каждой вершины (малоэффективно)
    for (ll i=1; i<4000; ++i) {
        for (ll j=1; j<4000; ++j) {
            for (auto& u : adj[j]) {
                weight[j][0] = min(weight[j][0], weight[u.F][0]+u.S);
            }
        }
    }

    ll tt, y;
    cin>>tt;
    while (tt--) {
        cin>>y;
        cout << weight[y][0] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
