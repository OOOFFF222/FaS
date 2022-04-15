#include <stdio.h>
#include <string.h>

unsigned long long sec_1_byte(FILE* fp) {

	unsigned long long size_byte_ex[2] = { 0x00, };

	fseek(fp, 11, SEEK_SET);
	fread(size_byte_ex, 2, 1, fp);

	size_byte_ex[1] = size_byte_ex[1] & 0xff00;
	unsigned long long size_byte = size_byte_ex[1] | size_byte_ex[0];
	return size_byte;
}

unsigned long long cla_1_sec(FILE* fp) {
	unsigned long long area_num = 0;
	unsigned long long* ad = &(area_num);

	fseek(fp, 0, SEEK_CUR);
	fseek(fp, 13, SEEK_SET);
	fread(ad, 1, 1, fp);
	return area_num;
}

unsigned long long fat_yet_re(FILE* fp) {
	unsigned long long fat_yet_ex[2] = { 0x00, };
	fseek(fp, 0, SEEK_CUR);
	fseek(fp, 14, SEEK_SET);
	fread(fat_yet_ex, 2, 1, fp);

	fat_yet_ex[1] = fat_yet_ex[1] & 0xff00;
	unsigned long long fat_yet = fat_yet_ex[1] | fat_yet_ex[0];
	return fat_yet;
}

unsigned long long fat_size_4b(FILE* fp) {
	unsigned long long fat_size_ex[2] = { 0x00 };
	fseek(fp, 0, SEEK_CUR);
	fseek(fp, 36, SEEK_SET);
	fread(fat_size_ex, 2, 1, fp);

	fat_size_ex[1] = fat_size_ex[1] & 0xff00;
	unsigned long long fat_size = fat_size_ex[1] | fat_size_ex[0];
	return fat_size;
}

unsigned long long root_start_ad(unsigned long long size_byte, unsigned long long fat_yet, unsigned long long fat_size) {
	unsigned long long root_start = (size_byte * fat_yet) + 2 * (size_byte * fat_size);
	return root_start;
}
