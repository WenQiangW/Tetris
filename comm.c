/*************************************************************************
	> File Name: comm.c
	> Author: WenQiang
	> Mail: wenqiangw1208@gmail.com
	> Created Time: Fri 10 Mar 2017 11:25:30 AM PST
 ************************************************************************/

#include "comm.h"

static int comm_sems(int which,int flags)
{
	key_t key = ftok(PATHNAME,PROJ_ID);
	int semid = semget(key,which,flags);
	if(semid < 0)
	{
		perror("semget");
	}
	return semid;
}
int create_sems(int which)
{
	return comm_sems(which,IPC_CREAT|IPC_EXCL|0666);
}
int get_sem()
{
	return comm_sems(0,IPC_CREAT);
}
int init_sem(int semid,int which)
{
	my_semun semun;
	semun.val = 1;
	if(semctl(semid,which,SETVAL,semun)< 0)
	{
		perror("Init_sem");
		return -1;
	}
	return 0;
}
int destory_sem(int semid)
{
	if(semctl(semid,0,IPC_RMID,NULL) < 0)
	{
		perror("destory");
		return -1;
	}
	return 0;
}
static int comm_op(int semid,int which,int _op)
{
	struct sembuf mysembuf;
	mysembuf.sem_num = which;
	mysembuf.sem_op = _op;
	mysembuf.sem_flg = 0;
	return semop(semid,&mysembuf,1);
}
int P(int semid)
{
	return comm_op(semid,0,-1);
}
int V(int semid)
{
	return comm_op(semid,0,1);
}
