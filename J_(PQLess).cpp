// ICPC 2025, Москва, квалификация
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vll = vector<ll>;
using pll = pair<ll, ll>;
template<typename T>
using PQLess= priority_queue<T, vector<T>, greater<T>>;

#define F first
#define S second
#define u second.first
#define v second.second

class DSU {
    vll link;
    vll size;

public:
    DSU(ll n) {
        link.resize(n+1);
        for (ll i=0; i<n; ++i) {
            link[i] = i;
        }
        size = vll(n+1, 1);
    }

    ll find(ll x) {
        if (x == link[x]) return x;
        return link[x] = find(link[x]);
    }

    bool same(ll a, ll b) {
        return find(a) == find(b);
    }

    void unite(ll a, ll b) {
        if (same(a, b)) return;

        a = find(a);
        b = find(b);
        if (size[a]<size[b]) swap(a, b);
        link[b] = a;
        size[a] += size[b];
    }
};

///

class MinOstov {
    PQLess<pair<ll, pll>> min_edges;
    ll cnt_n;

public:
    MinOstov(const auto& list_edges, ll n, ll x) {
        for (const auto& line : list_edges) {
            min_edges.push({line[2]+line[3]*x, {line[0], line[1]}});
        }
        cnt_n = n;
    }

    ll get() {
        DSU dsu(cnt_n);
        ll w=0;
        while (!min_edges.empty()) {
            if (dsu.same(min_edges.top().u, min_edges.top().v)) {
                min_edges.pop();
                continue;
            }
            dsu.unite(min_edges.top().u, min_edges.top().v);

            w += min_edges.top().first;
        }
        return w;
    }
};

void solve(ll n, ll m, ll l, ll r) {
    vector edges(m, vll(4));
    for (ll i=0; i<m; ++i) {
        for (auto& item : edges[i])
            cin>>item;
    }

    MinOstov ostov1(edges, n, l), ostov2(edges, n, r);

    cout << min(ostov1.get(), ostov2.get()) << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll n, m, l, r;
    
    while (true) {
        cin>>n>>m>>l>>r;
        if (n==m && m==l && l==r && r==0) 
            break;
        solve(n,m,l,r);
    }
    
    return 0;
}

/*
5 4 1 5
1 2 5 -1
2 3 1 -4
3 4 -1 3
4 5 2 -8
*/

/*
5 6 2 5
1 2 4 1
2 3 6 -1
3 4 2 2
4 5 2 -1
5 1 6 3
2 4 4 -1
5 7 1 5
1 2 1 1
2 3 2 2
3 4 1 -10
3 4 2 10
5 1 1 10
2 4 2 -10
1 2 1 0
0 0 0 0
*/

