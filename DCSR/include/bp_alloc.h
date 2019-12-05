
#ifndef BUMP_ALLOC_H
#define BUMP_ALLOC_H


#include <memory>
#include <functional>
#include <utility>
#include <stdexcept>
#include <list>

namespace user {

template<class T, typename pointer_type = std::shared_ptr<T> >
class bp_alloc {
private:

/*
    Classe bump_pointer allocator, utiliza como padrão de armazenamento o std::shared_ptr,
    os alocadores da classe devem ser compatíveis com as funções do alocador padrão.
*/
    pointer_type storage;
    std::list<size_t> removed; //Lista com os índices dos elementos removidos.
    size_t lenght; //tamanho.

    typedef typename std::list<size_t>::iterator list_it;
    typedef typename std::list<size_t>::const_iterator const_list_it;

protected:

    // Acesso interno ao elementos.
    T &access (size_t i) {
        size_t pos = index_convert(i);
        return storage.get()[pos];
    }

    // Instanciação constante.
    const T &access (size_t i) const {
        size_t pos = index_convert(i);
        return storage.get()[pos];
    }

    // Converte o index global para o local.
    size_t index_convert(size_t i) {
        size_t sum = 0;
        for(list_it it = removed.begin();i > *it && it != removed.end(); ++it) {sum++;}
        size_t pos = i + sum;
        return pos;
    }

public:

    // Construtores.

    explicit bp_alloc (T *data, size_t lenght): storage(std::move(data)), lenght(lenght) {};
    explicit bp_alloc (size_t lenght): storage(std::make_shared<T>(lenght)), lenght(lenght) {};
    bp_alloc () : storage(std::make_shared<T>(0)), removed(),lenght(0){};

    ~bp_alloc (){};

    // Retorno do arranjo dinâmico.
    T* gett() {return (T*) storage.get();}

    // Retorno de um elemento do ponteiro.
    T &operator[] (size_t i) {
        if (i >= lenght) {throw std::out_of_range("Array boundary exceeded!");}
        return this->access(i);
    }

    // Instanciação constante.
    const T &operator[] (size_t i) const {
        if (i >= lenght) {throw std::out_of_range("Array boundary exceeded!");}
        return this->access(i);
    }


    // Tamanho.
    size_t size() {return lenght;}
    const size_t size() const {return lenght;}


    //Adição de elementos. Direta.
    T* back_push(const T data) {
        this->access(lenght++) = data;
        return &this->access(lenght);
    }

    // Inserção no primeiro elemento. Implementar depois...
    T* first_push(const T data) {}

    // Remove o elemento do vetor.
    void remove(size_t pos) {
        pos = index_convert(pos);
        list_it it = removed.begin();
        while (it != removed.end()) {
          if (*it > pos)
            break;
          ++it;
        }
        if (it == removed.end()) { removed.push_back(pos); }
        else { removed.insert(it, pos); }
        lenght--;
    }

    // ITERADORES (FALTA AJUSTAR PARA OS SALTOS DAS REMOÇÕES):
    class iterator {
    public:

        typedef T* pointer;
        typedef T& reference;
        iterator(pointer ptr): pointer_(ptr) {}

        // Precisa considerar salto de remoções.
        iterator operator++() {
            iterator it = *this; ++pointer_;
            return it;
        }

        // Operadores de retorno.
        reference operator*() {return *pointer_;}
        pointer operator->() {return pointer_;}

    private:
        pointer pointer_;
    };

    iterator begin() {return this->gett();}
    iterator end() {return (this->gett() + lenght);}
// ############################################################################################
// Funções extras para teste.
    void print_rev() {

        std::cout << '\n';
        for(const_list_it it = removed.begin(); it != removed.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << '\n';

    }

    void print_() {

        std::cout << '\n';
        for(size_t i = 0; i < lenght; ++i) {
            std::cout << this->access(i) << '\n';
        }
        std::cout << '\n';
    }
};
}

#endif
