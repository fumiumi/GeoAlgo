#include "Polygon3D.h"
#include <stdexcept>

// コンストラクタ
Polygon3D::Polygon3D(const std::vector<GLfloat>& vertices, const std::vector<GLfloat>& colors)
    : vertices_(vertices), colors_(colors), vertexBufferObject(0), colorBufferObject(0) {
    //ポリゴンは3頂点で構成される
    if (vertices.size() % 3 != 0 || colors.size() % 3 != 0) {
        throw std::invalid_argument("Invalid vertex or color data size");
    }
    initializeBuffers();
}

// メモリを事前に確保するコンストラクタ
Polygon3D::Polygon3D(size_t vertexCount, size_t colorCount)
    : vertices_(vertexCount), colors_(colorCount), vertexBufferObject(0), colorBufferObject(0) {
    vertices_.reserve(vertexCount);
    colors_.reserve(colorCount);
    initializeBuffers();
}

// ムーブコンストラクタ => リソースの一意性を保つために、他のオブジェクトのリソースを移動する
Polygon3D::Polygon3D(Polygon3D&& other) noexcept
    : vertices_(std::move(other.vertices_)), colors_(std::move(other.colors_)),
      vertexBufferObject(other.vertexBufferObject), colorBufferObject(other.colorBufferObject) {
    other.vertexBufferObject = 0;
    other.colorBufferObject = 0;
}

// ムーブ代入演算子
Polygon3D& Polygon3D::operator=(Polygon3D&& other) noexcept {
    if (this != &other) {
        cleanupBuffers();

        vertices_ = std::move(other.vertices_);
        colors_ = std::move(other.colors_);

        vertexBufferObject = other.vertexBufferObject;
        colorBufferObject = other.colorBufferObject;

        other.vertexBufferObject = 0;
        other.colorBufferObject = 0;
    }
    //ムーブ代入演算なので、いずれにせよ自分自身を返す
    return *this;
}

Polygon3D::~Polygon3D() {
    cleanupBuffers();
    //...
}

// アクセサメソッド
const std::vector<GLfloat>& Polygon3D::getVertices() const noexcept {
    return vertices_;
}
const std::vector<GLfloat>& Polygon3D::getColors() const noexcept {
    return colors_;
}

// ミューテータメソッド
// こっちは例外危険性があるので、noexceptをつけない
void Polygon3D::setVertices(const std::vector<GLfloat>& vertices) {
    if (vertices.size() % 3 == 0) {
        vertices_ = vertices;
        initializeBuffers(); // バッファを再初期化
    }
}
void Polygon3D::setColors(const std::vector<GLfloat>& colors) {
    if (colors.size() % 3 == 0) {
        colors_ = colors;
        initializeBuffers(); // バッファを再初期化
    }
}

// バッファ初期化メソッド
void Polygon3D::initializeBuffers() {
    if (vertexBufferObject == 0) {
        glGenBuffers(1, &vertexBufferObject);
    }
    if (colorBufferObject == 0) {
        glGenBuffers(1, &colorBufferObject);
    }

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(GLfloat), vertices_.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferObject);
    glBufferData(GL_ARRAY_BUFFER, colors_.size() * sizeof(GLfloat), colors_.data(), GL_STATIC_DRAW);
}

// バッファクリーンアップメソッド
void Polygon3D::cleanupBuffers() {
    if (vertexBufferObject != 0) {
        glDeleteBuffers(1, &vertexBufferObject);
        vertexBufferObject = 0;
    }
    if (colorBufferObject != 0) {
        glDeleteBuffers(1, &colorBufferObject);
        colorBufferObject = 0;
    }
}

// 描画メソッド
void Polygon3D::draw() const {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferObject);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, nullptr);

    glDrawArrays(GL_TRIANGLES, 0, vertices_.size() / 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Cube::draw() const {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferObject);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, nullptr);

    glDrawArrays(GL_TRIANGLES, 0, vertices_.size() / 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}