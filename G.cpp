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

string solve(string&s) {
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
    cout << s.substr(s.size()-line1, line1) << " " << s.substr(0, line2) << endl;
    if (line1<line2 || (line1==line2 && strCmp(s, s.size()-line1, 0, line1, '<'))) {
        return s.substr(s.size()-line1, line1);
    } else {
        return s.substr(0, line2);
    }
}

class GenTests {
    vector<string> tests;
    vector<string> ans;

    void gen(string s, ll n) {
        if (s.size()==n) {
            tests.push_back(s);
            return;
        }

        gen(s+"1", n);
        gen(s+"2", n);
        gen(s+"3", n);
    }

    bool check(vector<string>& a) {
        if (a.size()<=2) 
            return true;

        bool flag=true;
        ll i;
        for (i=1; i<a.size()&&flag; ++i) {
            flag = (a[i-1].size()<a[i].size() || (a[i-1].size()==a[i].size() && memcmp(a[i-1].c_str(), a[i].c_str(), a[i].size())<0));
        }
        if (flag) {
            return true;
        }

        flag = true;
        for (i=1; i<a.size()&&flag; ++i) {
            flag = (a[i-1].size()>a[i].size() || (a[i-1].size()==a[i].size() && memcmp(a[i-1].c_str(), a[i].c_str(), a[i].size())>0));
        }
        return flag;
    }

    static bool cmp(const string& s1, const string& s2) {
        if (s1.size()<s2.size())
            return true;
        else if (s1.size()>s2.size()) {
            return false;
        } else {
            if (memcmp(s1.c_str(), s2.c_str(), s1.size()) < 0) {
                return true;
            } else {
                return false;
            }
        }
    }

    string solve(const string& s, ll i, vector<string> path={}) {
        if (i==s.size()) {
            if (check(path)) {
                // for (auto&x : path) {
                //     cout << x << " ";
                // } cout << endl;
                return *max_element(path.begin(), path.end(), cmp);
            } else {
                return string(s);
            }
        }
        path.push_back(s.substr(i, 1));
        string s1 = solve(s, i+1, path);
        path.pop_back();
        if (path.empty()) {
            return s1;
        }
        path.back().push_back(s[i]);
        string s2 = solve(s, i+1, path);
        //cout << s1 << " and " << s2 << endl;
        if (s1.size()<s2.size())
            return s1;
        else if (s1.size()>s2.size()) {
            return s2;
        } else {
            if (memcmp(s1.c_str(), s2.c_str(), s1.size()) < 0) {
                return s1;
            } else {
                return s2;
            }
        }
    }

public:
    GenTests() = default;
    ~GenTests() = default;

    vector<string> run(ll n) {
        gen("", n);
        return tests;
    }

    vector<string> answers() {
        for (int i=0; i<tests.size(); ++i) {
            ans.push_back(solve(tests[i], 0));
        }
        return ans;
    }
};


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin>>s;
    cout << solve(s) << endl;

    // GenTests gen;
    // vector test = gen.run(12), ans = gen.answers();
    // bool flag=true;
    // for (ll i=0; i<test.size(); ++i) {
    //     if (ans[i]!=solve(test[i])) {
    //         flag = false;
    //         cout << test[i] << " " << ans[i] << " " << solve(test[i]) << endl;
    //     }
    // }
    // if (flag) {
    //     cout << "OK" << endl;
    // } else {
    //     cout << "WA" << endl;
    // }
    return 0;
}

/*
11313123133 1131 3133
12213123133 1221 3133
13123123133 1312 3133
13223123133 1322 3133
13323123133 1332 3133
13333123133 1333 3133
22131321111 1111 2213
22131321112 1112 2213
22131321113 1113 2213
22131321121 1121 2213
22131321122 1122 2213
22131321123 1123 2213
22131321131 1131 2213
22131321132 1132 2213
22131321133 1133 2213
22131321211 1211 2213
22131321212 1212 2213
22131321213 1213 2213
22131321221 1221 2213
22131321222 1222 2213
22131321223 1223 2213
22131321231 1231 2213
22131321232 1232 2213
22131321233 1233 2213
22131321311 1311 2213
22131321312 1312 2213
22131321313 1313 2213
22131321321 1321 2213
22131322111 2111 2213
22131322112 2112 2213
22131322113 2113 2213
22131322121 2121 2213
22131322122 2122 2213
22131322123 2123 2213
22131322131 2131 2213
22131322132 2132 2213
22131322133 2133 2213
22131322211 2211 2213
22131322212 2212 2213
22131331111 1111 2213
22131331112 1112 2213
22131331113 1113 2213
22131331121 1121 2213
22131331122 1122 2213
22131331123 1123 2213
22131331131 1131 2213
22131331132 1132 2213
22131331133 1133 2213
22131331211 1211 2213
22131331212 1212 2213
22131331213 1213 2213
22131331221 1221 2213
22131331222 1222 2213
22131331223 1223 2213
22131331231 1231 2213
22131331232 1232 2213
22131331233 1233 2213
22131331311 1311 2213
22131331312 1312 2213
22131331313 1313 2213
22131331321 1321 2213
22131331322 1322 2213
22131331323 1323 2213
22131331331 1331 2213
22131332111 2111 2213
22131332112 2112 2213
22131332113 2113 2213
22131332121 2121 2213
22131332122 2122 2213
22131332123 2123 2213
22131332131 2131 2213
22131332132 2132 2213
22131332133 2133 2213
22131332211 2211 2213
22131332212 2212 2213
22323123133 2232 3133
23123123133 2312 3133
23333123133 2333 3133
31221221211 1211 3122
31221221212 1212 3122
31221221213 1213 3122
31221221221 1221 3122
32131331311 1311 3213
32131331312 1312 3213
32131331313 1313 3213
32131331322 1322 3213
32131331323 1323 3213
32131331331 1331 3213
32131332322 2322 3213
32131332323 2323 3213
32131332331 2331 3213
32131332332 2332 3213
32231331311 1311 3223
32231331312 1312 3223
32231331313 1313 3223
32231331322 1322 3223
32231331323 1323 3223
32231331331 1331 3223
32231332322 2322 3223
32231332323 2323 3223
32231332331 2331 3223
32231332332 2332 3223
33132332322 2322 3313
33132332323 2323 3313
33132332331 2331 3313
33132332332 2332 3313
*/
