#ifndef _COMM_H_
#define _COMM_H_

#include<stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>

#define PATHNAME "."
#define PROJ_ID 0x666
typedef union mysemun {
	        int val;    /* Value forSETVAL */
			struct semid_ds *buf;    /* Bufferfor IPC_STAT, IPC_SET */
			unsigned short  *array;  /* Array for GETALL, SETALL */
			struct seminfo  *__buf;  /* Buffer for IPC_INFO */
}my_semun;
//typedef struct sembuf
//{
//		unsigned short int sem_num; /* semaphore number */
//		short int sem_op;  /* semaphore operation */
//		short int sem_flg;  /* operation flag */
//}mysembuf;
int create_sems(int which);
int get_sem();
int init_sem(int semid,int which);
int destory_sem(int semid);
int P(int semid);
int V(int semid);
#endif
