#include "headers/file_reader.h"

int calc_hyperperiod(Process *processes, int no_of_processes)
{
	int lcm = processes[0].burst_duration;
	int a, b;
	for(int i = 1 ; i < no_of_processes ; i++)
	{
		a = lcm;
		b = processes[i].burst_duration;
		while(a != b)
		{
			if (a > b)
				a = a - b;
			else
				b = b - a;
		}
		
		lcm = (lcm * processes[i].burst_duration) / a;
	}
	return lcm;
} 


int calc_last_deadline(Process *processes, int no_of_processes){
    int deadline = -1;
    for(int i=0; i<no_of_processes; i++){
        if(processes[i].deadline_time > deadline){
            deadline = processes[i].deadline_time;
        }
    }
    return deadline;
}