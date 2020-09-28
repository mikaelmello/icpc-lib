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

const int N = 2e5 + 50;

struct dsu_save {
  bool anything = true;
  int v, u, szv, szu;
  set<ii> m;
  bool vBigger;
};

set<ii> cmp[N];
int p[N];
int sz[N];
int a[N];
vii edges;
vii queries;
vi forbiddenEdges;
set<int> fed;
stack<dsu_save> changes;

int n, m, q;

void bdsu() {
  for (int i = 1; i <= n; i++) {
    p[i] = i;
    sz[i] = 1;
    cmp[i].emplace(-a[i], i);
  }
}

int fnd(int a) {
  while (a != p[a]) a = p[a];
  return a;
}

void sjoin(int a, int b) {
  a = fnd(a);
  b = fnd(b);
  if (a == b) return;

  if (sz[a] < sz[b]) swap(a, b);

  p[b] = a;
  sz[a] += sz[b];
  for (auto x : cmp[b]) cmp[a].insert(x);
}

set<ii>& getcmp(int a) { return cmp[fnd(a)]; }

void join(int a, int b) {
  a = fnd(a);
  b = fnd(b);
  auto store = dsu_save();
  store.u = a;
  store.v = b;
  store.szu = sz[a];
  store.szv = sz[b];
  store.vBigger = false;

  if (sz[a] < sz[b]) {
    swap(a, b);
    store.vBigger = true;
  }

  if (a == b) {
    store.anything = false;
    changes.push(store);
    return;
  };
  changes.push(store);
  p[b] = a;
  sz[a] += sz[b];
  for (auto x : cmp[b]) cmp[a].insert(x);
}

void dsu_pop() {
  auto top = changes.top();
  changes.pop();

  if (!top.anything) return;

  if (top.vBigger) {
    swap(top.u, top.v);
    swap(top.szu, top.szv);
  }

  vii to_erase;
  for (auto x : cmp[top.v]) {
    if (cmp[p[top.u]].count(x) == 0)
      to_erase.pb(x);
    else
      cmp[p[top.u]].erase(x);
  }
  for (auto x : to_erase) {
    cmp[top.v].erase(x);
  }

  p[top.u] = top.u;
  p[top.v] = top.v;
  sz[top.u] = top.szu;
  sz[top.v] = top.szv;
}

// https://codeforces.com/contest/1416/problem/D

int(((((((((((((((main)))))))))))))))() {
  FASTIO;
  cin >> n >> m >> q;
  rep(i, 0, n) { cin >> a[i + 1]; }
  rep(i, 0, m) {
    int x, y;
    cin >> x >> y;
    edges.emplace_back(x, y);
  }
  bdsu();

  rep(i, 0, q) {
    int x, y;
    cin >> x >> y;
    queries.emplace_back(x, y);
    if (x == 2) {
      forbiddenEdges.pb(y - 1);
      fed.insert(y - 1);
    }
  }

  rep(i, 0, m) {
    if (fed.count(i)) continue;

    sjoin(edges[i].ff, edges[i].ss);
  }

  for (auto x = forbiddenEdges.rbegin(); x != forbiddenEdges.rend(); x++) {
    auto edge = edges[*x];
    join(edge.ff, edge.ss);
  }

  for (auto x : queries) {
    int type = x.ff;
    int v = x.ss;

    if (type == 1) {
      auto& cmp = getcmp(v);
      if (cmp.size() == 0)
        cout << 0 << endl;
      else {
        auto top = *cmp.begin();
        cout << -top.ff << endl;
        cmp.erase(top);
      }
    } else {
      dsu_pop();
    }
  }
}