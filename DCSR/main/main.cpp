#include <iostream>
#include"dcsr.h"

#define MAX_SIZE 1024 //large buffer.

void print_(long *buffer);

int main() {

    long *offsets = new long [MAX_SIZE] {0,3,3,5,5,7,7,11,11,13}; //Segmentos de tamanho 4.
    long *col_indices = new long [MAX_SIZE] {0,2,3,1,2,3,4,0,1,3,4,0,2};
    long *values = new long [MAX_SIZE] {1,3,4,9,5,7,8,7,2,6,2,11};
    long *row_sizes = new long [MAX_SIZE] {3,2,2,4,2};

    long *B_offsets = new long [20] {0,4,4,8,8,12,12,16};
    long *B_col_indices = new long [8] {1,2,0,3,0,4,1,0};
    long *B_values = new long [8] {3,4,5,0,2,1,5,7};


    user::DCSR dcsr(offsets, col_indices, values, row_sizes, 5);
    dcsr.AllocSegments(B_offsets, B_col_indices, B_values);
    std::cout << "Oioioioi" << std::endl;
    print_(offsets);
    return 0;
}


void print_(long *buffer) {

    long cont = 0;
    std::cout << "[";
    while (cont < 20) {
        std::cout << buffer[cont] << " ";
        cont++;
    }
    std::cout << "]" << '\n';
}
