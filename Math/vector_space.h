#ifndef VECTOR_SPACE_H
#define VECTOR_SPACE_H

#include <vector>
#include <cmath>

//まずベクトルを宣言
class Vector3 {
public:
  float x, y, z;

  // コンストラクタ
  Vector3();
  Vector3(float x, float y, float z);
  //ムーブコンストラクタ
  Vector3(Vector3&& other) noexcept;
  //ムーブ代入演算子
  Vector3& operator=(Vector3&& other) noexcept;


  // ベクトルの基本演算
  Vector3 operator+(const Vector3& other) const;
  Vector3 operator-(const Vector3& other) const;
  Vector3 operator*(float scalar) const;

  // ベクトルの内積
  float dot(const Vector3& other) const;

  // ベクトルの外積
  Vector3 cross(const Vector3& other) const;

  // ベクトルのノルム
  float norm() const;

  // ベクトルの正規化
  Vector3 normalize() const;
};

class Vector4 {
public:
  float x, y, z, w;

  // コンストラクタ
  Vector4();
  Vector4(float x, float y, float z, float w);
  //ムーブコンストラクタ
  Vector4(Vector4&& other) noexcept;
  //ムーブ代入演算子
  Vector4& operator=(Vector4&& other) noexcept;

  // ベクトルの基本演算
  Vector4 operator+(const Vector4& other) const;
  Vector4 operator-(const Vector4& other) const;
  Vector4 operator*(float scalar) const;

  // ベクトルの内積
  float dot(const Vector4& other) const;

  // ベクトルのノルム
  float norm() const;

  // ベクトルの正規化
  Vector4 normalize() const;
};

//次に行列を定義
class Matrix {
public:
  // デストラクタを仮想関数にして、継承クラスでのオーバーライドを可能にする
  virtual ~Matrix() = default;

  // 行列の転置
  virtual Matrix transpose() const;

  // 行列とベクトルの積
  virtual Vector3 multiply(const Vector3& vector) const = 0;
  virtual Vector4 multiply(const Vector4& vector) const = 0;
};

class Matrix3 : public Matrix {
public:
  float m[3][3];

  // コンストラクタ
  Matrix3();
  Matrix3(float m00, float m01, float m02,
      float m10, float m11, float m12,
      float m20, float m21, float m22);

  // 行列の基本演算
  Matrix3 operator+(const Matrix3& other) const;
  Matrix3 operator-(const Matrix3& other) const;
  Matrix3 operator*(const Matrix3& other) const;
  Matrix3 operator*(float scalar) const;

  // 行列の転置
  Matrix3* transpose() const override;

  // 行列とベクトルの積
  Vector3 multiply(const Vector3& vector) const override;
  Vector4 multiply(const Vector4& vector) const override;
};

class Matrix4 : public Matrix {
public:
  float m[4][4];

  // コンストラクタ
  Matrix4();
  Matrix4(float m00, float m01, float m02, float m03,
      float m10, float m11, float m12, float m13,
      float m20, float m21, float m22, float m23,
      float m30, float m31, float m32, float m33);

  // 行列の基本演算
  Matrix4 operator+(const Matrix4& other) const;
  Matrix4 operator-(const Matrix4& other) const;
  Matrix4 operator*(const Matrix4& other) const;
  Matrix4 operator*(float scalar) const;

  // 行列の転置
  Matrix4* transpose() const override;

  // 行列とベクトルの積
  Vector3 multiply(const Vector3& vector) const override;
  Vector4 multiply(const Vector4& vector) const override;
};

#endif // VECTOR_SPACE_H