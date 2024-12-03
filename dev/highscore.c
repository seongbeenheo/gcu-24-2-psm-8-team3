#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

struct RECORD {
	char id[20];
	float record;
}topten[10];

void highscore(char username[], float time) {
	FILE* leaderboard;
	
	leaderboard = fopen("leaderboard.txt", "r");
	if (!leaderboard) {
		printf("File Could Not Be Opened.\n");
		exit(1);
	}


	int i = 0;
	while (fscanf(leaderboard, "%s %f", topten[i].id, &topten[i].record) > 0) i++;
	fclose(leaderboard);
	int is_updated = 0;
	int j = 9;
	//�Է¹��� ��� ���� ��ϰ� �� �� ����
	for (j; j >= 0; j--) {
		if (time <= topten[j].record) {			
			if (j < 9) topten[j + 1] = topten[j]; //���� ��Ϻ��� ���ų� ������ �ڸ� �̵�
			//�� ��� ����
			strcpy(topten[j].id, username);
			topten[j].record = time;
			if (!is_updated) is_updated = 1;
		}
		else {//���� ��Ϻ��� �����ٸ� �ߴ�
		
			break;
		}
	}

	//���ŵ� ���̽��ھ� ����
	leaderboard = fopen("leaderboard.txt", "w");
	
	for (int k = 0; k < i; k++) {
		fprintf(leaderboard, "%s\t%.1f\n", topten[k].id, topten[k].record);
	}
	fclose(leaderboard);

	//���
	if (is_updated) printf("\nHIGHSCORE UPDATED!!\n");
	else printf("\nCURRENT HIGHSCORE\n");

	for (int k = 0; k < i; k++) {
		printf("%d. %s - %.1f", k + 1, topten[k].id, topten[k].record);
		if (is_updated && k == j + 1) {
			printf(" <--- NEW!!");
		}
		printf("\n");
	}
	

}