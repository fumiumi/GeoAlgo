//グラムシュミットの正規直交化

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <functional>
#include "operators.h"

using namespace std;

//ベクトルの順番に依存しないようにする

// Define the missing functions
void sub_inplace(vector<double>& a, const vector<double>& b) {
  transform(a.begin(), a.end(), b.begin(), a.begin(), minus<double>());
}

vector<double> scalar_multiple(const vector<double>& a, double scalar) {
  vector<double> result(a.size());
  transform(a.begin(), a.end(), result.begin(), bind(multiplies<double>(), placeholders::_1, scalar));
  return result;
}

void scalar_multiple_inplace(vector<double>& a, double scalar) {
  transform(a.begin(), a.end(), a.begin(), bind(multiplies<double>(), placeholders::_1, scalar));
}

void gram_schmidt_normalization(vector<vector<double>>& a) {
  // a: n次元ベクトルの集合
  int n = a.size();

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      double dot_product = dot(a[i], a[j]);
      double norm_squared = dot(a[j], a[j]);
      double scalar = dot_product / norm_squared;
      sub_inplace(a[i], scalar_multiple(a[j], scalar));
    }
  }
  for (int i = 0; i < n; ++i) {
    double norm_val = norm(a[i]);
    scalar_multiple_inplace(a[i], 1 / norm_val);
  }
}