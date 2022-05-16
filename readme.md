# principle-of-compiling-experiment-Njtech
## 说明
### 文件组织
>├── in.txt\
>├── LexicalAnalysis.cpp\
>├── LexicalFunction.cpp\
>├── main.cpp\
>├── MyComplier.h\
>├── out.txt\
>├── readme.md\
>├── Utils.cpp\
>├── VariablesDefination.cpp

- 说明
  - 头文件 MyComplier.h 存放函数声明 全局变量声明等预定义。
  - Utils.cpp、LexicalAnalysis.cpp、LexicalFunction.cpp 是函数的实现
  - VariablesDefination.cpp 是全局变量的声明。

### 出错管理
#### 词法出错：
词法出错主要放置在 Scanner函数中 如果Scanner识别出一个unknown类型的二元式那么久判断为词法分析出错。iHaveError变量就置为1
#### 语法出错：
语法出错主要由Match函数控制 如果Match函数匹配到一个不应该出现的词就会报错iHaveError = 2;
#### 语义出错：
在函数中某一个过程中去定义

#### 支持的出错类型：
- 变量声明【声明int的出错处理】
- known类型的单词 
- 标识符列表部分出现重复定义：
- 标识符列表部分缺少","
- 语法分析中缺少各类的关键字   【待验证】
- 表达式中因子项的缺失；
- 标识符未初始化
- 语句中出现不明标识符


#### 出错处理：
- 对于unknown类型单词处理。
  - 当unknown单词作为一个整体在标识符列表中出现的时候 （作为一个错误格式的标识符）
    > int$qbe,kkhbu,$shni;    警告+忽略
    > 这个可以看做是个词法错误
  - 当unknown作为一个前缀出现。
    > int$qbe,kkhbu$shni;   报错处理
  - 当unknown类型作为前缀&后缀出现在关键词中
    > kkhuifkkhbu            报错处理
- 缺少关键字(报错处理)
- 缺少分隔符
- 出现不认识的标识符
- 未初始化的标识符定义。