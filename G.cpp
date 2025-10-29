// ICPC 2025, квалификация, G (квадратичная динамика, конструктив)
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

bool strCmp(string& s, ll ind1, ll ind2, ll len, char pred='<') {
    int res = memcmp(s.c_str()+ind1, s.c_str()+ind2, len);
    if (pred=='<')
        return res<0;
    else
        return res>0;
}

void solve() {
    string s;
    cin>>s;
    ll k=2*sqrt(s.size())+1;

    vector dp(k+1, vb(s.size()+2, false));

    for (ll i=0; i<=k; ++i) {
        dp[i][0] = true;
    }

    ll line1, line2;
    for (ll i=1; i<=k && dp[i-1][s.size()]==false; ++i) {
        line1 = i;
        for (ll j=1; j<=s.size(); ++j) {
            dp[i][j] = dp[i][j] || dp[i-1][j];
            if (j>=i) {
                dp[i][j] = dp[i-1][j-i] || (dp[i][j-i] && strCmp(s, j-2*i, j-i, i, '<'));
            }
        }
    }

    // for (const auto& line : dp) {
    //     for (const auto& it : line) {
    //         cout << it << " ";
    //     } cout << endl;
    // }

    for (auto& line : dp) {
        for (ll i=0; i<line.size()-1; ++i)
            line[i] = false;
        line[line.size()-1] = true;
    }

    for (ll i=1; i<=k && dp[i-1][1]==false; ++i) {
        line2 = i;
        for (ll j=s.size(); j>0; --j) {
            dp[i][j] = dp[i][j] || dp[i-1][j];
            if (j+i<=s.size()+1) {
                dp[i][j] = dp[i-1][j+i] || (dp[i][j+i] && strCmp(s, j-1, j+i-1, i, '>'));
            }
        }
    }

    // for (const auto& line : dp) {
    //     for (const auto& it : line) {
    //         cout << it << " ";
    //     } cout << endl;
    // }
    
    if (line1<line2 || (line1==line2 && strCmp(s, s.size()-line1, 0, line1, '<'))) {
        cout << s.substr(s.size()-line1, line1) << endl;
    } else {
        cout << s.substr(0, line2) << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
