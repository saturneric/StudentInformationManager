//
//  main.c
//  SIManager
//
//  Created by Eric on 15-7-6.
//  Copyright (c) 2015年 Eric. All rights reserved.
//

#include "SIMager.h"

int main(int argc, const char * argv[]) {
    CLEAR    passwd_pass();
    
    return 0;
}

//PAINT MENU
void start_printf (int menu_number, char *MENU[]){
    
    for (int i = 0; i < WEIGHT_LENGTH_SQUARE; i++) printf("■");
    printf("\n");
    for (int i = 0; i < menu_number; i++ ){
        printf("■");
        for (int j = 0; j<MENU_WEIGHT; j++) printf(" ");
        printf("%s ",*(MENU+i));
        unsigned long length = strlen(*(MENU+i));
        for (int j = 0; j < (WEIGHT_LENGTH_SQUARE - (MENU_WEIGHT + length + 3)); j++) printf(" ");
        printf("■\n");
    }
    for (int i = 0; i < WEIGHT_LENGTH_SQUARE; i++) printf("■");
    printf("\n");
}

//MAIN MENTU PAINT CONTROL
void menu_main (void){
    
    char *MENU[MENU_NUM] = {
        MENU_1,
        MENU_2,
        MENU_3,
        MENU_4,
    };
    while (1){
    int ifnot = 1;
    start_printf(4, MENU);
    while (ifnot == 1){
        char choices = choice("Please input the number (q to quit): ");
        int num_stu=0;
        switch (choices) {
            case '1':
                printf("How many students: ");
                scanf("%d",&num_stu);
                CLEAR                add_info(num_stu);
                ifnot = 0;
                break;
            case '2':
                CLEAR                search_info_menu();
                ifnot = 0;
                break;
            case '3':
                CLEAR                delete_data_menu();
                ifnot = 0;
                break;
            case '4':
                CLEAR                passwd_set();
                ifnot = 0;
                break;
            case 'q':
                exit(0);
                break;
                
            default:
                printf("Wrong,try again!\n");
                break;
        }
        
    }
       CLEAR    }
    
}

//RETURN THE CHOICS OF USER
char choice (char *string){
    printf("%s: ",string);
    char first_choice[MAX_NUM] ,choice = '0';
    scanf("%s",first_choice);
    choice = first_choice[0];
    if (first_choice[1] != '\0') return 'E';
    return choice;
}

//DEAL WITH PASSWORD
void passwd_pass (void){
    char *LOGIN_MENU[] = {
        "                 LOGIN",
    };
    start_printf(1, LOGIN_MENU);
    int count = 0, c_count = 3;
    char passwd[12];
    for (int i = 0; i < 12; i++) passwd[i] = 0;
    while (c_count > 0){
        count = 0;
        printf("Input the password (Chance :  %d) : ",c_count);
        char temp = '0';
        while ((count < PASSED_MAX)&& (temp != '\n')){
            passwd [count] = getchar();
            temp = passwd [count];
            count++;
        }
        passwd[--count] = '\0';
        int pass = 0;
        char r_passwd[12];
        FILE *fp = fopen("passwd.db", "r");
        fscanf(fp,"%s",r_passwd);
        fclose(fp);
        if (strcmp(passwd,r_passwd) == 0) pass =1;
        if (pass == 1){
            CLEAR            menu_main();
            break;
        }
        else {
            printf("Wrong,try again!\n");
            c_count--;
        }
    }
}

