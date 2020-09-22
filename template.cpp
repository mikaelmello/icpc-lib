#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;  // or pb_ds;

using namespace std;

#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
#define fff ff
#define sss ss.ff
#define ttt ss.ss
#define INF (1 << 30)
#define LLF (1ll << 60)
#define PRIME (1000000007)
#define FASTIO std::ios::sync_with_stdio(false)

#ifdef DEBUG
#define debug(x) cerr << #x << " = " << x << endl
#else
#define debug(x)
#define endl '\n'
#endif

#define rep(i, begin, end)                            \
  for (__typeof(end) i = (begin) - ((begin) > (end)); \
       i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))

#define FILE_INPUT                  \
  freopen("input.txt", "r", stdin); \
  freopen("output.txt", "w", stdout)

#define all(x) x.begin(), x.end()

typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<string> vs;

template <typename T, typename B = null_type>
using oset =
    tree<T, B, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order / order_of_key

const ld eps = 1e-6;

ll fexp(ll b, ll e, ll p = PRIME) {
  ll res = 1;
  while (e) {
    if (e & 1) res = (res * b) % p;
    b = (b * b) % p;
    e >>= 1;
  }
  return res;
}

const ll RANDOM_SEED =
    chrono::high_resolution_clock::now().time_since_epoch().count();
/*
mt19937 rng(RANDOM_SEED);
shuffle(permutation.begin(), permutation.end(), rng);
 */

struct no_hack_hash {
  ll operator()(ll x) const { return x ^ RANDOM_SEED; }
};

struct iihash {
  ll operator()(ii x) const { return x.first * 31 + x.second; }
};

// To use most bits rather than just the lowest ones:
struct ghash {  // large odd number for C
  const uint64_t C = ll(4e18 * acos(0)) | 71;
  ll operator()(ll x) const { return __builtin_bswap64(x * C); }
};

void ae(ll val) {
  cout << val << endl;
  exit(0);
}

/*-----------------END TEMPLATE-----------------*/