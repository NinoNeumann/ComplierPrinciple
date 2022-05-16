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
    InitMap();
    char ch;
    freopen("in.txt", "r", stdin);

    iFileLength = 0;
    // 将程序txt读入到letter buffer中
    while (~scanf("%c", &ch)) {
        str_arrLetters[iFileLength++] = ch;
        //if (ch == ',')str_arrLetters[iFileLength++] = " ";
        //else if(ch==';')str_arrLetters[iFileLength++] = "\n";
    }
    //// 文件写出
    //FILE* stream;
    //if ((stream = freopen("file.txt", "w", stdout)) == NULL)
    //    exit(-1);
    //for (int i = 0; i < iFileLength; ++i)printf("%c", str_arrLetters[i].c_str());

    //fflush(stream);
    //stream = freopen("CON", "w", stdout); //stdout 是向程序的末尾的控制台重定向
    //printf("And now back to the console once again\n");
    //// 将输出缓冲区清空
    freopen("CON", "r", stdin);    // 关闭 将cout的权限重新放回console上

   /* ofstream fout("out.txt");
    for (int i = 0; i < iFileLength; ++i) {
        fout<<str_arrLetters[i].c_str();
    }
    fout.close();*/
    
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
    try {
        ParseProgram();
    }
    catch (const char* s) {
        cout << s << endl;
        cout << "line: " << wdNextWord.iLine << " have an error!!" << " error message: " << wdNextWord.strValue << " at the " << iCur << "th letter" << endl;
    }
    



    // 输出 标识符table
    cout << "identifier table:";
    map<string, ll>::iterator it;
    for (it = mpIdentifierTable.begin(); it != mpIdentifierTable.end(); it++) {
        string s = it->first;
        printf("%s %d\n", s.data(), it->second);
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

    // 输出四元式
    for (int i = 0; i < qua.size(); ++i) {
        cout <<"idx:"<<i<<"  "<< qua[i].op << " " << qua[i].arg1 << " " << qua[i].arg2 << " " << qua[i].res << endl;
    }
   
    system("pause");
    return 0;
}
