// ICPC 2025, квалификация, H (Дейкстра, графы, римские числа)
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

void solve() {
    RomulNum rn;
    map<string, ll> nums;
    vector<vpll> adj(4000);
    vector weight(4000, vll(2));

    for (ll i=1; i<4000; ++i) {
        nums[rn.translate(i)] = i;
        weight[i][0] = weight[i][1] = i;
    }

    ll n, x; 
    cin>>n;
    for (ll i=0; i<n; ++i) {
        cin>>x>>weight[x][0]>>weight[x][1];
    }

    ll u, v;
    string currentRomulNum;
    for (ll i=1; i<4000; ++i) {
        adj[0].push_back({i, weight[i][0]});

        currentRomulNum = rn.translate(i);

        for (ll j=1; j<currentRomulNum.size(); ++j) {
            if (nums.count(currentRomulNum.substr(0, j))==1 && nums.count(currentRomulNum.substr(j))==1) {
                x = nums[currentRomulNum];
                u = nums[currentRomulNum.substr(0, j)];
                v = nums[currentRomulNum.substr(j)];

                adj[u].push_back({x, weight[v][0]});
                adj[x].push_back({u, weight[v][1]});
                adj[v].push_back({x, weight[u][0]});
                adj[x].push_back({v, weight[u][1]});
            }
        }
        
    }

    // Граф adj не зависит от RomulNum => можно запустить Дейкстру от нуля
    PQLess<pll> pq;
    pq.push({0,0});
    vll dist(4000, LONG_MAX);
    vb used(4000, false);
    used[0] = true;
    dist[0] = 0;

    while (!pq.empty()) {
        auto t = pq.top();
        pq.pop();
        used[t.S] = true;

        for (auto u : adj[t.S]) {
            if (used[u.F]) continue;
            if (dist[u.F] > dist[t.S]+u.S) {
                dist[u.F] = dist[t.S]+u.S;
                pq.push({dist[u.F], u.F});
            }
        }
    }

    ll tt, y;
    cin>>tt;
    while (tt--) {
        cin>>y;
        cout << dist[y] << "\n";
    }
}

/*
2
100 1 2
1200 2 3
2
500
3000
*/

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
