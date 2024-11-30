#ifndef DISPLAY_H
#define DISPLAY_H

#include "process.h"

void clear_screen();
void print_header();
void print_menu();
void show_cursor();
void hide_cursor();
void animate_process_execution(Process process, int current_time);
void print_results(ProcessQueue* queue, const char* algorithm_name);
void compare_algorithms(ProcessQueue fcfs, ProcessQueue rr, ProcessQueue priority, ProcessQueue sjf, ProcessQueue srtf);
void print_loading_bar(int percentage);

#endif
