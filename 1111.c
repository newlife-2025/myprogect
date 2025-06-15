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
void Import();  //��ȡԱ��������Ϣ
void Save();    //���湤����Ϣ
void Locate();  //��ѯ 
void Append();  //���� 
void Modify();  //�޸� 
void Delete();  //ɾ�� 
void display(); //��ʾ������Ϣ 
void show(struct employee temp);//��ʾ����Ա����Ϣ 
void Title();   //��ʾ��ͷ

void write_log(char* action) // ������־�ļ�
{
    FILE *log = fopen("��־.log", "a");
    if(!log) return;
    time_t now = time(NULL);
    fprintf(log, "[%s] %s\n", ctime(&now), action);
    fclose(log);
}

void Import()	//���ļ��ж�ȡԱ��������Ϣ		
{
	int n=0;
	struct employee temp;
	FILE *fp;
	if((fp=fopen("����.txt","r"))==NULL)
	{
		printf("can't open file!\n");
		return ;
	}
	while(fscanf(fp,"%s%s%d%d%d%d",temp.num,temp.name,&temp.base,&temp.bonus,&temp.fund,&temp.fine)!=EOF)
		emp[n++]=temp;
	NN=n;
	printf("������Ϣ��ȡ���!�� %d ��!\n",NN);

}

