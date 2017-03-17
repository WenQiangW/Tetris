

#ifndef __CONTACT_H__
#define __CONTACT_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME 20
#define MAX_SEX 10
#define MAX_TELE 10
#define MAX_ADDR 10
#define MAX 1000
#define INIT_NUM 5

typedef struct PeoInfo
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
}PeoInfo;

typedef struct Contact
{
	struct PeoInfo *peoinfo;
	int size;//实际个数
	int capacity;//容量
}Contact ,*Pcon;

void init(Pcon pcon);
void check_capacity(Pcon pcon);
int find_name(Pcon pcon, const char *name);
void add_person(Pcon pcon);
void del_person(Pcon pcon);
void find_person(Pcon pcon);
void alter_person(Pcon pcon);
void show_person(Pcon pcon);
void clear_person(Pcon pcon);
void sort_name(Pcon pcon);
void load_data(Pcon pcon);
void save_data(Pcon pcon);

#endif