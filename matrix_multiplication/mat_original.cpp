#include "../Clock.hpp"

int main() {
  constexpr unsigned N=1<<12;

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

  c.ptock();

  for (unsigned long i=0; i<N*N; ++i)
    std::cout << C[i] << " ";
  std::cout << std::endl;

  return 0;
}
