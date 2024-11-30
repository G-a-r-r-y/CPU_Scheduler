#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/process.h"
#include "../include/algorithms.h"
#include "../include/display.h"
#include "../include/utils.h"

int main() {
    int n, time_quantum;
    ProcessQueue original_queue;
    ProcessQueue fcfs_queue;
    ProcessQueue rr_queue;
    ProcessQueue priority_queue;
    ProcessQueue sjf_queue;
    ProcessQueue srtf_queue;

    clear_screen();
    print_header();
    
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    
    init_process_queue(&original_queue, n);
    
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i + 1);
        original_queue.processes[i].id = i + 1;
        
        printf("Arrival Time: ");
        scanf("%d", &original_queue.processes[i].arrival_time);
        
        printf("Burst Time: ");
        scanf("%d", &original_queue.processes[i].burst_time);
        
        printf("Priority: ");
        scanf("%d", &original_queue.processes[i].priority);
        
        original_queue.processes[i].remaining_time = original_queue.processes[i].burst_time;
        original_queue.processes[i].started = 0;
    }
    
    printf("\nEnter Time Quantum for Round Robin: ");
    scanf("%d", &time_quantum);
    
    // Create copies for each algorithm
    copy_process_queue(&fcfs_queue, &original_queue);
    copy_process_queue(&rr_queue, &original_queue);
    copy_process_queue(&priority_queue, &original_queue);
    copy_process_queue(&sjf_queue, &original_queue);
    copy_process_queue(&srtf_queue, &original_queue);
    
    clear_screen();
    print_header();
    
    // Run FCFS
    printf("\nRunning FCFS Algorithm...\n");
    fcfs(&fcfs_queue);
    print_results(&fcfs_queue, "FCFS");
    
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    
    // Run Round Robin
    clear_screen();
    print_header();
    printf("\nRunning Round Robin Algorithm...\n");
    round_robin(&rr_queue, time_quantum);
    print_results(&rr_queue, "Round Robin");
    
    printf("\nPress Enter to continue...");
    getchar();
    
    // Run Priority
    clear_screen();
    print_header();
    printf("\nRunning Priority Scheduling Algorithm...\n");
    priority_scheduling(&priority_queue);
    print_results(&priority_queue, "Priority");
    
    printf("\nPress Enter to see comparison...");
    getchar();
    
    
    // Run SJF
    clear_screen();
    print_header();
    printf("\nRunning Shortest Job First Algorithm...\n");
    sjf(&sjf_queue);
    print_results(&sjf_queue, "Shortest Job First");

    printf("\nPress Enter to continue...");
    getchar();

    // Run SRTF
    clear_screen();
    print_header();
    printf("\nRunning Shortest Remaining Time First Algorithm...\n");
    srtf(&srtf_queue);
    print_results(&srtf_queue, "Shortest Remaining Time First");

    printf("\nPress Enter to see comparison...");
    getchar();
    
    
    clear_screen();
    print_header();
    compare_algorithms(fcfs_queue, rr_queue, priority_queue,sjf_queue,srtf_queue);
    
    // Cleanup
    free_process_queue(&original_queue);
    free_process_queue(&fcfs_queue);
    free_process_queue(&rr_queue);
    free_process_queue(&priority_queue);
    return 0;
}
