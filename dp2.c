#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <errno.h>

float dpunroll(long N, float *pA, float *pB)
{
  float R = 0.0;
  long j;
  for (j=0;j<N;j+=4)
    R += pA[j]*pB[j] + pA[j+1]*pB[j+1] \
           + pA[j+2]*pB[j+2] + pA[j+3] * pB[j+3];
return R;
}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s <N> <reps>\n", argv[0]);
    return 1;
  }

  long N = strtol(argv[1], NULL, 10);
  long repetitions = strtol(argv[2], NULL, 10);

  float *pA = malloc(sizeof(float) * (size_t)N);
  float *pB = malloc(sizeof(float) * (size_t)N);

  if (pA == NULL || pB == NULL)
  {
    fprintf(stderr, "Error allocating memory: %s\n", strerror(errno));
    free(pA);
    free(pB);
    return 1;
  }

  // fill values of pA and pB
  for (long k = 0; k < N; k++)
  {
    pA[k] = 1.0f;
    pB[k] = 1.0f;
  }

  struct timespec t0, t1;
  long halfOfRepetitions = repetitions/2;
  double* allProgramLengthTimes= malloc(sizeof(double) * halfOfRepetitions); 

  float res = 0.0f;
  for (long i = 0; i < repetitions; i++)
  {
    clock_gettime(CLOCK_MONOTONIC, &t0);
    res = dpunroll((long)N, pA, pB);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    if (i >= halfOfRepetitions)
    { 
        allProgramLengthTimes[i-halfOfRepetitions] = ((double)t1.tv_sec - (double)t0.tv_sec) + ((double)t1.tv_nsec - (double)t0.tv_nsec) * 1e-9;
    }
  }
  fprintf(stderr, "Result: %f\n", res);

  double totalTime = 0.0;
  for (long i = 0; i < halfOfRepetitions; i++) {
    totalTime += allProgramLengthTimes[i];
  }
  double averageTime = totalTime / halfOfRepetitions;
  double bytesPerCall = 2.0 * (double)sizeof(float) * (double)N;
  double bandwidth = (bytesPerCall / 1e9) / averageTime;
  double flops = (2.0 * (double)N) / averageTime;

  printf("N: %ld <T>: %.6f sec B: %.3f GB/sec F: %.3f FLOP/sec\n", N, averageTime, bandwidth, flops);

  free(pA); 
  free(pB); 
  free(allProgramLengthTimes);
  return 0;
}