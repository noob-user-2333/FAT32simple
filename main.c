#include <stdio.h>
#include "Inc/FAT32_struct.h"

#define FILE_PATH "/dev/shm/fat32.bin"
#define MAX_SIZE  256 * 1024 * 1024
extern int media_create(struct MEDIA_DISK* media_ptr,int ID,char*name,unsigned int max_size);
extern void FAT32_driver(struct FAT32_MEDIA *media_ptr);
struct MEDIA_DISK disk;
struct FAT32_MEDIA media;

unsigned char buffer[10240];
unsigned char buff[10240];
unsigned long entry = 0;
struct FAT32_DIR dest_dir;
char *name = "/ dev / shm.fat.bin/test/";
unsigned int status = FAT_SUCCESS;

int main() {
    media_create(&disk,0,FILE_PATH,MAX_SIZE);
    FAT32_media_open(&media,&disk,FAT32_driver,buffer,10240);
    do {
        status = FAT32_directory_search(&media,"/test dir/success.txt",&dest_dir);
        FAT32_utility_logic_sector_read(&media,buff,FAT32_utility_cluster_to_sector(&media, dest_dir.first_cluster_l),10);
        printf("name:%s\n",media.name_buff);
    }while(status == FAT_SUCCESS);

    return 0;
}
