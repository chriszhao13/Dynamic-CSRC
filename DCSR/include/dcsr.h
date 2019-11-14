#include <iostream>

#ifndef DCSR_H
#define DCSR_H

namespace user {

class DCSR
{

private:

    long *offsets;
    long *col_indices;
    long *values;
    long *row_sizes;
    size_t matrix_size;
    long pitch; // Distância para o próximo segmento.
    int seg_size; //Tamanho do segmento.
    long *seg_ptr; //Ponteiro para a identificação do índice do segmento atual.

public:
    DCSR(int seg_size = 4);
    explicit DCSR(long *offsets, long *col_indices,
                  long *values, long *row_sizes, size_t matrix_size, long *seg_ptr, int seg_size = 4);

    ~DCSR();
    //Alocando segmentos e definindo os tamanhos dos vetores.
    void AllocSegments(long *B_offsets, long *B_cols, long *B_vals);
    //Inserindo elementos na matriz principal.
    void InsertElements(long *B_offsets, long *B_cols, long *B_vals, size_t row, long idx, int sid);

};
}
#endif // DCSR_H
