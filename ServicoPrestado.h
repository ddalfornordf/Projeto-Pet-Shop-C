#include <stdbool.h>

struct servicoPrestado{
	int codigoPet;
	char nome[50];
	float preco;
};
typedef struct servicoPrestado ServicoPrestado;

int VerificaTamanhoAlocacaoServicosPrestados();

bool InicializarServicosPrestados();
bool EncerraServicosPrestados();
bool SalvarServicoPrestado(ServicoPrestado* servicoPrestadoTemp);
int QuantidadeServicosPrestados();
ServicoPrestado* ObterServicoPrestadoPeloIndice(int indice);
ServicoPrestado* ObterServicoPrestadoPeloCodigoDoPet(int codigo);
ServicoPrestado* ObterServicoPrestadoPeloNome(char* nome);
bool AtualizarServicoPrestado();
float CalcularLucro();