# principle-of-compiling-experiment-Njtech
## ˵��
### �ļ���֯
>������ in.txt\
>������ LexicalAnalysis.cpp\
>������ LexicalFunction.cpp\
>������ main.cpp\
>������ MyComplier.h\
>������ out.txt\
>������ readme.md\
>������ Utils.cpp\
>������ VariablesDefination.cpp

- ˵��
  - ͷ�ļ� MyComplier.h ��ź������� ȫ�ֱ���������Ԥ���塣
  - Utils.cpp��LexicalAnalysis.cpp��LexicalFunction.cpp �Ǻ�����ʵ��
  - VariablesDefination.cpp ��ȫ�ֱ�����������

### �������
#### �ʷ�����
�ʷ�������Ҫ������ Scanner������ ���Scannerʶ���һ��unknown���͵Ķ�Ԫʽ��ô���ж�Ϊ�ʷ���������iHaveError��������Ϊ1
#### �﷨����
�﷨������Ҫ��Match�������� ���Match����ƥ�䵽һ����Ӧ�ó��ֵĴʾͻᱨ��iHaveError = 2;
#### �������
�ں�����ĳһ��������ȥ����

#### ֧�ֵĳ������ͣ�
- ��������������int�ĳ�����
- known���͵ĵ��� 
- ��ʶ���б��ֳ����ظ����壺
- ��ʶ���б���ȱ��","
- �﷨������ȱ�ٸ���Ĺؼ���   ������֤��
- ���ʽ���������ȱʧ��
- ��ʶ��δ��ʼ��
- ����г��ֲ�����ʶ��


#### ������
- ����unknown���͵��ʴ���
  - ��unknown������Ϊһ�������ڱ�ʶ���б��г��ֵ�ʱ�� ����Ϊһ�������ʽ�ı�ʶ����
    > int$qbe,kkhbu,$shni;    ����+����
    > ������Կ����Ǹ��ʷ�����
  - ��unknown��Ϊһ��ǰ׺���֡�
    > int$qbe,kkhbu$shni;   ������
  - ��unknown������Ϊǰ׺&��׺�����ڹؼ�����
    > kkhuifkkhbu            ������
- ȱ�ٹؼ���(������)
- ȱ�ٷָ���
- ���ֲ���ʶ�ı�ʶ��
- δ��ʼ���ı�ʶ�����塣