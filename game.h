

// 预处理块
#ifndef __GAME_H__    // 防止重复game.h被重复引用
#define __GAME_H__
#define  LINE 3   // 行的大小
#define  ROWS 3   // 列的大小
#define _CRT_SECURE_NO_WARNINGS 1 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void init(char board[][ROWS]);

void print_board(char board[][ROWS]);

void p_game(char board[][ROWS]);

void npc_game(char board[][ROWS]);

char check_win(char board[][ROWS]);

int check_full(char board[][ROWS]);


#endif