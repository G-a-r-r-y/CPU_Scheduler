#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int started;
} Process;

typedef struct {
    Process* processes;
    int count;
    float avg_turnaround_time;
    float avg_waiting_time;
} ProcessQueue;

#endif
