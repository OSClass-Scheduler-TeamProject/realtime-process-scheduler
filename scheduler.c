// txt 파일로 프로세스의 도착 시간, CPU 버스트 시간, 데드라인이 정해짐
// 프로세스의 도착 시간, CPU 버스트 시간, 데드라인은 , 로 구분되어 있음
#include "function_def.c"

void init_queue(Queue_Node **node, int hyperperiod){
    // Hyper Period 까지 CPU에 실행 중인 작업을 나타내는 큐
    *node = (Queue_Node*)malloc(sizeof(Queue_Node) * hyperperiod);
    for(int i = 0; i < hyperperiod; i++){
        (*node)[i].process_id = -1;
    }
}

// 특정 시간에 작업이 큐에 있는지 확인하고 넣어주는 함수
int refresh_queue(Process *processes, Queue_Node *job_queue, int no_of_process_in_queue, int current_time, int no_of_process){
    for(int i=0; i<no_of_process; i++){
        if(processes[i].arrival_time == current_time){
            job_queue[no_of_process_in_queue].process_id = processes[i].process_id;
            job_queue[no_of_process_in_queue].deadline_time = processes[i].deadline_time;
            job_queue[no_of_process_in_queue].remained_time = processes[i].burst_duration;
            job_queue[no_of_process_in_queue].arrival_time = current_time;
            no_of_process_in_queue++;
        }
    }

    return no_of_process_in_queue;
}

void execute_scheduler(Process *processes, Queue_Node *job_queue, int no_of_process, int hyperperiod){
    int no_of_process_in_queue = 0; // 작업 큐안에 얼마나 있는지
    int which_process_to_run = -1; // 어떤 프로세스가 실행중인지
    int which_pid_to_run = -1; // 실행중인 프로세스의 pid
    int shortest_deadline = 999999999; // 제일 짧은 데드라인인지
    int remained_process = no_of_process;
    int max_deadline = calc_last_deadline(processes, no_of_process);
    // 0부터 hyperperiod 까지 반복
    for(int current_time=0; current_time<=hyperperiod; current_time++){
        // 해당 시간에 들어온 작업이 있나 확인
        no_of_process_in_queue = refresh_queue(processes, job_queue, no_of_process_in_queue, current_time, no_of_process);

        if(job_queue[which_process_to_run].deadline_time < current_time){
            which_process_to_run = -1;
            which_pid_to_run = -1;
            shortest_deadline = 999999999; 
        }
        // 큐 내부 모든 작업에 대해 Deadline이 더 빠른 작업이 있는지 확인
        for(int i=0; i<no_of_process_in_queue; i++){
            if(job_queue[i].process_id != -1 && (job_queue[i].deadline_time - current_time) < shortest_deadline && job_queue[i].deadline_time - current_time > 0 && job_queue[i].remained_time > 0){
                which_process_to_run = i;
                which_pid_to_run = job_queue[i].process_id;
                shortest_deadline = job_queue[i].deadline_time - current_time;
            }
        }


        // 특정 시점에 대해 실행중인 프로세스에 대해 남은 시간 감소
        job_queue[which_process_to_run].remained_time--;
        // printf("현재 시간:%d 실행프로세스:%d 큐 내부 작업:%d\n", current_time, which_pid_to_run, remained_process);
        printf("%d, %d\n", current_time, which_pid_to_run);
        // 종료된 프로세스라면 CPU를 IDLE 상태로 변경
        if(job_queue[which_process_to_run].remained_time == 0){
            job_queue[which_process_to_run].process_id = -1;
            which_pid_to_run = -1;
            shortest_deadline = 999999999;
            remained_process--;
        }

        if(max_deadline == current_time){
            break;
        }
    }

    // 스케줄러 종료 후 남은 프로세스 출력
    for(int i=0; i<no_of_process_in_queue; i++){
        if(job_queue[i].process_id != -1)
            printf("PID:%d Remained:%d\n", job_queue[i].process_id, job_queue[i].remained_time);
    }
}

int main(){
    // txt 파일 읽는 부분
    int no_of_process = read_file();
    printf("총 프로세스 갯수: %d\n", no_of_process);
    
    // for(int i=0; i<no_of_process; i++){
    //     printf("PID:%d Arrive at:%d Burst:%d\n", g_process[i].process_id, g_process[i].arrival_time, g_process[i].burst_duration);
    // }

    int hyperperiod = calc_hyperperiod(g_process, no_of_process);
    printf("CPU Burst Time 최소공배수: %d\n", hyperperiod);

    // 작업 큐
    Queue_Node *job_queue;
    init_queue(&job_queue, hyperperiod);

    // 스케줄러 실행
    execute_scheduler(g_process, job_queue, no_of_process, hyperperiod);

    // Gantt Chart 출력 부분
    return 0;
}