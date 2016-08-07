#ifndef STATEMETHODS_H
#define STATEMETHODS_H

#include "Extra.h"
#include "ListTxt.h"
#include <list>

void desfazer_action(list<EXTRA> &lista_state, list<EXTRA> &lista_state_rem, ListTxt &lista){
    if(lista_state.size() < 1) return;
    EXTRA extra = lista_state.front();
    lista_state.pop_front(); //remove a acao
    lista_state_rem.push_front(extra);
    switch (extra.estate) {
        case '<':
           lista.avancar();
           break;
        case '>':
           lista.voltar();
           break;
        case 'B':
            lista.insert(extra.value);
          break;
        case 'D':
            lista.insert(extra.value);
            lista.voltar();
            break;
        case 'I':
            if(extra.value == lista.mark()->value)
                lista.apagar_ant();
            else
                lista.apagar_prox();
            break;
    }
    //delete extra;
}

void refazer_action(list<EXTRA> &lista_state, list<EXTRA> &lista_state_rem, ListTxt &lista){ ////BUG
    if(lista_state_rem.size() < 1) return;
    EXTRA extra = lista_state_rem.front();
    lista_state_rem.pop_front();
    lista_state.push_front(extra);
    switch (extra.estate) {
        case '<':
           lista.voltar();
           break;
        case '>':
           lista.avancar();
           break;
        case 'B':
             lista.apagar_ant();
          break;
        case 'D':
            lista.apagar_prox();
            break;
        case 'I':
            lista.insert(extra.value);
            break;
    }
}


#endif // STATEMETHODS_H
