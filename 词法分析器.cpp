#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

int Letter(char c)        //字母
{
	if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z'))
		return 1;
	else
		return 0;
}
int Digit(char c)         //数字
{
	if (c >= '0'&&c <= '9')
		return 1;
	else
		return 0;
}
int Key(char c[])         //关键字
{
	int i = 0;
	char m[10][10] = { "then","main","if","else","while","int","for","return","do" };
	for (i = 0; i<9; i++)
	{
		if (strcmp(c, m[i]) == 0)
			return 1;
	}
	return 0;
}
int Opera(char c)         //运算符
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '>' || c == '<' || c == '!' || c == ':')
		return 1;
	else
		return 0;
}
int Sepera(char c)        //分隔符
{
	if (c == '(' || c == ')' || c == '{' || c == '}' || c == ';' || c == ',')
		return 1;
	else
		return 0;
}

int main()
{
	char string1[110];      //源程序
	char ch;
	int i = 0;    //识别的第i个字符
	int j = 1;
	int m = 0;    //识别行数
	int k = 0;
	int a = 0;
	int b = 1;
	double strl = 0;     //读取字符串长度
	char str[100][11];
	FILE *fp1;
	fp1 = fopen("D:\\input.txt", "r+");  //打开文件
	for (i = 0; ; i++)
	{
		fscanf(fp1, "%c", &string1[i]);
		if (string1[i] == '#')
		{
			string1[i] = '\0';
			break;
		}
	}
	printf("源代码:\n%s\n", string1);
	printf("编译后:\n");

	strl = strlen(string1);      //读取字符串长度
	for (i = 0; i<strl; i++, m++)
	{
		k = 0;
		char strToken[11] = {};   //存放构成单词符号的字符串
		ch = string1[i];
		if (ch == ' ') {
			continue;
		}
		else
			if (Letter(ch))       //保留字或标识符
			{
				strToken[0] = ch;
				i++;
				m++;
				ch = string1[i];
				while (Letter(ch) || Digit(ch))
				{
					k++;
					strToken[k] = ch;
					i++;
					m++;
					ch = string1[i];
				}
				i--;    //回退
				m--;
				ch = string1[i];
				if (Key(strToken))
					printf("(3,%s)\n", strToken);
				else {
					for (int c = 0; c < b; c++) {
						if (strcmp(str[c], strToken) != 0) {
							if (c == b - 1) {
								strcpy_s(str[a++], 11, strToken);
								printf("(1,%d)---%s\n", a, strToken);
								b++;
								break;
							}
						}
						else {
							printf("(1,%d)---%s\n", c + 1, strToken);
							break;
						}
					}
				}

			}
			else if (Digit(ch))        //数字
			{
				strToken[0] = ch;
				i++;
				m++;
				ch = string1[i];
				while (Digit(ch))
				{
					k++;
					strToken[k] = ch;
					i++;
					m++;
					ch = string1[i];
				}
				i--;    //回退
				m--;
				ch = string1[i];
				printf("(2,%s)\n", strToken);
			}
			else if (Opera(ch))                //运算符
			{
				if (ch == '+')
				{
					if (string1[i + 1] == '+')       //++
					{
						i++;
						m++;
						printf("(4,++)\n");
					}
					else printf("(4,+)\n");     //+
				}
				else if (ch == '-')
				{
					if (string1[i + 1] == '-')       //--
					{
						i++;
						m++;
						printf("(4,--)\n");
					}
					else printf("(4,-)\n");     //-
				}
				else if (ch == '*')
				{
					if (string1[i + 1] == '*')       //指针的指针**
					{
						i++;
						m++;
						printf("(4,**)\n");
					}
					else printf("(4,*)\n");     //*
				}
				else if (ch == '/')
				{
					printf("(4,/)\n");          // /
				}
				else if (ch == '=')
				{
					if (string1[i + 1] == '=')       //==
					{
						i++;
						m++;
						printf("(4,==)\n");
					}
					else printf("(4,=)\n");     //=
				}
				else if (ch == '<')
				{
					if (string1[i + 1] == '<')       //左移运算符<<
					{
						i++;
						m++;
						printf("(4,<<)\n");
					}
					else if (string1[i + 1] == '=')  //<=
					{
						i++;
						m++;
						printf("(4,<=)\n");
					}
					else printf("(4,<)\n");     //<
				}
				else if (ch == '>')
				{
					if (string1[i + 1] == '>')       //右移运算符>>
					{
						i++;
						m++;
						printf("(4,>>)\n");
					}
					else if (string1[i + 1] == '=')  //>=
					{
						i++;
						m++;
						printf("(4,>=)\n");
					}
					else printf("(4,>)\n");      //>
				}
				else if (ch == '!')
				{
					if (string1[i + 1] == '=')       // !=
					{
						i++;
						m++;
						printf("(4,!=)\n");
					}
					else
						printf("(error,!)\n");
				}
				else if (ch == ':')
				{
					if (string1[i + 1] == '=')       // !=
					{
						i++;
						m++;
						printf("(4,:=)\n");
					}
					else
						printf("(非法字符,:)\n");
				}
			}
			else if (Sepera(ch))
				printf("(5,%c)\n", ch);        //分隔符
			else {
				if (ch == '\n') {
					m = 0;
					j++;
				}
				else {
					printf("(非法字符,%c) column: %d row: %d\n", ch, m, j);
				}
			}
	}
	fclose(fp1);
	system("pause");
	return 0;
}