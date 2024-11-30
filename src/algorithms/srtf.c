#include <stdio.h>
#include "../../include/algorithms.h"
#include "../../include/display.h"
#include "../../include/utils.h"

void srtf(ProcessQueue* queue) {
    int current_time = 0;
    int completed = 0;
    float total_turnaround_time = 0;
    float total_waiting_time = 0;
    
    // Initialize remaining times
    for(int i = 0; i < queue->count; i++) {
        queue->processes[i].remaining_time = queue->processes[i].burst_time;
    }
    
    while (completed != queue->count) {
        int shortest_remaining = -1;
        int min_remaining = 9999;
        
        // Find process with minimum remaining time among arrived processes
        for (int i = 0; i < queue->count; i++) {
            if (queue->processes[i].arrival_time <= current_time && 
                queue->processes[i].remaining_time > 0) {
                if (queue->processes[i].remaining_time < min_remaining) {
                    min_remaining = queue->processes[i].remaining_time;
                    shortest_remaining = i;
                }
                // If remaining times are equal, choose the one that arrived earlier
                else if (queue->processes[i].remaining_time == min_remaining) {
                    if (queue->processes[i].arrival_time < 
                        queue->processes[shortest_remaining].arrival_time) {
                        shortest_remaining = i;
                    }
                }
            }
        }
        
        // If no process is available, increment time
        if (shortest_remaining == -1) {
            current_time++;
            continue;
        }
        
        // Calculate response time when process starts for the first time
        if (!queue->processes[shortest_remaining].started) {
            queue->processes[shortest_remaining].response_time = 
                current_time - queue->processes[shortest_remaining].arrival_time;
            queue->processes[shortest_remaining].started = 1;
        }
        
        // Animate process execution
        animate_process_execution(queue->processes[shortest_remaining], current_time);
        
        // Execute process for 1 time unit
        queue->processes[shortest_remaining].remaining_time--;
        current_time++;
        
        // If process completes
        if (queue->processes[shortest_remaining].remaining_time == 0) {
            completed++;
            queue->processes[shortest_remaining].completion_time = current_time;
            
            // Calculate process metrics
            queue->processes[shortest_remaining].turnaround_time = 
                queue->processes[shortest_remaining].completion_time - 
                queue->processes[shortest_remaining].arrival_time;
                
            queue->processes[shortest_remaining].waiting_time = 
                queue->processes[shortest_remaining].turnaround_time - 
                queue->processes[shortest_remaining].burst_time;
                
            total_turnaround_time += queue->processes[shortest_remaining].turnaround_time;
            total_waiting_time += queue->processes[shortest_remaining].waiting_time;
        }
        animate_process_execution(queue->processes[shortest_remaining], current_time);

    }
    
    // Calculate averages
    queue->avg_turnaround_time = total_turnaround_time / queue->count;
    queue->avg_waiting_time = total_waiting_time / queue->count;
}
