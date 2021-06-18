#include <iostream>
#include<omp.h>

//using namespace std;

int main(void) {
  float a[10000], b[10000], c[10000];
  int i;

  /* Initialize arrays a and b */
  for (i = 0; i < 10000; i++) {
    a[i] = i * 2.0;
    b[i] = i * 3.0;
  }

 /* Compute values of array c = a+b in parallel. */
  #pragma omp parallel shared(a, b, c) private(i)
  {
    #pragma omp for
    for (i = 0; i < 10000; i++) {
      c[i] = a[i] + b[i];
    }
    //printf ("%f\n", c[10]);
  }
  printf ("%f\n", c[10]);
}
