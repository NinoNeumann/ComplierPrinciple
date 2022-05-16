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


    // 词法分析程序的main函数部分
    //while (iCur != iFileLength) {
    //    try {
    //        Scanner();
    //    }
    //    catch(const char *s){
    //        cout << s << endl;
    //        cout<< "line: " << wdNextWord.iLine << " have an error!!" << " error message: " << wdNextWord.strValue << " at the " << iCur << "th letter" << endl;
    //        bHaveError = false;
    //    }
    //    
    //    // 这里是词法分析中如果出现错误的报错处理
    //    /*if (bHaveError) {
    //        cout <<"line: "<< wdNextWord.iLine << " have an error!!"<<" error message: "<< wdNextWord.strValue<<" at the "<<iCur<<"th letter"<<endl;
    //    }
    //    bHaveError = false;*/
    //    
    //    // 输出词法分析过程中出现的二元式
    //    cout <<"(" << mpNum2Name[wdNextWord.iType] << "," << wdNextWord.strValue << ")" << endl;
    //}
    // 
    

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
    while (!stckError.empty()) {
        cout << stckError.top() << endl;
        stckError.pop();
    }
    cout << endl;

    // 输出四元式
    
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
