#ifndef QUATERNION_H
#define QUATERNION_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

// 四元数クラス
class Quaternion {
public:
    float w, x, y, z;

    Quaternion();

    Quaternion(float angle, const glm::vec3& axis);

    //成分を指定して初期化
    Quaternion(float w, float x, float y, float z);

    // 正規化
    void normalize();

    // 四元数の乗算（回転の合成）
    Quaternion operator*(const Quaternion& q) const;

    //スカラー倍
    Quaternion operator*(float k) const;

    // 四元数の加算
    Quaternion operator+(const Quaternion& q) const;

    // 四元数の減算
    Quaternion operator-(const Quaternion& q) const;

    // 回転行列に変換
    glm::mat4 toMatrix() const;

    //線型補間
    static Quaternion lerp(const Quaternion& q1, const Quaternion& q2, float t);

  };

//四元数の共役
inline Quaternion conjugate(const Quaternion& q);

// 四元数の逆元
inline Quaternion inverse(const Quaternion& q);

#endif // QUATERNION_H