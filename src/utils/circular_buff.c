/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#include "client.h"

size_t write_buffer(const char *str, struct buff_s *buff)
{
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        buff->output_buff[buff->write_index] = str[i];
        buff->write_index++;
        if (buff->write_index == BUFFER_SIZE) {
            buff->write_index = 0;
        }
        buff->len++;
        if (buff->len == BUFFER_SIZE) {
            NOT_FATAL("Buffer is full !");
            return -1;
        }
    }
    return len;
}

size_t read_buffer(const size_t size, struct buff_s *buff,
                char new_buff[BUFFER_SIZE])
{
    size_t i;

    for (i = 0; i < size && buff->len > 0; i++) {
        new_buff[i] = buff->output_buff[buff->read_index];
        buff->len--;
        buff->read_index++;
        if (buff->read_index == BUFFER_SIZE) {
            buff->read_index = 0;
        }
        if (buff->len == 0) {
            return (i);
        }
    }
    return size;
}
