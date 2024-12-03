#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "register.h"

void login(char* id) {
	FILE* login_file;
	//회원 정보 파일 열기(읽기)
	login_file = fopen("login_info.txt", "r");
	if (login_file == NULL) {
		printf("file could not be opened!");
		exit(1);
	}
	//아이디 입력받고 저장
	char id_input[20];
	char pw_input[20];
	printf("LOG IN\n");
	printf("Username: ");
	gets_s(id_input, sizeof(id_input));
	printf("\n");

	int username_matched = 0; //아이디 일치 여부 확인용 플래그
	int is_logged_in = 0; //로그인 성공 여부 확인용 플래그

	//회원 정보 파일 한줄씩 읽기
	char idpw[100];
	char existing_id[20], existing_pw[20];

	while (fgets(idpw, sizeof(idpw), login_file)) {
		//idpw에서 ID와 PW를 분리
		if (sscanf(idpw, "%s %s", existing_id, existing_pw) == 2) {
			//printf("ID: %s, PW: %s\n", existing_id, existing_pw);
			
			//유저명이 틀린 경우 --> 다음 줄로 넘어감
			if (strcmp(existing_id, id_input)) continue;
			username_matched = 1;

			while (1) { //패스워드 틀렸을 때 재입력 위해 무한루프 생성
				//패스워드 입력받고 저장
				printf("Password: ");
				gets_s(pw_input, sizeof(pw_input));
				printf("\n");

				//유저명 맞고 비밀번호가 틀린 경우 --> 다시 입력
				if (strcmp(existing_pw, pw_input)) {
					printf("Wrong password. Try again.\n");
				}
				//둘다 맞은 경우 --> 로그인 성공! 루프 탈출
				else {
					printf("Log in successful. Welcome, %s\n", id_input);
					strcpy(id, id_input);
					is_logged_in = 1;
					break;
				}
			}

			if (is_logged_in) break; //로그인 성공했을 경우 남은 줄 확인할 필요 X


		}
		else {
			//형식이 잘못된 경우(한 줄이 string string이 아닌 경우)
			printf("Wrong file structure");
			exit(1);
		}
	}

	if (!username_matched) {
		printf("Username not found! Please sign up.\n");
		regi(id);
	}
}