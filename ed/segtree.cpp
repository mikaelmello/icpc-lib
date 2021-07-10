
struct segtree {
  int n, depth;

  void init(long s, int* arr) {
    n = s;
    memset(t, 0, sizeof(t));
    memset(lazy, 0, sizeof(lazy));

    init(1, 1, n, arr);
  }

  ll init(int i, int l, int r, int* arr) {
    if (l == r) {
      return t[i] = arr[l - 1];
    }

    int mid = (l + r) / 2;
    ll a = init(i * 2, l, mid, arr);
    ll b = init(i * 2 + 1, mid + 1, r, arr);

    return t[i] = min(a, b);
  }

  void eval_lazy(int i, int l, int r) {
    t[i] += lazy[i];

    if (l != r) {
      lazy[i * 2] += lazy[i];
      lazy[i * 2 + 1] += lazy[i];
    }
    lazy[i] = 0;
  }

  ll query(int l, int r) {
    if (l > r) return 0;

    return query(1, 1, n, l, r);
  }

  ll query(int i, int tl, int tr, int ql, int qr) {
    eval_lazy(i, tl, tr);

    if (ql <= tl && tr <= qr) return t[i];
    if (tl > tr || tr < ql || qr < tl) return 0;

    int mid = (tl + tr) / 2;
    ll a = query(i * 2, tl, mid, ql, qr);
    ll b = query(i * 2 + 1, mid + 1, tr, ql, qr);
    return min(a, b);
  }

  void update(int l, int r, ll v) {
    if (l > r) return;
    update(1, 1, n, l, r, v);
  }

  ll update(int i, int tl, int tr, int ql, int qr, ll v) {
    eval_lazy(i, tl, tr);

    if (tl > tr || tr < ql || qr < tl) return t[i];
    if (ql <= tl && tr <= qr) {
      lazy[i] += v;
      eval_lazy(i, tl, tr);
      return t[i];
    }
    if (tl == tr) return t[i];

    int mid = (tl + tr) / 2;
    ll a = update(i * 2, tl, mid, ql, qr, v);
    ll b = update(i * 2 + 1, mid + 1, tr, ql, qr, v);
    return t[i] = min(a, b);
  }

  ll bsearch(int i, int l, int r, int v) {
    eval_lazy(i, l, r);
    if (l == r) return l;

    int mid = (l + r) / 2;
    eval_lazy(i * 2, l, mid);
    if (t[i * 2] < v) return bsearch(i * 2, l, mid, v);
    return bsearch(i * 2 + 1, mid + 1, r, v);
  }
};