//ADD STUDENTS INFO
int add_info (int const max_count){
    int *count = (int*) malloc(sizeof(int));
    int w_ifnot = 0;
    stuc *head = NULL;
    *count = 1;
    stuc *stu = NULL, *stu_last = NULL;
    struct _students *stu_s;
    while((*count) <= max_count){
        w_ifnot = 0;
        for (int i = 0; i < 20-(*count % 10); i++ ) printf("■");
        printf("[ %d ] of [ %d ]",*count,max_count);
        for (int i = 0; i < 20-(*count % 10); i++ ) printf("■");
        printf("\n");
        char u_name[12],u_class[6],u_year[6],u_number[28] = "";
        printf("NAME: ");
        scanf("%s",u_name);
        printf("CLASS: ");
        scanf("%s",u_class);
        printf("YEAR: ");
        scanf("%s",u_year);
        int int_uname = (int)u_name[0], int2_uname = (int)u_name[1];
        char u1_name[4] = {'0','0','0','\0'}, u2_name[4] = {'0','0','0','\0'};
        char c_rand[4]={'0','0','0','\0'};
        for (int i = 2; i >= 0;i--){
            u1_name[i] = (int_uname%10)+48;
            int_uname/=10;
        }
        for (int i = 2; i >= 0;i--){
            u2_name[i] = (int2_uname%10)+48;
            int2_uname/=10;
        }
        
        srand((unsigned int)time(0));
        int int_rand = (rand()%1000);
        for (int i = 2; i >= 0;i--){
            c_rand[i] = (int_rand%10)+48;
            int_rand/=10;
        }
        strcat(u_number, u_year);
        strcat(u_number, u_class);
        strcat(u_number, u1_name);
        strcat(u_number, u2_name);
        strcat(u_number, c_rand);
        
        printf("NUMBER: %s\n",u_number);
        for (int i = 0; i < WEIGHT_LENGTH_SQUARE+2; i++ ) printf("■");
        printf("\n");
        printf("YES?(y or n): ");
        char yon = 'y';
        getchar();
        scanf("%c",&yon);
        switch (yon) {
            case 'y':
                w_ifnot = 1;
                break;
            case '\n':
                w_ifnot = 1;
                break;
            default:
                w_ifnot = 0;
                break;
        }
        if (w_ifnot == 1){
            stu = (stuc*) malloc(sizeof(stuc));
            stu_s = &stu->stu_info;
            strcpy(stu_s->name,u_name);
            strcpy(stu_s->class,u_class);
            strcpy(stu_s->year,u_year);
            strcpy(stu_s->number,u_number);
            (*count)++;
        }
        if ((head == NULL) && (w_ifnot == 1)){
            head = stu;
            stu_last = head;
        }
        else if ((head != NULL) && (w_ifnot == 1)){
            stu_last->next = stu;
            stu_last = stu;
            if(*count == max_count) stu->next = NULL;
            }
            CLEAR    }
    
    stu = head;
    FILE *fp;
    fp = fopen("stuinfo.db", "a+");
    if (fp == NULL) {
        printf("ERROR IN OPEN FILE!");
        return -1;
    }
    for (int i = 0; i < max_count; i++){
        stu_s = &stu->stu_info;
        fprintf(fp, "%s\n",stu_s->name);
        fprintf(fp, "%s\n",stu_s->class);
        fprintf(fp, "%s\n",stu_s->year);
        fprintf(fp, "%s\n",stu_s->number);
        stu = stu->next;
    }
    
    
    fclose(fp);
    free(count);
    //内存泄漏问题();
    
    //
    count = NULL;
    printf("Done,any key to continue...\n");
    getchar();getchar();
    
    return 0;
 
 }

//MENU OF SEARCH
int search_info_menu(){
    
    char *SEARCH_MENU[5] = {
        "                 SEARCH",
        "1.NAME",
        "2.CLASS",
        "3.YEAR",
        "4.NUMBER",
    };
    start_printf(5, SEARCH_MENU);
    int ifnot = 1;
    stuc *head, *s_head;
    while (ifnot){
        char choices = choice("Choose the number (q to quit): ");
        switch(choices){
            case '1':
                head = search_info_read();
                s_head = search_info_name(head);
                search_info_printf(s_head);
                ifnot = 0;
                break;
            case '2':
                head = search_info_read();
                s_head = search_info_class(head);
                search_info_printf(s_head);
                ifnot = 0;
                break;
            case '3':
                head = search_info_read();
                s_head = search_info_year(head);
                search_info_printf(s_head);
                ifnot = 0;
                break;
            case '4':
                head = search_info_read();
                s_head = search_info_number(head);
                search_info_printf(s_head);
                ifnot = 0;
                break;
            case 'q':
                ifnot = 0;
                break;
            default:
                printf("Wrong,please try again!\n");
                break;
        }
        
    }
    return 0;
}

