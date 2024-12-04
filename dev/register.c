#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "login.h"

#define SHIFT 3 // ī�̻縣 ��ȣȭ�� �̵� ��

// ��� ���ڿ� ���� ī�̻縣 ��ȣȭ �Լ�
void caesarEncrypt(char* text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = (text[i] + shift) % 256; // 256���� ��ⷯ �����Ͽ� ��� char�� ����
    }
}

// ��� ���ڿ� ���� ī�̻縣 ��ȣȭ �Լ�
void caesarDecrypt(char* text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = (text[i] - shift + 256) % 256; // ���� ������ ���� +256
    }
}

void regi(char* id) {
    FILE* login_info;

    char username[20], password[20];
    int is_duplicate = 0; //�ߺ� Ȯ�ο� �÷���

    do {
        is_duplicate = 0;

        //������ �Է�
        printf("REGISTRATION\n");
        printf("Please enter username: ");
        gets_s(username, sizeof(username));

        //���� ���� (�б�) NULL�̸� ����
        login_info = fopen("login_info.txt", "r");
        if (!login_info) {
            printf("Error opening file");
            exit(1);
        }

        else {
            char existing_username[20], existing_password[20];

            //������ �ߺ� �˻�
            while (fscanf(login_info, "%s %s", existing_username, existing_password) > 0) {
                if (!strcmp(username, existing_username)) {
                    printf("Username already exists. Please try again.\n");
                    is_duplicate = 1; //�ߺ� �߻�
                    break;
                }
            }
            fclose(login_info); //�б� ���� �ݱ�
        }

    } while (is_duplicate); //�ߺ��̸� �ٽ� ����

    //��й�ȣ �Է�
    printf("Please enter password: ");
    gets_s(password, sizeof(password));

    // ��й�ȣ ��ȣȭ
    caesarEncrypt(password, SHIFT);

    //���� ���� (�߰�)
    login_info = fopen("login_info.txt", "a");
    if (!login_info) {
        printf("Error opening file");
        exit(1);
    }

    //�� ȸ�� ���� �߰�
    fprintf(login_info, "%s %s\n", username, password);
    fclose(login_info); //���� �ݱ�

    printf("Registration successful!\n");
    login(id);
    
}