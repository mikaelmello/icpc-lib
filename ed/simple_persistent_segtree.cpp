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
const int M = 60 * N;

ii t[M];
int lf[M];
int rg[M];

int n, q;
int a[N];
int last[N];
int lft[N];
int sz;

ii combine(ii a, ii b) { return min(a, b); }

int newnode(ii val) {
  t[sz] = val;
  return sz++;
}

int newnode(int l, int r) {
  lf[sz] = l;
  rg[sz] = r;
  t[sz] = combine(t[l], t[r]);
  return sz++;
}

ii query(int v, int tl, int tr, int l, int r) {
  if (l >= r) return {INF, 0};

  if (l == tl && r == tr) return t[v];

  int mid = (tl + tr) / 2;

  return combine(query(lf[v], tl, mid, l, min(mid, r)),
                 query(rg[v], mid, tr, max(l, mid), r));
}

int update(int v, int tl, int tr, int pos, int val) {
  if (tl == tr - 1) return newnode({val, pos});

  int mid = (tl + tr) / 2;
  if (pos < mid)
    return newnode(update(lf[v], tl, mid, pos, val), rg[v]);
  else
    return newnode(lf[v], update(rg[v], mid, tr, pos, val));
}

int build(int l, int r) {
  if (l == r - 1) return newnode({INF, l});

  int mid = (l + r) / 2;
  return newnode(build(l, mid), build(mid, r));
}

int(((((((((((((((main)))))))))))))))() {
  FASTIO;
  scanf("%d", &n);
  rep(i, 0, n) { scanf("%d", &a[i]); }

  memset(last, -1, sizeof last);
  for (int i = 0; i < n; i++) {
    lft[i] = last[a[i]];
    last[a[i]] = i;
  }

  vi sgt(n + 2);
  sgt[0] = build(0, n);
  for (int i = 0; i < n; i++) {
    int cur = sgt[i];
    if (lft[i] != -1) cur = update(cur, 0, n, lft[i], INF);
    cur = update(cur, 0, n, i, lft[i]);
    sgt[i + 1] = cur;
  }

  scanf("%d", &q);
  rep(i, 0, q) {
    int l, r;
    scanf("%d %d", &l, &r);
    l--;

    ii ans = query(sgt[r], 0, n, l, r);
    if (ans.ff < l)
      printf("%d\n", a[ans.ss]);
    else
      printf("0\n");
  }
}