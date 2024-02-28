# DataConvCpp

データ構造のシリアライズとデシリアライズ機能をヘッダオンリーライブラリで提供します．
使いやすさ重視で速度はあまり重視していません．
英語のREADMEは[こちら](README.md)．

## クイックスタート

```c++
#include <DataConv/Core>

using namespace dataconv;

// オリジナルのデータ構造の定義
struct MyData : DATACONV_WITH_MULTI_CONVERTER {
    int a;
    short b;
    float b;

    MyData() : a(0), b(0), c(0) {}
    MyData(int a, short b, float c) : a(a), b(b), c(c) {}

    DATACONV_DEFINE_REQUIRED_MULTI_CONVERTER(MyData, a, b, c);
};

int main() {
    auto bin_data = std::vector<std::uint8_t>{};
    auto cpp_data MyData{1, 2, 3.0f};

    // バイナリデータにシリアライズ
    cpp_data >> bin_data;

    // バイナリデータからデシリアライズ
    cpp_data << bin_data;
}
```

## 使い方

### 1. 文字列への変換

本ライブラリはユーザー定義型の文字列変換を簡略化する為の機能を持っています．  
現状では一方通行で文字列からデータ構造への変換はできません．

機能を使う為にはコード生成マクロ`DATACONV_WITH_STRING_CONVERTER`と`DATACONV_DEFINE_REQUIRED_STRING_CONVERTER`を使用します．

例として`int`型メンバ変数`a`，`b`，`c`を持つような以下のようなデータ構造を考えます．

```c++
struct Data {
    int a;
    int b;
    int c;
};
```

上記のデータ構造`Data`に文字列変換機能を追加するには以下の様にコードを追加します．

```c++
struct Data : DATACONV_WITH_STRING_CONVERTER {
    int a;
    int b;
    int c;

    DATACONV_DEFINE_REQUIRED_STRING_CONVERTER(Data, a, b, c);
};
```

簡単にそれぞれのマクロを説明すると．

* `DATACONV_WITH_STRING_CONVERTER`  
変換に関わるインターフェースの機能を継承します．

* `DATACONV_DEFINE_REQUIRED_STRING_CONVERTER(Data, a, b, c)`  
型`Data`に対して`a`，`b`，`c`の順でメンバ変数を文字列に変換するコードを自動生成します．

のような機能を提供します．  
変換可能な型は組込み型と列挙型，そして同様の機能を持つユーザー定義型です．また，上記の型のシーケンスコンテナも変換可能です．

文字列への変換は`toString`メンバ関数を使用します．  
デフォルトではデリミタはスペースですが，変更することもできます．

```c++
Data data{1, 2, 3};
std::cout << data.toString(); << std::endl;   // 1 2 3
std::cout << data.toString(",") << std::endl; // 1,2,3
```

出力ストリームの場合は`<<`演算子を使用してそのまま渡すことができます．

```c++
std::cout << data << std::endl; // 1 2 3
```

テキストデータに変換する際には`toString`でデリミタを指定しても良いですが，代表的なテキストデータ形式 (例えばCSV) に変換する場合は専用のメンバ関数を使用することをお勧めします．

```c++
std::cout << data.toCsv() << std::endl; // 1,2,3
std::cout << data.toSsv() << std::endl; // 1 2 3
std::cout << data.toTsv() << std::endl; // 1        2        3
```

各型式のヘッダ行を生成することもできます．

```c++
std::cout << data.makeCsvHeader() << std::endl; // a,b,c
std::cout << data.makeSsvHeader() << std::endl; // a b c
std::cout << data.makeTsvHeader() << std::endl; // a        b        c
```

### 2. バイナリデータの相互変換

本ライブラリではバイナリデータとデータ構造の相互変換機能を持たせています．  
用途が限られますが，エンディアンが異なるシステム間でデータをやり取りする際や，環境に依存しないバイナリデータを作成する際や操作する際に便利かもしれません．

同様にユーザー定義型`Data`に対してバイナリデータ変換機能を追加するには以下の様にコードを追加します．

```c++
struct Data : DATACONV_WITH_BINARY_CONVERTER {
    int a;
    int b;
    int c;

    DATACONV_DEFINE_REQUIRED_BINARY_CONVERTER(Data, a, b, c);
};
```

簡単にそれぞれのマクロを説明すると．

* `DATACONV_WITH_BINARY_CONVERTER`  
相互変換に関わるインターフェースの機能を継承します．

