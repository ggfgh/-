#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
 
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100	//顺序表可能达到的最大长度
 
typedef int Status;	//Status 是函数返回值类型，其值是函数结果状态代码。
 
typedef struct
{
    char no[8];
    char name[20];
    int price;
} Book;
 
typedef Book ElemType;
 
typedef struct
{
    ElemType *elem;	//存储空间的基地址
    int length;	    //当前长度
} BookList;
 
void input(ElemType *e)
{
    printf("图书编号:");
    scanf("%s",e->no);
    printf("图书名称:");
    scanf("%s",e->name);
    printf("价格<100:");
    scanf("%d",&e->price);
    printf("***OK***\n\n");
}
 
void output(ElemType *e)
{
    printf("图书编号：%-10s 图书名称：%-10s  价格：%-10d\n\n", e->no, e->name, e->price);
}
 
Status InitList(BookList *bl) 	  //算法2.1 顺序表的初始化
{
    //构造一个空的顺序表L
    bl->elem=malloc(sizeof(ElemType)*MAXSIZE);	    //为顺序表分配一个大小为MAXSIZE的数组空间
    if(!bl->elem)
        exit(OVERFLOW);		//存储分配失败
    bl->length=0;	  //空表长度为0
    return OK;
}
 
int LocateElem_Sq(BookList *bl,ElemType e) 	//算法2.3 顺序表的查找
{
    //顺序表的查找
    int i;
    for(i=0; i<bl->length; i++)
        if(!strcmp(bl->elem[i].name,e.name))
            return i+1;
    return 0;
}
 
Status InsertElem(BookList *bl,int i,ElemType e)      //算法2.4 顺序表的插入
{
    //在顺序表L中第i个位置之前插入新的元素e
    //i值的合法范围是1<=i<=bl.length+1
    int k;
    if(i<1 || i>bl->length+1)
        return ERROR;	//i值不合法
    if(bl->length==MAXSIZE)
        return ERROR;	 //当前存储空间已满
    for(k=bl->length-1; k>=i-1; k--)
        bl->elem[k+1]=bl->elem[k];	//插入位置及之后的元素后移
    bl->elem[i-1]=e;	 //将新元素e放入第i个位置
    ++bl->length;									//表长增1
    return OK;
}
 
Status DeleteElem(BookList *bl,char *i,char *e)      //算法2.5 顺序表的删除
{
    int k=0;
    while(k<bl->length && strcmp(bl->elem[k].no,i))
        k++;
    if (k!=bl->length)
    {
        strcpy(e,bl->elem[k].name);
        for(; k<=bl->length; k++)
            bl->elem[k]=bl->elem[k+1];
    }
    else
        return ERROR;
    --bl->length;	//表长减2
    return OK;
}
 
void menu()
{
	printf("         ****** 图书信息管理系统 ******       \n\n");
	printf("主菜单：\n");
	printf("  1.建立顺序表             ");printf("2.输入图书信息\n");
	printf("  3.查找                   ");printf("4.插入\n");
	printf("  5.删除                   ");printf("6.输出图书信息\n");
	printf("  7.退出\n\n");
}
 
int main()
{
    BookList bl;
    int i,temp,a,choice,x;
    ElemType b,e;
    char res[20],c[10];
    menu();
    choice=-1;
    while(choice!=7)
    {
        printf("请选择功能:");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:        //创建顺序表
            if(InitList(&bl))
                printf("成功建立顺序表\n\n");
            else
                printf("顺序表建立失败\n\n");
            break;
        case 2:
            printf("请输入图书数量<100:");
            scanf("%d",&x);
            for(i=0; i<x; i++)
            {
                printf("第%d种:\n",i+1);
                input(&bl.elem[i]);
            }
            bl.length=x;
            putchar('\n');
            break;
        case 3:		//顺序表的查找
            printf("请输入所要查找的图书名称:");
            scanf("%s",e.name);
            temp=LocateElem_Sq(&bl,e);
            if(temp!=0)
            {
                printf("%s是第%d种图书.\n\n",e.name,temp);
                printf("该图书信息如下：\n");
                output(&bl.elem[temp-1]);
            }
            else
                printf("查找失败！没有这种图书，检查是否输入正确\n\n");
            break;
        case 4:		//顺序表的插入
            printf("请输入一个数，代表插入的位置:");
            scanf("%d",&a);
            printf("请输入所要插入图书的信息:\n");
            printf("图书编号:");
            scanf("%s",b.no);
            printf("图书名称:");
            scanf("%s",b.name);
            printf("价格:");
            scanf("%d",&b.price);
            if(InsertElem(&bl,a,b))
                printf("插入成功.\n\n");
            else
                printf("插入失败.\n\n");
            break;
        case 5:		//顺序表的删除
            printf("请输入所要删除的图书编号:");
            scanf("%s",c);
            if(DeleteElem(&bl,c,res))
                printf("删除成功.\n被删除的图书是:%s\n\n",res);
            else
                printf("删除失败.\n\n");
            break;
        case 6:		//顺序表的输出
            printf("当前图书总数为：%d\n",bl.length);
            printf("当前顺序表为:\n");
            for(i=0; i<bl.length; i++)
                output(&bl.elem[i]);
            printf("\n");
            break;
        case 7:
            printf("********************************END************************************\n");
            break;
        }
    }
    return 0;
}
