#include<iostream>
#include<vector>
#include<string>
#include<stack>
using namespace std;
#define BEGIN_SYB 'E'

class Tab {                   //预测分析表中单个产生式
public:
    Tab(char n,char e,string p):noend(n),end(e),prod(p) {};
    char noend;
    char end;
    string prod;
};

vector<Tab>  pTab;       //预测分析表
stack<char>  pStack;     //栈
string       pStr;       //输入串
int Index = 0;           //输入串的下标
int num = 0;             //下标
char X;                  //从栈顶取出的符号
char a;                  //字符串目前分析到的位置
vector<char> VT{'i','+','*','(',')','#'};    //终结符号集合
vector<char> VN{'E','K','T','M','F'};    //非终结符号集合

int isPartVT(char ch)  //判断终结符
{
    for(auto u:VT) {
        if(u == ch) {
            return 1;
        }
    }
    return 0;
}

int isPartVN(char ch)  //判断非终结符
{
    for(auto u:VN) {
        if(u == ch) {
            return 1;
        }
    }
    return 0;
}

void initpTab()
{
    pTab.push_back(Tab('E','i',"TK"));       //K表示E'
    pTab.push_back(Tab('E','(',"TK"));
    pTab.push_back(Tab('K','+',"+TK"));
    pTab.push_back(Tab('K',')',"$"));
    pTab.push_back(Tab('K','#',"$"));
    pTab.push_back(Tab('T','i',"FM"));
    pTab.push_back(Tab('T','(',"FM"));       //M表示T'
    pTab.push_back(Tab('M','+',"$"));
    pTab.push_back(Tab('M','*',"*FM"));
    pTab.push_back(Tab('M',')',"$"));
    pTab.push_back(Tab('M','#',"$"));
    pTab.push_back(Tab('F','i',"i"));
    pTab.push_back(Tab('F','(',"(E)"));
}

void printStack()
{
    stack<char> pTemp(pStack);
    while(pTemp.size() != 0) {
        cout << pTemp.top()<< " ";
        pTemp.pop();
    }
    cout << "\t\t\t";
}

int synaly()
{
    pStack.push(pStr[Index++]);  //#
    pStack.push(BEGIN_SYB);      //E开始符
    a = pStr[Index++];
    bool flag = true;
    while(flag) {
        cout << 1+num++ << "\t\t\t";  //输出行号
        printStack();
        if(pStack.size() != 0) {
            X = pStack.top();              //将符号栈顶给X
            pStack.pop();
        }
        
        if(isPartVT(X)) {                  //如果是终结符
            if(X == '#' && a == '#') {
                cout <<"\t"<<"接受"<<endl;
                flag = false;
            }else if(X == a){
                cout <<a<<"匹配" << endl;
                a = pStr[Index++];
            }else {
                cout << "EROOR!" << endl;
                return 0;
            }
            
        }else if (X == '#') {
            if(X == a) {
                flag = false;
            }else {
                cout << "EROOR!" << endl;
                return 0;
            }
            
        }else if (isPartVN(X) && isPartVT(a)) {  //如果非终结符
            int type = 0;
            for(auto u:pTab) {
                if(u.noend == X && u.end == a) {
                    string tempProd = u.prod;
                    cout <<  X << "->" << tempProd << endl;   //输出产生式
                    if(tempProd == "$") {
                        type = 1;
                        break;
                    }else
                    {
                        for(int i = tempProd.size()-1;i>=0;--i) {
                            pStack.push(tempProd[i]);
                        }
                        type = 1;
                        break;
                    }
                }
            }
            if(type != 1) {
                cout << "EROOR!" << endl;
                return 0;
                
            }
            
        }else {
            cout << "EROOR!" << endl;
            return 0;
        }
        
    }
    return 1;
}

int main(int argc,char *argv[])
{
    initpTab();
    cout << "请输入语法串:";
    cin >> pStr;
    cout << "步骤" << "\t\t\t" << "符号栈" << "\t\t\t" << "所用产生式" << endl;
    int flag = synaly();
    cout << endl;
    if(flag == 1) {
        cout << "分析成功" << endl;
    }
    else{
        cout << "分析失败" << endl;
    }
    return 0;
}
