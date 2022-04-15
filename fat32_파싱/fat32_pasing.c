#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "fat32_기본크기.h"

unsigned long long boot_start_find(FILE* fp) {

	unsigned long long size_byte = sec_1_byte(fp);

	unsigned long long area_num = cla_1_sec(fp);

	unsigned long long area_size = 0;
	area_size = size_byte * area_num;

	unsigned long long fat_yet = fat_yet_re(fp);

	unsigned long long fat_size = fat_size_4b(fp);

	unsigned long long boot_start = boot_start_ad(size_byte, fat_yet, fat_size);

	return boot_start;
}


int main() {
	FILE* fp = fopen("D:\\문서\\카카오톡 받은 파일\\FaS 활동 1\\fat32_image\\fat32_image", "rb");
	if (fp == NULL) {
		printf("open error\n");
		return 1;
	}

	unsigned long long root_start = root_start_find(fp);

	unsigned long long end_ad;

	int i = 0;

	while(1){
		unsigned long long fi = 0;
		unsigned long long* ad = &(fi);
		fseek(fp, 0, SEEK_CUR);
		fseek(fp, root_start + i, SEEK_SET);
		fread(ad, 1, 1, fp);
		if (fi == 00) {
			end_ad = root_start + i;
			break;
		}
		i += 32;
	}

	printf("%08x", end_ad);

	fclose(fp);
}