#include <stdio.h>
#include "../../include/algorithms.h"
#include "../../include/display.h"
#include "../../include/utils.h"

void round_robin(ProcessQueue* queue, int time_quantum) {
    int current_time = 0;
    int completed = 0;
    float total_turnaround_time = 0;
    float total_waiting_time = 0;
    
    while (completed < queue->count) {
        int flag = 0;
        
        for (int i = 0; i < queue->count; i++) {
            if (queue->processes[i].remaining_time > 0 && 
                queue->processes[i].arrival_time <= current_time) {
                flag = 1;
                
                if (!queue->processes[i].started) {
                    queue->processes[i].response_time = current_time - queue->processes[i].arrival_time;
                    queue->processes[i].started = 1;
                }
                
                animate_process_execution(queue->processes[i], current_time);
                
                if (queue->processes[i].remaining_time > time_quantum) {
                    current_time += time_quantum;
                    queue->processes[i].remaining_time -= time_quantum;
                } else {
                    current_time += queue->processes[i].remaining_time;
                    queue->processes[i].completion_time = current_time;
                    queue->processes[i].remaining_time = 0;
                    completed++;
                    
                    queue->processes[i].turnaround_time = 
                        queue->processes[i].completion_time - queue->processes[i].arrival_time;
                    queue->processes[i].waiting_time = 
                        queue->processes[i].turnaround_time - queue->processes[i].burst_time;
                    
                    total_turnaround_time += queue->processes[i].turnaround_time;
                    total_waiting_time += queue->processes[i].waiting_time;
                }
                animate_process_execution(queue->processes[i], current_time);

            }

        }
        
        if (!flag) current_time++;
    }
    
    queue->avg_turnaround_time = total_turnaround_time / queue->count;
    queue->avg_waiting_time = total_waiting_time / queue->count;
}
