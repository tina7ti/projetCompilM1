
struct quadr {
	char* opr;
	char* op1;
	char* op2;
	char* res;
};

struct quadr qu[100];

void init();
void create(char* opr,char* op1,char* op2,char* res);
char* convert(int i);
void quadComp(char* opr,char* op1,char* op2);
void quadFinIF();
void quadFinIF_else(int ielse);
void afficherQuad();
void majBR_vide();
void assembler(int CptabSym);
void quad_fin();
void simplfyMulti();
void suppAffNutil();
void appelSuppAffNutil();
int isBranchement(char *opr);
void mise_ajour_adr(int i,int cpt);
void optimisation2_propagation_expression();
int f_numeric(char* a);
void optimisation_propagation_copie();
void inserer_quad(int j,int debut,int cpt,char* var);
void optimiser();
