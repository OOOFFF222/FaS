#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "fat32_기본크기.h";

void fsinfo_ser(FILE* fp) {
	unsigned long long sec_byte = sec_1_byte(fp);
	int i = 0;

	for(int i=4; i < 484; i++) {
		unsigned long long fi = 0;
		unsigned long long* ad = &(fi);
		fseek(fp, 0, SEEK_CUR);
		fseek(fp, sec_byte + i, SEEK_SET);
		fread(ad, 1, 1, fp);

		if (fi != 00) {
			printf("Fsinfo 미사용 영역 - 은닉 데이터 존재\n");
			break;
		}
	}
}

void boot_st_ser(FILE* fp) {
	unsigned long long sec_byte = sec_1_byte(fp);

	unsigned long long boot_st_st = 2 * sec_byte;

	unsigned long long boot_st_da[512] = { 0x00, };

	fseek(fp, 0, SEEK_CUR);
	fseek(fp, boot_st_st, SEEK_SET);
	fread(boot_st_da, sec_byte, 1, fp);

	unsigned long long boot_st_ba_da[512] = { 0x00, };

	unsigned long long boot_st_ba_st = 8 * sec_byte;

	fseek(fp, 0, SEEK_CUR);
	fseek(fp, boot_st_ba_st, SEEK_SET);
	fread(boot_st_ba_da, sec_byte, 1, fp);

	for (int i = 0; i < sec_byte; i++) {
		if (boot_st_da[i] != boot_st_ba_da[i]) {
			printf("Boot Strap - 은닉 데이터 존재\n");
			break;
		}
	}
}

void fat_ser(FILE* fp) {
	unsigned long long size_byte = sec_1_byte(fp);
	unsigned long long fat_yet = fat_yet_re(fp);
	unsigned long long fat_1_ad = fat_yet * size_byte;

	unsigned long long fat_si = fat_size_4b(fp);
	unsigned long long fat_by_si = fat_si * size_byte;

	unsigned long long* fat_1_da = (unsigned long long*)calloc(fat_by_si, sizeof(unsigned long long));

	fseek(fp, 0, SEEK_CUR);
	fseek(fp, fat_1_ad, SEEK_SET);
	fread(fat_1_da, fat_si, 1, fp);

	unsigned long long fat_2_ad = fat_1_ad + fat_by_si;
	unsigned long long* fat_2_da = (unsigned long long*)calloc(fat_by_si, sizeof(unsigned long long));

	fseek(fp, 0, SEEK_CUR);
	fseek(fp, fat_2_ad, SEEK_SET);
	fread(fat_2_da, fat_si, 1, fp);

	for (int i = 0; i < fat_by_si; i++) {
		if (fat_1_da[i] != fat_2_da[i]) {
			printf("Fat Area - 은닉 데이터 존재\n");
			printf("은닉 데이터 : %04x <-> %04x\n", fat_1_da[i], fat_2_da[i]);
			printf("은닉 위치 : %d\n", i);
			break;
		}
	}

	free(fat_1_da);
	free(fat_2_da);
}

int main() {
	FILE* fp = fopen("D:\\문서\\카카오톡 받은 파일\\FaS 활동 1\\fat32_image\\fat32_image", "rb");
	if (fp == NULL) {
		printf("open error\n");
		return 1;
	}
	fsinfo_ser(fp);
	boot_st_ser(fp);
	fat_ser(fp);
}