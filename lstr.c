#include "lstr.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct lstr
{
    int tam; // quantidade de strings na lista
    int cap; // quantidade de bytes alocados para strings
    int pos; // posição corrente
    int *div; // índice das separações entre strings 
    str *mem; // memória
};

static void ls_realloc(Lstr self){
    int oldcap = self->cap;
    if(self->cap == self->tam)
        self->cap = self->cap * 1.5;
    if(self->cap < self->tam * 0.5 && self->tam * 1.25 > 8)
        self->cap = self->tam * 1.25;
    
    if(self->cap != oldcap){
        self->mem = realloc(self->mem,sizeof(str)*self->cap);
    }
}

Lstr ls_cria(){
    Lstr new = malloc(sizeof(struct lstr));
    new->cap = 8;
    new->tam = 0;
    new->mem = malloc(8*sizeof(str));
    new->pos = -1;
    return new;
}

void ls_destroi(Lstr self){
    for(int i=0;i<self->tam;i++){
        s_destroi(self->mem[i]);
    }
    free(self->mem);
    free(self);
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
    if(pos >= self->tam){
        ls_final(self);
        return;
    }
    self->pos = pos;
}

bool ls_avanca(Lstr self){
    if(self->pos < self->tam) self->pos += 1;
    return (self->pos < self->tam);
}

bool ls_recua(Lstr self){
    if(self->pos > -1) self->pos -= 1;
    return (self->pos > -1);
}


void ls_insere_antes(Lstr self, str cad){
    int newpos = self->pos;
    if(self->pos <= 0) newpos = 0;
    if(self->pos >= self->tam) newpos = self->tam;
    ls_realloc(self);
    if(self->tam > newpos){
        memmove(self->mem+newpos+1,self->mem+newpos,sizeof(str)*(self->tam - newpos));
    }
    self->mem[newpos] = cad;
    self->pos = newpos;
    self->tam += 1;
}

void ls_insere_depois(Lstr self, str cad){
    int newpos = self->pos + 1;
    if(self->pos < 0) newpos = 0;
    if(self->pos >= self->tam) newpos = self->tam;
    ls_realloc(self);
    if(self->tam > newpos){
        memmove(self->mem+self->pos+2,self->mem+self->pos+1,sizeof(str)*(self->tam - self->pos - 1));
    }
    self->mem[newpos] = cad;
    self->pos = newpos;
    self->tam += 1;
}

str ls_remove(Lstr self){
    str removida = s_copia(self->mem[self->pos]);
    s_destroi(self->mem[self->pos]);
    if(self->pos < self->tam - 1){
        memmove(self->mem + self->pos, self->mem + self->pos + 1, sizeof(str) * (self->tam - self->pos - 1));
    }
    self->tam -= 1;
    return removida;
}

Lstr ls_sublista(Lstr self, int tam){
    Lstr new = ls_cria();
    if(tam<=0 || self->pos >= self->tam) return new;
    if(self->pos + tam > self->tam) tam = self->tam - self->pos;
    int fim = self->pos + tam;
    do{
        ls_insere_depois(new,self->mem[self->pos]);
        ls_avanca(self);
    }while(self->pos < fim);
    new->tam = tam;
    return new;
}

str ls_junta(Lstr self, str separador){
    str newFixed = s_cria("");
    str new = s_copia(newFixed);
    for(ls_inicio(self);ls_avanca(self);){
        s_cat(&new,self->mem[self->pos]);
        if(self->pos < self->tam - 1) s_cat(&new,separador);
    }
    return new;
}

void ls_imprime(Lstr self){
    for(ls_inicio(self);ls_avanca(self);){
        s_imprime(ls_item(self));
        printf("\n");
    }
    ls_inicio(self);
}