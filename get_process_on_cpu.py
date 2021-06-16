with open("output.txt", "r") as f:
    lines = f.readlines()
execute_list = []
for line in lines:
    if not line.strip():
        continue
    time, pid = line.strip().split(",")
    execute_list.append((int(time), int(pid)))

start_time, last_pid = execute_list[0]

result = []
for time, pid in execute_list[1:]:
    if last_pid != pid:
        result.append((last_pid, start_time, time))
        start_time = time
        last_pid = pid
result.append((pid, start_time, time))
for pid, start_time, time in result:
    print(f"{pid},{start_time},{time-1}")