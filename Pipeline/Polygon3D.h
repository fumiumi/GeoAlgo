#ifndef POLYGON3D_H
#define POLYGON3D_H

#include <vector>
#include <GL/glew.h>

class Polygon3D {
public:
    Polygon3D(const std::vector<GLfloat>& vertices, const std::vector<GLfloat>& colors);
    Polygon3D(size_t vertexCount, size_t colorCount); // メモリを事前に確保するコンストラクタ
    Polygon3D(Polygon3D&& other) noexcept;            // ムーブコンストラクタ

    Polygon3D& operator=(Polygon3D&& other) noexcept; // ムーブ代入演算子
    ~Polygon3D();

    // メソッド
    void draw() const;

    const std::vector<GLfloat>& getVertices() const noexcept;
    const std::vector<GLfloat>& getColors() const noexcept;
    void setVertices(const std::vector<GLfloat>& vertices);
    void setColors(const std::vector<GLfloat>& colors);
    
private:
    std::vector<GLfloat> vertices_;
    std::vector<GLfloat> colors_;
    // 頂点バッファオブジェクトのID
    GLuint vertexBufferObject;
    // 色バッファオブジェクトのID
    GLuint colorBufferObject;       

    // バッファの初期化
    void initializeBuffers(); 
    // バッファのクリーンアップ
    void cleanupBuffers();    
};

class Cube : public Polygon3D {
public:
    Cube(const std::vector<GLfloat>& vertices, const std::vector<GLfloat>& colors);
    Cube(size_t vertexCount, size_t colorCount); // メモリを事前に確保するコンストラクタ
    Cube(Cube&& other) noexcept;                 // ムーブコンストラクタ

    Cube& operator=(Cube&& other) noexcept;      // ムーブ代入演算子
    ~Cube();

    // メソッド
    void draw() const override;
};

#endif // POLYGON3D_H


