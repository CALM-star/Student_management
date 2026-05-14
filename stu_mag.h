#ifndef STU_MAG_H
#define STU_MAG_H

// 1. 定义链表节点结构体 (你的新会议室)
typedef struct Student {
    int id;             // 学号
    char name[20];      // 姓名
    float score;        // 成绩
    struct Student *next; // 【灵魂所在】手里攥着下一位同学的内存地址
} Student;



void saveToFile();
void loadFromFile();
void addStudent();
void displayStudents();
void deleteStudent();



#endif