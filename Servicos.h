#include <stdbool.h>

struct servico{
	int codigoServico;
	char nome[50];
	float preco;
};
typedef struct servico Servico;

int VerificaTamanhoAlocacaoServicos();

bool InicializarServicos();
bool EncerraServicos();
bool SalvarServico(Servico* servicoTemp);
int QuantidadeServicos();
Servico* ObterServicoPeloIndice(int indice);
Servico* ObterServicoPeloCodigo(int codigo);
Servico* ObterServicoPeloNome(char* nome);
bool AtualizarServico();
bool MudarServico(Servico* servicoTemp);
bool ApagarServicoPeloCodigo(int codigo);
