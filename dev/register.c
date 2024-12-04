#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "login.h"

#define SHIFT 3 // 카이사르 암호화의 이동 값

// 모든 문자에 대해 카이사르 암호화 함수
void caesarEncrypt(char* text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = (text[i] + shift) % 256; // 256으로 모듈러 연산하여 모든 char에 적용
    }
}

// 모든 문자에 대해 카이사르 복호화 함수
void caesarDecrypt(char* text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = (text[i] - shift + 256) % 256; // 음수 방지를 위해 +256
    }
}

void regi(char* id) {
    FILE* login_info;

    char username[20], password[20];
    int is_duplicate = 0; //중복 확인용 플래그

    do {
        is_duplicate = 0;

        //유저명 입력
        printf("REGISTRATION\n");
        printf("Please enter username: ");
        gets_s(username, sizeof(username));

        //파일 열기 (읽기) NULL이면 종료
        login_info = fopen("login_info.txt", "r");
        if (!login_info) {
            printf("Error opening file");
            exit(1);
        }

        else {
            char existing_username[20], existing_password[20];

            //유저명 중복 검사
            while (fscanf(login_info, "%s %s", existing_username, existing_password) > 0) {
                if (!strcmp(username, existing_username)) {
                    printf("Username already exists. Please try again.\n");
                    is_duplicate = 1; //중복 발생
                    break;
                }
            }
            fclose(login_info); //읽기 파일 닫기
        }

    } while (is_duplicate); //중복이면 다시 실행

    //비밀번호 입력
    printf("Please enter password: ");
    gets_s(password, sizeof(password));

    // 비밀번호 암호화
    caesarEncrypt(password, SHIFT);

    //파일 열기 (추가)
    login_info = fopen("login_info.txt", "a");
    if (!login_info) {
        printf("Error opening file");
        exit(1);
    }

    //새 회원 정보 추가
    fprintf(login_info, "%s %s\n", username, password);
    fclose(login_info); //파일 닫기

    printf("Registration successful!\n");
    login(id);
    
}