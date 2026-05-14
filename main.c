#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stu_mag.h"



int main() {
    int choice;
    loadFromFile();
    while(1) {
        printf("\n=== 动态链表版学生系统 ===\n");
        printf("1. 添加学生 (动态扩容)\n");
        printf("2. 显示所有学生\n");
        printf("3. 删除学生 (释放内存)\n");
        printf("4. 退出系统\n");
        printf("请选择操作: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // 清空输入缓冲区，防止死循环
            printf("请输入数字！\n");
            continue;
        }

        switch(choice) {
            case 1: addStudent();saveToFile(); break;
            case 2: displayStudents(); break;
            case 3: deleteStudent(); saveToFile(); break;
            case 4: 
                printf("退出程序。\n");
                // 严谨的程序员会在退出前写一个循环 free 掉所有的节点，今天先放过你
                exit(0);
            default: printf("无效选择！\n");
        }
    }
    return 0;
}