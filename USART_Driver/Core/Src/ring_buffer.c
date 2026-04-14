#include "ring_buffer.h"

void RingBuffer_Init(RingBuffer * ringBuffer, void * dataBuffer, size_t dataBufferSize) {
    if (ringBuffer == NULL || dataBuffer == NULL || dataBufferSize == 0) {
        return;
    }
    ringBuffer->bufferSize = dataBufferSize;
    ringBuffer->head = 0;
    ringBuffer->tail = 0;
    ringBuffer->ptr_buffer = dataBuffer;
    ringBuffer->incrementator = 0;
    return;
}

bool RingBuffer_Clear(RingBuffer * ringBuffer) {
    if (ringBuffer == NULL) {
        return false;
    }
    ringBuffer->head = ringBuffer->tail = 0;
    ringBuffer->incrementator = 0;
    return true;
}

bool RingBuffer_IsEmpty(RingBuffer const * ringBuffer) {
    if (ringBuffer == NULL) {
        return false;
    }
    if (ringBuffer->incrementator == 0) {
        return true;
    } else {
        return false;
    }
}

size_t RingBuffer_GetLength(RingBuffer const * ringBuffer) {
    if (ringBuffer == NULL) {
        return 0;
    }
    return ringBuffer->incrementator;
}

size_t RingBuffer_getCapacity(RingBuffer const * ringBuffer) {
    if (ringBuffer == NULL) {
        return 0;
    }
    return ringBuffer->bufferSize;
}

bool RingBuffer_GetChar(RingBuffer * ringBuffer, char * c) {
    if (ringBuffer == NULL || c == NULL || ringBuffer->incrementator == 0) {
        return false;
    }
    char * ptr = (char *)ringBuffer->ptr_buffer;
    *c = ptr[ringBuffer->tail];
    ringBuffer->tail++;
    if (ringBuffer->tail >= ringBuffer->bufferSize) {
        ringBuffer->tail = 0;
    }
    ringBuffer->incrementator--;
    return true;
}

bool RingBuffer_PutChar(RingBuffer * ringBuffer, char c) {
    if (ringBuffer == NULL) {
        return false;
    }
    if (ringBuffer->incrementator >= ringBuffer->bufferSize) {
        return false;
    }
    char * ptr = (char *)ringBuffer->ptr_buffer;
    ptr[ringBuffer->head] = c;
    ringBuffer->head++;
    if (ringBuffer->head >= ringBuffer->bufferSize) {
        ringBuffer->head = 0;
    }
    ringBuffer->incrementator++;
    return true;
}

