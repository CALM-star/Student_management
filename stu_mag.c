#include <stdio.h>
#include "stu_mag.h"
#include <stdlib.h>
#include <string.h>


Student *head = NULL; 

void saveToFile()
{
    FILE *file = fopen("students.data", "wb");
    if (file == NULL)
    {
        printf("无法打开文件进行保存！\n");
        return;
    }
    Student *current = head;
    while (current != NULL)
    {
        fwrite(current, sizeof(Student),1, file);
        current = current-> next ;
    }
    
    fclose(file);
}

void loadFromFile()
{
    FILE *file = fopen("students.data", "rb");
    if (file == NULL)
    {
        printf("没有找到保存的学生数据文件，开始新的记录。\n");
        return;
    }

   Student temp;
   while(fread(&temp, sizeof(Student),1 ,file) == 1)
   {
    Student *newStudent = (Student *)malloc(sizeof(Student));
    *newStudent = temp;
    newStudent->next = head;
    head = newStudent;
   }
   fclose(file);

}



// ==========================================
// 核心功能 1：添加学生 (动态申请内存，头插法)
// ==========================================
void addStudent() {
    // 1. 向操作系统强行要一块内存 (大小刚好是一个 Student 结构体)
    while(1) {

    char tempinput[20];

    Student *newStudent = (Student *)malloc(sizeof(Student));
    if (newStudent == NULL) {
        printf("内存分配失败，系统崩溃！\n");
        return;
    }

    // 2. 往这块新内存里填数据
    printf("请输入学号: ");
    scanf("%s", tempinput);
    if(strcmp( tempinput, "quit") == 0)
    {
        free(newStudent);
        printf("退出添加学生。\n");
        return;
     }

    newStudent->id = atoi(tempinput);

    if (newStudent->id <= 0) {
        printf("学号必须是正整数！\n");
        free(newStudent);
        while(getchar() != '\n'); // 清空输入缓冲区，防止死循环
        continue;
    }

    printf("请输入姓名: ");
    scanf("%s", newStudent->name);

    printf("请输入成绩: ");
    scanf("%f", &newStudent->score);
    if(newStudent->score < 0 || newStudent->score > 100) {
        printf("成绩必须在0到100之间！\n");
        free(newStudent);
        while(getchar() != '\n'); // 清空输入缓冲区，防止死循环
        continue;
    }


    // 3. 玩弄指针 (注意顺序，千万不能反！)
    // 让新同学的手，牵住目前的第一个同学

    newStudent->next = head; 
    
    // 让系统承认，新同学才是现在的排头兵
    head = newStudent;       

    printf("添加成功！内存已动态扩容。\n");
}
}

// ==========================================
// 核心功能 2：遍历显示 (顺藤摸瓜)
// ==========================================
void displayStudents() {
    if (head == NULL) {
        printf("系统里空空如也，连个鬼影都没有。\n");
        return;
    }

    // 拿一个临时指针充当“探照灯”，从头开始照
    Student *current = head; 
    
    printf("\n--- 学生列表 ---\n");
    // 只要探照灯没照到 NULL (尽头)，就一直往下走
    while (current != NULL) {
        printf("学号: %d | 姓名: %s | 成绩: %.1f\n", current->id, current->name, current->score);
        // 核心步进：探照灯照向下一个人的地址
        current = current->next; 
    }
    printf("----------------\n");
}

// ==========================================
// 核心功能 3：删除学生 (最容易出现段错误的禁区)
// ==========================================
void deleteStudent()
{
    while(1)
    {
    char name[20];
    int id;
    char tempinput[20];
    Student *current = head;
    Student *previous = NULL;

    displayStudents();

    if(head == NULL) {
        printf("系统里空空如也，连个鬼影都没有。\n");
        return;
    }   

    printf("请输入要删除的学生学号: ");
    id = 0;
    scanf("%s", tempinput);
    if (strcmp (tempinput, "quit") == 0) {
        printf("退出删除学生。\n");
        return;
    }
    id = atoi(tempinput);

    if(id <= 0) 
    {
        printf("输入无效，请输入一个正整数学号。\n");
        while(getchar() != '\n'); // 清空输入缓冲区，防止死循环
        continue;
    }

    int found = 0;
    while (current != NULL) {
        if (current->id == id) {
            found = 1;
            if (previous == NULL)
            {
                head = current ->next;
                free(current);
                printf("学生已成功删除。\n");
                break;
            }
            else{
                previous->next = current->next;
                free(current);
                printf("学生已成功删除。\n");
            break;}
        }
        previous = current;
        current = current->next;
    }
    if (!found) {
        printf("没有找到学号为 %d 的学生。\n", id);
        continue;
    }

    }
}
// ==========================================