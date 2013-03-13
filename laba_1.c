#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct students{
    char name[256];
    int marks[25];
    int number_of_marks;
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
void search_excellent_student(faculty*,int);
void sorting_excellent_student(specialitys,int);
void output_list_of_sorting_specilitys(specialitys,int);

int main()
{
    faculty info[10];
    int number_of_faculty = 0;
    puts("Enter information about the university, to complete the entry, press 'exit'");
    number_of_faculty = input_faculty(info, number_of_faculty);
    search_excellent_student(info,number_of_faculty);
    return 0;
}

int input_faculty(faculty* info, int number_of_faculty)
{
    int number_of_speciality = 0;
    int number_of_student = 0;
    int number_of_marks = 0;
    while(number_of_faculty < 3)
    {
        printf("Enter name of %d faculty, to complete the entry, press 'exit':",number_of_faculty+1);
        fflush(stdin);
        gets(info[number_of_faculty].name);
        if(!(strcmp(info[number_of_faculty].name, "exit"))) break;
        else
        {   
            while(number_of_speciality < 5)
            {
                printf("Enter name %d speciality of faculty %s, to complete the entry, press 'exit':",number_of_speciality+1, info[number_of_faculty].name);
                fflush(stdin);
                gets( info[number_of_faculty].sp[number_of_speciality].name);
                if(!(strcmp(info[number_of_faculty].sp[number_of_speciality].name, "exit"))) 
                {
                    info[number_of_faculty].number_of_speciality = number_of_speciality; 
                    number_of_speciality = 0;
                    break;
                }
                else
                {
                    while(number_of_student < 30)
                    {
                        printf("Enter student's surname by speciality %s, to complete the entry, press 'exit':", info[number_of_faculty].sp[number_of_speciality].name);
                        fflush(stdin);
                        gets(info[number_of_faculty].sp[number_of_speciality].st[number_of_student].name);
                        if(!(strcmp(info[number_of_faculty].sp[number_of_speciality].st[number_of_student].name, "exit"))) 
                        {   info[number_of_faculty].sp[number_of_speciality].number_of_student = number_of_student;
                            number_of_student = 0;
                            break;
                        }
                        else
                        {
                            while(number_of_marks < 25)
                            {
                                printf("Enter student's marks  %s, to complete the entry, press '0':", info[number_of_faculty].sp[number_of_speciality].st[number_of_student].name);
                                scanf("%d",&info[number_of_faculty].sp[number_of_speciality].st[number_of_student].marks[number_of_marks]);
                                if(!(info[number_of_faculty].sp[number_of_speciality].st[number_of_student].marks[number_of_marks]))
                                {
                                    info[number_of_faculty].sp[number_of_speciality].st[number_of_student].number_of_marks = number_of_marks;
                                    number_of_marks = 0;
                                    break;
                                }
                            number_of_marks++;
                            }

                        }
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
   int i,number_of_speciality,number_of_student;
   for(i = 0; i < number_of_faculty; i++)
       for(number_of_speciality = 0; number_of_speciality < info[i].number_of_speciality; number_of_speciality++)
           for(number_of_student = 0; number_of_student < info[i].sp[number_of_speciality].number_of_student; number_of_student++)
               puts(info[i].sp[number_of_speciality].st[number_of_student].name);
}

void search_excellent_student(faculty* info,int number_of_faculty)
{
    char name_of_speciality[256];
    int number_of_excellent_student=0;
    int i, k, number_of_speciality, number_of_marks, quarter, ind=0, number_of_student;
    students std;
    specialitys input_specialitys;
    puts("Enter name of speciality for search excellnt students");
    fflush(stdin);
    gets(name_of_speciality);
        for(i = 0; i < number_of_faculty; i++)
            for(number_of_speciality = 0;number_of_speciality < info[i].number_of_speciality; number_of_speciality++)
                if(!(strcmp(info[i].sp[number_of_speciality].name,name_of_speciality)))
                    {
                       
                        for(number_of_student = 0;number_of_student < info[i].sp[number_of_speciality].number_of_student; number_of_student++)
                            for(k = number_of_student; k < info[i].sp[number_of_speciality].number_of_student; k++)
                            {
                                quarter = info[i].sp[number_of_speciality].st[k].number_of_marks * 0.25;
                                for(number_of_marks = 0; number_of_marks < info[i].sp[number_of_speciality].st[k].number_of_marks; number_of_marks++)
                                    {
                                        if(info[i].sp[number_of_speciality].st[k].marks[number_of_marks] < 4)
                                        { 
                                            ind = 1;
                                            quarter = 0;
                                            break;
                                        }                                
                                        else 
                                            if(info[i].sp[number_of_speciality].st[k].marks[number_of_marks] == 4) 
                                                ind++;
                                    }
                                if(ind <= quarter)
                                {
                                    std = info[i].sp[number_of_speciality].st[k];
                                    info[i].sp[number_of_speciality].st[k] = info[i].sp[number_of_speciality].st[number_of_student];
                                    info[i].sp[number_of_speciality].st[number_of_student] = std;
                                    number_of_excellent_student++;
                                    break;
                                }
                                else ind = 0;
                            }
                                          input_specialitys =  info[i].sp[number_of_speciality];
                        sorting_excellent_student( input_specialitys , number_of_excellent_student);
                        return;
                     }
                
}

void sorting_excellent_student(specialitys input_specialitys, int number_of_excellent_student)
{
    int i,j;
    students spesh;  
    for(i = 0; i < number_of_excellent_student-1; i++)
  	{
		for (j = i+1; j < number_of_excellent_student; j++)
		{			
			if (strcmp( input_specialitys.st[i].name,  input_specialitys.st[j].name) > 0)
			{
				spesh = input_specialitys.st[i];
				 input_specialitys.st[i] =  input_specialitys.st[j];
				 input_specialitys.st[j] = spesh;
			} 
		}
	}
    for(i = number_of_excellent_student; i <  input_specialitys.number_of_student -1; i++ )
        for (j = i+1; j <  input_specialitys.number_of_student; j++)
		{			
			if (strcmp(input_specialitys.st[i].name, input_specialitys.st[j].name) > 0)
			{
				spesh = input_specialitys.st[i];
				input_specialitys.st[i] = input_specialitys.st[j];
				input_specialitys.st[j] = spesh;
			} 
        }
     output_list_of_sorting_specilitys(input_specialitys, number_of_excellent_student);
     return;
}

void output_list_of_sorting_specilitys(specialitys input_specialitys, int number_of_excellent_student)
{
    int i;
    puts("The list of excellent students:");
    for(i = 0; i < number_of_excellent_student; i++)
        puts(input_specialitys.st[i].name);
    puts("The list other students:");
    for(i = number_of_excellent_student; i<input_specialitys.number_of_student;i++)
        puts(input_specialitys.st[i].name);
    return;
}
