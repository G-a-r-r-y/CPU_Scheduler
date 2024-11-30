#ifndef UTILS_H
#define UTILS_H

#include "process.h"

void init_process_queue(ProcessQueue* queue, int count);
void copy_process_queue(ProcessQueue* dest, ProcessQueue* src);
void free_process_queue(ProcessQueue* queue);
void sleep_ms(int milliseconds);
void reset_process_queue(ProcessQueue* queue);

#endif
