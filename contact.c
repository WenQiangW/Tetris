#include "contact.h"

void load_data(Pcon pcon) //从文件中读取
{
	PeoInfo peo;
	FILE *pfread = fopen("aaa","r");
	if (pfread == NULL)
	{
		perror("open for read");
		return;
	}
	while (fread(&peo,sizeof(PeoInfo),1,pfread))
	{
		check_capacity(pcon);
		pcon->peoinfo[pcon->size] = peo;
		pcon->size++;
	}
	fclose(pfread);
}
void save_data(Pcon pcon)//保存数据到文件中
{
	int i = 0;
	FILE *pfwrite = fopen("aaa", "w");
	if (pfwrite == NULL)
	{
		perror("open for write");
		return;
	}
	for (i = 0; i< pcon->size; i++)
	{
		fwrite(&(pcon->peoinfo[i]), sizeof(PeoInfo), 1, pfwrite);
	}
	fclose(pfwrite);
}
void init(Pcon pcon) //初始化
{
	pcon->peoinfo = (PeoInfo *)malloc(sizeof(PeoInfo)*INIT_NUM);
	if (pcon->peoinfo == NULL)
	{
		perror("初始化");
		exit(EXIT_FAILURE);
	}
	memset(pcon->peoinfo, 0, INIT_NUM*sizeof(PeoInfo));
	pcon->capacity = INIT_NUM;
	pcon->size = 0;
	load_data(pcon);
}
void check_capacity(Pcon pcon) //检查是否需要扩容
{
	if (pcon->size == pcon->capacity)
	{
		int sz = pcon->capacity + INIT_NUM;
		PeoInfo* tmp = (PeoInfo *)realloc(pcon->peoinfo, sz);
		//避免扩容失败
		if (pcon->peoinfo == NULL)
		{
			perror("再开辟失败！");
			return;
		}
		pcon->capacity += INIT_NUM;
		pcon->peoinfo = tmp;
	}
}
int find_name(Pcon pcon, const char *name)
{
	int i = 0;
	for (i = 0; i < pcon->size; i++)
	{
		if (strcmp(pcon->peoinfo[i].name, name) == 0)
			return i;
	}
	return -1;
}
void add_person(Pcon pcon)
{
	check_capacity(pcon);
	printf("输入联系人的姓名：");
	scanf("%s", pcon->peoinfo[pcon->size].name);
	printf("\n输入联系人的性别：");
	scanf("%s", pcon->peoinfo[pcon->size].sex);
	printf("\n输入联系人的年龄：");
	scanf("%d", &pcon->peoinfo[pcon->size].age);
	printf("\n输入联系人的电话：");
	scanf("%s", pcon->peoinfo[pcon->size].tele);
	printf("\n输入联系人的地址：");
	scanf("%s", pcon->peoinfo[pcon->size].addr);
	pcon->size++;
}

void del_person(Pcon pcon)
{
	char name[MAX_NAME];
	int index = 0;
	int start = 0;
	if (pcon->size == 0)
	{
		printf("联系人为空！\n");
		return;
	}
	printf("请输入姓名：");
	scanf("%s", name);
	index = find_name(pcon, name);
	if (index == -1)
	{
		printf("没有该联系人！\n");
		return;
	}
	for (start = index; start < pcon->size - 1; start++)
	{
		pcon->peoinfo[start] = pcon->peoinfo[start + 1];
	}
	pcon->size--;
	printf("删除成功 \n");
}
void find_person(Pcon pcon)
{
	char name[MAX_NAME];
	int index = 0;
	printf("请输入查找的姓名：");
	scanf("%s", name);
	index = find_name(pcon, name);
	if (index == -1)
	{
		printf("查找的人不存在\n");
	}
	else
	{
		printf("姓名：%s 性别：%s 年龄：%d 电话：%s 地址：%s\n",
			pcon->peoinfo[index].name, pcon->peoinfo[index].sex, pcon->peoinfo[index].age,
			pcon->peoinfo[index].tele, pcon->peoinfo[index].addr);
	}
}
void alter_person(Pcon pcon)
{
	char name[MAX_NAME];
	int index = 0;
	printf("请输入更改的姓名：");
	scanf("%s", name);
	index = find_name(pcon, name);
	if (index == -1)
	{
		printf("更改的人不存在\n");
	}
	else
	{
		printf("输入联系人的姓名：");
		scanf("%s", pcon->peoinfo[index].name);
		printf("\n输入联系人的性别：");
		scanf("%s", pcon->peoinfo[index].sex);
		printf("\n输入联系人的年龄：");
		scanf("%d", &pcon->peoinfo[index].age);
		printf("\n输入联系人的电话：");
		scanf("%s", pcon->peoinfo[index].tele);
		printf("\n输入联系人的地址：");
		scanf("%s", pcon->peoinfo[index].addr);
	}
}
void show_person(Pcon pcon)
{
	int i = 0;
	for (i = 0; i < pcon->size; i++)
	{
		printf("姓名：%s 性别：%s 年龄：%d 电话：%s 地址：%s\n",
			pcon->peoinfo[i].name, pcon->peoinfo[i].sex, pcon->peoinfo[i].age,
			pcon->peoinfo[i].tele, pcon->peoinfo[i].addr);
	}
}
void clear_person(Pcon pcon)
{
	pcon->size = 0;
}
void sort_name(Pcon pcon)
{
	int i = 0;
	int j = 0;
	PeoInfo tmp;
	for (i = 0; i < pcon->size - 1; i++)
	{
		for (j = i; j < pcon->size - 1; j++)
		{
			if (strcmp(pcon->peoinfo[j].name, pcon->peoinfo[j + 1].name)>0)
			{
				tmp = pcon->peoinfo[j];
				pcon->peoinfo[j] = pcon->peoinfo[j + 1];
				pcon->peoinfo[j + 1] = tmp;
			}
		}
	}
	printf("排序成功！\n");
	show_person(pcon);
}