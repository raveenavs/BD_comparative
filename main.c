#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibl.h"

int main () {
    FILE *model = fopen("model.txt", "r"), *comp = fopen("comparacao.txt", "r"), *relat = fopen("relatorio.txt", "w");
    int i, j;
    int numTabelas, numCampos, numComparacoes;

    // TODO: relacionamentos
    // TODO: melhorar relatorio

    // cria e aloca tabelas / table temporaria
    tTable tmpTable;
    lTable *listaModel = (lTable *) malloc(sizeof(lTable));
    criaListaTabelas(listaModel);
    lTable *listaComparacao = (lTable *) malloc(sizeof(lTable));
    criaListaTabelas(listaComparacao);
    // lista de campos
    tCampo tmpCampos;
    lCampo *listaCampos = (lCampo *) malloc(sizeof(lCampo));

    // le arquivo de model
    fscanf(model, "%d\n", &numTabelas);
    for (i = 0; i < numTabelas; i++) {
        fscanf(model, ">%s\n", tmpTable.nomeTabela);
        fscanf(model, "%d\n", &numCampos);
        //campos
        criaListaCampos(listaCampos);
        for (j = 0; j < numCampos; j++) {
            fscanf(model, "-%s\n", tmpCampos.nomeCampo);
            insereCampo(tmpCampos, listaCampos);
        }
        // .
        tmpTable.numCampos = numCampos;
        tmpTable.listaCampos = *listaCampos;
        insereTabela(tmpTable, listaModel);
    }
    // .

    // le arquivo de comparacao
    fscanf(comp, "%d\n", &numComparacoes);
    for (i = 0; i < numComparacoes; i++) {
        fscanf(comp, ">%s\n", tmpTable.nomeTabela);
        fscanf(comp, "%d\n", &numCampos);
        //campos
        criaListaCampos(listaCampos);
        for (j = 0; j < numCampos; j++) {
            fscanf(comp, "-%s\n", tmpCampos.nomeCampo);
            insereCampo(tmpCampos, listaCampos);
        }
        // .
        tmpTable.numCampos = numCampos;
        tmpTable.listaCampos = *listaCampos;
        insereTabela(tmpTable, listaComparacao);
    }
    // .
    // geracao do relatorio
    fprintf(relat, "===== Relatorio n%d%d%d =====\n", numTabelas, numComparacoes, j);
    comparaEGeraRelatorio(*listaModel, *listaComparacao, relat, numComparacoes, numTabelas);
    fprintf(relat, "\n\n>> WARNING: comparacao as avessas! Coisas 'novas' relatadas a seguir foram excluidas do Model original!\n");
    comparaEGeraRelatorio(*listaComparacao, *listaModel, relat, numTabelas, numComparacoes);

    return 0;
}
