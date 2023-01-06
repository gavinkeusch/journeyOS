#include "ata.h"

void wait_drive_until_ready()
{
    int status = 0;

    do {
        status = dev_read(BASE_PORT + 7);
    } while ((status ^ 0x80) == 128);
}

void* read_disk(int address)
{
    dev_write(BASE_PORT + 6, (0x0e0 | ((address & 0x0F000000) >> 24)));
    dev_write(BASE_PORT + 2, 1);
    dev_write(BASE_PORT + 3, address & 0x000000FF);
    dev_write(BASE_PORT + 4, (address & 0x0000FF00) >> 8);
    dev_write(BASE_PORT + 5, (address & 0x00FF0000) >> 16);
    dev_write(BASE_PORT + 7, 0x20);
}

void write_disk(int address, short* buffer)
{
    dev_write(BASE_PORT + 6,(0x0e0 | ((address & 0x0F000000) >> 24)));
    dev_write(BASE_PORT + 2, 1);
    dev_write(BASE_PORT + 3, address & 0x000000FF);
    dev_write(BASE_PORT + 4, (address & 0x0000FF00) >> 8);
    dev_write(BASE_PORT + 5, (address & 0x00FF0000) >> 16);
    dev_write(BASE_PORT + 7, 0x30);

    wait_drive_until_ready();

    for (int curr_byte = 0; curr_byte < (SECTOR_SIZE /2); curr_byte++)
        dev_write_word(BASE_PORT, buffer[curr_byte]);

    wait_drive_until_ready();
}

void* read_disk_chs(int sector)
{
    dev_write(BASE_PORT + 6, 0x0a0);
    dev_write(BASE_PORT + 2, 1);
    dev_write(BASE_PORT + 3, sector);
    dev_write(BASE_PORT + 4, 0);
    dev_write(BASE_PORT + 5, 0);
    dev_write(BASE_PORT + 7, 0x20);

    wait_drive_until_ready();

    short* buffer = kalloc(SECTOR_SIZE);

    for (int curr_byte = 0; curr_byte < (SECTOR_SIZE /2); curr_byte++)
        buffer[curr_byte] = dev_read(BASE_PORT);

    return buffer;
}

void write_disk_chs(int sector, short* buffer)
{
    dev_write(BASE_PORT + 6, 0x0a0);
    dev_write(BASE_PORT + 2, 1);
    dev_write(BASE_PORT + 3, sector);
    dev_write(BASE_PORT + 4, 0);
    dev_write(BASE_PORT + 5, 0);
    dev_write(BASE_PORT + 7, 0x30);

    wait_drive_until_ready();

    for (int curr_byte = 0; curr_byte < (SECTOR_SIZE /2); curr_byte++)
        dev_write_word(BASE_PORT, buffer[curr_byte]);

    wait_drive_until_ready();
}