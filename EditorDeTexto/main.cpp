#include <iostream>
#include <list>
#include "ListTxt.h"
#include "Extra.h"
#include "StateMethods.h"

using namespace std;

list<EXTRA> lista_state;
list<EXTRA> lista_state_removidos;

void action(ListTxt lista, char letra){
    switch (letra) {
        case '<':
            if(lista.voltar())
                lista_state.push_front(EXTRA('<'));
            break;
        case '>':
            if(lista.avancar())
                lista_state.push_front(EXTRA('>'));
            break;
        case 'B':
            lista_state.push_front(EXTRA('B', lista.mark()->value));
            lista.apagar_ant();
            break;
        case 'D':
            if(lista.mark()->next != nullptr)
                lista_state.push_front(EXTRA('D', lista.mark()->next->value));
            lista.apagar_prox();
            break;
        case 'Z':
            desfazer_action(lista_state, lista_state_removidos, lista);
            break;
        case 'R':
            refazer_action(lista_state, lista_state_removidos, lista);
            break;
        default:
            if((letra >= 'a' && letra <= 'z') || letra == '-' || letra == '_'){
                lista_state.push_front(EXTRA('I', letra));
                lista.insert(letra);
            }
            break;
    }
}

char action_performed(ListTxt lista, string palavra){
    for(unsigned int i = 0; i < palavra.length(); i++){
        if(palavra[i] == '$')
            return '$'; //Poderia salvar estado e so fazer action apos td ser executado
        action(lista, palavra[i]);
    }
    return 'N'; //N - Nada pra fazer
}

int main(){
    ListTxt lista;
    string palavra;
    char letra;

    lista.print();

    do{
        cout << "$ - Sair " << endl;  //padrao
        cin >> palavra;
        letra = action_performed(lista, palavra);
        lista.print();
    }while(letra != '$');

    //cout << lista_state.front().estate << "-extra";
    //POR MAIS QUE NAO RECONHEÇA COMO PONTEIRO - FUNCIONA
    return 0;
}


/**
 * @autor Gabriel Cesar
 *
 */
