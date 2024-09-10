#include "quaternion.h"
#include <cmath>

Quaternion::Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}

Quaternion::Quaternion(float angle, const glm::vec3& axis) {
    float halfAngle = angle / 2.0f;
    float sinHalfAngle = std::sin(halfAngle);
    w = std::cos(halfAngle);
    x = axis.x * sinHalfAngle;
    y = axis.y * sinHalfAngle;
    z = axis.z * sinHalfAngle;
}

Quaternion::Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

void Quaternion::normalize() {
    float length = std::sqrt(w * w + x * x + y * y + z * z);
    if (length > 1e-6) {  // 小さな閾値を設定
        w /= length;
        x /= length;
        y /= length;
        z /= length;
    }
}

// 四元数の乗算（回転の合成）
Quaternion Quaternion::operator*(const Quaternion& q) const {
    return Quaternion(
        w * q.w - x * q.x - y * q.y - z * q.z,
        w * q.x + x * q.w + y * q.z - z * q.y,
        w * q.y - x * q.z + y * q.w + z * q.x,
        w * q.z + x * q.y - y * q.x + z * q.w
    );
}

// スカラー倍
Quaternion Quaternion::operator*(float k) const {
    return Quaternion(w * k, x * k, y * k, z * k);
}

// 四元数の加算
Quaternion Quaternion::operator+(const Quaternion& q) const {
    return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
}

// 四元数の減算
Quaternion Quaternion::operator-(const Quaternion& q) const {
    return Quaternion(w - q.w, x - q.x, y - q.y, z - q.z);
}

// 回転行列に変換
glm::mat4 Quaternion::toMatrix() const {
    Quaternion q = *this;
    q.normalize();  // メソッド内で正規化

    glm::mat4 result(1.0f);
    result[0][0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
    result[0][1] = 2.0f * q.x * q.y - 2.0f * q.w * q.z;
    result[0][2] = 2.0f * q.x * q.z + 2.0f * q.w * q.y;
    result[1][0] = 2.0f * q.x * q.y + 2.0f * q.w * q.z;
    result[1][1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
    result[1][2] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
    result[2][0] = 2.0f * q.x * q.z - 2.0f * q.w * q.y;
    result[2][1] = 2.0f * q.y * q.z + 2.0f * q.w * q.x;
    result[2][2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;
    return result;
}

// 線形補間
Quaternion Quaternion::lerp(const Quaternion& q1, const Quaternion& q2, float t) {
    return q1 * (1.0f - t) + q2 * t;
}


Quaternion conjugate(const Quaternion& q) {
    return Quaternion(q.w, -q.x, -q.y, -q.z);
}

// 四元数の逆元
Quaternion inverse(const Quaternion& q) {
    float lengthSquared = q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z;
    if (lengthSquared < 1e-6) {
        return Quaternion();
    }
    return conjugate(q) * (1.0f / lengthSquared);
}
