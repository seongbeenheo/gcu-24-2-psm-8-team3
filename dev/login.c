#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "register.h"

void login(char* id) {
	FILE* login_file;
	//ȸ�� ���� ���� ����(�б�)
	login_file = fopen("login_info.txt", "r");
	if (login_file == NULL) {
		printf("file could not be opened!");
		exit(1);
	}
	//���̵� �Է¹ް� ����
	char id_input[20];
	char pw_input[20];
	printf("LOG IN\n");
	printf("Username: ");
	gets_s(id_input, sizeof(id_input));
	printf("\n");

	int username_matched = 0; //���̵� ��ġ ���� Ȯ�ο� �÷���
	int is_logged_in = 0; //�α��� ���� ���� Ȯ�ο� �÷���

	//ȸ�� ���� ���� ���پ� �б�
	char idpw[100];
	char existing_id[20], existing_pw[20];

	while (fgets(idpw, sizeof(idpw), login_file)) {
		//idpw���� ID�� PW�� �и�
		if (sscanf(idpw, "%s %s", existing_id, existing_pw) == 2) {
			//printf("ID: %s, PW: %s\n", existing_id, existing_pw);
			
			//�������� Ʋ�� ��� --> ���� �ٷ� �Ѿ
			if (strcmp(existing_id, id_input)) continue;
			username_matched = 1;

			while (1) { //�н����� Ʋ���� �� ���Է� ���� ���ѷ��� ����
				//�н����� �Է¹ް� ����
				printf("Password: ");
				gets_s(pw_input, sizeof(pw_input));
				printf("\n");

				//������ �°� ��й�ȣ�� Ʋ�� ��� --> �ٽ� �Է�
				if (strcmp(existing_pw, pw_input)) {
					printf("Wrong password. Try again.\n");
				}
				//�Ѵ� ���� ��� --> �α��� ����! ���� Ż��
				else {
					printf("Log in successful. Welcome, %s\n", id_input);
					strcpy(id, id_input);
					is_logged_in = 1;
					break;
				}
			}

			if (is_logged_in) break; //�α��� �������� ��� ���� �� Ȯ���� �ʿ� X


		}
		else {
			//������ �߸��� ���(�� ���� string string�� �ƴ� ���)
			printf("Wrong file structure");
			exit(1);
		}
	}

	if (!username_matched) {
		printf("Username not found! Please sign up.\n");
		regi(id);
	}
}