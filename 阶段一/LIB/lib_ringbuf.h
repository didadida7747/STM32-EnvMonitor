#ifndef __LIB_RINGBUF_H
#define __LIB_RINGBUF_H

#include <stdint.h>

/* 环形缓冲区结构体定义（阶段二具体使用） */
typedef struct {
    uint8_t *buffer;
    uint16_t head;
    uint16_t tail;
    uint16_t size;
} RingBuf_t;

void Lib_RingBuf_Init(void);

#endif