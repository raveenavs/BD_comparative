// lista de campos
typedef struct campo {
    char nomeCampo[100];
} tCampo;

typedef struct celulaCampo *pCampo;
typedef struct celulaCampo {
    tCampo campo;
    pCampo prox;
} celCampo;

typedef struct campoLista {
    pCampo primeiro, ultimo;
} lCampo;
//.

// lista de tabelas
typedef struct table {
    char nomeTabela[100];
    int numCampos;
    lCampo listaCampos; // lista de campos
} tTable;

typedef struct celulaTable *pTable;
typedef struct celulaTable {
    tTable tabela;
    pTable prox;
} celTable;

typedef struct tableLista {
    pTable primeiro, ultimo;
} lTable;
//.

// cabecalhos
void criaListaTabelas(lTable *lista);
void insereTabela(tTable x, lTable *lista);
void criaListaCampos(lCampo *lista);
void insereCampo(tCampo x, lCampo *lista);
void comparaEGeraRelatorio (lTable model, lTable comp, FILE *relatorio, int numTabelas, int numComparacoes);
// .
