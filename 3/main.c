
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "string.h"
#include "stdlib.h"
typedef struct data {//
    char name[30];
    char surname[30];
    char gender[30];
    char occupation[30];
    char salary[30];
} data;
void printdata(data *struc) {//функция вывода строки
    printf("%s\n",struc->name);
    printf("%s\n",struc->surname);
    printf("%s\n",struc->gender);
    printf("%s\n",struc->occupation);
    printf("%s\n",struc->salary);
}
int comparator1(const void* p0, const void* p1)//операторы сравнения
{
    struct data* ps0 = (struct data*) p0;
    struct data* ps1 = (struct data*) p1;
    return strcmp( ps0->name, ps1->name);
}
int comparator2(const void* p0, const void* p1)
{
    struct data* ps0 = (struct data*) p0;
    struct data* ps1 = (struct data*) p1;
    return strcmp( ps0->surname, ps1->surname);
}
int comparator3(const void* p0, const void* p1)
{
    struct data* ps0 = (struct data*) p0;
    struct data* ps1 = (struct data*) p1;
    return strcmp( ps0->gender, ps1->gender);
}
int comparator4(const void* p0, const void* p1)
{
    struct data* ps0 = (struct data*) p0;
    struct data* ps1 = (struct data*) p1;
    return strcmp( ps0->occupation, ps1->occupation);
}
int comparator5(const void* p0, const void* p1)
{
    struct data* ps0 = (struct data*) p0;
    struct data* ps1 = (struct data*) p1;
    return strcmp( ps0->salary, ps1->salary);
}
int main() {
    char path[100]="data.csv";
    FILE *file = fopen(path, "r");//открываем файл для заполнения массива
    assert(file != NULL);
    char line[100];
    int n=0;
    while (fgets(line, sizeof(line), file) != NULL) {
        n++;
    }
    fclose(file);
    file = fopen(path, "r");
    data* arr=malloc(n*sizeof(data));
    int i=0;
    fgets(line, sizeof(line), file);
    while (fgets(line, sizeof(line), file) != NULL) {//копируем все данные в массив
        strcpy(arr[i].name,strtok(line, ",\""));
        strcpy(arr[i].surname,strtok(NULL, ",\""));
        strcpy(arr[i].gender,strtok(NULL, ",\""));
        strcpy(arr[i].occupation,strtok(NULL, ",\""));
        strcpy(arr[i].salary,strtok(NULL, ",\""));
        i++;
    }
    fclose(file);
    printf("enter mode(1-name,2-surname,3-gender, 4-occupation, 5-salary):");
    int mode=0;
    scanf("%d",&mode);
    switch (mode)
    {//меню для выбора столбца сортьировки
        case 1:
            qsort(arr, n, sizeof(data),comparator1);
            break;
        case 2:
            qsort(arr, n, sizeof(data),comparator2);
            break;
        case 3:
            qsort(arr, n, sizeof(data),comparator3);
            break;
        case 4:
            qsort(arr, n, sizeof(data),comparator4);
            break;
        case 5:
            qsort(arr, n, sizeof(data),comparator5);
            break;
        default:
            break;
    }
    for (int j=0;j<n;j++){
        printdata(arr + j);//вывод массива в консоль
        printf("\n");
    }
    remove ("path");
    FILE *f = fopen(path, "w");
    if (f == NULL) return -1;
    fprintf(f, "\"First Name\",\"Last Name\",\"Gender\",\"Occupation\",\"Salary\"");
    for (int j=0;j<n;j++) {
        fprintf(f, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n", arr[j].name, arr[j].surname, arr[j].gender,arr[j].occupation,arr[j].salary); //вывод массива в файл
    }
    fclose(f);
    free(arr);
}