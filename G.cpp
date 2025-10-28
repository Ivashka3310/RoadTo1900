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

bool strCmpLow(const char& a, const char& b) {
    return a<b;
}

bool strCmpLow(const string& a, const string& b) {
    for (size_t i=0; i<a.size(); ++i) {
        if (a[i]>b[i]) 
            return false;
        else if (a[i]<b[i])
            return true;
    }
    return false;
}

bool strCmpHigh(const string& a, const string& b) {
    for (size_t i=0; i<a.size(); ++i) {
        if (a[i]<b[i]) 
            return false;
        else if (a[i]>b[i])
            return true;
    }
    return false;
}

void solve() {
    string s;
    cin>>s;
    ll k=2*sqrt(s.size());

    vector dp(k+1, vb(s.size()+2, false));

    for (ll i=0; i<=k; ++i) {
        dp[i][0] = true;
    }

    ll line1, line2;
    for (ll i=1; i<=k && dp[i-1][s.size()]==false; ++i) {
        line1 = i;
        for (ll j=1; j<=s.size(); ++j) {
            if (j>=i) {
                dp[i][j] = dp[i-1][j-i] || (dp[i][j-i] 
                    && strCmpLow(s.substr(j-2*i, i), s.substr(j-i, i)));
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
            if (j+i<=s.size()+1) {
                dp[i][j] = dp[i-1][j+i] || (dp[i][j+i] 
                    && strCmpHigh(s.substr(j-1, i), s.substr(j+i-1, i)));
            }
        }
    }

    // for (const auto& line : dp) {
    //     for (const auto& it : line) {
    //         cout << it << " ";
    //     } cout << endl;
    // }
    
    string ans1=s.substr(s.size()-line1, line1), ans2=s.substr(0, line2);
    if (ans1.size()<ans2.size() || (ans1.size()==ans2.size() && strCmpLow(ans1, ans2))) {
        cout << ans1 << endl;
    } else {
        cout << ans2 << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}