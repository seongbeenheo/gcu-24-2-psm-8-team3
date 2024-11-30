#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


void regi() {
    FILE* login_info;

    char username[20], password[20];
    int is_duplicate = 0; //�ߺ� Ȯ�ο� �÷���

    do {
        is_duplicate = 0;

        //������ �Է�
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
}
