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
    "volatile", "while"};                                 //�����ֱ� 
    
string operatorword[100]={"+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==",
    "!=", ";", "(", ")", "^", ",", "\'", "\'", "#", "&",
    "&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{",
    "}", "\\", ".", "\?", ":", "!"};                     //������������ 

char identifier[100][100]={};                        //��ʶ���� 

bool Isletter(char c)           //�ж��Ƿ�Ϊ��ĸ 
{
	if(isalpha(c)||c=='_')
		return 1;
	else
		return 0;
}

bool Isdigital(char c)         //�ж��Ƿ�Ϊ���� 
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
	int count=0,p,n=0;               //countΪproject��ǰָ�룬pΪָ��ƫ�ƣ�nΪidentifier��ǰָ�� 
	ofstream outfile("Sequence.txt",ios::app);
    if(!outfile)
	{
		cerr<<"open error!"<<endl;
		exit(1);
	}
	while(count!=length-1)
	{
		while(project[count]==' '||project[count]=='\t'||project[count]=='\n')        //ȥ���ո񡢻��з� 
			count++;
		//cout<<count; 
		if(Isletter(project[count]))      //�жϱ�ʶ���ͱ����� 
		{
			bool b=0; 
			char s[20]={};              //�ǵó�ʼ�� 
			int i=0;
			p=count;
			while(Isletter(project[p])||Isdigital(project[p]))
			{
				s[i]=project[p];
				p++;
				i++;
				//cout<<s; 
			}
			for(int j=0;j<100;j++)       //�ж��Ƿ��Ǳ����� 
			{
				if(strcmp(reserveword[j],s)==0)
				{
					//cout<<reserveword[j];
					cout<<"(3��"<<s<<")"<<endl;
					outfile<<"(3��"<<s<<")"<<endl;
					b=1;
					break;
				}
			}
			if(b==0)
			{
				strcpy(identifier[n],s);     //��ֵ����ʶ���� 
				cout<<"(1��"<<n<<")"<<endl;
				outfile<<"(1��"<<n<<")"<<endl;
				n++;
			}		
			count=count+i;
			//cout<<"count="<<count;	
		}
		else if(Isdigital(project[count]))        //�ж��Ƿ��ǳ���
		{
			char s[20]={};              //�ǵó�ʼ��
			int i=0;
			p=count;
			while(Isdigital(project[p]))
			{
				s[i]=project[p];
				p++;
				i++;
			}
			cout<<"(2��"<<s<<")"<<endl;
			outfile<<"(2��"<<s<<")"<<endl;
			count=count+i;
		}
		else if(Isoperator(project[count]))                //ʣ�µĶ���������ͽ�� 
		{
			char s[20]={'\0'};
			int i=0;
			bool b=0;
			p=count;
			if(project[count]==';'||project[count]=='{'||project[count]=='}')     //�ж��Ƿ��ǽ�� 
			{
				cout<<"(5��"<<project[count]<<")"<<endl;
				outfile<<"(5��"<<project[count]<<")"<<endl;
				count++;
			}
			else                //����� 
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
						cout<<"(4��"<<s<<")"<<endl;
						outfile<<"(4��"<<s<<")"<<endl;
						b=1;
						break;
					}
				}
				if(b==0)
				{
					for(int j=0;j<i;j++)
					{
						cout<<"(4��"<<s[j]<<")"<<endl;
						outfile<<"(4��"<<s[j]<<")"<<endl;
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
					//cout<<"(4��"<<project[p]<<")"<<endl;
					//count++;
					count=count+i;
				}
				//cout<<"count="<<count;	
		//	}
		}
		else
		{
			cout<<"��"<<count<<"���ַ�Ϊ�Ƿ��ַ�"<<endl;
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
    {//��Դ����
        cerr<<"can't open this file";
        exit(1);
    }
    project[datalen]=fgetc(fp);
    while(project[datalen]!='$')
    {//��Դ�������project[]����
        datalen++;
        project[datalen]=fgetc(fp);
    }
    //project[datalen]='\0';
    fclose(fp);
    cout<<endl<<"Դ����Ϊ:"<<endl;
    for(int i=0;i<datalen;i++)
    	cout<<project[i];
    //cout<<datalen;
    scan(project,datalen);
	return 0; 
}  
