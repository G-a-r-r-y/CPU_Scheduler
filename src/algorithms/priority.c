#include <stdio.h>
#include "../../include/algorithms.h"
#include "../../include/display.h"
#include "../../include/utils.h"

void priority_scheduling(ProcessQueue* queue) {
    int current_time = 0;
    int completed = 0;
    float total_turnaround_time = 0;
    float total_waiting_time = 0;
    
    while (completed < queue->count) {
        int highest_priority = -1;
        int selected_process = -1;
        
        for (int i = 0; i < queue->count; i++) {
            if (queue->processes[i].arrival_time <= current_time && 
                queue->processes[i].remaining_time > 0) {
                if (highest_priority == -1 || 
                    queue->processes[i].priority < highest_priority) {
                    highest_priority = queue->processes[i].priority;
                    selected_process = i;
                }
            }
        }
        
        if (selected_process == -1) {
            current_time++;
            continue;
        }
        
        if (!queue->processes[selected_process].started) {
            queue->processes[selected_process].response_time = 
                current_time - queue->processes[selected_process].arrival_time;
            queue->processes[selected_process].started = 1;
        }
        
        animate_process_execution(queue->processes[selected_process], current_time);
        
        queue->processes[selected_process].remaining_time--;
        current_time++;
        
        if (queue->processes[selected_process].remaining_time == 0) {
            completed++;
            queue->processes[selected_process].completion_time = current_time;
            queue->processes[selected_process].turnaround_time = 
                queue->processes[selected_process].completion_time - 
                queue->processes[selected_process].arrival_time;
            queue->processes[selected_process].waiting_time = 
                queue->processes[selected_process].turnaround_time - 
                queue->processes[selected_process].burst_time;
            
            total_turnaround_time += queue->processes[selected_process].turnaround_time;
            total_waiting_time += queue->processes[selected_process].waiting_time;
        }
        animate_process_execution(queue->processes[selected_process], current_time);

    }
    
    queue->avg_turnaround_time = total_turnaround_time / queue->count;
    queue->avg_waiting_time = total_waiting_time / queue->count;
}
