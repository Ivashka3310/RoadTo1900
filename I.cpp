// ICPC 2025, квалификация, I (binsearch, mod2)
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vll = vector<ll>;
using pll = pair<ll, ll>;
template<typename T>
using PQLess= priority_queue<T, vector<T>, greater<T>>;

#define F first
#define S second

ll ask(ll x) {
    cout << "? " << x << endl;
    cin>>x;
    return x;
}

void answer(ll x) {
    cout << "! " << x << endl;
}

void solve() {
    ll l=2, r=65536, mid, x;

    while (true) {
        mid = min(l+(r-l)/2, l*l-1);

        x = ask(mid);
        if (x==0) {
            r = mid;
        } else {
            l = mid+1;
        }
        if (l==r) {
            break;
        }
    }
    answer(r);
}

int main() {
    ll t;
    cin>>t;
    while (t--) {
        solve();
    }
    return 0;
}
