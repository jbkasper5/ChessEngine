from subprocess import Popen, STDOUT, PIPE
import time

p = Popen(['./engine/engine'], stdout=PIPE, stdin=PIPE, stderr=PIPE)
ba = bytearray([1])
# stdout_data = p.communicate(input=ba)[0]
# print(f"Received data: {stdout_data.decode()}")
# new_ba = bytearray([10])
# stdout_data = p.communicate(input=new_ba)[0]
# print(f"Received data: {stdout_data.decode()}")

# p = Popen(['./upline.py'], stdout=PIPE, stdin=PIPE)

p.stdin.write(ba)
p.stdin.flush()
print(p.stdout.readline().decode()[:-1])

ba = bytearray([5])
p.stdin.write(ba)
p.stdin.flush()
print(p.stdout.readline().decode()[:-1])


# time.sleep(1)

# p.stdin.write('bonne journeé\n'.encode())
# p.stdin.flush()
# print(p.stdout.readline().decode()[:-1])

# time.sleep(1)

# p.stdin.write('goodbye world\n'.encode())
# p.stdin.flush()
# print(p.stdout.readline().decode()[:-1])