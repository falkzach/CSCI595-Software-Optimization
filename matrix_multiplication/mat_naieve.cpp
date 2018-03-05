#include "../Clock.hpp"
#include <stdlib.h>
#include <iostream>

__attribute__ ((noinline))
void transpose(double*__restrict dest, double*__restrict source, const unsigned long r, const unsigned long c) {
  for (unsigned long i=0; i<r; ++i) {
    for (unsigned long j=0; j<c; ++j) {
      dest[j*r + i] = source[i*c +j];
    }
  }
}

void square_mat_mul(double* & A, double* & B, double* & C, unsigned long N) {
  for (unsigned long i=0; i<N; ++i) {
    for (unsigned long j=0; j<N; ++j) {
      for (unsigned long k=0; k<N; ++k) {
        C[(i*N) + j] += ( A[(i*N)+k] * B[(k*N)+j] );
      }
    }
  }
}

void fast_square_mat_mul(double* & A, double* & B, double* & C, unsigned long N) {
  double* t_B = new double[N*N];
  transpose(t_B, B, N, N);
  for (unsigned long j=0; j<N; ++j) {
    for (unsigned long i=0; i<N; ++i) {
      for (unsigned long k=0; k<N; ++k) {
        C[(i*N) + j] += ( A[(i*N)+k] * t_B[(j*N)+k] );
      }
    }
  }
}

int main() {
//  constexpr unsigned N=1<<2;
  constexpr unsigned N=1<<10;
//  constexpr unsigned N=1<<12;

  srand(0);

  double*A=new double[N*N];
  double*B=new double[N*N];

  for (unsigned long i=0; i<N*N; ++i)
    A[i] = (rand() % 1000)/999.0;
  for (unsigned long i=0; i<N*N; ++i)
    B[i] = (rand() % 1000)/999.0;
  
  double*C=new double[N*N];

  Clock c;

  // TODO: Compute matrix product in C:
  // C = A*B, means
  // C[i,j] = A[i,0]*B[0,j] + A[i,1]*B[1,j] + ... + A[0,N-1]*B[N-1,j]
    square_mat_mul(A, B, C, N);
//  fast_square_mat_mul(A, B, C, N);

  c.ptock();

  for (unsigned long i=0; i<N*N; ++i)
    std::cout << C[i] << " ";
  std::cout << std::endl;

//  C=new double[N*N];
//
//  c.tock();
//
//  square_mat_mul(A, B, C, N);
//
//  c.ptock();

//  for (unsigned long i=0; i<N*N; ++i)
//    std::cout << C[i] << " ";
//  std::cout << std::endl;

  return 0;
}
