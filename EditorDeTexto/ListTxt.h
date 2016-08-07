#ifndef LISTTXT_H
#define LISTTXT_H

#include <iostream>

#include "Node.h"

using namespace std;

struct ListTxt{
    Node * head; //Sabe somente o prox
    Node * tail; //Sabe somente o anterior

    private:
    Node * posMark; //Marca o cara para inserir na sua frente

    public:
    ListTxt(){
        head = new Node;
        tail = new Node;
        posMark = new Node('#', head); //# representa o cursor(onde sera inserido)

    }

    void _insert_void(Node * node){
        head->next = node;
        tail->prev = node;
        posMark->next = node; //mark insere na frente ?
    }

    void _insert_begin(Node * node){
        node->next = head->next;
        head->next = node;
        node->next->prev = node;
        posMark->next = node;
    }

    void _insert_middle(Node * node){
        auto posOld = mark();
        node->next = posOld->next; //node sabe quem é prox
        posOld->next = node; //anterior sabe quem é proximo
        node->prev = posOld; //node sabe anterior
        node->next->prev = node; //prox sabe anterior
        posMark->next = node;
    }

    void _insert_end(Node * node){
        node->prev = tail->prev;
        tail->prev = node;
        node->prev->next = node;
        posMark->next = node;
    }

    void insert(char value){
        auto node = new Node(value);
        if(is_empty()) //vazio
            _insert_void(node);
        else if(mark() == nullptr) //no começo antes do old first
            _insert_begin(node);
        else if(mark() == back()) //end
            _insert_end(node);
        else
            _insert_middle(node); //middle
    }

    Node * front(){
        return head->next;
    }

    Node * back(){
        return tail->prev;
    }

    bool is_empty(){
        return head->next == nullptr;
    }

    int _rsize(Node * node){
        if(node == nullptr)
            return 0;
        return 1 + _rsize(node->next);
    }

    int size(){
        if(is_empty())
            return 0;
        return _rsize(head->next);
    }

    void _rprint(Node * node){
        if(node == nullptr)
            return;
        else if(node == mark()){
            cout << node->value;
            cout << posMark->value;
        }
        else if(mark() == head && node == head->next){
            cout << posMark->value;
            cout << node->value;
        }
        else
            cout << node->value;
        _rprint(node->next);
    }

    void print(){
        if(is_empty())
            cout << posMark->value;
        _rprint(head->next);
        cout << endl;
    }

    bool avancar(){
        if(mark()->next == nullptr)
            return false;
        posMark->next = mark()->next;
        return true;
    }

    bool voltar(){
        if(mark() == head) return false;
        if(mark()->prev == nullptr){
            posMark->next = head;
            return true;
        }
        posMark->next = mark()->prev;
        return true;
    }

    void apagar_ant(){ //salva atual -> voltar o cursor -> delete value salvo
        if(mark() == head)
            return;
        Node * node = mark();
        voltar();
        remover(node);
    }

    void apagar_prox(){ //apaga prox
        if(mark()->next == nullptr)
            return;
        remover(mark()->next);
    }

    Node * mark(){
        return posMark->next;
    }

    private: ///Todos os metodos abaixo sao private

    void remover(Node * node){
        if(front() == node){//se for o primeiro
            auto node = front();
            if(node->next == nullptr)
                head->next = nullptr;
            else{
                head->next = node->next;
                node->next->prev = nullptr;
            }
        }
        else if(back() == node){  // se for o ultimo
            tail->prev = node->prev;
            node->prev->next = nullptr;
        }else{ //meio
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        delete node;
    }
};


#endif // LISTTXT_H
