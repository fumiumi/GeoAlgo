#include "vector_space.h"
#include <stdexcept>
#include <cmath>

// Vector3の実装
Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3::Vector3(Vector3&& other) noexcept : x(other.x), y(other.y), z(other.z) {
    other.x = 0.0f;
    other.y = 0.0f;
    other.z = 0.0f;
}

Vector3& Vector3::operator=(Vector3&& other) noexcept {
    if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        other.x = 0.0f;
        other.y = 0.0f;
        other.z = 0.0f;
    }
    return *this;
}

Vector3 Vector3::operator+(const Vector3& other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(float scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
}

float Vector3::dot(const Vector3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::cross(const Vector3& other) const {
    return Vector3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

float Vector3::norm() const {
    return std::sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::normalize() const {
    float length = norm();
    if (length > 1e-6) {
        return *this * (1.0f / length);
    }
    return *this;
}

// Vector4の実装
Vector4::Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Vector4::Vector4(Vector4&& other) noexcept : x(other.x), y(other.y), z(other.z), w(other.w) {
    other.x = 0.0f;
    other.y = 0.0f;
    other.z = 0.0f;
    other.w = 0.0f;
}

Vector4& Vector4::operator=(Vector4&& other) noexcept {
    if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        other.x = 0.0f;
        other.y = 0.0f;
        other.z = 0.0f;
        other.w = 0.0f;
    }
    return *this;
}

Vector4 Vector4::operator+(const Vector4& other) const {
    return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4 Vector4::operator-(const Vector4& other) const {
    return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4 Vector4::operator*(float scalar) const {
    return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

float Vector4::dot(const Vector4& other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

float Vector4::norm() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

Vector4 Vector4::normalize() const {
    float length = norm();
    if (length > 1e-6) {
        return *this * (1.0f / length);
    }
    return *this;
}

// Matrix3の実装

Matrix3::Matrix3() {
    // 単位行列として初期化
    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
}

Matrix3::Matrix3(float m00, float m01, float m02,
                 float m10, float m11, float m12,
                 float m20, float m21, float m22) {
    m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
    m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
    m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
}

// 行列の加算
Matrix3 Matrix3::operator+(const Matrix3& other) const {
    return Matrix3(
        m[0][0] + other.m[0][0], m[0][1] + other.m[0][1], m[0][2] + other.m[0][2],
        m[1][0] + other.m[1][0], m[1][1] + other.m[1][1], m[1][2] + other.m[1][2],
        m[2][0] + other.m[2][0], m[2][1] + other.m[2][1], m[2][2] + other.m[2][2]
    );
}

// 行列の減算
Matrix3 Matrix3::operator-(const Matrix3& other) const {
    return Matrix3(
        m[0][0] - other.m[0][0], m[0][1] - other.m[0][1], m[0][2] - other.m[0][2],
        m[1][0] - other.m[1][0], m[1][1] - other.m[1][1], m[1][2] - other.m[1][2],
        m[2][0] - other.m[2][0], m[2][1] - other.m[2][1], m[2][2] - other.m[2][2]
    );
}

// スカラー乗算
Matrix3 Matrix3::operator*(float scalar) const {
    return Matrix3(
        m[0][0] * scalar, m[0][1] * scalar, m[0][2] * scalar,
        m[1][0] * scalar, m[1][1] * scalar, m[1][2] * scalar,
        m[2][0] * scalar, m[2][1] * scalar, m[2][2] * scalar
    );
}

// 行列の乗算
Matrix3 Matrix3::operator*(const Matrix3& other) const {
    Matrix3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.m[i][j] = m[i][0] * other.m[0][j] + m[i][1] * other.m[1][j] + m[i][2] * other.m[2][j];
        }
    }
    return result;
}

// 行列の転置
Matrix3 Matrix3::transpose() const {
    return Matrix3(
        m[0][0], m[1][0], m[2][0],
        m[0][1], m[1][1], m[2][1],
        m[0][2], m[1][2], m[2][2]
    );
}

// 行列と3次元ベクトルの積
Vector3 Matrix3::multiply(const Vector3& vector) const {
    return Vector3(
        m[0][0] * vector.x + m[0][1] * vector.y + m[0][2] * vector.z,
        m[1][0] * vector.x + m[1][1] * vector.y + m[1][2] * vector.z,
        m[2][0] * vector.x + m[2][1] * vector.y + m[2][2] * vector.z
    );
}

//Matrix4の実装

Matrix4::Matrix4() {
    // 単位行列として初期化
    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

Matrix4::Matrix4(float m00, float m01, float m02, float m03,
                 float m10, float m11, float m12, float m13,
                 float m20, float m21, float m22, float m23,
                 float m30, float m31, float m32, float m33) {
    m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
    m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
    m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
    m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

// 行列の加算
Matrix4 Matrix4::operator+(const Matrix4& other) const {
    return Matrix4(
        m[0][0] + other.m[0][0], m[0][1] + other.m[0][1], m[0][2] + other.m[0][2], m[0][3] + other.m[0][3],
        m[1][0] + other.m[1][0], m[1][1] + other.m[1][1], m[1][2] + other.m[1][2], m[1][3] + other.m[1][3],
        m[2][0] + other.m[2][0], m[2][1] + other.m[2][1], m[2][2] + other.m[2][2], m[2][3] + other.m[2][3],
        m[3][0] + other.m[3][0], m[3][1] + other.m[3][1], m[3][2] + other.m[3][2], m[3][3] + other.m[3][3]
    );
}

// 行列の減算
Matrix4 Matrix4::operator-(const Matrix4& other) const {
    return Matrix4(
        m[0][0] - other.m[0][0], m[0][1] - other.m[0][1], m[0][2] - other.m[0][2], m[0][3] - other.m[0][3],
        m[1][0] - other.m[1][0], m[1][1] - other.m[1][1], m[1][2] - other.m[1][2], m[1][3] - other.m[1][3],
        m[2][0] - other.m[2][0], m[2][1] - other.m[2][1], m[2][2] - other.m[2][2], m[2][3] - other.m[2][3],
        m[3][0] - other.m[3][0], m[3][1] - other.m[3][1], m[3][2] - other.m[3][2], m[3][3] - other.m[3][3]
    );
}

// スカラー乗算
Matrix4 Matrix4::operator*(float scalar) const {
    return Matrix4(
        m[0][0] * scalar, m[0][1] * scalar, m[0][2] * scalar, m[0][3] * scalar,
        m[1][0] * scalar, m[1][1] * scalar, m[1][2] * scalar, m[1][3] * scalar,
        m[2][0] * scalar, m[2][1] * scalar, m[2][2] * scalar, m[2][3] * scalar,
        m[3][0] * scalar, m[3][1] * scalar, m[3][2] * scalar, m[3][3] * scalar
    );
}

// 行列の乗算
Matrix4 Matrix4::operator*(const Matrix4& other) const {
    Matrix4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = m[i][0] * other.m[0][j] + m[i][1] * other.m[1][j] + m[i][2] * other.m[2][j] + m[i][3] * other.m[3][j];
        }
    }
    return result;
}

// 行列の転置
Matrix4 Matrix4::transpose() const {
    return Matrix4(
        m[0][0], m[1][0], m[2][0], m[3][0],
        m[0][1], m[1][1], m[2][1], m[3][1],
        m[0][2], m[1][2], m[2][2], m[3][2],
        m[0][3], m[1][3], m[2][3], m[3][3]
    );
}

// 行列と3次元ベクトルの積（3次元ベクトルのWを1として4次元に変換）
Vector3 Matrix4::multiply(const Vector3& vector) const {
    Vector4 temp(vector.x, vector.y, vector.z, 1.0f);
    Vector4 result = multiply(temp);
    return Vector3(result.x, result.y, result.z);
}

// 行列と4次元ベクトルの積
Vector4 Matrix4::multiply(const Vector4& vector) const {
    return Vector4(
        m[0][0] * vector.x + m[0][1] * vector.y + m[0][2] * vector.z + m[0][3] * vector.w,
        m[1][0] * vector.x + m[1][1] * vector.y + m[1][2] * vector.z + m[1][3] * vector.w,
        m[2][0] * vector.x + m[2][1] * vector.y + m[2][2] * vector.z + m[2][3] * vector.w,
        m[3][0] * vector.x + m[3][1] * vector.y + m[3][2] * vector.z + m[3][3] * vector.w
    );
}


// 行列と4次元ベクトルの積（未対応、代わりに例外を投げる）
Vector4 Matrix3::multiply(const Vector4& vector) const {
    throw std::logic_error("Matrix3 cannot multiply with Vector4");
}