//READ FILE TO MAKE TABLE
stuc *search_info_read(){
    FILE *fp = fopen("stuinfo.db", "r");
    if (fp == NULL){
        printf("ERROR IN OPEN FILE!");
        return NULL;
    }
    stuc *stu = NULL, *head = NULL, *stu_last = NULL;
    struct _students *stu_s = NULL;
    stu = (stuc*) malloc(sizeof(stuc));
    stu_s = &stu->stu_info;
    while (fscanf(fp,"%s",stu_s->name) != EOF){
        fscanf(fp, "%s",stu_s->class);
        fscanf(fp, "%s",stu_s->year);
        fscanf(fp, "%s",stu_s->number);
        if (head == NULL){
            head = stu;
            stu_last = head;
            stu->front = NULL;
        }
        else {
            stu_last->next = stu;
            stu->front = stu_last;
            stu_last = stu;
        }
        stu = (stuc*) malloc(sizeof(stuc));
        stu_s = &stu->stu_info;
    }
    stu->next = NULL;
    fclose(fp);
    return head;
}

//SERACH INFO FROM CLASS
stuc *search_info_class(stuc *head){
    printf("CLASS: ");
    char s_class[6]= {'\0','\0','\0','\0','\0','\0'};
    scanf("%s",s_class);
    CLEAR    stuc *p_head = head, *s_head = NULL,*s_stu = NULL, *s_stu_last = NULL;
    struct _students *p_head_s = &p_head->stu_info;
    struct _students *s_head_s = NULL;
    p_head_s = &p_head->stu_info;
    int ifnot = 0;
    while (p_head != NULL){
        if (strcmp(p_head_s->class, s_class) == 0){
            ifnot = 1;
            s_stu = (stuc*) malloc(sizeof(stuc));
            s_head_s = &s_stu->stu_info;
            strcpy(s_head_s->name,p_head_s->name);
            strcpy(s_head_s->class,p_head_s->class);
            strcpy(s_head_s->year,p_head_s->year);
            strcpy(s_head_s->number,p_head_s->number);
            if(s_head == NULL){
                s_head = s_stu;
                s_stu_last = s_head;
                s_head->front = NULL;
            }
            else {
                s_stu_last->next = s_stu;
                s_stu->front = s_stu_last;
                s_stu_last = s_stu;
            }
        }
        p_head = p_head->next;
        p_head_s = &p_head->stu_info;
    }
    if (ifnot){
        s_stu->next = NULL;
    }
    else{
        return NULL;
    }
    return s_head;
}

//SERACH INFO FROM NAME
stuc *search_info_name(stuc *head){
    printf("NAME: ");
    char s_name[12];
    scanf("%s",s_name);
    CLEAR    stuc *p_head = head, *s_head = NULL,*s_stu = NULL, *s_stu_last = NULL;
    struct _students *p_head_s = &p_head->stu_info;
    struct _students *s_head_s = NULL;
    p_head_s = &p_head->stu_info;
    int ifnot = 0;
    while (p_head != NULL){
        if (strcmp(p_head_s->name, s_name) == 0){
            ifnot = 1;
            s_stu = (stuc*) malloc(sizeof(stuc));
            s_head_s = &s_stu->stu_info;
            strcpy(s_head_s->name,p_head_s->name);
            strcpy(s_head_s->class,p_head_s->class);
            strcpy(s_head_s->year,p_head_s->year);
            strcpy(s_head_s->number,p_head_s->number);
            if(s_head == NULL){
                s_head = s_stu;
                s_stu_last = s_head;
                s_head->front = NULL;
            }
            else {
                s_stu_last->next = s_stu;
                s_stu->front = s_stu_last;
                s_stu_last = s_stu;
            }
        }
        p_head = p_head->next;
        p_head_s = &p_head->stu_info;
    }
    if (ifnot){
        s_stu->next = NULL;
    }
    else{
        return NULL;
    }
    
    return s_head;
}


//SERACH INFO FROM YEAR
stuc *search_info_year(stuc *head){
    
    printf("YEAR: ");
    char s_year[12];
    scanf("%s",s_year);
    CLEAR    stuc *p_head = head, *s_head = NULL,*s_stu = NULL, *s_stu_last = NULL;
    struct _students *p_head_s = &p_head->stu_info;
    struct _students *s_head_s = NULL;
    p_head_s = &p_head->stu_info;
    int ifnot = 0;
    while (p_head != NULL){
        if (strcmp(p_head_s->year, s_year) == 0){
            ifnot = 1;
            s_stu = (stuc*) malloc(sizeof(stuc));
            s_head_s = &s_stu->stu_info;
            strcpy(s_head_s->name,p_head_s->name);
            strcpy(s_head_s->class,p_head_s->class);
            strcpy(s_head_s->year,p_head_s->year);
            strcpy(s_head_s->number,p_head_s->number);
            if(s_head == NULL){
                s_head = s_stu;
                s_stu_last = s_head;
                s_head->front = NULL;
            }
            else {
                s_stu_last->next = s_stu;
                s_stu->front = s_stu_last;
                s_stu_last = s_stu;
            }
        }
        p_head = p_head->next;
        p_head_s = &p_head->stu_info;
    }
    if (ifnot){
        s_stu->next = NULL;
    }
    else{
        return NULL;
    }
    CLEAR    return s_head;
}

