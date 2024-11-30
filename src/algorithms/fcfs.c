#include <stdio.h>
#include "../../include/algorithms.h"
#include "../../include/display.h"
#include "../../include/utils.h"

void fcfs(ProcessQueue* queue) {
    int current_time = 0;
    float total_turnaround_time = 0;
    float total_waiting_time = 0;
    
    for (int i = 0; i < queue->count - 1; i++) {
        for (int j = 0; j < queue->count - i - 1; j++) {
            if (queue->processes[j].arrival_time > queue->processes[j + 1].arrival_time) {
                Process temp = queue->processes[j];
                queue->processes[j] = queue->processes[j + 1];
                queue->processes[j + 1] = temp;
            }
        }
    }
    
    for (int i = 0; i < queue->count; i++) {
        if (current_time < queue->processes[i].arrival_time) {
            current_time = queue->processes[i].arrival_time;
        }
        
        queue->processes[i].response_time = current_time - queue->processes[i].arrival_time;
        
        animate_process_execution(queue->processes[i], current_time);
        
        current_time += queue->processes[i].burst_time;
        queue->processes[i].completion_time = current_time;
        queue->processes[i].turnaround_time = 
            queue->processes[i].completion_time - queue->processes[i].arrival_time;
        queue->processes[i].waiting_time = 
            queue->processes[i].turnaround_time - queue->processes[i].burst_time;
        
        total_turnaround_time += queue->processes[i].turnaround_time;
        total_waiting_time += queue->processes[i].waiting_time;
        queue->processes[i].remaining_time=0;
        animate_process_execution(queue->processes[i], current_time);
    }
    
    queue->avg_turnaround_time = total_turnaround_time / queue->count;
    queue->avg_waiting_time = total_waiting_time / queue->count;
}
