//
// Created by user on 2021/9/23.
//
#include "../Inc/FAT32_struct.h"

void FAT32_driver(struct FAT32_MEDIA *media_ptr)
{
    if(media_ptr == NULL || media_ptr->disk == NULL)
        return;
    switch(media_ptr->request)
    {
        case(INIT):
        {
            if(media_ptr->disk->open(media_ptr->disk) == 0)
                media_ptr->status = FAT_SUCCESS;
            else
                media_ptr->status = FAT_IO_ERROR;
            return;
        }
        case(UNINIT):
        {

            media_ptr->disk->close(media_ptr->disk);
            media_ptr->status = FAT_SUCCESS;
            return;
        }
        case(READ_BOOT):
        {
            int read_bytes = media_ptr->disk->read(media_ptr->disk,0,media_ptr->operate_buff,SECTOR_SIZE);
            if(read_bytes != SECTOR_SIZE)
                media_ptr->status = FAT_IO_ERROR;
            else
                media_ptr->status = FAT_SUCCESS;
            return;
        }
        case(READ):
        {
            unsigned int read_bytes = media_ptr->operate_sectors * SECTOR_SIZE;
            if(media_ptr->disk->read(media_ptr->disk,media_ptr->operate_sectors_start * SECTOR_SIZE
                                     ,media_ptr->operate_buff,read_bytes) <= 0)
                media_ptr->status = FAT_IO_ERROR;
            else
                media_ptr->status = FAT_SUCCESS;
            return;
        }
        case(WRITE_BOOT):
        {
            if(media_ptr->disk->write(media_ptr->disk,0,media_ptr->operate_buff,sizeof(struct FAT32_BOOT)) != sizeof(struct FAT32_BOOT))
                media_ptr->status = FAT_IO_ERROR;
            else
                media_ptr->status = FAT_SUCCESS;
            return;
        }
        case(WRITE):
        {
            unsigned int write_bytes = media_ptr->operate_sectors * SECTOR_SIZE;
            if(media_ptr->disk->write(media_ptr->disk,media_ptr->operate_sectors_start * SECTOR_SIZE
                    ,media_ptr->operate_buff,write_bytes) <= 0)
                media_ptr->status = FAT_IO_ERROR;
            else
                media_ptr->status = FAT_SUCCESS;
            return;
        }
        case(FLUSH):
        {


        }
        default:
        {
            media_ptr->status = FAT_INVALID_PARA;
            return;
        }
    }
    media_ptr->status = FAT_UNKNOWN_ERROR;
}