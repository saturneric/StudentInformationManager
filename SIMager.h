//
//  SIMager.h
//  SIManager
//
//  Created by Eric on 15-8-16.
//  Copyright (c) 2015年 Eric. All rights reserved.
//

#ifndef SIManager_SIMager_h
#define SIManager_SIMager_h

#include   <stdio.h>
#include   <stdlib.h>
#include   <time.h>
#include   <string.h>
#include   <time.h>

#define MAX_NUM 64
#define PASSED_MAX 12
#define WEIGHT_LENGTH_SQUARE 50
#define HEIGHT_LENGTH_SQUARE 4
#define MENU_NUM 4
#define MENU_WEIGHT 3
#define MENU_COMTEST 3
#define MENU_1 "1.Add Students Information"
#define MENU_2 "2.Search Students Information"
#define MENU_3 "3.Delete Students Information"
#define MENU_4 "4.Change Password"

//SYSTEM DIFFERENT (WINNDOWS: Clear = Cls)
#define CLEAR system("clear");

struct _students{
    char name[12];
    char class[6];
    char year[6];
    char number[28];
};
struct student{
    struct _students stu_info;
    struct student *next;
    struct student *front;
} students;

typedef struct student stuc;

void start_printf (int menu_number, char *MENU[]);
int add_info (int const max_count);

int search_info_menu(void);
stuc *search_info_read(void);
stuc *search_info_name(stuc *head);
stuc *search_info_class(stuc *head);
stuc *search_info_year(stuc *head);
stuc *search_info_number(stuc *head);
int delete_info_printf(stuc *head, stuc *r_head);
int search_info_printf(stuc *head);

int delete_data_menu (void);
void passwd_set (void);
void passwd_pass (void);
void menu_main (void);
char choice (char *string);

#endif
