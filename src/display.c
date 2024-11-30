#include <stdio.h>
#include <string.h>
#include "../include/display.h"
#include "../include/utils.h"

void clear_screen() {
    printf("\033[2J\033[H");
}

void hide_cursor() {
    printf("\033[?25l");
}

void show_cursor() {
    printf("\033[?25h");
}

void print_header() {
    printf("\033[1;36m");  // Cyan color
    printf("╔══════════════════════════════════════════╗\n");
    printf("║        Process Scheduler Simulator       ║\n");
    printf("╚══════════════════════════════════════════╝\n");
    printf("\033[0m");  // Reset color
}

void animate_process_execution(Process process, int current_time) {
    printf("\033[K");  // Clear line
    printf("Time %d: Executing Process %d [", current_time, process.id);
    
    int width = 20;
    int progress = (process.burst_time - process.remaining_time) * width / process.burst_time;
    //printf("%d \n",progress);
    
    for (int i = 0; i < width; i++) {
        if (i < progress) {
            printf("\033[1;32m█\033[0m");  // Green blocks for completed
        } else {
            printf("\033[1;31m█\033[0m");  // Red blocks for remaining
        }
    }
    
    printf("] %d%%\n", progress * 100 / width);
    sleep_ms(100);  // Animation delay
}

void print_results(ProcessQueue* queue, const char* algorithm_name) {
    printf("\n\033[1;33m%s Results:\033[0m\n", algorithm_name);
    printf("╔════╦════════╦════════╦══════════╦══════════╦══════════╗\n");
    printf("║ PID║ Arrival║  Burst ║   TAT    ║ Waiting  ║Response  ║\n");
    printf("╠════╬════════╬════════╬══════════╬══════════╬══════════╣\n");
    
    for (int i = 0; i < queue->count; i++) {
        printf("║ %2d ║   %3d  ║   %3d  ║   %3d    ║   %3d    ║   %3d    ║\n",
            queue->processes[i].id,
            queue->processes[i].arrival_time,
            queue->processes[i].burst_time,
            queue->processes[i].turnaround_time,
            queue->processes[i].waiting_time,
            queue->processes[i].response_time);
    }
    
    printf("╚════╩════════╩════════╩══════════╩══════════╩══════════╝\n");
    printf("\nAverage Turnaround Time: %.2f\n", queue->avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", queue->avg_waiting_time);
}

void print_loading_bar(int percentage) {
    printf("\033[K");  // Clear line
    printf("[");
    for (int i = 0; i < 50; i++) {
        if (i < percentage/2) {
            printf("█");
        } else {
            printf(" ");
        }
    }
    printf("] %d%%\r", percentage);
    fflush(stdout);
}


void compare_algorithms(ProcessQueue fcfs, ProcessQueue rr, ProcessQueue priority, ProcessQueue sjf, ProcessQueue srtf) {
    printf("\n\033[1;35mAlgorithm Comparison:\033[0m\n");
    printf("╔══════════════════╦═══════════════╦═══════════════╗\n");
    printf("║     Algorithm    ║    Avg TAT    ║    Avg WT     ║\n");
    printf("╠══════════════════╬═══════════════╬═══════════════╣\n");
    printf("║       FCFS       ║     %.2f     ║     %.2f     ║\n", 
        fcfs.avg_turnaround_time, fcfs.avg_waiting_time);
    printf("║   Round Robin    ║     %.2f     ║     %.2f     ║\n", 
        rr.avg_turnaround_time, rr.avg_waiting_time);
    printf("║    Priority      ║     %.2f     ║     %.2f     ║\n", 
        priority.avg_turnaround_time, priority.avg_waiting_time);
    printf("║       SJF        ║     %.2f     ║     %.2f     ║\n", 
        sjf.avg_turnaround_time, sjf.avg_waiting_time);
    printf("║      SRTF        ║     %.2f     ║     %.2f     ║\n", 
        srtf.avg_turnaround_time, srtf.avg_waiting_time);
    printf("╚══════════════════╩═══════════════╩═══════════════╝\n\n");
    
    // Create array of algorithm metrics for easier comparison
    struct AlgoMetrics {
        const char* name;
        float avg_tat;
        float avg_wt;
        float combined_score;  // Lower is better
    } algorithms[] = {
        {"FCFS", fcfs.avg_turnaround_time, fcfs.avg_waiting_time, 0},
        {"Round Robin", rr.avg_turnaround_time, rr.avg_waiting_time, 0},
        {"Priority", priority.avg_turnaround_time, priority.avg_waiting_time, 0},
        {"SJF", sjf.avg_turnaround_time, sjf.avg_waiting_time, 0},
        {"SRTF", srtf.avg_turnaround_time, srtf.avg_waiting_time, 0}
    };
    
    // Calculate combined score for each algorithm (weighted average of TAT and WT)
    const float TAT_WEIGHT = 0.5;  // Weight for Turnaround Time
    const float WT_WEIGHT = 0.5;   // Weight for Waiting Time
    
    for (int i = 0; i < 5; i++) {
        algorithms[i].combined_score = 
            (TAT_WEIGHT * algorithms[i].avg_tat) + 
            (WT_WEIGHT * algorithms[i].avg_wt);
    }
    
    // Find the best algorithm (lowest combined score)
    int best_index = 0;
    for (int i = 1; i < 5; i++) {
        if (algorithms[i].combined_score < algorithms[best_index].combined_score) {
            best_index = i;
        }
    }
    
    // Print recommendation with detailed explanation
    printf("\033[1;32mRecommended Algorithm: %s\033[0m\n", algorithms[best_index].name);
    printf("Based on:\n");
    printf("- Average Turnaround Time: %.2f\n", algorithms[best_index].avg_tat);
    printf("- Average Waiting Time: %.2f\n", algorithms[best_index].avg_wt);
    printf("This algorithm provides the best balance between turnaround time and waiting time.\n");
    
    // Print close competitors if any exist
    const float THRESHOLD = 1.0;  // Threshold for "close" competitors
    printf("\nClose alternatives:\n");
    int found_alternatives = 0;
    for (int i = 0; i < 5; i++) {
        if (i != best_index && 
            (algorithms[i].combined_score - algorithms[best_index].combined_score) <= THRESHOLD) {
            printf("- %s (TAT: %.2f, WT: %.2f)\n", 
                algorithms[i].name, 
                algorithms[i].avg_tat, 
                algorithms[i].avg_wt);
            found_alternatives = 1;
        }
    }
    if (!found_alternatives) {
        printf("None - %s is significantly better than other algorithms for this workload.\n", 
            algorithms[best_index].name);
    }
}
