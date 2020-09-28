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
#ifndef DEBUG
#define endl '\n'
#endif
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

const int RANDOM =
    chrono::high_resolution_clock::now().time_since_epoch().count();

struct no_hack_hash {
  int operator()(int x) const { return x ^ RANDOM; }
};

struct iihash {
  int operator()(ii x) const { return x.first * 31 + x.second; }
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

const int N = 1e5 + 100;

int n, q;
ld t[4 * N];
ld mul[4 * N], add[4 * N];

void push(int v, int l, int r) {
  if (abs(mul[v] - 1.0) > eps) {
    t[v] *= mul[v];
    if (l < r) {
      add[2 * v] *= mul[v];
      add[2 * v + 1] *= mul[v];
      mul[2 * v] *= mul[v];
      mul[2 * v + 1] *= mul[v];
    }
    mul[v] = 1;
  }
  if (abs(add[v]) > eps) {
    t[v] += add[v] * (r - l + 1);

    if (l < r) {
      add[2 * v] += add[v];
      add[2 * v + 1] += add[v];
    }

    add[v] = 0;
  }
}

ld sum(int v, int tl, int tr, int l, int r) {
  push(v, l, r);
  if (l > tr || r < tl) return 0;
  if (l <= tl && tr <= r) return t[v];

  int tm = (tl + tr) / 2;
  return sum(v * 2, tl, tm, l, r) + sum(v * 2 + 1, tm + 1, tr, l, r);
}

void add_u(int v, int tl, int tr, int l, int r, ld exp) {
  push(v, l, r);
  if (l > tr || r < tl) return;
  if (l <= tl && tr <= r) {
    add[v] += exp;
    push(v, l, r);
  } else {
    int tm = (tl + tr) / 2;
    add_u(v * 2, tl, tm, l, r, exp);
    add_u(v * 2 + 1, tm + 1, tr, l, r, exp);
  }
}

void mul_u(int v, int tl, int tr, int l, int r, ld val) {
  push(v, l, r);
  if (l > tr || r < tl) return;
  if (l <= tl && tr <= r) {
    mul[v] = val;
    push(v, l, r);
  } else {
    int tm = (tl + tr) / 2;
    mul_u(v * 2, tl, tm, l, r, val);
    mul_u(v * 2 + 1, tm + 1, tr, l, r, val);
  }
}

int(((((((((((((((main)))))))))))))))() {
  cin >> n >> q;
  rep(i, 1, n + 1) {
    int x;
    cin >> x;
    add_u(1, 1, n, i, i, x);
  }

  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int l1, r1, l2, r2;
      cin >> l1 >> r1 >> l2 >> r2;
      ld exp1 = sum(1, 1, n, l1, r1);
      ld exp2 = sum(1, 1, n, l2, r2);

      int len1 = r1 - l1 + 1;
      int len2 = r2 - l2 + 1;
      exp1 /= len1;
      exp1 /= len2;
      exp2 /= len1;
      exp2 /= len2;

      mul_u(1, 1, n, l1, r1, ld(len1 - 1) / len1);
      mul_u(1, 1, n, l2, r2, ld(len2 - 1) / len2);
      add_u(1, 1, n, l1, r1, exp1);
      add_u(1, 1, n, l2, r2, exp2);
    } else {
      int l, r;
      cin >> l >> r;
      cout << fixed << setprecision(20) << sum(1, 1, n, l, r) << endl;
    }
  }
}

// https://codeforces.com/contest/895/problem/E