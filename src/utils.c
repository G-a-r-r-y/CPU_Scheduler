#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/utils.h"

void init_process_queue(ProcessQueue* queue, int count) {
    queue->count = count;
    queue->processes = (Process*)malloc(count * sizeof(Process));
    queue->avg_turnaround_time = 0;
    queue->avg_waiting_time = 0;
}

void copy_process_queue(ProcessQueue* dest, ProcessQueue* src) {
    init_process_queue(dest, src->count);
    memcpy(dest->processes, src->processes, src->count * sizeof(Process));
    dest->avg_turnaround_time = src->avg_turnaround_time;
    dest->avg_waiting_time = src->avg_waiting_time;
}

void free_process_queue(ProcessQueue* queue) {
    free(queue->processes);
    queue->count = 0;
    queue->processes = NULL;
}

void sleep_ms(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

void reset_process_queue(ProcessQueue* queue) {
    for (int i = 0; i < queue->count; i++) {
        queue->processes[i].remaining_time = queue->processes[i].burst_time;
        queue->processes[i].completion_time = 0;
        queue->processes[i].turnaround_time = 0;
        queue->processes[i].waiting_time = 0;
        queue->processes[i].response_time = 0;
        queue->processes[i].started = 0;
    }
    queue->avg_turnaround_time = 0;
    queue->avg_waiting_time = 0;
}
