#include "operators.h"

double dot(const std::vector<double>& a, const std::vector<double>& b) {
  double sum = 0;
  for (int i = 0; i < a.size(); ++i) {
	sum += a[i] * b[i];
  }
  return sum;
}

std::vector<double> scalar_multiple(const std::vector<double>& a, double k) {
  std::vector<double> res(a.size());
  for (int i = 0; i < a.size(); ++i) {
	res[i] = a[i] * k;
  }
  return res;
}

std::vector<double> add(const std::vector<double>& a, const std::vector<double>& b) {
  std::vector<double> res(a.size());
  for (int i = 0; i < a.size(); ++i) {
	res[i] = a[i] + b[i];
  }
  return res;
}

std::vector<double> sub(const std::vector<double>& a, const std::vector<double>& b) {
  std::vector<double> res(a.size());
  for (int i = 0; i < a.size(); ++i) {
	res[i] = a[i] - b[i];
  }
  return res;
}

double norm(const std::vector<double>& a) {
  return std::sqrt(dot(a, a));
}

std::vector<double> operator+(const std::vector<double>& a, const std::vector<double>& b) {
  return add(a, b);
}

std::vector<double> operator-(const std::vector<double>& a, const std::vector<double>& b) {
  return sub(a, b);
}

std::vector<double> operator*(const std::vector<double>& a, double k) {
  return scalar_multiple(a, k);
}

std::vector<double> operator*(double k, const std::vector<double>& a) {
  return scalar_multiple(a, k);
}