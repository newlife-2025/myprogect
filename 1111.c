#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 100
int NN;
struct employee
{
	char num[6];
	char name[8];
	int base;
	int bonus;
	int fund;
	int fine;
}emp[N];
void Import();  //读取员工工资信息
void Save();    //保存工资信息
void Locate();  //查询 
void Append();  //新增 
void Modify();  //修改 
void Delete();  //删除 
void display(); //显示所有信息 
void show(struct employee temp);//显示单个员工信息 
void Title();   //显示表头

void write_log(char* action) // 生成日志文件
{
    FILE *log = fopen("日志.log", "a");
    if(!log) return;
    time_t now = time(NULL);
    fprintf(log, "[%s] %s\n", ctime(&now), action);
    fclose(log);
}

void Import()	//从文件中读取员工工资信息		
{
	int n=0;
	struct employee temp;
	FILE *fp;
	if((fp=fopen("工资.txt","r"))==NULL)
	{
		printf("can't open file!\n");
		return ;
	}
	while(fscanf(fp,"%s%s%d%d%d%d",temp.num,temp.name,&temp.base,&temp.bonus,&temp.fund,&temp.fine)!=EOF)
		emp[n++]=temp;
	NN=n;
	printf("工资信息读取完毕!共 %d 人!\n",NN);

}

void Title()  //显示表头 
{
	printf("%-6s %-8s  %-10s %-7s %-7s %-7s\n","工号","姓名","基本工资","津贴","扣款"," 实发工资");
}

void show(struct employee temp)
{
	printf("%-6s",temp.num);
	printf("%-8s ",temp.name);
	printf("  %-10d ",temp.base);
	printf("%-8d ",temp.bonus);
	printf("%-8d  ",temp.fund);	
	printf("%-8d\n",temp.fine);		

}

void Save()  //保存 
{
	FILE *fp;
	int i=0,k=0;
	if((fp=fopen("工资.txt","w"))==NULL)
	{
		printf("can't open file!\n");
		return ;
	}
    while(i<NN)
	{
		fprintf(fp,"%-6s %-8s %-10d %-8d %-8d %-8d\n",emp[i].num,emp[i].name,emp[i].base,emp[i].bonus,emp[i].fund,emp[i].fine);
		i++;
	}
	printf("系统工资信息已保存!共 %d 人!\n",NN);
	fclose(fp);
}

void display()  //全部显示 
{
	char ch;
	int i,n=0;
	printf("\n\n");
	printf("系统共有%d个员工工资信息\n",NN);
	printf("======================================================================");
	putchar('\n');
	Title();
	for(i=0;i<NN;i++)
	{
		show(emp[i]);
	}
	printf("======================================================================");
	printf("\n\n工资信息显示结束，按回车键键继续.....");
	getchar();
	system("cls");
	return ;
}


void Append()   //添加 
{
	struct employee temp;
	char ch='y',num[6];
	int i,flag;
	while(ch=='y'||ch=='Y')
	{
		printf("\n\n");
		flag=0;
		printf("请输入新增员工个人信息\n\n");
		printf("工号： ");
		gets(num);
        for(i=0;i<NN;i++)
			if(strcmp(num,emp[i].num)==0) flag=1;
		if(!flag)
		{
			strcpy(temp.num,num);
			printf("姓名： ");
			gets(temp.name);
			printf("基本工资： ");
			scanf("%d",&temp.base);
			printf("津贴： ");
			scanf("%d",&temp.bonus);
			printf("扣款： ");
			scanf("%d",&temp.fund);
			getchar();
			temp.fine=temp.base+temp.bonus-temp.fund;
			emp[i]=temp;
			NN++;
			Save();	
			char log_msg[50];
        	sprintf(log_msg, "增加员工:%s", emp[i].num); // 记录增加对象
        	write_log(log_msg); //  增加日志
			printf("是否继续输入信息（y或者n）:");
			scanf("%c",&ch);
			getchar();
			system("cls");
			continue;
		}
		else
		{
			printf("系统已有工号为 %s 的员工!请重新编号!\n\n",num); 
			getchar();
			system("cls");
			return;
		}
	}
	return ;
}

