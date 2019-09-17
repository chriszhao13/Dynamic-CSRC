#include "dcsr.h"

user::DCSR::DCSR(int seg_size) :
    offsets(),
    col_indices(),
    values(),
    row_sizes(),
    seg_ptr(),
    seg_size(seg_size)
{}


user::DCSR::DCSR(long *offsets, long *col_indices,
           long *values, long *row_sizes, size_t matrix_size, long *seg_ptr, int seg_size) :
    offsets(offsets),
    col_indices(col_indices),
    values(values),
    row_sizes(row_sizes),
    matrix_size(matrix_size),
    pitch(matrix_size * 2),
    seg_ptr(seg_ptr),
    seg_size(seg_size)
{}

user::DCSR::~DCSR() {
    offsets = nullptr;
    col_indices = nullptr;
    values = nullptr;
    seg_ptr = nullptr;
    row_sizes = nullptr;
}


void user::DCSR::AllocSegments(long *B_offsets, long *B_cols, long *B_vals) {

    size_t row = 0;
    while (row < matrix_size) {

        std::cout << "Para row = " << row << '\n';
        int sid = 0; //Índice dos segmentos.
        int row_len = row_sizes[row]; //Dimensão da linha.
        long idx = 0; //Índice da linha. (Precisa de melhor entendimento)

        long seg_start = offsets[row * 2]; //Início do par do segmento.
        long seg_end = offsets[row * 2 + 1]; //Fim do par do segmento.

        std::cout << "seg_start = " << seg_start << " e " << "seg_end = " << seg_end << "\n";

        long free_memory = 0; //Memória livre do segmento atual.
        //Verificar para casos em que B tiver linhas diferentes.
        long B_row_len = B_offsets[row * 2 + 1] - B_offsets[row * 2];

        if (row_len >= 0) { // Entender..
            while (idx < row_len) {
                idx += seg_end - seg_start;
                std::cout << "idx (linha 50) = " << idx << "\n";
                if (idx < row_len) {
                    sid = sid + 1; //Atualiza índice do segmento para o pŕoximo.
                    std::cout << "sid" << sid << "\n";
                    seg_start = offsets[(sid * pitch) + (row * 2)]; //Verificar implementação do pitch.
                    seg_end = offsets[(sid * pitch) + (row * 2) + 1];
                    std::cout << "seg_start = " << seg_start << "\n";
                    std::cout << "seg_end = " << seg_end;
                }
            }
            idx = seg_end + row_len - idx;
        }
        else idx = seg_start; //Precisa de melhor entendimento.
        std::cout << "idx (linha 64) = " << idx <<'\n';
        std::cout << "======================================================================" << '\n';
        free_memory = seg_end - seg_start;

        if (free_memory < B_row_len && B_row_len > 0) {
            //Alocando memória dos segmentos, alterado da função atomicAdd.
           offsets[(sid + 1) * pitch + (row * 2)] = *seg_ptr;
           offsets[(sid + 1) * pitch + (row * 2) + 1] = *seg_ptr + seg_size;
           seg_ptr = &offsets[(sid + 1) * pitch + (row * 2) + 1];
        }
        //Algoritmo para a inserção de elementos, implementar depois.
        InsertElements(B_offsets, B_cols, B_vals, row, idx, sid);

        ++row;
    }
}

//Inserindo elementos (utilizando os vetores de uma matiz B). Incompleta.
void user::DCSR::InsertElements(long *B_offsets, long *B_cols, long *B_vals, size_t row, long idx, int sid) {

    long B_idx = B_offsets[row * 2];
    long pos, seg_start, seg_end;

    //Verifica se o índice do elemento é menor que o offset final do segmento.
    while (B_idx < B_offsets[(row * 2) + 1]) {
        //Verifica se o índice da matriz principal é menor que o offset final da linha considerada.
        if (idx >= offsets[(row * 2) + 1]) {
            pos = idx - offsets[(row * 2) + 1];
            sid += 1;
            seg_start = offsets[(sid * pitch) + (row * 2)];
            seg_end = offsets[(sid * pitch) + (row * 2) + 1];
            //Atualiza o índice para o valor após o offset final.
            idx = seg_start + pos;
        }
        //Alocação dos valores.
        col_indices[idx] = B_cols[B_idx];
        values[idx] = B_vals[B_idx];
        B_idx += 1;
        idx += 1;
        //..... Verificar atualização de B_idx e idx.
    }
}
