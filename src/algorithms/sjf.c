#include <stdio.h>
#include "../../include/algorithms.h"
#include "../../include/display.h"
#include "../../include/utils.h"

void sjf(ProcessQueue* queue) {
    int current_time = 0;
    int completed = 0;
    float total_turnaround_time = 0;
    float total_waiting_time = 0;
    
    // Initialize remaining times
    for(int i = 0; i < queue->count; i++) {
        queue->processes[i].remaining_time = queue->processes[i].burst_time;
    }
    
    while (completed != queue->count) {
        int shortest_job = -1;
        int min_burst = 9999;
        
        // Find process with minimum burst time among arrived processes
        for (int i = 0; i < queue->count; i++) {
            if (queue->processes[i].arrival_time <= current_time && 
                queue->processes[i].remaining_time > 0) {
                if (queue->processes[i].burst_time < min_burst) {
                    min_burst = queue->processes[i].burst_time;
                    shortest_job = i;
                }
                // If burst times are equal, choose the one that arrived earlier
                else if (queue->processes[i].burst_time == min_burst) {
                    if (queue->processes[i].arrival_time < 
                        queue->processes[shortest_job].arrival_time) {
                        shortest_job = i;
                    }
                }
            }
        }
        
        // If no process is available, increment time
        if (shortest_job == -1) {
            current_time++;
            continue;
        }
        
        // Calculate response time when process starts
        if (!queue->processes[shortest_job].started) {
            queue->processes[shortest_job].response_time = 
                current_time - queue->processes[shortest_job].arrival_time;
            queue->processes[shortest_job].started = 1;
        }
        
        // Animate process execution
        animate_process_execution(queue->processes[shortest_job], current_time);
        
        // Execute the process completely (non-preemptive)
        current_time += queue->processes[shortest_job].burst_time;
        queue->processes[shortest_job].remaining_time = 0;
        queue->processes[shortest_job].completion_time = current_time;
        
        // Calculate process metrics
        queue->processes[shortest_job].turnaround_time = 
            queue->processes[shortest_job].completion_time - 
            queue->processes[shortest_job].arrival_time;
            
        queue->processes[shortest_job].waiting_time = 
            queue->processes[shortest_job].turnaround_time - 
            queue->processes[shortest_job].burst_time;
            
        total_turnaround_time += queue->processes[shortest_job].turnaround_time;
        total_waiting_time += queue->processes[shortest_job].waiting_time;
        
        completed++;
        animate_process_execution(queue->processes[shortest_job], current_time);

    }
    
    // Calculate averages
    queue->avg_turnaround_time = total_turnaround_time / queue->count;
    queue->avg_waiting_time = total_waiting_time / queue->count;
}
