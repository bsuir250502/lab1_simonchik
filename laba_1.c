#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdio_ext.h>
#define string_size 256

typedef struct students {
    char name[string_size];
    int marks[25];
    int number_of_marks;
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

char *my_gets(char *str, size_t strin_size)
{
    fgets(str, strin_size, stdin);
    str[strlen(str) - 1] = '\0';
    return str;
}

specialitys sorting_lists(specialitys spech, int num_of_excellent_stud);

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
        printf("Enter name %d speciality of faculty %s: ",
               num_of_spech + 1, info[num_of_fac].name);
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
            info[num_of_fac].sp[num_of_spech].number_of_student =num_of_stud;
            break;
        } 
        else
            num_of_stud++;
    }
}

void input_of_mark(faculty * info, int num_of_fac, int num_of_spech,int num_of_stud)
{
    printf("Enter marks, to complete the entry, press '0'\n");
    int num_of_mark = 0;
    while (num_of_mark < 25) {
        printf("Enter %d marks of %s: ", num_of_mark + 1,info[num_of_fac].sp[num_of_spech].st[num_of_stud].name);
        __fpurge(stdin);
        if (!scanf("%d", &info[num_of_fac].sp[num_of_spech].st[num_of_stud].marks[num_of_mark])) {
            printf("ERROR!!!, ENTER NUMBER\n");
            continue;
        }
        if (!info[num_of_fac].sp[num_of_spech].st[num_of_stud].marks[num_of_mark]) {
            info[num_of_fac].sp[num_of_spech].st[num_of_stud].number_of_marks = num_of_mark;
            break;
        } 
        else
            num_of_mark++;
    }
}

specialitys search_spech(faculty * info, int number_of_faculty, char *name_of_speciality)
{
    int i, j;
    for (i = 0; i < number_of_faculty; i++) {
        for (j = 0; j < info[i].number_of_speciality; j++) {
            if (!(strcmp(info[i].sp[j].name, name_of_speciality)))
                return info[i].sp[j];
        }
    }
    printf("ERROR!!!! there is no such specialty");
    exit(1);
}

int number_of_excellent_stud(specialitys spech)
{
    int num_of_excellent_stud = 0;
    int i, j, ind = 0, quarter;
    for (i = 0; i < spech.number_of_student; i++) {
        quarter = spech.st[i].number_of_marks * 0.25;
        for (j = 0; j < spech.st[i].number_of_marks; j++) {
            if (spech.st[i].marks[j] < 4) {
                ind = 1;
                quarter = 0;
                break;
            }
            else if (spech.st[i].marks[j] == 4)
                ind++;
        }
        if (ind <= quarter)
            num_of_excellent_stud++;
        else
            ind = 0;
    }
    return num_of_excellent_stud;
}

specialitys creating_lists(specialitys spech, int num_of_excellent_stud)
{
    int i = 0, j, k, ind = 0, quarter;
    students std;
    for (i = 0; i < spech.number_of_student - 1; i++) {
        for (j = i; j < spech.number_of_student; j++) {
            quarter = spech.st[j].number_of_marks * 0.25;
            for (k = 0; k < spech.st[j].number_of_marks; k++) {
                if (spech.st[j].marks[k] < 4) {
                    ind = 1;
                    quarter = 0;
                    break;
                }
                else if (spech.st[j].marks[k] == 4)
                    ind++;
            }
            if (ind <= quarter) {
                std = spech.st[j];
                spech.st[j] = spech.st[i];
                spech.st[i] = std;
                break;
            } else
                ind = 0;
        }
    }
    spech = sorting_lists(spech, num_of_excellent_stud);
    return spech;
}

specialitys sorting_lists(specialitys spech, int num_of_excellent_stud)
{
    int i, j;
    students stud;
    for (i = 0; i < num_of_excellent_stud - 1; i++) {
        for (j = i + 1; j < num_of_excellent_stud; j++) {
            if (strcmp(spech.st[i].name, spech.st[j].name) > 0) {
                stud = spech.st[i];
                spech.st[i] = spech.st[j];
                spech.st[j] = stud;
            }
        }
    }
    for (i = num_of_excellent_stud; i < spech.number_of_student - 1; i++) {
        for (j = i + 1; j < spech.number_of_student; j++) {
            if (strcmp(spech.st[i].name, spech.st[j].name) > 0) {
                stud = spech.st[i];
                spech.st[i] = spech.st[j];
                spech.st[j] = stud;
            }
        }
    }
    return spech;
}

void output_list_of_sorting_specilitys(specialitys spech,int num_of_excellent_stud)
{
    int i;
    printf("The list of excellent students of spechiality %s:\n",spech.name);
    for (i = 0; i < num_of_excellent_stud; i++)
        puts(spech.st[i].name);
    printf("The list other students of spechiality %s:\n", spech.name);
    for (i = num_of_excellent_stud; i < spech.number_of_student; i++)
        puts(spech.st[i].name);
}

int main()
{
    puts("Enter information about the university, to complete the entry, press 'exit'");
    faculty info[10];
    specialitys spech;
    int i, j, k, num_of_excellent_stud;
    int number_of_faculty = input_of_fac(info);
    for (i = 0; i < number_of_faculty; i++) {
        input_of_spech(info, i);
        for (j = 0; j < info[i].number_of_speciality; j++) {
            input_of_stud(info, i, j);
            for (k = 0; k < info[i].sp[j].number_of_student; k++) {
                input_of_mark(info, i, j, k);
            }
        }
    }
    char name_of_speciality[string_size];
    puts("Enter name of speciality for search excellnt students");
    __fpurge(stdin);
    my_gets(name_of_speciality, string_size);
    spech = search_spech(info, number_of_faculty, name_of_speciality);
    num_of_excellent_stud = number_of_excellent_stud(spech);
    spech = creating_lists(spech, num_of_excellent_stud);
    output_list_of_sorting_specilitys(spech, num_of_excellent_stud);
    return 0;
}
