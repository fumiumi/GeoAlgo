#ifndef OPERATORS_H
#define OPERATORS_H

#include <vector>
#include <cmath>

// ベクトルの内積
double dot(const std::vector<double>& a, const std::vector<double>& b);

// ベクトルのスカラー倍
std::vector<double> scalar_multiple(const std::vector<double>& a, double k);

// ベクトルの和
std::vector<double> add(const std::vector<double>& a, const std::vector<double>& b);

// ベクトルの差
std::vector<double> sub(const std::vector<double>& a, const std::vector<double>& b);

// ベクトルのノルム
double norm(const std::vector<double>& a);

// 演算子オーバーロード
std::vector<double> operator+(const std::vector<double>& a, const std::vector<double>& b);
std::vector<double> operator-(const std::vector<double>& a, const std::vector<double>& b);
std::vector<double> operator*(const std::vector<double>& a, double k);
std::vector<double> operator*(double k, const std::vector<double>& a);

#endif // OPERATORS_H