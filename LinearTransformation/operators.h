#ifndef OPERATORS_H
#define OPERATORS_H

#include <vector>
#include <cmath>

// ベクトルの内積
double dot(const std::vector<double>& a, const std::vector<double>& b) {
  double sum = 0;
  for (int i = 0; i < a.size(); ++i) {
    sum += a[i] * b[i];
  }
  return sum;
}

// ベクトルのスカラー倍
std::vector<double> scalar_multiple(const std::vector<double>& a, double k) {
  std::vector<double> res(a.size());
  for (int i = 0; i < a.size(); ++i) {
    res[i] = a[i] * k;
  }
  return res;
}

// ベクトルの和
std::vector<double> add(const std::vector<double>& a, const std::vector<double>& b) {
  std::vector<double> res(a.size());
  for (int i = 0; i < a.size(); ++i) {
    res[i] = a[i] + b[i];
  }
  return res;
}

// ベクトルの差
std::vector<double> sub(const std::vector<double>& a, const std::vector<double>& b) {
  std::vector<double> res(a.size());
  for (int i = 0; i < a.size(); ++i) {
    res[i] = a[i] - b[i];
  }
  return res;
}

// ベクトルのノルム
double norm(const std::vector<double>& a) {
  return std::sqrt(dot(a, a));
}

#endif // OPERATORS_H