from time import time

N = 2**24

t1 = time()
tot = 0
for i in range(N):
	tot += i

t2=time()
print(tot)
print("TOOK", t2-t1)
