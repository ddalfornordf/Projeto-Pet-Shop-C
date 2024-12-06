#include <stdbool.h>

struct pet{
	int codigoPet;
	int codigoPetCliente;
	char nomePet[50];
	char especiePet[50];
};

typedef struct pet Pet;

int VerificaTamanhoAlocacaoPets();

bool InicializarPets();
bool EncerraPets ();
bool SalvarPets(Pet* petsTemp);
int QuantidadePets();
Pet* ObterPetPeloIndice(int indice);
Pet* ObterPetPeloCodigo(int codigo);
Pet* ObterPetPeloCodigoDoCliente(int codigo);
Pet* ObterPetPeloNome(char* nome);
Pet* ObterPetPelaEspecie(char* especie);
bool AtualizarPets();
bool ApagarPetsPeloCodigo(int codigo);
bool ApagarPetsPeloNome(char* nome);