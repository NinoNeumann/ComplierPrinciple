#define _CRT_SECURE_NO_WARNINGS
#include "MyComplier.h"



/*
命名规范：
    严格按照 匈牙利表示法 其中前缀的表示规则如下：
    mp-  :  mp      前缀 表示 map<>类型 其中的具体的映射关系主要从命名逻辑上表示  例如mpName2Num  表示Name 到 Num的map 那就是string 到 int 的一个映射关系（关于这样的hash表的内部映射字段的类型声明我省略了）
    uset-:  uset    前缀 表示 unordered_set<>类型
    str- :  str     前缀 表示 string类型
    i-   :  i       前缀 表示 int类型
    wd-  :  wd      前缀 表示 word（自定义的结构体）类型  详细见下面的函数定义
    -arr-:  arr     前缀 表示 数组类型 可以在前面添加其他的类型组合成不同类型的数组  例如 str_arr ：string类型的数组。
    b-   :  b       前缀 表示 bool类型
*/



int sj;
string cpy_f;


int main() {
    // 读入程序
    //setfill(' ');
    InitMap();
    char ch;

    ifstream i_file("in.txt");
    streambuf* in_file = cin.rdbuf();
    cin.rdbuf(i_file.rdbuf());

    iFileLength = 0;
    // 将程序txt读入到letter buffer中
    while (cin>>ch && ch!=EOF) {
        str_arrLetters[iFileLength++] = ch;
        
    }
    cin.rdbuf(in_file);
    
    //
    cout << "File_length: " << iFileLength << endl;
    iCur = 0;
    iCurLine = 1;


    //int sj = 0;
    ////// 词法分析程序的main函数部分
    //while (iCur != iFileLength) {
    //    
    //     Scanner();
    //     string str = wdNextWord.strValue;
    //     if (str == "then" || str == "do" || str == "begin") {
    //         sj.push(str);
    //         cpy_f = cpy_f.substr(0, cpy_f.length() - 1);
    //         cpy_f = cpy_f + str + "\n";
    //         for (int i = 0; i < sj.size(); ++i) {
    //             cpy_f = cpy_f + "\t";
    //         }
    //     }
    //     else if (str == "end" || str == "else") {
    //         sj.pop();
    //         cpy_f = cpy_f.substr(0,cpy_f.length()-1);
    //         cpy_f = cpy_f + str + "\n";
    //         for (int i = 0; i < sj.size(); ++i) {
    //             cpy_f = cpy_f + "\t";
    //         }

    //     }
    //     else if (str == ";" && (!sj.empty()  &&  sj.top() == "do" )) {
    //         sj.pop();
    //         cpy_f = cpy_f + str + "\n";
    //         for (int i = 0; i < sj.size(); ++i) {
    //             cpy_f = cpy_f + "\t";
    //         }
    //     }
    //     else if (str == ";") {
    //         cpy_f = cpy_f + str + "\n";
    //         for (int i = 0; i < sj.size(); ++i) {
    //             cpy_f = cpy_f + "\t";
    //         }
    //     }
    //     //Anstyle(str, sj.size());
    //     cpy_f = cpy_f + str;
    // 
    //}

    //iCur = 0;
    //// 

    //cout << cpy_f << endl;
    

    // 语法分析程序部分的main函数
    Scanner();
    ParseProgram();



    cout << endl;
    // 输出 标识符table
    cout << "identifier table:";
    map<string, ll>::iterator it;
    for (it = mpIdentifierTable.begin(); it != mpIdentifierTable.end(); it++) {
        string s = it->first;
        printf("(int, %s, %d)", s.data(), it->second);
    }
    cout << ";\n";
    // 输出常量table
    cout << "constant table: ";
    for (auto x:usetConstantsTable) {
        cout << x<<" ";
    }
    cout << ";\n";
    // 报错处理
    if(!stckError.empty())
        cout << "===============================Error Messages==============================" << endl<<endl;
    while (!stckError.empty()) {
        if (stckError.top().find("warning") != stckError.top().npos) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        }
        cout << stckError.top() << endl;
        stckError.pop();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    }
    cout << endl<<endl;

    // 输出四元式
    cout << "=======================================quaternaries====================================" << endl<< endl;
    for (int i = 0; i < qua.size(); ++i) {
        cout <<"("<< setw(2) << setiosflags(ios::left) << i<<")  ("
            <<setw(3)<<setiosflags(ios::left)<< qua[i].op << ", " 
            <<setw(5) << setiosflags(ios::left) << qua[i].arg1 << ", " 
            << setw(5) << setiosflags(ios::left) << qua[i].arg2 << ", " 
            << setw(5) << setiosflags(ios::left) << qua[i].res <<")" << endl;
    }

    // 将四元式输出到文件
    ofstream outf("out.txt");
    streambuf* strmBuf = cout.rdbuf();
    cout.rdbuf(outf.rdbuf());
    for (int i = 0; i < qua.size(); ++i) {
        cout << "(" << setw(2) << setiosflags(ios::left) << i << ")  ("
            << setw(3) << setiosflags(ios::left) << qua[i].op << ", "
            << setw(5) << setiosflags(ios::left) << qua[i].arg1 << ", "
            << setw(5) << setiosflags(ios::left) << qua[i].arg2 << ", "
            << setw(5) << setiosflags(ios::left) << qua[i].res << ")" << endl;
    }
    cout.rdbuf(strmBuf);
    system("pause");
    return 0;
}
