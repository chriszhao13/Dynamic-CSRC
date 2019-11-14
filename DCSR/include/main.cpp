#include <iostream>
#include"dcsr.h"
#include "bp_alloc.h"
#define MAX_SIZE 1024 //large buffer.

void print_(long *buffer);

int main() {

    long *stor = new long [MAX_SIZE] {1,2,3,4,5,6,7,8,9};

    user::bp_alloc<long> a(stor, 9);
    std::cout << a[2] << '\n';


    // std::cout << a[9] << '\n';
    // std::cout << a.size() << '\n';
    a.remove(1);
    std::cout << a[7] << '\n';
    a.remove(7);
    // std::cout << a[7] << '\n';
    a.back_push(100);
    a.print_rev();
    a.print_();
    // std::cout << a.size() << '\n';
    // long *offsets = new long [MAX_SIZE] {0,4,4,8,8,12,12,16,-1,-1,-1,-1,-1,-1,-1,-1}; //Segmentos de tamanho 4.
    // long *off_ptr = &offsets[7];
    // long *col_indices = new long [MAX_SIZE] {0,2,3,0,1,2,0,0,3,4,0,0,2,0,1,3,4};//Alguns zeros marcam um elemento vazio.
    // long *values = new long [MAX_SIZE] {1,3,4,0,9,5,0,0,7,8,0,0,7,2,8,6};
    // long *row_sizes = new long [MAX_SIZE] {3,2,2,4};
    //
    // long *B_offsets = new long [20] {0,2,2,3,3,3,3,6};
    // long *B_col_indices = new long [8] {1,4,2,2,9,7};
    // long *B_values = new long [8] {1,2,3,1,8,4};
    //
    // user::DCSR dcsr(offsets, col_indices, values, row_sizes, 4, off_ptr);
    // dcsr.AllocSegments(B_offsets, B_col_indices, B_values);
    // std::cout << "Oioioidfsdfoi" << std::endl;
    // print_(offsets);
    // print_(col_indices);
    // print_(values);
    return 0;
}


void print_(long *buffer) {

    long cont = 0;
    std::cout << "[";
    while (cont < 16) {
        std::cout << buffer[cont] << " ";
        cont++;
    }
    std::cout << "]" << '\n';
}
