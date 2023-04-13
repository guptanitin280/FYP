#include <bits/stdc++.h>
#include "shared/Input.h"
#include "aco/aco.h"
#include "shared/Output.h"
#include "shared/Score.h"

#define int long long


#define nitin          ios_base::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.f << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef FYP
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

void solve() {
    Input I("test_data/me_at_the_zoo.in");
    aco::ff.open("ip.txt");
    {
        aco a(I,initializingAlgo::CLASSICAL_WAY);
        Output o=a.run(200);
        cout<<Score::calculate(I,o)<<endl;
        cout<<a.isValid()<<endl;
    }

    {
        aco b(I,initializingAlgo::RANDOM_GREEDY_WAY);
        Output p=b.run(200);
        cout<<Score::calculate(I,p)<<endl;
        cout<<b.isValid()<<endl;
    }
    aco::ff.close();
}

int32_t main() {
    nitin;

    solve();
}