#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string.h>
using namespace std; 
char reserveword[100][100]={"auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"};                                 //保留字表 
    
string operatorword[100]={"+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==",
    "!=", ";", "(", ")", "^", ",", "\'", "\'", "#", "&",
    "&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{",
    "}", "\\", ".", "\?", ":", "!"};                     //界符、运算符表 

char identifier[100][100]={};                        //标识符表 

bool Isletter(char c)           //判断是否为字母 
{
	if(isalpha(c)||c=='_')
		return 1;
	else
		return 0;
}

bool Isdigital(char c)         //判断是否为数字 
{
	if(isdigit(c))
		return 1;
	else
		return 0;
}

bool Isoperator(char c)
{
	string t="0";
	t[0]=c;
	for(int j=0;j<100;j++)
	{
		//cout<<operatorword[j];
		if(operatorword[j]==t)
		{		
			return 1;
		}
	}
	return 0;
}

void scan(char project[],int length)
{
	int count=0,p,n=0;               //count为project当前指针，p为指针偏移，n为identifier当前指针 
	ofstream outfile("Sequence.txt",ios::app);
    if(!outfile)
	{
		cerr<<"open error!"<<endl;
		exit(1);
	}
	while(count!=length-1)
	{
		while(project[count]==' '||project[count]=='\t'||project[count]=='\n')        //去掉空格、换行符 
			count++;
		//cout<<count; 
		if(Isletter(project[count]))      //判断标识符和保留字 
		{
			bool b=0; 
			char s[20]={};              //记得初始化 
			int i=0;
			p=count;
			while(Isletter(project[p])||Isdigital(project[p]))
			{
				s[i]=project[p];
				p++;
				i++;
				//cout<<s; 
			}
			for(int j=0;j<100;j++)       //判断是否是保留字 
			{
				if(strcmp(reserveword[j],s)==0)
				{
					//cout<<reserveword[j];
					cout<<"(3，"<<s<<")"<<endl;
					outfile<<"(3，"<<s<<")"<<endl;
					b=1;
					break;
				}
			}
			if(b==0)
			{
				strcpy(identifier[n],s);     //赋值给标识符表 
				cout<<"(1，"<<n<<")"<<endl;
				outfile<<"(1，"<<n<<")"<<endl;
				n++;
			}		
			count=count+i;
			//cout<<"count="<<count;	
		}
		else if(Isdigital(project[count]))        //判断是否是常数
		{
			char s[20]={};              //记得初始化
			int i=0;
			p=count;
			while(Isdigital(project[p]))
			{
				s[i]=project[p];
				p++;
				i++;
			}
			cout<<"(2，"<<s<<")"<<endl;
			outfile<<"(2，"<<s<<")"<<endl;
			count=count+i;
		}
		else if(Isoperator(project[count]))                //剩下的都是运算符和界符 
		{
			char s[20]={'\0'};
			int i=0;
			bool b=0;
			p=count;
			if(project[count]==';'||project[count]=='{'||project[count]=='}')     //判断是否是界符 
			{
				cout<<"(5，"<<project[count]<<")"<<endl;
				outfile<<"(5，"<<project[count]<<")"<<endl;
				count++;
			}
			else                //运算符 
			{
				while(Isoperator(project[p])&&i<2)
				{
					s[i]=project[p];
					p++;
					i++;
				}
				for(int j=0;j<100;j++)
				{
					if(operatorword[j]==s)
					{
					//cout<<reserveword[j];
						cout<<"(4，"<<s<<")"<<endl;
						outfile<<"(4，"<<s<<")"<<endl;
						b=1;
						break;
					}
				}
				if(b==0)
				{
					for(int j=0;j<i;j++)
					{
						cout<<"(4，"<<s[j]<<")"<<endl;
						outfile<<"(4，"<<s[j]<<")"<<endl;
					}
				}
				//Isoperator(project[p]);
			/*	cout<<"!!!!";
				cout<<project[p];			
				while(Isoperator(project[p]))
				{
					s[i]=project[p];
					p++;
					i++;
					cout<<s;
					system("pause");
				}*/
					//cout<<"(4，"<<project[p]<<")"<<endl;
					//count++;
					count=count+i;
				}
				//cout<<"count="<<count;	
		//	}
		}
		else
		{
			cout<<"第"<<count<<"个字符为非法字符"<<endl;
			count++; 
		 } 
	}
} 

int main()
{
	char project[1000];
	int datalen=0;
	FILE *fp, *fp1;
    if ((fp = fopen("data.txt", "r")) == NULL)
    {//打开源程序
        cerr<<"can't open this file";
        exit(1);
    }
    project[datalen]=fgetc(fp);
    while(project[datalen]!='$')
    {//将源程序读入project[]数组
        datalen++;
        project[datalen]=fgetc(fp);
    }
    //project[datalen]='\0';
    fclose(fp);
    cout<<endl<<"源程序为:"<<endl;
    for(int i=0;i<datalen;i++)
    	cout<<project[i];
    //cout<<datalen;
    scan(project,datalen);
	return 0; 
}  
