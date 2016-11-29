#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibl.h"
// ------------ Tabelas
// cria uma lista de tabelas
void criaListaTabelas(lTable *lista) {
 lista->primeiro = (celTable *)malloc(sizeof(celTable));
 lista->ultimo = lista->primeiro;
 lista->primeiro->prox = NULL;
}
// .
// insere nova tabela
void insereTabela(tTable x, lTable *lista) {
 lista->ultimo->prox  = (celTable *)malloc(sizeof(celTable));
 lista->ultimo = lista->ultimo->prox;
 lista->ultimo->tabela = x;
 lista->ultimo->prox = NULL;
}
// .
// ------------ Campos
// cria uma lista de tabelas
void criaListaCampos(lCampo *lista) {
 lista->primeiro = (celCampo *)malloc(sizeof(celCampo));
 lista->ultimo = lista->primeiro;
 lista->primeiro->prox = NULL;
}
// .
// insere nova tabela
void insereCampo(tCampo x, lCampo *lista) {
 lista->ultimo->prox  = (celCampo *)malloc(sizeof(celCampo));
 lista->ultimo = lista->ultimo->prox;
 lista->ultimo->campo = x;
 lista->ultimo->prox = NULL;
}
// .

//
void comparaEGeraRelatorio (lTable model, lTable comp, FILE *relatorio, int numTabelas, int numComparacoes) {
    // cria apontadores para as tabelas base e de comparacao
    pTable apComp = comp.primeiro->prox, apModel = model.primeiro->prox;
    // .
    int i, j, k, l, tblDiferente = 1, cmpDiferente = 1;

    // loop para conferir todas as tabelas
    for (i = 0; i < numTabelas; i++) {
        // varre lista de tabelas base em busca de tabela igual a atual de comparacao
        for (j = 0; j < numComparacoes; j++) {
            // se as tabelas atuais sao iguais, diz que sao iguais e sai da repeticao
            if (strcmp (apComp->tabela.nomeTabela, apModel->tabela.nomeTabela) == 0) {
                tblDiferente = 0;
                j = numComparacoes;
            }
            // se as tabelas forem diferentes, pula pra proxima tabela da lista base
            else {
                apModel = apModel->prox;
            }
            // .
        }
        // .
        // se tblDiferente = 1, ou seja, se for uma tabela nova, imprime no relatorio
        if (tblDiferente == 1) {
            fprintf(relatorio, "* Nova Tabela!\n>%s\n\n", apComp->tabela.nomeTabela);
        }
        // se as tabelas forem iguais, comeca a comparacao entre campos
        else {
            // cria os apontadores de campo para as tabelas de base e de comparacao atuais
            pCampo apCampComp = apComp->tabela.listaCampos.primeiro->prox, apCampModel = apModel->tabela.listaCampos.primeiro->prox;
            // .
            // loop para conferir todos os campos da tabela de comparacao
            for (l = 0; l < apComp->tabela.numCampos; l++) {
                // varre lista de campos da tabela de base em busca de campo igual ao atual da tabela de comparacao
                for (k = 0; k < apModel->tabela.numCampos; k++) {
                    // confere se lista base ja foi completamente varrida
                    if (apCampModel->campo.nomeCampo == NULL) {
                        cmpDiferente = 1;
                    }
                    // se os campos forem iguais, pula para proximo campo da tabela de comparacao e comeca nova repeticao
                    else if(strcmp (apCampComp->campo.nomeCampo, apCampModel->campo.nomeCampo) == 0) {
                        cmpDiferente = 0;
                        k = apModel->tabela.numCampos;
                        apCampComp = apCampComp->prox;
                        apCampModel = apModel->tabela.listaCampos.primeiro->prox;
                    }
                    // se os campos forem diferentes, declara que sao diferentes e pula pro proximo
                    else {
                        apCampModel = apCampModel->prox;
                        cmpDiferente = 1;
                    }
                    // .
                }
                // .
                // zera variavel
                apCampModel = apModel->tabela.listaCampos.primeiro->prox;
                // se os campos forem definitivamente diferentes, imprime no relatorio
                if (cmpDiferente == 1) {
                    fprintf(relatorio, "* Novo Campo em %s!\n>%s\n\n", apComp->tabela.nomeTabela, apCampComp->campo.nomeCampo);
                    apCampComp = apCampComp->prox;
                }
                // se campos forem iguais, prepara para nova comparacao
                else {
                    cmpDiferente = 1;
                }
                // .
            }
            // .
        }
        // .
        // zera variaveis
        apModel = model.primeiro->prox;
        apComp = apComp->prox;
        tblDiferente = 1;
        cmpDiferente = 1;
    }
    // .

    fprintf(relatorio, "END_OF_SEARCH\n");
}
// .
