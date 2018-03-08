#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
char current;
char buffer[1000];
int mark=0;
//单词编码表  
struct Token{
	int defination;
	char seman[10];
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



bool factor();
bool expression();
bool term();
bool statement();
void scanner();
bool Condition_statement();
bool Assignment_statement();
bool while_statement();
void Variable_id();




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
 
 int main()
{
	p=0;
	freopen("test.txt","r",stdin);
	do
	{
		cin.get(current);
		buffer[p++]=current;
	}
	while(current!='#');	
	p=0;
	scanner();
	Variable_id();
	
	do
	{
		scanner();
		statement();
	}while(temp.defination!=0);
	
	if(mark==0)
		printf("\n success!");
	
	return 0;
}
 void scanner()
 {
 	for(int i=0;i<10;i++)
	 {
	 	temp.seman[i]='\0';
		 	
	 } 
 	current=buffer[p++];
 	while((current==' ')||(current=='\n'))
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
		case EOF:   temp.defination=-1;break;
		case '#':		temp.defination=0;break;	
		default:	temp.defination=0;break;
		 
					
	}
//	if(temp.defination==34&&mark==0) 
	//	cout<<sum;
	//cout<<temp.seman;//显示读取的内容，方便查错 
 	
 }
//变量声明 
void Variable_id()
{
	if(strcmp(temp.seman,"var")==0)
	{
		scanner();
		if(temp.defination==33)//变量名 
		{
			scanner();
			while(temp.defination==14)//逗号
			{
				scanner();
				if(temp.defination==33)
				{
					scanner();
				}
				else
				{
					mark=1;
					cout<<"变量声明error!"<<endl; 
				}
			 }
			if(temp.defination==13)//;
			{
			}
			else
			{
				mark=1;
				cout<<"变量声明error!"<<endl; 
			}
		}
	}
	else
	{
		mark=1;
		cout<<"程序中变量未声明error！"<<endl;
		p=0;//重新读取文本 
	}
}

bool Assignment_statement()//声明语句 
 {
 	scanner();
	if(temp.defination==32)	//":="
	{
		scanner();
		expression();
		return true;
	}
	else
	{
		cout<<" ERROR1!\n "<<endl;		//赋值部分出错 
		mark=1;
	}

  } 

  
bool Compound_statement()//复合语句 
{
	scanner();
	while(statement())
	{
		if(temp.defination==13)
		{
			scanner();
			if(temp.defination==6)
			{
				break;
			}
			
		}
	}
	
	if(temp.defination==6)
	{
		scanner();
		return true;
	}
	else
	{
		cout<<"复合语句未结束，缺少end！error"<<endl; 
		mark=1;
		return false;
	}
	
	if(temp.defination==0)
	{
		
	}
}

bool Condition()//条件语句 
{
	expression();
	if(temp.defination==19||temp.defination==20||temp.defination==21||temp.defination==23||temp.defination==16)
	{
		scanner();
	}
	else
	{
		cout<<"关系运算符ERROR！"<<endl; 
		mark=1;
		return false;
	}
	
	expression();
}

bool Condition_statement()
{
	if(temp.defination==5)
	{
		scanner();
		Condition();
		if(temp.defination==4)//then
		{
			scanner();
			statement();
			if(temp.defination==7)
			{
				scanner();
				statement();
			}
			else
			{
				return true;
			}
		 } 
		 else
		 {
		 	cout<<"条件语句error！\n"<<endl;
			 return false; 
			 mark=1;
		  } 
	}
	else
	{
		return false;
	}
}

bool expression() //表达式 +、-、 
 {
 	
 	do{
 		if((temp.defination==24)||(temp.defination==25))
 		{
	 		scanner();
	 		term();
		 }
		 else
		 {
		 	term();
		 }
	 }while((temp.defination==24)||(temp.defination==25));
	 return true;

 	
 }
 
bool While_statement()
{
   
	scanner();
    Condition();
	if(temp.defination==2)
    {
        scanner();
        statement();
        return true;
    }
	else
	{
		mark=1;
		cout<<"循环语句error"<<endl;
		return false;
	}
        
}

bool statement()
{
    if(temp.defination==33)//声明
    {
        Assignment_statement();
        return true;    
    }
    if(temp.defination==3)  //while循环 
    {
        While_statement(); 
        return true;
    }
    else if(temp.defination==1)//复合语句 
    {
        Compound_statement();
        return true;
    }
    else if(temp.defination==5)//条件语句 
    {
        Condition_statement();
        return true;
    }
    else
    {
        return false;
    }
}


bool term()// *、/ 
 {
 	while(factor())
    { 
		if((temp.defination==26)||(temp.defination==31))
		{
			scanner();             /*读下一个单词符号*/
		}
		else
		{
			return true;
		}
    	
    }
    return false;

 }
 
bool factor()//因子 
{
	if(temp.defination==33)
	{
		scanner();
		return true;
	 }
	 else if(temp.defination==34)
	 {
	 	scanner();
		return true;
	 }
	 else if(temp.defination==27) //" ( "
	 {
	 	scanner();
	 	expression();
	 	
	 	if(temp.defination==28)//" ) "
	 	{
	 		scanner();
	 		return true;
		 }
		else
		{
		 	cout<<" ERROR3! "<<endl;//少了） 
		 	mark=1;
		 	return false;
		}
	 }
	 else{
	 	cout<<" ERROR4! "<<endl;
	 	mark=1;
	 	return false;
	 } 
	 return false;
 } 

