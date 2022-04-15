#include <stdio.h>
#include <string.h>

unsigned long long sec_1_byte(FILE* fp);

unsigned long long cla_1_sec(FILE* fp);

unsigned long long fat_size_4b(FILE* fp);

unsigned long long root_start_ad(unsigned long long size_byte, unsigned long long fat_yet, unsigned long long fat_size);

