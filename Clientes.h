#include <stdbool.h>

struct clientes{
	int codigoCliente;
	char nome[50];
	char cpf[12];
	char telefone[12];
};
typedef struct clientes Cliente;

int VerificaTamanhoAlocacaoClientes();

bool InicializarClientes();
bool EncerraClientes();
bool SalvarCliente(Cliente* clientesTemp);
int QuantidadeClientes();
Cliente* ObterClientePeloIndice(int indice);
Cliente* ObterClientePeloCodigo(int codigo);
Cliente* ObterClientePeloNome(char* nome);
bool AtualizarCliente();
bool ApagarClientePeloCodigo(int codigo);
bool ApagarClientePeloNome(char* nome);