void Title()  //��ʾ��ͷ 
{
	printf("%-6s %-8s  %-10s %-7s %-7s %-7s\n","����","����","��������","����","�ۿ�"," ʵ������");
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

void Save()  //���� 
{
	FILE *fp;
	int i=0,k=0;
	if((fp=fopen("����.txt","w"))==NULL)
	{
		printf("can't open file!\n");
		return ;
	}
    while(i<NN)
	{
		fprintf(fp,"%-6s %-8s %-10d %-8d %-8d %-8d\n",emp[i].num,emp[i].name,emp[i].base,emp[i].bonus,emp[i].fund,emp[i].fine);
		i++;
	}
	printf("ϵͳ������Ϣ�ѱ���!�� %d ��!\n",NN);
	fclose(fp);
}

void display()  //ȫ����ʾ 
{
	char ch;
	int i,n=0;
	printf("\n\n");
	printf("ϵͳ����%d��Ա��������Ϣ\n",NN);
	printf("======================================================================");
	putchar('\n');
	Title();
	for(i=0;i<NN;i++)
	{
		show(emp[i]);
	}
	printf("======================================================================");
	printf("\n\n������Ϣ��ʾ���������س���������.....");
	getchar();
	system("cls");
	return ;
}


void Append()   //��� 
{
	struct employee temp;
	char ch='y',num[6];
	int i,flag;
	while(ch=='y'||ch=='Y')
	{
		printf("\n\n");
		flag=0;
		printf("����������Ա��������Ϣ\n\n");
		printf("���ţ� ");
		gets(num);
        for(i=0;i<NN;i++)
			if(strcmp(num,emp[i].num)==0) flag=1;
		if(!flag)
		{
			strcpy(temp.num,num);
			printf("������ ");
			gets(temp.name);
			printf("�������ʣ� ");
			scanf("%d",&temp.base);
			printf("������ ");
			scanf("%d",&temp.bonus);
			printf("�ۿ ");
			scanf("%d",&temp.fund);
			getchar();
			temp.fine=temp.base+temp.bonus-temp.fund;
			emp[i]=temp;
			NN++;
			Save();	
			char log_msg[50];
        	sprintf(log_msg, "����Ա��:%s", emp[i].num); // ��¼���Ӷ���
        	write_log(log_msg); //  ������־
			printf("�Ƿ����������Ϣ��y����n��:");
			scanf("%c",&ch);
			getchar();
			system("cls");
			continue;
		}
		else
		{
			printf("ϵͳ���й���Ϊ %s ��Ա��!�����±��!\n\n",num); 
			getchar();
			system("cls");
			return;
		}
	}
	return ;
}

void Locate()  //��ѯ 
{
	char name[8],num[6];
	int i,n=0,flag,ch;
	while(1)
	{
		flag=0;
		putchar('\n');
		printf("                 "); 
		printf("��ѯԱ����Ϣ\n");
		printf("======================================================================");
		putchar('\n');
		printf("                 "); 
		printf("1.�����ֲ�ѯ\n");
		printf("                 "); 
		printf("2.�����Ų�ѯ\n");
		printf("                 "); 
		printf("3.������һ��\n");
		printf("======================================================================"); 
		putchar('\n');
		printf("���������ѡ��1-3��:");
		scanf("%d",&ch);
		getchar();
		if(ch==1)
		{
			printf("������Ҫ���ҵ�������");
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
					printf("û���ҵ����ϵļ�¼��\n");
				char log_msg[50];
        		sprintf(log_msg, "����Ա��:%s", emp[i].name); // ��¼���Ҷ���
        		write_log(log_msg); //  ������־
				printf("\n�����������...");
				getchar();
				system("cls");
		}
		else if(ch==2)
		{
			printf("������Ҫ���ҵĹ��ţ�");
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
				printf("û���ҵ����ϵļ�¼��\n");
			char log_msg[50];
        	sprintf(log_msg, "����Ա��:%s", emp[i].num); // ��¼���Ҷ���
        	write_log(log_msg); // ? ������־
			printf("\n�����������...");
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

void Modify()  //�޸� 
{
	char num[6];
	int i,flag,ch;
	while(1)
	{
		flag=0;
		printf("��������޸�Ա�����ţ�");
		gets(num);
		for(i=0;i<NN;i++)
			if(strcmp(num,emp[i].num)==0) 
			{
				flag=1;
				break;
			}
		if(flag)
		{
			printf("��Ա����ϢΪ��\n");
			Title();
			show(emp[i]);
			printf("\n�������µ���Ϣ��\n");
			printf("������ ");
			gets(emp[i].name);
			printf("�������ʣ� ");
			scanf("%d",&emp[i].base);
			printf("������ ");
			scanf("%d",&emp[i].bonus);
			printf("�ۿ ");
			scanf("%d",&emp[i].fund);
			getchar();
			emp[i].fine=emp[i].base+emp[i].bonus-emp[i].fund;
			printf("�޸ĺ����Ϣ����:\n");
			show(emp[i]);
			Save();
			char log_msg[50];
        	sprintf(log_msg, "�޸�Ա��:%s", emp[i].num); // ��¼�޸Ķ���
			write_log(log_msg); // ������־
		}
		else
			printf("��Ա��������!\n");
		printf("�����޸�(y����n)?");
		ch=getchar();
		getchar();
		system("cls");
		if(ch!='Y' && ch!='y')  break; 
	}
}

void Delete()  //ɾ�� 
{
	char num[6];
	int i,j,flag,ch;
	while(1)
	{
		flag=0;
		printf("�������ɾ��Ա�����ţ�");
		gets(num);
		for(i=0;i<NN;i++)
			if(strcmp(num,emp[i].num)==0) 
			{
				flag=1;
				break;
			}
		if(flag)
		{
			printf("��Ա����ϢΪ��\n");
			Title();
			show(emp[i]);
			printf("ȷ��ɾ��(Y/N)?  ");
			ch=getchar();
			getchar();
			if(ch=='Y' || ch=='y') 
			{
				char log_msg[50];
        		sprintf(log_msg, "ɾ��Ա��:%s", emp[i].num); // ��¼ɾ������
        		write_log(log_msg); // ������־
				for(j=i;j<NN-1;j++)
				    emp[j]=emp[j+1];
				NN--;
				printf("ɾ���ɹ�!\n");
				getchar();
				system("cls");
				Save();
			}
			system("cls");
			break;
		}
		else
		{
			printf("��Ա��������!\n");
			getchar();
			system("cls");
			break;
		}
	}
}

//������ 
int main()
{
	int choice;
	Import();
	while(1)
	{
		printf("\n\n");
		printf("                            ");
		printf("���ʹ���ϵͳ\n");
		printf("======================================================================"); 
		putchar('\n');
		printf("                           ");
		printf("1.��ʾ������Ϣ\n");
		printf("                           ");
		printf("2.����������Ϣ\n");
		printf("                           ");
		printf("3.���ҹ�����Ϣ\n");
		printf("                           ");
		printf("4.�޸Ĺ�����Ϣ\n");
		printf("                           ");
		printf("5.ɾ��������Ϣ\n");
		printf("                           ");
		printf("6.�˳�\n");
		printf("======================================================================"); 
		putchar('\n');
		printf("���������ѡ��(1-6): ");
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
			printf("ллʹ��!\n");
			exit(0);
		default:
			system("cls");
			continue;
		}
	}
}