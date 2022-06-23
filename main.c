#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Stars "************************************"

FILE *fp;

void getMenu();
void getStars();
void InsertStu();
void Check();
void Read();
void Save();

struct STU
{
    int number;
    char name[20];
    int sex;
    double score[5];
}student;

int main()
{
    int index,ok=1;

    while(ok){
        getMenu();
        getStars();
        printf("请输入你的选项：");
        scanf("%d",&index);
        switch(index)
        {
            case 1:
                InsertStu();
                break;
            case 2:
                Check();
                break;
            case 3:
                Read();
                break;
            case 4:
                Save();
                break;
            case 5:
                ok=0;
                break;
        }
        getStars();
    }

    return 0;
}

void getMenu()
{
    printf("1)新增：从键盘输入一个学生信息\n");
    printf("2)查找：输入学号查找学生\n");
    printf("3)读取：读取所有学生信息\n");
    printf("4)保存：保存所有学生信息\n");
    printf("5)退出：退出学生管理系统\n");
}

void getStars()
{
    puts(Stars);
}


void InsertStu()
{
    int j;

    fp=fopen("D:\\学生管理系统.dat","a");
    fseek(fp,0L,SEEK_END);

    printf("\n请输入学生信息:\n学号:");
    scanf("%d%*c",&student.number);
    printf("姓名:");
    scanf("%s%*c",student.name);
    printf("性别（1代表男，0代表女）:");
    scanf("%d%*c",&student.sex);
    printf("请输入他（她）的成绩:");
    for(j=0;j<5;j++){
        scanf("%lf",&student.score[j]);
    }
    fwrite(&student,sizeof(struct STU),1,fp);
    printf("已输入!\n");
    fclose(fp);
}

void Check()
{
    int k,i=0;
    int size=0;
    char Check1[20],Check2[20];

    fp=fopen("D:\\学生管理系统.dat","r");
    fseek(fp,0,SEEK_END);
    size=ftell(fp);
    rewind(fp);
    printf("请输入你要查找学生的学号或姓名:");
    scanf("%s",Check1);
    while(!feof(fp))
    {
        fseek(fp,(long)(sizeof(struct STU)*i),SEEK_SET);
        i++;
        fread(&student,sizeof(struct STU),1,fp);
        sprintf(Check2,"%d",student.number);
        if(strcmp(Check1,Check2)==0||strcmp(Check1,student.name)==0){
            printf("学号            姓名            性别     成绩\n");
             printf("%-15d%-15s%-15d\t",student.number,student.name,student.sex);
            for(k=0;k<5;k++){
                printf("%.0lf ",student.score[k]);
            }
            printf("\n");
            break;
        }
    }
    if(i>size/(int)(sizeof(struct STU)))
    {
         printf("没有这个学生！\n");
    }
    fclose(fp);
}

void Read()
{
         int ret1,k;

         fp=fopen("D:\\学生管理系统.dat","r");
         printf("学号            姓名           性别     成绩\n");
         while(!feof(fp)){
            ret1=fread(&student,sizeof(struct STU),1,fp);
             if(ret1>0){
                 printf("%-15d%-10s%8d\t",student.number,student.name,student.sex);
                    for(k=0;k<5;k++){
                        printf("%.0lf ",student.score[k]);
                    }
                    printf("\n");
                }
            }
         printf("\n");
         fclose(fp);
}

void Save()
{
    FILE *fp1,*fp2;
    int i=0,k,ret1,size=0;

    fp1=fopen("D:\\学生信息.txt","w");
    fp2=fopen("D:\\学生管理系统.dat","r");
    fseek(fp2,0L,SEEK_END);
    size=ftell(fp2);
    rewind(fp2);
    fprintf(fp1,"共有%d个学生的信息被输入！\n\n",size/(int)(sizeof(struct STU)));
    fprintf(fp1,"%s","学号            姓名            性别     成绩\n");
    printf("正在存档中——:\n");
    while(!feof(fp2)){
        fseek(fp2,(long)(i*sizeof(struct STU)),SEEK_SET);
        i++;
        ret1=fread(&student,sizeof(struct STU),1,fp2);
        if(ret1>0){
            fprintf(fp1,"%-15d%-10s%8d\t",student.number,student.name,student.sex);
            for(k=0;k<5;k++){
                fprintf(fp1,"%.0lf ",student.score[k]);
                if(k==4){
                    fprintf(fp1,"%c",'\n');
                }
            }
        }
    }
    fclose(fp1);
    fclose(fp2);
    printf("保存成功！\n");
}
