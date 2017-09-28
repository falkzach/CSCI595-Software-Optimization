#include "Clock.hpp"
#include <iostream>

void selection_sort(unsigned long*source, const unsigned long n) {
    for (unsigned long i=0; i<n; ++i) {
        for (unsigned long j=i+1; j<n; ++j) {
            if(source[j] < source[i]) {
                std::swap(source[i], source[j]);
            }
        }
    }
}

void merge_sort(unsigned long*source, const unsigned long n, const unsigned long k) {
    if (n <= k) {
        selection_sort(source, n);
        return;
    }

    unsigned long*source_2 = source + n/2;
    merge_sort(source, n/2, k);
    merge_sort(source_2, n-n/2, k);

    unsigned long*buffer = new unsigned long[n];
    //Merge sorted halves into buffer:
    unsigned long i=0, j=0, buffer_ind=0;
    while ( (i<n/2) && (j < (n-n/2)) ) {
        if (source[i] < source_2[j]) {
            buffer[buffer_ind] = source[i];
            ++i;
        } else {
            buffer[buffer_ind] = source_2[j];
            ++j;
        }

        ++buffer_ind;
    }

    for (; i<n/2;++i, ++buffer_ind) {
        buffer[buffer_ind] = source[i];
    }
    for (; j<n-n/2; ++j, ++buffer_ind) {
        buffer[buffer_ind] = source_2[j];
    }

    // Copy sorted list from buffer
    for(i=0; i<n; ++i) {
        source[i] = buffer[i];
    }


    delete[] buffer;
}

int main(int argc, char**argv) {
    if(argc == 3) {
        const unsigned long N = atoi(argv[1]);
        const unsigned long K = atoi(argv[2]);

        unsigned long*x = new unsigned long[N];

        for (unsigned long i=0; i<N; ++i) {
            x[i] = N-i;
        }

        Clock c;
        merge_sort(x, N, K);
        c.ptock();

    } else {
        std::cerr << "Usage: sort <n> <k>" <<std::endl;
    }
    return 0;
}
