//
// Created by user on 2021/9/24.
//

#include "Inc/FAT32_struct.h"


int media_open(struct MEDIA_DISK *media_ptr) {
    if (media_ptr && media_ptr->media_name) {
        media_ptr->ID = open(media_ptr->media_name, O_CREAT | O_RDWR, 0666);
        if (media_ptr->ID > 0) {
            media_ptr->status = 1;
            media_ptr->read_times = 0;
            media_ptr->write_times = 0;
            return 0;
        }
    }
    return -1;
}

void media_close(struct MEDIA_DISK *media_ptr) {
    if (media_ptr) {
        close(media_ptr->ID);
        media_ptr->status = 0;
    }
}


int media_read(struct MEDIA_DISK *media_ptr, unsigned int offset, void *dest, int length) {
    if (offset > media_ptr->max_size || media_ptr->status == 0)
        return -1;
    if (offset + length > media_ptr->max_size)
        return  -1;
    if (media_ptr && media_ptr->ID > 0) {
        lseek(media_ptr->ID, offset, SEEK_SET);
        media_ptr->read_times++;
        return read(media_ptr->ID, dest, length);
    }
    return -1;
}

int media_write(struct MEDIA_DISK *media_ptr, unsigned int offset, void *source, int length) {
    if (offset > media_ptr->max_size || media_ptr->status == 0)
        return -1;
    if (offset + length > media_ptr->max_size)
        return  -1;
    if (media_ptr && media_ptr->ID > 0) {
        lseek(media_ptr->ID, offset, SEEK_SET);
        media_ptr->write_times++;
        return  write(media_ptr->ID, source, length);
    }
    return -1;
}


int media_create(struct MEDIA_DISK *media_ptr,int ID, char *media_name, unsigned int max_size/*,int (*open)(struct MEDIA_BASE*,char *),
        int (*read)(struct MEDIA_BASE*,unsigned int,void*,int),int (*write)(struct MEDIA_BASE*,unsigned int,void *,int),
                void (*close)(struct MEDIA_BASE*)*/) {
    if (media_ptr && max_size) {
        media_ptr->status = 0;
        media_ptr->read_times = 0;
        media_ptr->write_times = 0;
        media_ptr->ID = ID;
        media_ptr->max_size = max_size;
        media_ptr->media_name = media_name;
        media_ptr->open = media_open;
        media_ptr->close = media_close;
        media_ptr->read = media_read;
        media_ptr->write = media_write;
        return 0;
    }
    return -1;
}