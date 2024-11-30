#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "process.h"

void fcfs(ProcessQueue* queue);
void round_robin(ProcessQueue* queue, int time_quantum);
void priority_scheduling(ProcessQueue* queue);
void sjf(ProcessQueue* queue);           // Added Shortest Job First
void srtf(ProcessQueue* queue);          // Added Shortest Remaining Time First

#endif

