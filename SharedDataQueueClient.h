#ifndef SharedDataQueueClient_h
#define SharedDataQueueClient_h

#include <stdint.h>
#include <IOKit/IODataQueueShared.h>

typedef uint32_t (*IODataQueueClientEnqueueReadBytesCallback)(void * refcon, void *data, uint32_t dataSize);

typedef IODataQueueEntry *(*IODataQueuePeek_fn_ptr)(IODataQueueMemory *dataQueue);
typedef IOReturn (*IODataQueueDequeue_fn_ptr)(IODataQueueMemory *dataQueue, void *data, uint32_t *dataSize);
typedef IOReturn (*IODataQueueEnqueue_fn_ptr)(IODataQueueMemory *dataQueue, void *data, uint32_t dataSize);
typedef IOReturn (*IODataQueueEnqueueWithReadCallback_fn_ptr)(IODataQueueMemory *dataQueue, uint32_t dataSize, IODataQueueClientEnqueueReadBytesCallback callback, void * refcon);

#endif /* SharedDataQueueClient_h */
