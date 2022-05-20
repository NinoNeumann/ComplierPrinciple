#define _CRT_SECURE_NO_WARNINGS
#include "MyComplier.h"



/*
�����淶��
    �ϸ��� ��������ʾ�� ����ǰ׺�ı�ʾ�������£�
    mp-  :  mp      ǰ׺ ��ʾ map<>���� ���еľ����ӳ���ϵ��Ҫ�������߼��ϱ�ʾ  ����mpName2Num  ��ʾName �� Num��map �Ǿ���string �� int ��һ��ӳ���ϵ������������hash����ڲ�ӳ���ֶε�����������ʡ���ˣ�
    uset-:  uset    ǰ׺ ��ʾ unordered_set<>����
    str- :  str     ǰ׺ ��ʾ string����
    i-   :  i       ǰ׺ ��ʾ int����
    wd-  :  wd      ǰ׺ ��ʾ word���Զ���Ľṹ�壩����  ��ϸ������ĺ�������
    -arr-:  arr     ǰ׺ ��ʾ �������� ������ǰ�����������������ϳɲ�ͬ���͵�����  ���� str_arr ��string���͵����顣
    b-   :  b       ǰ׺ ��ʾ bool����
*/



int sj;
string cpy_f;


int main() {
    // �������
    //setfill(' ');
    InitMap();
    char ch;

    ifstream i_file("in.txt");
    streambuf* in_file = cin.rdbuf();
    cin.rdbuf(i_file.rdbuf());

    iFileLength = 0;
    // ������txt���뵽letter buffer��
    while (cin>>ch && ch!=EOF) {
        str_arrLetters[iFileLength++] = ch;
        
    }
    cin.rdbuf(in_file);
    
    //
    cout << "File_length: " << iFileLength << endl;
    iCur = 0;
    iCurLine = 1;


    //int sj = 0;
    ////// �ʷ����������main��������
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
    

    // �﷨�������򲿷ֵ�main����
    Scanner();
    ParseProgram();



    cout << endl;
    // ��� ��ʶ��table
    cout << "identifier table:";
    map<string, ll>::iterator it;
    for (it = mpIdentifierTable.begin(); it != mpIdentifierTable.end(); it++) {
        string s = it->first;
        printf("(int, %s, %d)", s.data(), it->second);
    }
    cout << ";\n";
    // �������table
    cout << "constant table: ";
    for (auto x:usetConstantsTable) {
        cout << x<<" ";
    }
    cout << ";\n";
    // ������
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

    // �����Ԫʽ
    cout << "=======================================quaternaries====================================" << endl<< endl;
    for (int i = 0; i < qua.size(); ++i) {
        cout <<"("<< setw(2) << setiosflags(ios::left) << i<<")  ("
            <<setw(3)<<setiosflags(ios::left)<< qua[i].op << ", " 
            <<setw(5) << setiosflags(ios::left) << qua[i].arg1 << ", " 
            << setw(5) << setiosflags(ios::left) << qua[i].arg2 << ", " 
            << setw(5) << setiosflags(ios::left) << qua[i].res <<")" << endl;
    }

    // ����Ԫʽ������ļ�
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
