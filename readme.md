# principle-of-compiling-experiment-Njtech
## 说明
### 文件组织
>├── in.txt   // 存放源代码的文件\
>├── LexicalAnalysis.cpp\
>├── LexicalFunction.cpp\
>├── main.cpp\
>├── MyComplier.h\
>├── out.txt  // 存放输出的四元式 \
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
- 语法分析中缺少各类的关键字   
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


### 编译器适应的架空语言文法：
> <程序> →<变量说明部分>;<语句部分>\
> <变量说明部分> → <变量说明><标识符列表>\
> <变量说明> → int\
> <标识符列表> → <标识符列表>,<标识符>|<标识符>\
> <标识符> → $<字母>|<标识符><字母>|<标识符><数字>\
> <语句部分> → <语句部分><语句>;|<语句>;\
> <语句> → <赋值语句>|<条件语句>|<循环语句>\
> <赋值语句> → <标识符>=<表达式>\
> <条件语句> → if （<条件>） then <嵌套语句>; else <嵌套语句>\
> <循环语句> → while （<条件>） do <嵌套语句>\
> <表达式> → <项>|<表达式><加法运算符><项>\
> <项> → <因子>|<项><乘法运算符><因子>\
> <因子> → <标识符>|<常量>|(<表达式>)\
> <常量> → <无符号整数>\
> <无符号整数> → <数字序列>\
> <数字序列> → <数字序列><数字>|<数字>\
> <加法运算符> → +\
> <乘法运算符> → *\
> <关系运算符> → <|>|!= |>=|<= |== \
> <条件> → <表达式><关系运算符><表达式>\
> <复合语句> → begin <语句部分> end\
> <嵌套语句> → <语句>|<复合语句>\
> <字母> → a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z\
> <数字> → 0|1|2|3|4|5|6|7|8|9

#### log
- [x] 错误处理
  - [x] 错误处理提示美化【带颜色提示】
  - [x] 更多的错误处理
  - [ ] 对于缺少某些语句的起始符号的处理
  - [ ] more 
- [x] 四元式命令行输出
- [x] 输出到文件
- [ ] 美化源文件中的代码
- [ ] 可视化界面