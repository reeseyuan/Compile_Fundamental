#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

int Letter(char c)        //��ĸ
{
	if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z'))
		return 1;
	else
		return 0;
}
int Digit(char c)         //����
{
	if (c >= '0'&&c <= '9')
		return 1;
	else
		return 0;
}
int Key(char c[])         //�ؼ���
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
int Opera(char c)         //�����
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '>' || c == '<' || c == '!' || c == ':')
		return 1;
	else
		return 0;
}
int Sepera(char c)        //�ָ���
{
	if (c == '(' || c == ')' || c == '{' || c == '}' || c == ';' || c == ',')
		return 1;
	else
		return 0;
}

int main()
{
	char string1[110];      //Դ����
	char ch;
	int i = 0;    //ʶ��ĵ�i���ַ�
	int j = 1;
	int m = 0;    //ʶ������
	int k = 0;
	int a = 0;
	int b = 1;
	double strl = 0;     //��ȡ�ַ�������
	char str[100][11];
	FILE *fp1;
	fp1 = fopen("D:\\input.txt", "r+");  //���ļ�
	for (i = 0; ; i++)
	{
		fscanf(fp1, "%c", &string1[i]);
		if (string1[i] == '#')
		{
			string1[i] = '\0';
			break;
		}
	}
	printf("Դ����:\n%s\n", string1);
	printf("�����:\n");

	strl = strlen(string1);      //��ȡ�ַ�������
	for (i = 0; i<strl; i++, m++)
	{
		k = 0;
		char strToken[11] = {};   //��Ź��ɵ��ʷ��ŵ��ַ���
		ch = string1[i];
		if (ch == ' ') {
			continue;
		}
		else
			if (Letter(ch))       //�����ֻ��ʶ��
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
				i--;    //����
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
			else if (Digit(ch))        //����
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
				i--;    //����
				m--;
				ch = string1[i];
				printf("(2,%s)\n", strToken);
			}
			else if (Opera(ch))                //�����
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
					if (string1[i + 1] == '*')       //ָ���ָ��**
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
					if (string1[i + 1] == '<')       //���������<<
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
					if (string1[i + 1] == '>')       //���������>>
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
						printf("(�Ƿ��ַ�,:)\n");
				}
			}
			else if (Sepera(ch))
				printf("(5,%c)\n", ch);        //�ָ���
			else {
				if (ch == '\n') {
					m = 0;
					j++;
				}
				else {
					printf("(�Ƿ��ַ�,%c) column: %d row: %d\n", ch, m, j);
				}
			}
	}
	fclose(fp1);
	system("pause");
	return 0;
}