//SERACH INFO FROM NUMBER
stuc *search_info_number(stuc *head){
    
    printf("NUMBER: ");
    char s_number[28];
    scanf("%s",s_number);
    CLEAR    stuc *p_head = head, *s_head = NULL,*s_stu = NULL, *s_stu_last = NULL;
    struct _students *p_head_s = &p_head->stu_info;
    struct _students *s_head_s = NULL;
    p_head_s = &p_head->stu_info;
    int ifnot = 0;
    while (p_head != NULL){
        if (strcmp(p_head_s->number, s_number) == 0){
            ifnot = 1;
            s_stu = (stuc*) malloc(sizeof(stuc));
            s_head_s = &s_stu->stu_info;
            strcpy(s_head_s->name,p_head_s->name);
            strcpy(s_head_s->class,p_head_s->class);
            strcpy(s_head_s->year,p_head_s->year);
            strcpy(s_head_s->number,p_head_s->number);
            if(s_head == NULL){
                s_head = s_stu;
                s_stu_last = s_head;
                s_head->front = NULL;
            }
            else {
                s_stu_last->next = s_stu;
                s_stu->front = s_stu_last;
                s_stu_last = s_stu;
            }
        }
        p_head = p_head->next;
        p_head_s = &p_head->stu_info;
    }
    if (ifnot){
        s_stu->next = NULL;
    }
    else{
        return NULL;
    }
    CLEAR    return s_head;
}


//PRINTF THE RESULT OF THE SEARCH
int search_info_printf(stuc *head){
    stuc *p_head = head;
    int count = 0;
    if(head == NULL){
        char *PRINTF_MENU[5] = {
            "                 Not Found",
        };
        start_printf(1, PRINTF_MENU);
        printf("Done!(Any key to continue...)");
        getchar();getchar();
        CLEAR        return 0;
    };
    struct _students *p_head_s = &p_head->stu_info;
    int ifnot = 1;
    char input = 'e';
    while (ifnot){
        if ((input == 'w') && (p_head != NULL)){
            CLEAR            if (p_head->next != NULL){
            count++;
            p_head = p_head->next;
            p_head_s = &p_head->stu_info;
            }
            for (int i = 0; i < 20-(count % 10); i++ ) printf("■");
            printf("[ %d ]", count);
            for (int i = 0; i < 20-(count % 10); i++ ) printf("■");
            printf("\n");
            printf("NAME: %s\n",p_head_s->name);
            printf("CLASS: %s\n",p_head_s->class);
            printf("YEAR: %s\n",p_head_s->year);
            printf("NUMBER: %s\n",p_head_s->number);
            for (int i = 0; i < WEIGHT_LENGTH_SQUARE-7; i++ ) printf("■");
            printf("\n");
        }
        else if ((input == 's') && (p_head != NULL)){
            CLEAR            if (p_head->front != NULL){
            p_head = p_head->front;
            p_head_s = &p_head->stu_info;
            count--;
            }
            for (int i = 0; i < 20-(count % 10); i++ ) printf("■");
            printf("[ %d ]", count);
            for (int i = 0; i < 20-(count % 10); i++ ) printf("■");
            printf("\n");
            printf("NAME: %s\n",p_head_s->name);
            printf("CLASS: %s\n",p_head_s->class);
            printf("YEAR: %s\n",p_head_s->year);
            printf("NUMBER: %s\n",p_head_s->number);
            for (int i = 0; i < WEIGHT_LENGTH_SQUARE-7; i++ ) printf("■");
            printf("\n");
        }
        else if ((input == 'e') && (p_head != NULL)){
            count++;
            for (int i = 0; i < 20-(count % 10); i++ ) printf("■");
            printf("[ %d ]", count);
            for (int i = 0; i < 20-(count % 10); i++ ) printf("■");
            printf("\n");
            printf("NAME: %s\n",p_head_s->name);
            printf("CLASS: %s\n",p_head_s->class);
            printf("YEAR: %s\n",p_head_s->year);
            printf("NUMBER: %s\n",p_head_s->number);
            for (int i = 0; i < WEIGHT_LENGTH_SQUARE-7; i++ ) printf("■");
            printf("\n");
        }
        else{
            
        }
        
        if ((p_head->front == NULL) && (input != 'q')){
            printf("■:This is the first element in the list.\n");
        }
        
        if ((p_head->next == NULL) && (input != 'q')){
            printf("■:This is the last element of the list.\n");
        }
        
        getchar();
        printf("INPUT: w:Page down s:Page up q:Quit\n");
        printf("INPUT: ");
        input = getchar();
        
        if (input == 'q'){
            ifnot = 0;
        }
    }
    
    printf("Done,any key to continue...\n");
    getchar();getchar();
    return 0;
}

