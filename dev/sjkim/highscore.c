#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

struct RECORD {
	char id[20];
	int record;
}topten[10];

void highscore(char username[], int time) {
	FILE* leaderboard;
	
	leaderboard = fopen("leaderboard.txt", "r");
	if (!leaderboard) {
		printf("File Could Not Be Opened.\n");
		exit(1);
	}


	int i = 0;
	while (fscanf(leaderboard, "%s %d", topten[i].id, &topten[i].record) > 0) i++;
	fclose(leaderboard);
	int is_updated = 0;

	//입력받은 기록 기존 기록과 비교 및 삽입
	for (int j = 9; j >= 0; j--) {
		if (time <= topten[j].record) {			
			if (j < 9) topten[j + 1] = topten[j]; //현재 기록보다 같거나 빠르면 자리 이동
			//새 기록 삽입
			strcpy(topten[j].id, username);
			topten[j].record = time;
			if (!is_updated) is_updated = 1;
		}
		
		else {//현재 기록보다 느리다면 중단
			break;
		}
	}
	//갱신된 하이스코어 저장
	leaderboard = fopen("leaderboard.txt", "w");
	
	for (int k = 0; k < i; k++) {
		fprintf(leaderboard, "%s\t%d\n", topten[k].id, topten[k].record);
	}
	fclose(leaderboard);

	//출력
	if (is_updated) printf("HIGHSCORE UPDATED!!\n");
	else printf("CURRENT HIGHSCORE\n");

	for (int k = 0; k < i; k++) {
		printf("%d. %s - %d\n", k + 1, topten[k].id, topten[k].record);
	}
	

}