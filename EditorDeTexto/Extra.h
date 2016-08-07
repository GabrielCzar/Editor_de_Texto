#ifndef EXTRA_H
#define EXTRA_H

struct EXTRA{
    char estate;
    char value;

    EXTRA(char estate, char value = ' '){
        this->estate = estate;
        this->value = value;
    }
};

#endif // EXTRA_H
