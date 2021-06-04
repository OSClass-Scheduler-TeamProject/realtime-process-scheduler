# EDF Schedule

## input.txt

| Arrival_time | CPU_time  | Dead_line(Only Real Time) |
| ------------ | --------- | ------------------------- |
| \<entry\>    | \<entry\> | \<entry\>                 |

## process struct

```c
typedef struct Process
{
    int process_id;    // 프로세스 번호
    int arrival_time;   // 도착 시간
    int burst_duration; // 수행 시간
    int deadline_time;  // 데드라인 (실시간)
} Process;
```


```c
typedef struct Queue_Node
{
    int process_id;    // 프로세스 번호
    int arrival_time;   // 도착 시간
    int remained_time;   // 수행 후 남아있는 시간
    int deadline_time;  // 데드라인 (실시간)
} Queue_Node;
```


## use flow

1. input.txt 파일을 읽어온다.
2. `,`으로 데이터를 구분해서 프로세스 정보를 저장한다.
3. 프로세스 큐에(init queue) 넣어준다.
4. EDF 스케줄링을 통해 프로세스를 실행 시켜준다.

## How to Use

```bash
gcc <YOUR-PATH>/scheduler.c
./a.out
```