void Locate()  //查询 
{
	char name[8],num[6];
	int i,n=0,flag,ch;
	while(1)
	{
		flag=0;
		putchar('\n');
		printf("                 "); 
		printf("查询员工信息\n");
		printf("======================================================================");
		putchar('\n');
		printf("                 "); 
		printf("1.按名字查询\n");
		printf("                 "); 
		printf("2.按工号查询\n");
		printf("                 "); 
		printf("3.返回上一层\n");
		printf("======================================================================"); 
		putchar('\n');
		printf("请输入代码选择（1-3）:");
		scanf("%d",&ch);
		getchar();
		if(ch==1)
		{
			printf("请输入要查找的姓名：");
			gets(name);
			for(i=0;i<NN;i++)
				if(strcmp(emp[i].name,name)==0)
				{
					flag=1;
					putchar('\n');
					Title();
					show(emp[i]);
				}
				if(!flag)
					printf("没有找到符合的记录！\n");
				char log_msg[50];
        		sprintf(log_msg, "查找员工:%s", emp[i].name); // 记录查找对象
        		write_log(log_msg); //  增加日志
				printf("\n按任意键返回...");
				getchar();
				system("cls");
		}
		else if(ch==2)
		{
			printf("请输入要查找的工号：");
			gets(num);
			for(i=0;i<NN;i++)
			{
				if(strcmp(emp[i].num,num)==0)
				{
					flag=1;
					putchar('\n');
					Title();
					show(emp[i]);
				}
			}
			if(!flag)
				printf("没有找到符合的记录！\n");
			char log_msg[50];
        	sprintf(log_msg, "查找员工:%s", emp[i].num); // 记录查找对象
        	write_log(log_msg); // ? 增加日志
			printf("\n按任意键返回...");
			getchar();
			system("cls");
		}
		else if(ch==3)
		{
			system("cls");
			return;
		}
	}
}

void Modify()  //修改 
{
	char num[6];
	int i,flag,ch;
	while(1)
	{
		flag=0;
		printf("请输入待修改员工工号：");
		gets(num);
		for(i=0;i<NN;i++)
			if(strcmp(num,emp[i].num)==0) 
			{
				flag=1;
				break;
			}
		if(flag)
		{
			printf("该员工信息为：\n");
			Title();
			show(emp[i]);
			printf("\n请输入新的信息：\n");
			printf("姓名： ");
			gets(emp[i].name);
			printf("基本工资： ");
			scanf("%d",&emp[i].base);
			printf("津贴： ");
			scanf("%d",&emp[i].bonus);
			printf("扣款： ");
			scanf("%d",&emp[i].fund);
			getchar();
			emp[i].fine=emp[i].base+emp[i].bonus-emp[i].fund;
			printf("修改后的信息如下:\n");
			show(emp[i]);
			Save();
			char log_msg[50];
        	sprintf(log_msg, "修改员工:%s", emp[i].num); // 记录修改对象
			write_log(log_msg); // 增加日志
		}
		else
			printf("该员工不存在!\n");
		printf("继续修改(y或者n)?");
		ch=getchar();
		getchar();
		system("cls");
		if(ch!='Y' && ch!='y')  break; 
	}
}

void Delete()  //删除 
{
	char num[6];
	int i,j,flag,ch;
	while(1)
	{
		flag=0;
		printf("请输入待删除员工工号：");
		gets(num);
		for(i=0;i<NN;i++)
			if(strcmp(num,emp[i].num)==0) 
			{
				flag=1;
				break;
			}
		if(flag)
		{
			printf("该员工信息为：\n");
			Title();
			show(emp[i]);
			printf("确认删除(Y/N)?  ");
			ch=getchar();
			getchar();
			if(ch=='Y' || ch=='y') 
			{
				char log_msg[50];
        		sprintf(log_msg, "删除员工:%s", emp[i].num); // 记录删除对象
        		write_log(log_msg); // 增加日志
				for(j=i;j<NN-1;j++)
				    emp[j]=emp[j+1];
				NN--;
				printf("删除成功!\n");
				getchar();
				system("cls");
				Save();
			}
			system("cls");
			break;
		}
		else
		{
			printf("该员工不存在!\n");
			getchar();
			system("cls");
			break;
		}
	}
}

//主函数 
int main()
{
	int choice;
	Import();
	while(1)
	{
		printf("\n\n");
		printf("                            ");
		printf("工资管理系统\n");
		printf("======================================================================"); 
		putchar('\n');
		printf("                           ");
		printf("1.显示工资信息\n");
		printf("                           ");
		printf("2.新增工资信息\n");
		printf("                           ");
		printf("3.查找工资信息\n");
		printf("                           ");
		printf("4.修改工资信息\n");
		printf("                           ");
		printf("5.删除工资信息\n");
		printf("                           ");
		printf("6.退出\n");
		printf("======================================================================"); 
		putchar('\n');
		printf("请输入代码选择(1-6): ");
		scanf("%d",&choice);
		getchar();
		switch(choice)
		{
		case 1:
			display();
			break;
		case 2:
			Append();
			break;
		case 3:
			Locate();
			break;
		case 4:
			Modify();
			break;
		case 5:
			Delete();
			break;
		case 6:
			Save();
			printf("谢谢使用!\n");
			exit(0);
		default:
			system("cls");
			continue;
		}
	}
}