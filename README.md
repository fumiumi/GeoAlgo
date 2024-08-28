# GeoAlgo
3DCGで使用する線形代数のアルゴリズムをテスト実装するためのリポジトリ

## 命名規則

chatgptの命名規則を参考にしています。

### 1. **変数名**
   - **ローワーキャメルケース**（lowerCamelCase）: 最初の単語は小文字で始め、続く単語の先頭は大文字にする。
     - 例: `totalCount`, `index`, `userName`
   - **アンダースコア区切り**（snake_case）を使うこともありますが、C++ではlowerCamelCaseが一般的です。
     - 例: `total_count`, `user_name`

### 2. **クラス名**
   - **アッパーキャメルケース**（UpperCamelCase, パスカルケース）: 各単語の先頭を大文字にする。
     - 例: `UserAccount`, `CustomerData`, `FileReader`

### 3. **関数名**
   - **ローワーキャメルケース**（lowerCamelCase）: 最初の単語は小文字で始め、続く単語の先頭は大文字にする。
     - 例: `calculateTotal()`, `getUserName()`, `setAge()`
   - メンバ関数と非メンバ関数で異なる場合がありますが、基本的に同じスタイルを使用します。

### 4. **メンバ変数**
   - **アンダースコアで始める**: プライベートメンバ変数の場合、区別するために前にアンダースコアを付けることがあります。
     - 例: `_age`, `_totalCount`, `_userName`
   - **m_プレフィックスを使用する**: これはクラスメンバ変数を示すためのもう一つのスタイルです。
     - 例: `m_age`, `m_totalCount`, `m_userName`

### 5. **定数**
   - **全て大文字でアンダースコア区切り**（SNAKE_CASE）: 定数は通常全て大文字を使用し、単語間をアンダースコアで区切る。
     - 例: `MAX_BUFFER_SIZE`, `PI`, `DEFAULT_TIMEOUT`
   - **クラススコープの定数**: クラス内の定数は、通常の変数のスタイルを維持することもあります。
     - 例: `const int MaxItems = 100;`

### 6. **名前空間**
   - **小文字で単語間をアンダースコアで区切る**（snake_case）または**アッパーキャメルケース**（UpperCamelCase）を使用する。
     - 例: `namespace my_project {}`, `namespace AudioProcessing {}`

### 7. **列挙型（Enum）**
   - C++11以降のスコープ付き列挙型（`enum class`）では、アッパーキャメルケースを使用することが一般的です。
     - 例: 
       ```cpp
       enum class Color {
           Red,
           Green,
           Blue
       };
       ```
   - スコープなしの列挙型（古いスタイルの`enum`）では、全て大文字を使用することもあります。
     - 例: 
       ```cpp
       enum Direction {
           NORTH,
           EAST,
           SOUTH,
           WEST
       };
       ```

### 8. **ファイル名**
   - **スネークケース**（snake_case）で、ファイルの内容を反映する名前を付ける。
     - 例: `user_account.cpp`, `file_reader.hpp`, `main_window.cpp`

### 9. **マクロ**
   - **全て大文字でアンダースコア区切り**（SNAKE_CASE）: マクロ名は通常全て大文字で記述し、単語間をアンダースコアで区切ります。
     - 例: `#define MAX_BUFFER_SIZE 1024`, `#define PI 3.14159`
