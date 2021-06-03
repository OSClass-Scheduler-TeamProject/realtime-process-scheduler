import random

max_process = 40
max_set_size = 20
no_process = 0

process_list = []
insert_time = 1
set_start_time = 1

while no_process < max_process:
    set_size = random.randint(1, min(max_set_size, max_process - no_process))
    set_burst_time = 0
    process_set = []
    insert_time = set_start_time
    for _ in range(set_size):
        burst_time = random.randint(1, 10)
        process_set.append((insert_time, burst_time))
        insert_time += 1
        set_burst_time += burst_time
    for insert_time, burst_time in process_set:
        process_list.append((insert_time, burst_time, random.randint(insert_time + burst_time, set_start_time + set_burst_time)))
    set_start_time += set_burst_time
    no_process += set_size

for insert_time, burst_time, deadline in process_list:
    print(f"{insert_time},{burst_time},{deadline}")