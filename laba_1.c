#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdio_ext.h>

#define string_size 256
#define number_mark 4

typedef struct students {
    char name[string_size];
    int marks[number_mark];
} students;

typedef struct specialitys {
    char name[string_size];
    int number_of_student;
    struct students st[30];
} specialitys;

typedef struct faculty {
    char name[string_size];
    struct specialitys sp[5];
    int number_of_speciality;
} faculty;

char *my_gets(char *str, int strin_size)
{
    fgets(str, strin_size, stdin);
    str[strlen(str) - 1] = '\0';
    return str;
}

int input_number_mark(void)
{
    char num_mark[string_size];
    int num;
    while (1) {
        fgets(num_mark, string_size, stdin);
        num = atoi(num_mark);
        if (num <= 0) {
            printf("ERROR!!! ENTER NUMBER: ");
            continue;
        }
        break;
    }
    return num;
}

int input_of_fac(faculty * info)
{
    int num_of_fac = 0;
    while (num_of_fac < 3) {
        printf("Enter name of %d faculty: ", num_of_fac + 1);
        __fpurge(stdin);
        my_gets(info[num_of_fac].name, string_size);
        if (!(strcmp(info[num_of_fac].name, "exit"))) {
            info[num_of_fac].number_of_speciality = num_of_fac;
            break;
        }
            else
                num_of_fac++;
    }
    return num_of_fac;
}

void input_of_spech(faculty * info, int num_of_fac)
{
    int num_of_spech = 0;
    while (num_of_spech < 5) {
        printf("Enter name %d speciality of faculty %s: ",num_of_spech + 1, info[num_of_fac].name);
        my_gets(info[num_of_fac].sp[num_of_spech].name, string_size);
        if (!(strcmp(info[num_of_fac].sp[num_of_spech].name, "exit"))) {
            info[num_of_fac].number_of_speciality = num_of_spech;
            break;
        }
            else
                num_of_spech++;
    }
}

void input_of_stud(faculty * info, int num_of_fac, int num_of_spech)
{
    int num_of_stud = 0;
    while (num_of_stud < 30) {
        printf("Enter name %d student of spechialyti %s: ",num_of_stud + 1, info[num_of_fac].sp[num_of_spech].name);
        __fpurge(stdin);
        my_gets(info[num_of_fac].sp[num_of_spech].st[num_of_stud].name,string_size);
        if (!(strcmp(info[num_of_fac].sp[num_of_spech].st[num_of_stud].name,"exit"))) {
            info[num_of_fac].sp[num_of_spech].number_of_student = num_of_stud;
            break;
        }   
            else
                num_of_stud++;
    }
}

void input_of_mark(faculty * info, int num_of_fac, int num_of_spech,int num_of_stud)
{

    int num_of_mark = 0;
    while (num_of_mark < number_mark) {
        printf("Enter %d marks of %s: ", num_of_mark + 1,info[num_of_fac].sp[num_of_spech].st[num_of_stud].name);
        __fpurge(stdin);
        info[num_of_fac].sp[num_of_spech].st[num_of_stud].marks[num_of_mark] = input_number_mark();
        num_of_mark++;
    }
}

specialitys search_spech(faculty * info, int num_of_fac)
{
    char name_of_speciality[string_size];
    int i, j;
    while (1) {
        puts("Enter name of speciality for search excellnt students");
        __fpurge(stdin);
        my_gets(name_of_speciality, string_size);
        for (i = 0; i < num_of_fac; i++) {
            for (j = 0; j < info[i].number_of_speciality; j++) {
                if (!(strcmp(info[i].sp[j].name, name_of_speciality)))
                    return info[i].sp[j];
            }
        }
        printf("ERROR,INCCORECT INPUT\n");
    }
}

int compare_students_by_name(const void *a, const void *b)
{
    students *pa = (students *) a;
    students *pb = (students *) b;
    return strcmp(pa->name, pb->name);
}

specialitys sorting_list(specialitys spech)
{
     qsort(&(spech.st[0]), spech.number_of_student, sizeof(students),compare_students_by_name);
     return spech;
}

int check_marks(students st)
{
    int i = 0; int ind = 0;
    int quarter = number_mark * 0.25;
    for(i=0;i<number_mark;i++){
        if (st.marks[i] < 4) {
                ind = 1;
                quarter = 0;
                break;
            } else if (st.marks[i] == 4)
                ind++;
        }
    return ind-quarter;
}

void output_lists(specialitys spech)
{
    int i , ind = 0;
    printf("The list of excellent students of spechiality %s: \n",spech.name);
    for (i = 0; i < spech.number_of_student; i++) {
        ind = check_marks(spech.st[i]);
        if(ind<0){
            puts(spech.st[i].name);
        }
    }
    printf("The list of other students of spechiality %s: \n", spech.name);
    for (i = 0; i < spech.number_of_student; i++) {
        ind = check_marks(spech.st[i]);
        if(ind>=0){
            puts(spech.st[i].name);
        }
    }
}


int main()
{   
    faculty info[3];
    specialitys spech;
    int i, j, k,number_of_faculty;
    puts("Enter information about the university, to complete the entry, press 'exit'");
    number_of_faculty = input_of_fac(info);
    for (i = 0; i < number_of_faculty; i++) {
        input_of_spech(info, i);
        for (j = 0; j < info[i].number_of_speciality; j++) {
            input_of_stud(info, i, j);
            for (k = 0; k < info[i].sp[j].number_of_student; k++) {
                input_of_mark(info, i, j, k);
            }
        }
    }
    spech = search_spech(info, number_of_faculty);
    spech = sorting_list(spech);
    output_lists(spech);
    return 0;
}
