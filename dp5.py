import numpy as np
import time
import sys

N, repetitions = [int(x) for x in input().split()]

pA = np.ones(N,dtype=np.float32)
pB = np.ones(N,dtype=np.float32)
  
halfOfRepetions = repetitions // 2
allProgramLengthTimes = []

for i in range(repetitions):
  start = time.perf_counter()
  res = numpy.dot(pA, pB)
  end = time.perf_counter()
  if i >= halfOfRepetions:
    programLengthTime = (end - start) 
    allProgramLengthTimes.append(programLengthTime)

print(res, file=sys.stderr)
totalTime = 0.0
for repetitionTime in allProgramLengthTimes:
  totalTime += repetitionTime
  
averageTime = totalTime / len(allProgramLengthTimes)
bytesPerCall = 2.0 * 4.0 * N
bandwidth = (bytesPerCall / 1.0e9) / averageTime
flops = (2.0 * N) / averageTime

print(f"N: {N} <T>: {averageTime:.6f} sec B: {bandwidth:.3f} GB/sec F: {flops:.3f} FLOP/sec")