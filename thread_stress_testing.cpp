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
using ii = pair<ll, ll>;
using iii = tuple<int, int, int>;
using vii = vector<ii>;
using viii = vector<iii>;
using vs = vector<string>;

template <typename T, typename B = null_type>
using oset =
    tree<T, B, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order / order_of_key

const int PRIME = 998244353;
const int INF = 1 << 30;
const ll LLF = 1ll << 60;
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

#define ae(val)                \
  {                            \
    cout << (((val))) << endl; \
    exit(0);                   \
  }

#define ar(val)                \
  {                            \
    cout << (((val))) << endl; \
    return;                    \
  }

void pc(char c, int t) { rep(i, 0, t) cout << c; }

/*-----------------END TEMPLATE-----------------*/

// Function to find Nth number in base 9
long long findNthNumber(long long N) {
  // Stores the Nth number
  long long result = 0;

  long long p = 1;

  // Iterate while N is
  // greater than 0
  while (N > 0) {
    // Update result
    result += (p * (N % 9));

    // Divide N by 9
    N = N / 9;

    // Multiply p by 10
    p = p * 10;
  }
  // Return result
  return result;
}

bool has_digit(ll n, ll d) {
  if (n == d) return true;
  while (n > 0) {
    if (n % 10 == d) return true;
    n /= 10;
  }
  return false;
}

ll brute(ll n, ll d) {
  int cnt = 0;
  for (int i = 1;; i++) {
    if (has_digit(i, d)) continue;
    cnt++;
    if (cnt == n) {
      return i;
    }
  }
}

ll my_ans(ll n, ll d) {
  if (d == 0) {
    ll converted = findNthNumber(n);
    ll org = converted;

    ll logx = 0;

    ll agora_vai = 0;
    ll base = 1;
    while (converted > 10) {
      converted /= 10;
      logx++;
    }

    agora_vai = org + base;

    ll brute_res = brute(n, d);
    if (agora_vai != brute_res) {
      cout << org << endl;
      cout << n << ' ' << d << endl;
      cout << agora_vai << ' ' << brute_res << endl;
      assert(false);
    }
    return agora_vai;
  }
  ll converted = findNthNumber(n);

  ll agora_vai = 0;
  ll base = 1;
  while (converted > 0) {
    ll digit = converted % 10;
    if (digit >= d) digit++;
    agora_vai += base * digit;
    base *= 10;
    converted /= 10;
  }

  ll brute_res = brute(n, d);
  if (agora_vai != brute_res) {
    cout << n << ' ' << d << endl;
    cout << agora_vai << ' ' << brute_res << endl;
    assert(false);
  }
  return agora_vai;
}

int main() {
  FASTIO;
  // ll n, d;
  // cin >> n >> d;
  // ae(my_ans(n, d));

  // for (int d = 0; d <= 9; d++) {
  //   for (int n = 1; n < 10000000; n++) {
  //     my_ans(n, d);
  //   }
  // }

  std::thread thread_0([] {
    for (int n = 1; n < 100000; n++) {
      my_ans(n, 0);
    }
  });

  std::thread thread_1([] {
    for (int n = 1; n < 100000; n++) {
      my_ans(n, 1);
    }
  });

  std::thread thread_2([] {
    for (int n = 1; n < 100000; n++) {
      my_ans(n, 2);
    }
  });

  std::thread thread_3([] {
    for (int n = 1; n < 100000; n++) {
      my_ans(n, 3);
    }
  });

  std::thread thread_4([] {
    for (int n = 1; n < 100000; n++) {
      my_ans(n, 4);
    }
  });

  std::thread thread_5([] {
    for (int n = 1; n < 100000; n++) {
      my_ans(n, 5);
    }
  });

  std::thread thread_6([] {
    for (int n = 1; n < 100000; n++) {
      my_ans(n, 6);
    }
  });

  std::thread thread_7([] {
    for (int n = 1; n < 100000; n++) {
      my_ans(n, 7);
    }
  });

  std::thread thread_8([] {
    for (int n = 1; n < 100000; n++) {
      my_ans(n, 8);
    }
  });

  std::thread thread_9([] {
    for (int n = 1; n < 100000; n++) {
      my_ans(n, 9);
    }
  });

  thread_0.join();
  thread_1.join();
  thread_2.join();
  thread_3.join();
  thread_4.join();
  thread_5.join();
  thread_6.join();
  thread_7.join();
  thread_8.join();
  thread_9.join();
}