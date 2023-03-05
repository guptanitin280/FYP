#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> p32;
typedef pair<ll,ll> pll;
typedef pair<double,double> pdd;
typedef vector<ll> vll;
typedef vector<vector<ll> > vvll;
typedef vector<vector<pll> > vvpll;
typedef vector<pll> vpll;
const ll MOD = 1e9 +7;
const ll MOD2= 998244353;
double eps = 1e-12;
#define fori(e) for(ll i = 0; i < e; i++)
#define forj(e) for(ll j = 0; j < e; j++)
#define fork(e) for(ll k = 0; k < e; k++)
#define forri(e) for(ll i = e; i >= 0; i--)
#define forrj(e) for(ll j = e; j >= 0; j--)
#define forrk(e) for(ll k = e; k >= 0; k--)
#define forsi(s,e) for(ll i = s; i < e; i++)
#define forsj(s,e) for(ll j = s; j < e; j++)
#define forsk(s,e) for(ll k = s; k < e; k++)
#define forn(k,e) for(ll k = 0; k < e; k++)
#define forsn(i,s,e) for(ll i = s; i < e; i++)
#define forx(v) for(auto x:v)
#define gcd             __gcd
#define setbits(x)     __builtin_popcountll(x)
#define zrobits(x)     __builtin_ctzll(x)
#define maxe           *max_element
#define mine           *min_element
#define deci(x, y)     fixed<<setprecision(y)<<x
#define ln endl
#define dbg1(x) cout<<#x<<" = "<<x<<endl
#define dbg2(x,y) cout<<#x<<" = "<<x<<endl<<#y<<" = "<<y<<endl
#define dbg3(x,y,z) cout<<#x<<" = "<<x<<endl<<#y<<" = "<<y<<endl<<#z<<" = "<<z<<endl
//#define mp make_pair
#define append push_back
#define fi first
#define se second
#define INF 2e18
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())
#define mem0(x)        memset(x,0,sizeof x)
#define mem1(x)        memset(x,-1,sizeof x)
//!!don't use memset for anything other than these 2
#define YES cout<<"YES"<<endl
#define NO  cout<<"NO"<<endl
#define Yes cout<<"Yes"<<endl
#define No  cout<<"No"<<endl

using namespace std;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }


#ifdef RISHAB
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#define endl           "\n"
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#endif


template <typename T>
void printar(T *ar, ll n)
{
    fori(n) cout<<ar[i]<<" ";
    cout<<endl;
}


ll power(ll x, ll y, ll p)
{
    ll res = 1;
    x = x % p;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}
ll imod(ll a, ll m)
{
    return power(a, m - 2, m);
}


template< typename T, size_t N, size_t M >
void print2dArray( T(&theArray)[N][M]  ,ll n=N, ll m=M) {
    for ( ll x = 0; x < n; x ++ ) {
        for ( ll y = 0; y < m; y++ ) {
            cout << theArray[x][y] << " ";
        }
        cout<<endl;
    }
}


template< typename T, size_t N >
void print_ar( T(&theArray)[N]  ,ll n=N) {
    for ( ll x = 0; x < n; x ++ )
    {
        cout << theArray[x] << " ";
    }
    cout<<endl;
}

template<class T>
bool ckmin(T& a, const T& b)
{
    return b < a ? a = b, 1 : 0;
} // a = min(a,b)

template<class T>
bool ckmax(T& a, const T& b)
{
    return a < b ? a = b, 1 : 0;
} //a=max(a,b)

string to_strin(ll num)
{
    string ans;
    while(num)
    {
        ll t= num%10;
        ans+= ('0'+t);
        num/=10;
    }
    reverse(all(ans));
    return ans;
}

//add & if needed
ll to_in(const string& s){
    ll ans=0;
    forx(s){ans*=10;ans+=(x-'0');}
    return ans;
}

ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up

ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down

bool ispow2(ll i) { return i && (i & -i) == i; } //checks if i is a power of 2

const string path_input="../DIMAC_graphs/brock200-2.txt";
const string output="../test_data/brock200-2.txt";
ifstream fin(path_input);
ofstream fout(output);

void solve(){
    ll n,K,m,tmp;
    fin>>n>>m;
    vll temp[n];
    fori(n){
        temp[i].assign(n,1);
    }
    fori(m){
        ll a,b;
        fin>>a>>b;
        a--;
        b--;
        temp[a][b]=0;
        temp[b][a]=0;
    }
    vll g[n];
    vector<vll> ed;
    fori(n){
        forj(n){
            if(i==j)temp[i][j]=0;
            if(temp[i][j]==0)continue;
            g[i].push_back(j);
            ed.push_back({i,j});
        }
    }
    set<ll> fliked[n],fdislike[n];
    ll cur=1;
    forx(ed){
        ll a=x[0],b=x[1];
//        ll hogya=0;
//        for(auto t:fliked[a]){
//            if(fdislike[b].count(t)){
//                hogya=1;
//                break;
//            }
//        }
//        if(hogya)continue;
//        for(auto t:fdislike[a]){
//            if(fliked[b].count(t)){
//                hogya=1;
//                break;
//            }
//        }
//        if(hogya)continue;
//        for(auto t:fliked[a]){
//            if(!fliked[b].count(t)){
//                fdislike[b].insert(t);
//                hogya=1;
//                break;
//            }
//        }
//        if(hogya)continue;
//
//        for(auto t:fliked[b]){
//            if(!fliked[a].count(t)){
//                fdislike[a].insert(t);
//                hogya=1;
//                break;
//            }
//        }
//        if(hogya)continue;
        fliked[a].insert(cur);
        fdislike[b].insert(cur);
        cur++;
        continue;
    }
    fout<<n<<endl;
    fori(n){
        fout<<sz(fliked[i])<<" ";
        forx(fliked[i])fout<<x<<" ";
        fout<<endl;

        fout<<sz(fdislike[i])<<" ";
        forx(fdislike[i])fout<<x<<" ";
        fout<<endl;
    }
    dbg_out(cur);




}
int32_t main()
{
    fast_cin();
    ll t=1;
//    cin >> t;
    for(ll it=1;it<=t;it++) {
        solve();
    }
    return 0;
}