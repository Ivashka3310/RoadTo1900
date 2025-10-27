// ICPC 2025, Москва, квалификация, J (2 min ostov)
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vll = vector<ll>;
using pll = pair<ll, ll>;
template<typename T>
using PQLess= priority_queue<T, vector<T>, greater<T>>;

#define F first
#define S second

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

ll MinOstov(auto& edges, ll n) {
    ll w1, w2;
    
    stable_sort(edges.begin(), edges.end(), [](auto& a, auto& b) {return a.F.F < b.F.F;});
    {
        w1 = 0;
        DSU dsu(n);
        for (const auto& edge : edges) {
            if (dsu.same(edge.S.F, edge.S.S)) continue;
            dsu.unite(edge.S.F, edge.S.S);
            w1 += edge.F.F;
        }
    }
    stable_sort(edges.begin(), edges.end(), [](auto& a, auto& b) {return a.F.S < b.F.S;});
    {
        w2 = 0;
        DSU dsu(n);
        for (const auto& edge : edges) {
            if (dsu.same(edge.S.F, edge.S.S)) continue;
            dsu.unite(edge.S.F, edge.S.S);
            w2 += edge.F.S;
        }
    }

    return min(w1, w2);
}

void solve(ll n, ll m, ll l, ll r) {
    vector<pair<pll, pll>> edges(m);
    ll a, b, u, v;
    for (ll i=0; i<m; ++i) {
        cin>>u>>v>>a>>b;
        edges[i] = {{a + b*l, a + b*r}, {u, v}};
    }

    cout << min(MinOstov(edges, n), MinOstov(edges, n)) << "\n";
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
