#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <errno.h>

float dp(long N, float *pA, float *pB)
{
  float R = 0.0;
  long j;
  for (j = 0; j < N; j++)
    R += pA[j] * pB[j];
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
  long repititions = strtol(argv[2], NULL, 10);

  float *pA = malloc(sizeof(float) * N);
  float *pB = malloc(sizeof(float) * N);

  // fill values of pA and pB
  for (int k = 0; k < N; k++)
  {
    pA[k] = 1.0f;
    pB[k] = 1.0f;
  }

  struct timespec t0, t1;
  long halfOfRepititions = repititions/2;
  double* allProgramLengthTimes= malloc(sizeof(double) * halfOfRepititions); 

  for (long i = 0; i < repititions; i++)
  {
    clock_gettime(CLOCK_MONOTONIC, &t0);
    float res = dp((long)N, pA, pB);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    if (i >= halfOfRepititions)
    { 
        allProgramLengthTimes[i-halfOfRepititions] = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) * 1e-9;
    }
    fprintf(stderr, "Result: %f\n", res);
  }

  double totalTime = 0.0;
  for (long i = 0; i < halfOfRepititions; i++) {
    totalTime += allProgramLengthTimes[i];
  }
  double averageTime = totalTime / halfOfRepititions;
  printf("N: %ld <T>: %f sec B: <TODO> GB/sec F: <TODO> FLOP/sec", N, averageTime);

  free(pA); 
  free(pB); 
  free(allProgramLengthTimes);
}