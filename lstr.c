#include "lstr.h"

#include <stdlib.h>
#include <stdio.h>

struct lstr
{
    int tam;
    int cap;
    int pos;
    str *mem;
};


Lstr ls_cria(){
    Lstr new = (Lstr*)malloc(64);
    new->cap = 8;
    new->tam = 0;
    new->pos = -1;
    return new;
}

void ls_destroi(){

}

bool ls_vazia(Lstr self){
    return (self->tam==0);
}

int ls_tam(Lstr self){
    return self->tam;
}

bool ls_item_valido(Lstr self){
    return (self->pos > -1 && self->pos < self->tam);
}

str ls_item(Lstr self){
    return self->mem[self->pos];
}


void ls_inicio(Lstr self){
    self->pos = -1;
}

void ls_final(Lstr self){
    self->pos = self->tam;
}

void ls_posiciona(Lstr self, int pos){
    if(pos<0) pos = self->tam + pos;
    if(pos<0){
        ls_inicio(self);
        return;
    }
    if(pos > self->tam){
        ls_final(self);
        return;
    }
    self->pos = pos;
}

bool ls_avanca(Lstr self){
    if(self->pos < self->tam) self->pos += 1;
    if(self->pos == self->tam) return false;
    return true;
}