* `DATACONV_DEFINE_REQUIRED_BINARY_CONVERTER(Data, a, b, c)`  
型`Data`に対して`a`，`b`，`c`の順でメンバ変数とバイナリデータを相互変換するコードを自動生成します．

のような機能を提供します．  
変換可能な型は組込み型と列挙型，そして同様の機能を持つユーザー定義型です．  
また，上記の型のシーケンスコンテナも変換可能です．

基本的にバイナリデータはビッグエンディアンで取り扱われ，  
デシリアライズする際にシステムのエンディアンに合わせて自動で変換されます．

バイナリデータへシリアライズする際には`toBinary`メンバ関数を使用します．  
尚，バイナリデータは`std::vector<std::uint8_t>`型で取り扱われます．

```c++
auto bin_data = std::vector<std::uint8_t>{};
data.toBinary(bin_data); // bin_data = {0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03}
```

バイナリデータからデシリアライズする際には`fromBinary`メンバ関数を使用します．  

```c++
data.fromBinary(bin_data); // data = {1, 2, 3}
```

尚，シフト演算子`<<`，`>>`を使用して省略して記述することもできます．  

```c++
data >> bin_data; // シリアライズ
data << bin_data; // デシリアライズ
```

バイナリ変換後のバイトサイズは`size`メンバ関数で取得できます．  

```c++
std::cout << data.size() << std::endl; // 12
```

### 3. JSON文字列の相互変換

本ライブラリではJSON文字列とデータ構造の相互変換機能を持たせています．(Nlohmann JSONを経由しています)

同様にユーザー定義型`Data`に対してJSON文字列変換機能を追加するには以下の様にコードを追加します．

```c++
struct Data : DATACONV_WITH_JSON_CONVERTER {
    int a;
    int b;
    int c;

    DATACONV_DEFINE_REQUIRED_JSON_CONVERTER(Data, a, b, c);
};
```

簡単にそれぞれのマクロを説明すると．

* `DATACONV_WITH_JSON_CONVERTER`  
相互変換に関わるインターフェースの機能を継承します．

* `DATACONV_DEFINE_REQUIRED_JSON_CONVERTER(Data, a, b, c)`  
型`Data`に対して`a`，`b`，`c`の順でメンバ変数とJSON文字列を相互変換するコードを自動生成します．

のような機能を提供します．

JSON文字列へのシリアライズは`toJsonString`メンバ関数を使用します．

```c++
std::cout << data.toJsonString() << std::endl; // {"a":1,"b":2,"c":3}
```

JSON文字列からデシリアライズする際には`fromJsonString`メンバ関数を使用します．

```c++
data.fromJsonString("{\"a\":1,\"b\":2,\"c\":3}"); // data = {1, 2, 3}
```

### 4. マルチ変換機能

本ライブラリでは複数の変換機能を同時に持たせることができます．

同様にユーザー定義型`Data`に使用できる全ての変換機能を追加するには以下の様にコードを追加します．

```c++
struct Data : DATACONV_WITH_MULTI_CONVERTER {
    int a;
    int b;
    int c;

    DATACONV_DEFINE_REQUIRED_MULTI_CONVERTER(Data, a, b, c);
};
```

この様にすることで，`Data`型は文字列変換，バイナリ変換，JSON変換の全ての機能を持つことができます．

### 5. ユーザー定義型を持つデータ構造の変換

本ライブラリではユーザー定義型をメンバ変数として持つデータ構造に対しても変換機能を追加することができます．

例として`BaseData1`型と`BaseData2`型のメンバ変数を持つデータ構造`Data`に対して機能を追加するには以下の様にします．

```c++
struct BaseData1 : DATACONV_WITH_MULTI_CONVERTER {
    int a;

    DATACONV_DEFINE_REQUIRED_MULTI_CONVERTER(BaseData1, a);
};

struct BaseData2 : DATACONV_WITH_MULTI_CONVERTER {
    int b;

    DATACONV_DEFINE_REQUIRED_MULTI_CONVERTER(BaseData2, d);
};

struct Data : DATACONV_WITH_MULTI_CONVERTER {
    BaseData1 data1;
    BaseData2 data2;

    DATACONV_DEFINE_REQUIRED_MULTI_CONVERTER(Data, data1, data2);
};
```

基本的には使用している型が対応する変換機能を持っていれば，その型をメンバ変数として持つデータ構造にも同様の機能を追加することができます．

### 6. 変換機能のカスタマイズ

TODO

## SpecialThanks

本ライブラリは[Nlohmann JSON](https://github.com/nlohmann/json)を使用しています．
