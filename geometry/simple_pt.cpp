#include <bits/stdc++.h>

typedef long double ld;
const ld eps = 1e-6;

struct pt {
  double x, y;
  pt(double x, double y) : x(x), y(y) {}
  pt() : x(0), y(0) {}

  pt operator+(pt& other) { return {x + other.x, y + other.y}; }
  pt operator-(pt& other) { return {x - other.x, y - other.y}; }
  pt operator*(double& t) const { return {x * t, y * t}; }
  double dist(pt& other) {
    double dx = x - other.x;
    double dy = y - other.y;
    return sqrt(dx * dx + dy * dy);
  }
  pt normalized() {
    double norm = sqrt(x * x + y * y);
    if (norm > eps) x /= norm, y /= norm;
    return {x, y};
  }
};