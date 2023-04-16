#include <bits/stdc++.h>

typedef long double ld;
#define int long long

#define gcd            __gcd
#define endl           "\n"
#define setbits(x)     __builtin_popcountll(x)
#define zrobits(x)     __builtin_ctzll(x)
#define mod            1000000007
#define mod2           998244353
#define maxe           *max_element
#define mine           *min_element
#define inf            1e18
#define pb             push_back
#define all(x)         x.begin(), x.end()
#define f              first
#define s              second
#define sz(x)          (int)(x).size()
#define deci(x, y)     fixed<<setprecision(y)<<x
#define w(t)           int t; cin>>t; while(t--)
#define nitin          ios_base::sync_with_stdio(false); cin.tie(nullptr)
#define PI             3.141592653589793238
#define mem0(x)        memset(x,0,sizeof x)
#define mem1(x)        memset(x,-1,sizeof x)
using namespace std;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.f << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef NITIN
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

/*
 think about hashing while comparing contiguous elements...
 try to think backward..
 if you arent able to come up for answer, try to fix some variable, some bits, initial starting point or end point.....
 may be break a operation into two or combine two into one
*/
 std::mt19937  rng(std::chrono::steady_clock::now().time_since_epoch().count());

uint32_t rand(uint32_t x,uint32_t y) {
    return std::uniform_int_distribution<uint32_t>(x, y)(rng);
}

void solve(string fileName) {
    ofstream cout(fileName+".txt");
    int videos = 1000;
    int endpoints = 1000;
    int requests = 1000;
    int cacheServer = 100;
    int cacheCapacity = 5000;

    int minVideoSize = 100;
    int maxVideoSize = 1000;

    int maxCacheServerLatency = 2000;
    int maxDataServerLatency = 4000;


    cout << videos << " " << endpoints << " " << requests << " " << cacheServer << " " << cacheCapacity << endl;
    for (int i = 0; i < videos; i++) {
        cout << rand(minVideoSize, maxVideoSize) << " ";
    }
    cout << endl;

    for (int i = 0; i < endpoints; i++) {
        cout << rand(maxCacheServerLatency, maxDataServerLatency) << " ";

        int connectedTo = rand(0, cacheServer);
        cout << connectedTo << " ";
        set<int> s;
        while (sz(s) != connectedTo) {
            s.insert(rand(0, cacheServer - 1));
        }
        for (auto &c: s) {
            cout << c << " " << rand(1,maxCacheServerLatency)<<" ";
        }
        cout << endl;
    }

    for (int i = 0; i < requests; i++) {
        cout << rand(0, videos - 1) << " " << rand(0, endpoints - 1) << " " << rand(1, 1000) << endl;
    }

    cout.close();
}

int32_t main() {
    nitin;

    for (char x = 'A'; x <= 'I'; x++) {
        solve(string(1,x));
    }
}