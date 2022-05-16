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
- 定义部分的重复定义：
  - 