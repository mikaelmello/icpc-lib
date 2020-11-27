int sz, tz;
string s, t;
int dp[5005][5005];

string lcs() {
  for (int i = 0; i <= sz; i++) {
    for (int j = 0; j <= tz; j++) {
      if (i == 0 || j == 0)
        dp[i][j] = 0;
      else if (s[i - 1] == t[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    }
  }

  int index = dp[sz][tz];
  string ans(index, '-');

  int i = sz, j = tz;
  while (i > 0 && j > 0) {
    if (s[i - 1] == t[j - 1]) {
      ans[index - 1] = s[i - 1];
      i--;
      j--;
      index--;
    }

    else if (dp[i - 1][j] > dp[i][j - 1])
      i--;
    else
      j--;
  }

  debug(ans);
  return ans;
}