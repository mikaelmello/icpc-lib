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

const int N = 1e6;

int n, m, q;
int a[N];
int p[N], tin[N], tout[N];
ii t[4 * N], queries[N];
vi ed[N];
iii edges[N];
int timer;

void bdsu() {
  for (int i = 1; i <= n; i++) {
    p[i] = i;
  }
}

void dfs(int i) {
  tin[i] = ++timer;

  for (auto e : ed[i]) {
    dfs(e);
  }

  tout[i] = timer;
}

int find(int a) {
  if (a == p[a]) return a;
  return p[a] = find(p[a]);
}

void join(int a, int b) {
  a = find(a);
  b = find(b);

  if (a == b) return;

  n++;
  p[n] = n;
  p[a] = n;
  p[b] = n;
  ed[n].pb(a);
  ed[n].pb(b);
}

ii query(int v, int tl, int tr, int l, int r) {
  if (l > r || tl > r || tr < l) {
    return {0, 0};
  }
  if (l <= tl && r >= tr) {
    return t[v];
  }

  int mid = (tl + tr) >> 1;
  int c1 = (v << 1), c2 = (c1 | 1);

  return max(query(c1, tl, mid, l, r), query(c2, mid + 1, tr, l, r));
}

void update(int v, int tl, int tr, int pos, ii val) {
  if (tl == tr) {
    t[v] = val;
    return;
  }
  int mid = (tl + tr) >> 1;
  int c1 = (v << 1), c2 = (c1 | 1);

  if (pos <= mid) {
    update(c1, tl, mid, pos, val);
  } else {
    update(c2, mid + 1, tr, pos, val);
  }

  t[v] = max(t[c1], t[c2]);
}

// https://codeforces.com/contest/1416/problem/D

int(((((((((((((((main)))))))))))))))() {
  FASTIO;
  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  for (int i = 1; i <= m; i++) {
    int x, y;
    cin >> x >> y;
    edges[i] = make_tuple(x, y, 0);
  }

  bdsu();

  for (int i = 1; i <= q; i++) {
    int x, y;
    cin >> x >> y;
    queries[i] = {x, y};
    if (x == 2) {
      get<2>(edges[y]) = 1;
    }
  }

  for (int i = 1; i <= m; i++) {
    int x, y, z;
    tie(x, y, z) = edges[i];
    if (z) continue;
    join(x, y);
  }

  for (int i = q; i > 0; i--) {
    int& x = queries[i].ff;
    int& v = queries[i].ss;
    if (x == 1) {
      v = find(v);
    } else {
      int u, vv, z;
      tie(u, vv, z) = edges[v];
      join(u, vv);
    }
  }

  for (int i = 1; i <= n; i++) {
    if (i == find(i)) dfs(i);
  }

  for (int i = 1; i <= n; i++) {
    update(1, 1, n, tin[i], {a[i], tin[i]});
  }

  for (int i = 1; i <= q; i++) {
    int tp = queries[i].ff;
    int v = queries[i].ss;
    if (tp == 1) {
      ii res = query(1, 1, n, tin[v], tout[v]);

      cout << res.ff << endl;
      if (res.ss != 0) {
        update(1, 1, n, res.ss, {0, 0});
      }
    }
  }
}