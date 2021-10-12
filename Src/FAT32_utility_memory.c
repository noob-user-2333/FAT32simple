//
// Created by user on 2021/9/25.
//


#include "../Inc/FAT32_struct.h"


void FAT32_utility_memory_copy(void *src,void *dest,unsigned int length)
{
    memcpy(dest,src,length);
}
void FAT32_utility_memory_set(void *src,unsigned int ch,unsigned int length)
{
    memset(src,ch,length);
}
