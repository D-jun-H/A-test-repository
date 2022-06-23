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
        printf("���������ѡ�");
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
    printf("1)�������Ӽ�������һ��ѧ����Ϣ\n");
    printf("2)���ң�����ѧ�Ų���ѧ��\n");
    printf("3)��ȡ����ȡ����ѧ����Ϣ\n");
    printf("4)���棺��������ѧ����Ϣ\n");
    printf("5)�˳����˳�ѧ������ϵͳ\n");
}

void getStars()
{
    puts(Stars);
}


void InsertStu()
{
    int j;

    fp=fopen("D:\\ѧ������ϵͳ.dat","a");
    fseek(fp,0L,SEEK_END);

    printf("\n������ѧ����Ϣ:\nѧ��:");
    scanf("%d%*c",&student.number);
    printf("����:");
    scanf("%s%*c",student.name);
    printf("�Ա�1�����У�0����Ů��:");
    scanf("%d%*c",&student.sex);
    printf("���������������ĳɼ�:");
    for(j=0;j<5;j++){
        scanf("%lf",&student.score[j]);
    }
    fwrite(&student,sizeof(struct STU),1,fp);
    printf("������!\n");
    fclose(fp);
}

void Check()
{
    int k,i=0;
    int size=0;
    char Check1[20],Check2[20];

    fp=fopen("D:\\ѧ������ϵͳ.dat","r");
    fseek(fp,0,SEEK_END);
    size=ftell(fp);
    rewind(fp);
    printf("��������Ҫ����ѧ����ѧ�Ż�����:");
    scanf("%s",Check1);
    while(!feof(fp))
    {
        fseek(fp,(long)(sizeof(struct STU)*i),SEEK_SET);
        i++;
        fread(&student,sizeof(struct STU),1,fp);
        sprintf(Check2,"%d",student.number);
        if(strcmp(Check1,Check2)==0||strcmp(Check1,student.name)==0){
            printf("ѧ��            ����            �Ա�     �ɼ�\n");
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
         printf("û�����ѧ����\n");
    }
    fclose(fp);
}

void Read()
{
         int ret1,k;

         fp=fopen("D:\\ѧ������ϵͳ.dat","r");
         printf("ѧ��            ����           �Ա�     �ɼ�\n");
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

    fp1=fopen("D:\\ѧ����Ϣ.txt","w");
    fp2=fopen("D:\\ѧ������ϵͳ.dat","r");
    fseek(fp2,0L,SEEK_END);
    size=ftell(fp2);
    rewind(fp2);
    fprintf(fp1,"����%d��ѧ������Ϣ�����룡\n\n",size/(int)(sizeof(struct STU)));
    fprintf(fp1,"%s","ѧ��            ����            �Ա�     �ɼ�\n");
    printf("���ڴ浵�С���:\n");
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
    printf("����ɹ���\n");
}
