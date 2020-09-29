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

using ld = long double;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using ii = pair<int, int>;
using iii = tuple<int, int, int>;
using vii = vector<ii>;
using viii = vector<iii>;
using vs = vector<string>;

template <typename T, typename B = null_type>
using oset =
    tree<T, B, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order / order_of_key

const ld eps = 1e-6;
const int INF = 1 << 30;
const ll LLF = 1ll << 60;
const int PRIME = 1e9 + 7;

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

const int N = 5e5 + 50;
const int block_size = 800;
const int P = 800;

inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
  if (pow == 0) {
    return 0;
  }
  int hpow = 1 << (pow - 1);
  int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
  seg = (seg + rotate) & 3;
  const int rotateDelta[4] = {3, 0, 0, 1};
  int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
  int nrot = (rotate + rotateDelta[seg]) & 3;
  int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
  int64_t ans = seg * subSquareSize;
  int64_t add = gilbertOrder(nx, ny, pow - 1, nrot);
  ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
  return ans;
}

struct Query {
  int l, r, idx;
  int64_t ord;
  inline void calcOrder() { ord = gilbertOrder(l, r, 21, 0); }

  bool operator<(Query other) const { return ord < other.ord; }
};

int n, qn;
int a[N];
vector<Query> q;
int ans[N];

int cnt[N];
int bkt[P];
int tot;

void remove(int i) {
  int val = a[i];
  cnt[val]--;
  if (cnt[val] == 1) {
    bkt[val / P]++;
    tot++;
  } else if (cnt[val] == 0) {
    bkt[val / P]--;
    tot--;
  }
}

void add(int i) {
  int val = a[i];
  cnt[val]++;
  if (cnt[val] == 1) {
    bkt[val / P]++;
    tot++;
  } else if (cnt[val] == 2) {
    bkt[val / P]--;
    tot--;
  }
}

int answer() {
  if (tot == 0) return 0;

  for (int i = 0; i < P; i++) {
    if (bkt[i] == 0) continue;
    for (int j = i * P;; j++) {
      if (cnt[j] == 1) return j;
    }
  }

  assert(false);
}

// https://codeforces.com/contest/1000/problem/F

int(((((((((((((((main)))))))))))))))() {
  FASTIO;
  scanf("%d", &n);
  rep(i, 0, n) { scanf("%d", &a[i]); }
  scanf("%d", &qn);
  rep(i, 0, qn) {
    int l, r;
    scanf("%d %d", &l, &r);
    Query qq = {--l, --r, i};
    qq.calcOrder();
    q.push_back(qq);
  }

  sort(all(q));

  int cl = 0, cr = -1;
  for (auto qq : q) {
    while (cl > qq.l) {
      cl--;
      add(cl);
    }
    while (cr < qq.r) {
      cr++;
      add(cr);
    }
    while (cl < qq.l) {
      remove(cl);
      cl++;
    }
    while (cr > qq.r) {
      remove(cr);
      cr--;
    }
    ans[qq.idx] = answer();
  }

  rep(i, 0, qn) { printf("%d\n", ans[i]); }
}