void passwd_set (void){
    CLEAR    printf("Please enter the administrator password: ");
    char o_passwd[12];
    scanf("%s",o_passwd);
    FILE *fp = fopen("passwd.db","r");
    char r_passwd[12];
    fscanf(fp,"%s",r_passwd);
    fclose(fp);
    if(strcmp(o_passwd, r_passwd) == 0 ){
        int ifnot = 1;
        while (ifnot) {
            printf("Input the new password: ");
            char n_passwd[12];
            scanf("%s",n_passwd);
            printf("Input the new password again: ");
            char n2_passwd[12];
            scanf("%s",n2_passwd);
            if(strcmp(n2_passwd, n_passwd) == 0){
                fp = fopen("passwd.db", "w");
                fprintf(fp,"%s",n_passwd);
                fclose(fp);
                ifnot = 0;
                printf("Done,any key to continue...");
                getchar();getchar();
                CLEAR            }
            else{
                printf("Not the same!(Any key to continue...)");
                getchar();getchar();
                CLEAR            }

        }
    }
    else{
        printf("Wrong!(Any key to continue...)");
        getchar();getchar();
        CLEAR    }
    
}


int delete_data_menu (void){
    CLEAR    char *DELETE_MENU[5]={
        "             Delete From",
        "1.Name",
        "2.Class",
        "3.Year",
        "4.Number"
    };
    
    start_printf(5, DELETE_MENU);
    int ifnot = 1;
    stuc *head, *s_head;
    while (ifnot){
        char choices = choice("Choose the number (q to quit): ");
        switch(choices){
            case '1':
                head = search_info_read();
                s_head = search_info_name(head);
                delete_info_printf(s_head, head);
                ifnot = 0;
                break;
            case '2':
                head = search_info_read();
                s_head = search_info_class(head);
                delete_info_printf(s_head, head);
                ifnot = 0;
                break;
            case '3':
                head = search_info_read();
                s_head = search_info_year(head);
                delete_info_printf(s_head, head);
                ifnot = 0;
                break;
            case '4':
                head = search_info_read();
                s_head = search_info_number(head);
                delete_info_printf(s_head, head);
                ifnot = 0;
                break;
            case 'q':
                ifnot = 0;
                break;
            default:
                printf("Wrong,please try again!\n");
                break;
        }
    }
    return 0;
}

