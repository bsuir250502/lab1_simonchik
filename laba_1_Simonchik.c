#include<stdio.h>
#include<stdlib.h>

enum Month {ZERO,JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

struct date
{
    int day;
    enum Month mo;
    int year;
};

struct firma
{
	char name[30];
	char tax[7];
	struct date deadline_date;
	struct date fact_date;
};

int Mystrcmp(char* ,char *);
int Input_name (firma* );
void Display_rezult(firma*,int);
void Input_tax(firma*, int);
void Input_date(firma*, int);
void Display(firma*, int);
bool Compare_date(date,date);

int main()
{
	int number;
	puts("Enter information about the firms, to complete the entry, press 'end' ");
        firma info[50];
	number=Input_name(info);
	Input_tax(info, number);
	Input_date(info, number);
	Display(info,number);
	Display_rezult(info, number);
	return 0;
}

int Input_name(firma* info)
{
	char *str="end";
	int number=0;
	while( number<50)
	{
		printf("Enter the name of the firm number% d:",number+1);
		fflush(stdin);
		gets(info[number].name);
		if(!(Mystrcmp(info[number].name,str))) break;
		else number++;
        }
	return number;
}

void Input_tax(firma* info, int number)
{
    int i;
	for(i=0;i<number;i++)
	{
		printf("Enter the firm tax %s: ",info[i].name);
		fflush(stdin);
		gets(info[i].tax);
	}
}

enum Month char_to_enum(char *str)
{
    if ( !(Mystrcmp(str, "000") )) {return ZERO;}
	else if( !(Mystrcmp(str, "JAN")) ) {return JAN;}
    else if( !(Mystrcmp(str, "FEB")) ) {return FEB;}
    else if( !(Mystrcmp(str, "MAR")) ) {return MAR;}
    else if( !(Mystrcmp(str, "APR")) ) {return APR;}
    else if( !(Mystrcmp(str, "MAY")) ) {return MAY;}
    else if( !(Mystrcmp(str, "JUN")) ) {return JUN;}
    else if( !(Mystrcmp(str, "JUL")) ) {return JUL;}
    else if( !(Mystrcmp(str, "AUG")) ) {return AUG;}
    else if( !(Mystrcmp(str, "SEP")) ) {return SEP;}
    else if( !(Mystrcmp(str, "OCT")) ) {return OCT;}
    else if( !(Mystrcmp(str, "NOV")) ) {return NOV;}
    else if( !(Mystrcmp(str, "DEC")) ) {return DEC;}
   
}

void Input_date(firma* info, int number)
{
	int i;
	char *str;
	for(i=0;i<number;i++)
	{
	    str=(char*)calloc(3,1);
	    printf("Enter the date of the deadline for tax payment 'DD MMM YYYY' for the firm %s:\n",info[i].name);
		scanf("%d%s%d",&info[i].deadline_date.day,str,&info[i].deadline_date.year);
		info[i].deadline_date.mo=char_to_enum(str);
		printf("Enter date of the actual tax payment 'DD MMM YYYY'(or '0 'in all respects, if not been made) for the firm %s:\n",info[i].name);
		scanf("%d%s%d",&info[i].fact_date.day,str,&info[i].fact_date.year);
		info[i].fact_date.mo=char_to_enum(str);
	} 
}

int Mystrcmp(char *str1,char *str2)
{
	int i=0,ind=1;
        while(str1[i] && str2[i])
        {
        	if (str1[i]==str2[i]) ind=0;
        	else return 1;
        	if ((!str1[i+1] && str2[i+1]) || (str1[i+1] && !str2[i+1])) ind = 1;
       	        i++;
        }
        return ind;
}

void Display(firma* info, int number)
{
	int i=0;
	for(i;i<number;i++)
	{
		printf("Information about the firm %s:\n",info[i].name);
		printf("The value of tax - %s\n",info[i].tax);
        	printf("Date of tax payment deadline - %d/%d/%d\n",info[i].deadline_date.day,info[i].deadline_date.mo,info[i].deadline_date.year);
        	printf("Date of the actual tax payment - %d/%d/%d\n",info[i].fact_date.day,info[i].fact_date.mo,info[i].fact_date.year);
        }
}

void Display_rezult(firma* info, int number)
{
	char *str;
	int i=0;
	firma p;
	int t=0;
	date report_date;
	str=(char*)calloc(3,1);
	printf("\nEnter date  to display information about the debts of firms this month DD MMM YYYY:\n");
	scanf("%d%s%d",&report_date.day,str,&report_date.year);
	report_date.mo=char_to_enum(str);
   	 printf("Date of report - %d/%d/%d:\n",report_date.day,report_date.mo,report_date.year);
	for(;i<number;i++)
	{

		if(Compare_date(info[i].deadline_date,report_date))
			 if(Compare_date(report_date,info[i].fact_date))
			 {
				 p=info[t];
				 info[t]=info[i];
				 info[i]=p;
				 t++;
			 }
	}
	Display(info,number);
}

bool Compare_date(date date_1, date date_2)
{
	if(date_1.year==date_2.year)
	{	
		if(date_1.mo==date_2.mo)
		{
			if(date_1.day==date_2.day) return false;
			else if(date_1.day<date_2.day) return true;
			else return false;
		}
		else if(date_1.mo<date_2.mo) return true;
			else return false;
	}
	else if(date_1.year<date_2.year) return true;
		else return false;
}

