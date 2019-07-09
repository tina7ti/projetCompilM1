
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
void quadComp(char* opr);
void quadFinIF();
void afficherQuad();