//PRINTF THE RESULT OF THE SEARCH
int delete_info_printf(stuc *head, stuc *r_head){
    if(head == NULL){
        char *PRINTF_MENU[5] = {
            "                 Not Found",
        };
        start_printf(1, PRINTF_MENU);
        printf("Done!(Any key to continue...)");
        getchar();getchar();
        CLEAR        return 0;
    }
    stuc *p_head = head;
    int count = 1;
    struct _students *p_head_s = &p_head->stu_info;
    int ifnot = 1;
    char input = 'e';
    while (ifnot){
        int e_ifnot = 0;
        if ((input == 'w') && (p_head != NULL)){
            CLEAR            if (p_head->next != NULL){
                count++;
                p_head = p_head->next;
                p_head_s = &p_head->stu_info;
            }
            for (int i = 0; i < 20-(count % 10); i++ ) printf("■");
            printf("[ %d ]", count);
            for (int i = 0; i < 20-(count % 10); i++ ) printf("■");
            printf("\n");
            printf("NAME: %s\n",p_head_s->name);
            printf("CLASS: %s\n",p_head_s->class);
            printf("YEAR: %s\n",p_head_s->year);
            printf("NUMBER: %s\n",p_head_s->number);
            for (int i = 0; i < WEIGHT_LENGTH_SQUARE-7; i++ ) printf("■");
            printf("\n");
        }
        else if ((input == 's') && (p_head != NULL)){
            CLEAR            if (p_head->front != NULL){
                p_head = p_head->front;
                p_head_s = &p_head->stu_info;
                count--;
            }
            for (int i = 0; i < 20-(count % 10); i++ ) printf("■");
            printf("[ %d ]", count);
            for (int i = 0; i < 20-(count % 10); i++ ) printf("■");
            printf("\n");
            printf("NAME: %s\n",p_head_s->name);
            printf("CLASS: %s\n",p_head_s->class);
            printf("YEAR: %s\n",p_head_s->year);
            printf("NUMBER: %s\n",p_head_s->number);
            for (int i = 0; i < WEIGHT_LENGTH_SQUARE-7; i++ ) printf("■");
            printf("\n");
        }
        else if ((input == 'e') && (p_head != NULL)){
            p_head_s = &p_head->stu_info;
            for (int i = 0; i < 20-(count % 10); i++ ) printf("■");
            printf("[ %d ]", count);
            for (int i = 0; i < 20-(count % 10); i++ ) printf("■");
            printf("\n");
            printf("NAME: %s\n",p_head_s->name);
            printf("CLASS: %s\n",p_head_s->class);
            printf("YEAR: %s\n",p_head_s->year);
            printf("NUMBER: %s\n",p_head_s->number);
            for (int i = 0; i < WEIGHT_LENGTH_SQUARE-7; i++ ) printf("■");
            printf("\n");
        }
        else if (input == 'd'){
            stuc *p_front, *p_next, *pr_head = r_head;
            struct _students  *r_head_s;
            while(pr_head != NULL){
                r_head_s = &pr_head->stu_info;
                if (strcmp(r_head_s->number, p_head_s->number) == 0) {
                    p_front = pr_head->front;
                    p_next = pr_head->next;
                    if (p_front != NULL){
                        p_front->next = p_next;
                    }
                    if (p_next != NULL){
                        p_next->front = p_front;
                    }
                    if (p_front == NULL){
                        pr_head = p_next;
                        r_head = pr_head;
                    }
                    pr_head = NULL;
                }
                else{
                    pr_head = pr_head->next;
                }
            }
            if (p_head != NULL){
                p_front = p_head -> front;
                p_next = p_head -> next;
                if (p_front != NULL){
                    p_front->next = p_next;
                }
                if (p_next != NULL){
                    p_next->front = p_front;
                }
                if (p_next == NULL){
                    p_head = p_front;
                    count--;
                }
                else if(p_front == NULL){
                    p_head = p_next;
                    count++;
                }
                else if((p_front == NULL) && (p_next == NULL)){
                    p_head = NULL;
                }
                else{
                    p_head = p_head -> next;
                }
                e_ifnot = 1;
            }
        }
        else{
            
        }
        
        if ((e_ifnot == 0) && (p_head != NULL)) {
            if ((p_head->front == NULL) && (input != 'q')){
                printf("■:This is the first element in the list.\n");
            }
            if ((p_head->next == NULL) && (input != 'q')){
                printf("■:This is the last element of the list.\n");
            }
            getchar();
            printf("INPUT: w:Page down s:Page up d:delete q:Quit\n");
            printf("INPUT: ");
            input = getchar();
        }
        if ((e_ifnot == 1) && (p_head != NULL)){
            input = 'e';
            CLEAR        }
        
        if (input == 'q' ){
            ifnot = 0;
        }
        
        if(p_head == NULL){
            char *PRINTF_MENU[5] = {
                "                 Not Found",
            };
            start_printf(1, PRINTF_MENU);
            break;
        }
    }
    FILE *fp = fopen("stuinfo.db", "w");
    if (fp == NULL) {
        printf("ERROR IN OPEN FILE!");
        return -1;
    }
    stuc *prf_head = r_head;
    struct _students  *rf_head_s;
    while (prf_head != NULL){
        rf_head_s = &prf_head->stu_info;
        fprintf(fp, "%s\n", rf_head_s->name);
        fprintf(fp, "%s\n", rf_head_s->class);
        fprintf(fp, "%s\n", rf_head_s->year);
        fprintf(fp, "%s\n", rf_head_s->number);
        prf_head = prf_head->next;
    }
    
    printf("Done,any key to continue...\n");
    fclose(fp);
    getchar();getchar();
    return 0;
}
//End of program
