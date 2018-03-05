#include "../Clock.hpp"
#include <stdlib.h>
#include <iostream>
#include <omp.h>

constexpr unsigned int BLOCK_SIZE = 4;
constexpr unsigned int MAT_BLOCK_SIZE = 8;

static void recursive_transpose_buffered_helper(
        double *__restrict dest, double *__restrict source, const unsigned long R, const unsigned long C,
        const unsigned long r_start, const unsigned long r_end, const unsigned long c_start, const unsigned long c_end) {

  unsigned long r_span = r_end - r_start;
  unsigned long c_span = c_end - c_start;

  if ( r_span <= BLOCK_SIZE && c_span <= BLOCK_SIZE ) {
    for (unsigned long r=r_start; r<r_end; ++r)
      for (unsigned long c=c_start; c<c_end; ++c)
        dest[c*R +r] = source[r*C + c];
  } else {
    if (r_span > c_span) {
      recursive_transpose_buffered_helper(dest, source, R, C, r_start, r_start+r_span/2, c_start, c_end);
      recursive_transpose_buffered_helper(dest, source, R, C, r_start+r_span/2, r_end, c_start, c_end);
    } else {
      recursive_transpose_buffered_helper(dest, source, R, C, r_start, r_end, c_start, c_start+c_span/2);
      recursive_transpose_buffered_helper(dest, source, R, C, r_start, r_end, c_start+c_span/2, c_end);
    }
  }
}

__attribute__ ((noinline))
void recursive_transpose(double*__restrict dest, double*__restrict source, const unsigned long r, const unsigned long c) {
  recursive_transpose_buffered_helper(dest, source, r, c, 0, r, 0, c);
}

__attribute__ ((noinline))
void fast_square_mat_mul(double*__restrict & A, double*__restrict & B, double*__restrict & C, unsigned long N) {
  double* t_B = new double[N*N];
  recursive_transpose(t_B, B, N, N);
  unsigned long j, i, k;
#pragma omp parallel for private(j, i, k) shared(A, t_B, C) schedule(guided)
    for (j=0; j<N; ++j) {
      for (i=0; i<N; ++i) {
        for (k=0; k<N; ++k) {
            C[(i*N) + j] += ( A[(i*N)+k] * t_B[(j*N)+k] );
      }
    }
  }
}

int main() {
  constexpr unsigned N=1<<12;

  srand(0);

  double*A=new double[N*N];
  double*B=new double[N*N];

  for (unsigned long i=0; i<N*N; ++i)
    A[i] = (rand() % 1000)/999.0;
  for (unsigned long i=0; i<N*N; ++i)
    B[i] = (rand() % 1000)/999.0;

  double*C=new double[N*N]();

  Clock c;

  // TODO: Compute matrix product in C:
  // C = A*B, means
  // C[i,j] = A[i,0]*B[0,j] + A[i,1]*B[1,j] + ... + A[0,N-1]*B[N-1,j]
  fast_square_mat_mul(A, B, C, N);

  c.ptock();

  for (unsigned long i=0; i<N*N; ++i)
    std::cout << C[i] << " ";
  std::cout << std::endl;

  return 0;
}
