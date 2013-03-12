#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct students{
    char name[256];
    int marks[4];
    
};

struct specialitys{
    char name[256];
    int number_of_student;
    struct students st[30];
};

struct faculty{
    char name[256];
    struct specialitys sp[5];
    int number_of_speciality;
};

int input_faculty(faculty*,int);
void output_faculty(faculty*,int);

int main()
{
    faculty info[10];
    int number_of_faculty=0;
    puts("Enter information about the university, to complete the entry, press 'exit'");
    number_of_faculty=input_faculty(info, number_of_faculty);
    output_faculty(info,number_of_faculty);
    return 0;
}

int input_faculty(faculty* info, int number_of_faculty)
{
    int number_of_speciality=0;
    int number_of_student=0;
    int number_of_marks=0;
    while(number_of_faculty<3)
    {
        printf("Enter name %d faculty to complete the entry, press 'exit':",number_of_faculty+1);
        fflush(stdin);
        gets(info[number_of_faculty].name);
        if(!(strcmp(info[number_of_faculty].name,"exit"))) break;
        else
        {   
            while(number_of_speciality<5)
            {
                printf("Enter name %d speciality faculty %s to complete the entry, press 'exit':",number_of_speciality+1, info[number_of_faculty].name);
                fflush(stdin);
                gets( info[number_of_faculty].sp[number_of_speciality].name);
                if(!(strcmp(info[number_of_faculty].sp[number_of_speciality].name,"exit"))) 
                {
                    info[number_of_faculty].number_of_speciality=number_of_speciality; 
                    number_of_speciality=0;
                    break;
                }
                else
                {
                    while(number_of_student<30)
                    {
                        printf("Enter surname studentov by speciality  %s to complete the entry, press 'exit':", info[number_of_faculty].sp[number_of_speciality].name);
                        fflush(stdin);
                        gets(info[number_of_faculty].sp[number_of_speciality].st[number_of_student].name);
                        if(!(strcmp(info[number_of_faculty].sp[number_of_speciality].st[number_of_student].name,"exit"))) 
                        {   info[number_of_faculty].sp[number_of_speciality].number_of_student=number_of_student;
                            number_of_student=0;
                            break;
                        }
                        else
                        number_of_student++;
                    }
                    number_of_speciality++;
                }
                
             }
             number_of_faculty++;
         }
        
    }
    return number_of_faculty;
}

void output_faculty(faculty* info,int number_of_faculty)
{
   int i,j,m;
   for(i=0;i<number_of_faculty;i++)
       for(j=0;j<info[i].number_of_speciality;j++)
           for(m=0;m<info[i].sp[j].number_of_student;m++)
               puts(info[i].sp[j].st[m].name);
}


