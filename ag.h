
#ifndef AGREGADOR_H
#define AGREGADOR_H

// Structs

struct Agregador{
    int codigo;
    int vendas;
    int quantidade;
    float montante;
};

typedef struct Agregador Agregador;

// API

Agregador new_agregador (int codigo, int vendas, int quantidade, float montante);

Agregador clone_agregador (Agregador ag);

void store_agregador (Agregador ag);

void cria_agregador (int codigo, int vendas, int quantidade, float montante);

void atualiza_agregador (int codigo, int quantidade, float montante);

void ler_agregador (int codigo);

/* void ler_agregador (int codigo); */

#endif