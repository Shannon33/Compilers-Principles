#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iomanip>
using namespace std;
char current;
char buffer[1000];
//µ¥´Ê±àÂë±í  
struct Token{
	int defination;
	char seman[20];
};
Token temp;
Token Tokens[34]=
{
	1,"begin",
	2,"do",
	3,"while",
	4,"then",
	5,"if", 
	6,"end",
	7,"else",
	8,"true",
	9,"false",
	10,"const",
	11,"read",
	12,"write",
	13,";",
	14,",",
	15,":",
	16,"=",
	17,"!",
	18,"|",
	19,"<",
	20,">",
	21,"<=",
	22,"<>",
	23,">=",
	24,"+",
	25,"-",
	26,"*",
	27,"(",
	28,")",
	29,"{",
	30,"}",
	31,"/",
	32,":=" ,
	33,"IDEN",
	34,"NUMB"
};
int IsDigit(char ch)
{
	if((ch>='0')&&(ch<='9'))
		return 1;
	else
		return 0;
 } 
int IsLetter(char ch)
{
	if(((ch>='a')&&(ch<='z'))||((ch>='A')&&(ch<='Z')))
		return 1;
	else
		return 0;
}
int IsKeyword(char str_token[])
{
	int i=0;
	for(i=0;i<12;i++)
	{
		if(strcmp(Tokens[i].seman,str_token)==0)
			return i;
	}
	return -1;
}
 int n,p,m=0,rows,sum=0; 
 void scanner()
 {
 	current=buffer[p++];
 	while((current==' ')||(current=='\t'))
 	{
 		current=buffer[p];
 		p++;
	 }
	if(IsLetter(current))
	{
		m=0;
		while(IsLetter(current)||IsDigit(current))
		{
			temp.seman[m++]=current;
			current=buffer[p++];
		}
		temp.seman[m++]='\0';
		p--;
		temp.defination=33;
		for(n=0;n<12;n++)
		{
			if(strcmp(temp.seman,Tokens[n].seman)==0)
			{
				temp.defination=n+1;
				break;
			 } 
		}
	}
	else if(IsDigit(current))
	{
		{
			sum=0;
			while(IsDigit(current))
			{
				sum=sum*10+current-'0';
				current=buffer[p++];	
			}
		}
		p--;
		temp.defination=34;
		if(sum>32767)
			temp.defination=-1;
	}
	else switch(current)
	{
		case '<':	m=0;temp.seman[m++]=current;
					current=buffer[p++];
					if(current=='>')
					{
						temp.defination=22;
						temp.seman[m++]=current;
					}
					else if(current=='=')
					{
						temp.defination=21;
						temp.seman[m++]=current;
					}
					else
					{
						temp.defination=19;
						p--;
					}
					break;
		case '>':	m=0;temp.seman[m++]=current;
					current=buffer[p++];
					if(current=='=')
					{
						temp.defination=23;
						temp.seman[m++]=current;
						
					}
					else
					{
						temp.defination=20;
						p--;
					}
					break;
		case ':':	m=0;temp.seman[m++]=current;
					current=buffer[p++];
					if(current=='=')
					{
						temp.defination=32;
						temp.seman[m++]=current;
						
					}
					else
					{
						temp.defination=15;
						p--;
					}
					break;
		case '+':	temp.defination=24;temp.seman[0]=current;break;
		case '-':	temp.defination=25;temp.seman[0]=current;break;
		case '*':	temp.defination=26;temp.seman[0]=current;break;
		case '/':	temp.defination=31;temp.seman[0]=current;break;
		case '=':	temp.defination=16;temp.seman[0]=current;break;
		case '(':	temp.defination=27;temp.seman[0]=current;break;
		case ')':	temp.defination=28;temp.seman[0]=current;break;
		case '\n':	temp.defination=-2;temp.seman[0]=current;break;
		case '\r':	temp.defination=-2;temp.seman[0]=current;break;
		case ';':	temp.defination=13;temp.seman[0]=current;break;
		case ',':	temp.defination=14;temp.seman[0]=current;break;
		case '!':	temp.defination=17;temp.seman[0]=current;break;
		case '{':	temp.defination=29;temp.seman[0]=current;break;
		case '}':	temp.defination=30;temp.seman[0]=current;break;
		case '#':   temp.defination=0;break;
		case EOF:   temp.defination=-1;break;
		default:	temp.defination=0;break;
		 
					
	}
 	
 }
int main()
{
	cout<<left;
	p=0;
	freopen("test.txt","r",stdin);
	while(cin.get(current))
	{
		buffer[p++]=current;
	}	
	p=0;
	rows=1;
	do
	{
		scanner();
		switch(temp.defination)
		{
			case 34:	cout<<"("<<temp.defination<<","<<sum<<")"<<endl;break;
			case -1:	break;
			case -2:	rows=rows++;break;
			case 0:		cout<<"ERROR!"<<endl;break;
			default:	cout<<"("<<temp.defination<<","<<temp.seman<<")"<<endl;break; 
		 } 
		 for(int i=0;i<20;i++)
		 {
		 	temp.seman[i]='\0';
		 	
		 }
	}
	 while(temp.defination!=0);
	 
	 for(int i=0;i<=34;i=i+2) 
	 {
	 	cout<<setw(10)<<Tokens[i].defination\
		 <<setw(10)<<Tokens[i].seman<<setw(10)\
		 <<Tokens[i+1].defination<<setw(10)<<Tokens[i+1].seman<<endl;
	 }
	return 0;
}
