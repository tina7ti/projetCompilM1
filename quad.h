
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
void assembler(int CptabSym);
