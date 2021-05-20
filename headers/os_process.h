#ifndef OS_PROCESS_H
#define OS_PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESS 512
#define MAX_QUEUE 256

typedef struct Process
{
    int process_id;    // 프로세스 번호
    int arrival_time;   // 도착 시간
    int burst_duration; // 수행 시간
    int deadline_time;  // 데드라인 (실시간)
} Process;

typedef struct Queue_Node
{
    int process_id;    // 프로세스 번호
    int arrival_time;   // 도착 시간
    int remained_time;   // 수행 후 남아있는 시간
    int deadline_time;  // 데드라인 (실시간)
} Queue_Node;

Process g_process[MAX_PROCESS];

#endif