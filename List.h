#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <stdexcept>

struct Node 
{
    int value;
    Node *prev;
    Node *next;

    Node(const int& val, Node *prevPtr, Node *nextPtr)
    {
        value = val;
        prev = prevPtr;
        next = nextPtr;
    }

    ~Node() {
        std::cout << "removido: " << value << std::endl;
    }
};


//codigo reutilizado de 25 de maio
class List {
private:
    Node *m_head;    // ponteiro para o no sentinela
    size_t m_size;   // numero de elementos na lista

public:
    // classe que implementa um iterador para a lista
    class iterator {
    private:
        Node *pointer;
    public:
        iterator() {
            pointer = nullptr;
        }
        iterator(const iterator& it) {
            pointer = it.pointer;
        }
        iterator(Node *ptr) {
            pointer = ptr;
        }
        bool operator!=(const iterator& it) {
            return this->pointer != it.pointer;
        }
        bool operator==(const iterator& it) {
            return this->pointer == it.pointer;
        }
        int& operator*() {
            return pointer->value;
        }
        iterator operator++() {
            pointer = pointer->next;
            return *this;
        }
        iterator operator++(int) {
            iterator it_old(pointer);
            pointer = pointer->next;
            return it_old;
        }
        iterator operator=(const iterator& it) {
            pointer = it.pointer;
            return *this;
        }
    };

    // retorna um iterador apontando para o primeiro elemento da lista
    // se a lista estiver vazia, ele aponta para m_head
    iterator begin() {
        return iterator(m_head->next);
    }

    // retorna um iterador apontando para o final da lista, ou seja, 
    // para o node sentinela m_head
    iterator end() {
        return iterator(m_head);
    }

    // construtor: cria uma lista vazia
    // complexidade O(1)
    List() {
        m_head = new Node(0,nullptr,nullptr);
        m_head->next = m_head;
        m_head->prev = m_head;
        m_size = 0;
    }

    // construtor de copia: cria uma copia da lista dada
    // complexidade O(n)
    List(const List& lst) {
        m_head = new Node(0,nullptr,nullptr);
        m_head->next = m_head;
        m_head->prev = m_head;
        Node *aux = lst.m_head->next;
        Node *auxMain = m_head;
        while(aux != lst.m_head) {
            Node *newNode = new Node(aux->value,auxMain,m_head);
            auxMain->next = newNode;
            auxMain = auxMain->next;
            aux = aux->next;
        }
        m_head->prev = auxMain;
        m_size = lst.m_size;
    }

    // insere um valor no final da lista --> complexidade O(1)
    void push_back(const int& v) {
        Node *aux = new Node(v, m_head->prev, m_head);
        aux->prev->next = aux;
        m_head->prev = aux;
        m_size++;
    }

    // insere um valor no inicio da lista --> complexidade O(1)
    void push_front(const int& v) {
        Node *aux = new Node(v, m_head, m_head->next);
        m_head->next->prev = aux;
        m_head->next = aux;
        m_size++;
    }

    // remove um valor do final da lista --> complexidade O(1)
    void pop_back() {
        if(m_size != 0) {
            Node *aux = m_head->prev;
            aux->prev->next = m_head;
            m_head->prev = aux->prev;
            delete aux;
            m_size--;
        }
    }

    // retorna se lista esta vazia
    bool empty() const {
        return m_size == 0;
    }

    // retorna numero de elementos da lista
    size_t size() const{
        return m_size;
    }

    // retorna o primeiro elemento, se ele existir.
    // se nao existir, deve-se lancar uma std::out_of_range exception
    int& front(){
        if (m_head->next != m_head)
        {
            return m_head->next->value;
        }else throw std::out_of_range("Nao tem elemento na lista");
             
    }

    // retorna o ultimo elemento, se ele existir.
    // se nao existir, deve-se lancar uma std::out_of_range exception
    int& back(){
        if (m_head->prev != m_head)
        {
            return m_head->prev->value;
        }else throw std::out_of_range("Nao existe ultimo elemento");        
    }

    // remove o primeiro elemento da lista, se ele existir
    void pop_front() {
    if (m_head->next != m_head) {
        Node* aux = m_head++;
        m_head->next = aux->next;
        aux->next->prev = m_head;
        delete aux;
        m_size--;
    }else throw std::out_of_range("Lista vazia");
}


    // deixa a lista vazia e com m_size == 0 
    void clear(){
        Node* aux = m_head++;

        while (aux!=m_head)
        {
            Node* nextNode = aux->next;
            delete aux;
            aux = nextNode;
        }
        m_head->next = m_head; // Restaura a lista para um estado vazio
        m_head->prev = m_head;
        m_size = 0; // Atualiza o tamanho da lista
    }

    // remove da lista todos os elementos com valores iguais a val
    void remove(const int& val){
        Node* aux = m_head++;

        while (aux != m_head)
        {
            if (aux->value == val)
            {
                aux->next->prev = aux->prev;
                aux->next
            }
            
            
        }
        
        
    }

    // sobrecarga do operador de atribuicao
    List& operator=(const List& lst);

    // compara esta lista com a lista lst e decide se elas sao iguais.
    // duas listas sao iguais se elas tem o mesmo tamanho e se
    // o i-esimo elemento de uma eh igual ao i-esimo elemento da outra,
    // para todo 0 <= i <= m_size-1. 
    bool operator==(const List& lst) const;

    // compara esta lista com a lista lst e decide se elas sao diferentes
    bool operator!=(const List& lst) const;

    // troca o conteudo desta lista pelo conteudo de lst
    // os m_size das duas listas tambem devem ser trocados
    void swap(List& lst);

    // Destrutor: tem que descomentar e implementar
    //~List()

    // Redimensiona a lista para que contenha n elementos.
    // Se n for menor que o tamanho atual do container, 
    // o conteudo eh reduzido aos seus primeiros n elementos, 
    // removendo aqueles alem (e os destruindo).
    // Se n for maior que o tamanho da lista atual, o conteudo 
    // eh expandido inserindo no final quantos elementos forem necessarios 
    // para atingir um tamanho de n. 
    // Se val for especificado, os novos elementos serao inicializados 
    // como copias de val, caso contrario, eles serao inicializados com 0.
    // Observe que esta funcao altera o conteudo real da lista inserindo 
    // ou apagando elementos dele.
    void resize(size_t n, const int& val = 0);
};







//bubbleSort();
//insertionSort
//SelectionSort
//mergeSort();
//heapSort()
//QuickSort()














#endif
