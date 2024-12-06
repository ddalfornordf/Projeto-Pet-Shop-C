#include "ServicoPrestado.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO_INICIAL 5

int tamanhoAlocadoServicoPrestado = TAMANHO_INICIAL;
int novoTamanhoServicoPrestado = 0;

ServicoPrestado* servicosPrestados = NULL;
int qtdServicosPrestados = 0;

int VerificaTamanhoAlocacaoServicosPrestados(){
	return tamanhoAlocadoServicoPrestado;
}

bool InicializarServicosPrestados() {
    servicosPrestados = (ServicoPrestado*) malloc(tamanhoAlocadoServicoPrestado * sizeof(ServicoPrestado));
    
    if (servicosPrestados == NULL) {
        return false;
    }
    return true;
}
bool EncerraServicosPrestados(){
	free(servicosPrestados);
	if(servicosPrestados == NULL){
		return false;
	}
	return true;
}
bool SalvarServicoPrestado(ServicoPrestado* servicoPrestadoTemp){
	if(AtualizarServicoPrestado()){
		servicosPrestados[qtdServicosPrestados] = *servicoPrestadoTemp;
		qtdServicosPrestados++;
		return true;	
	} else return false;
	
}
int QuantidadeServicosPrestados(){
	return qtdServicosPrestados;
}

ServicoPrestado* ObterServicoPrestadoPeloIndice(int indice){
	ServicoPrestado* servicoPrestadoTemp = (ServicoPrestado*) malloc(sizeof(ServicoPrestado));
    if (indice >= 0 && indice < qtdServicosPrestados) {
        *servicoPrestadoTemp = servicosPrestados[indice];
		return servicoPrestadoTemp;
    } else return NULL;
}

ServicoPrestado* ObterServicoPrestadoPeloCodigoDoPet(int codigo){
	int i;
    ServicoPrestado* servicoPrestadoTemp = (ServicoPrestado*) malloc(sizeof(ServicoPrestado));
	for (i = 0; i < qtdServicosPrestados; i++) {
        if (servicosPrestados[i].codigoPet == codigo) {
            *servicoPrestadoTemp = servicosPrestados[i];
			return servicoPrestadoTemp;
        }
    }
    return NULL;
}

ServicoPrestado* ObterServicoPrestadoPeloNome(char* nome){
	int i;
	ServicoPrestado* servicoPrestadoTemp = (ServicoPrestado*) malloc(sizeof(ServicoPrestado));
    for (i = 0; i < qtdServicosPrestados; i++) {
        if (strcmp(nome, servicosPrestados[i].nome) == 0) {
            *servicoPrestadoTemp = servicosPrestados[i];
            return servicoPrestadoTemp;
			}
        }
    return NULL;
}

bool AtualizarServicoPrestado() {
    if (qtdServicosPrestados >= tamanhoAlocadoServicoPrestado) {
        novoTamanhoServicoPrestado = tamanhoAlocadoServicoPrestado * 2;
    } else if (qtdServicosPrestados <= tamanhoAlocadoServicoPrestado / 2 && tamanhoAlocadoServicoPrestado > 5) {
        novoTamanhoServicoPrestado = tamanhoAlocadoServicoPrestado / 2;
    } else {
        return true; 
    }
    
    ServicoPrestado* temp = (ServicoPrestado*) realloc(servicosPrestados, novoTamanhoServicoPrestado * sizeof(ServicoPrestado));
    
    if (temp == NULL) {
        return false; 
    }
    
    servicosPrestados = temp;
    tamanhoAlocadoServicoPrestado = novoTamanhoServicoPrestado;
    return true;
}

float CalcularLucro(){
	int i;
	float lucro;
	for(i = 0; i < qtdServicosPrestados; i++){
		lucro += servicosPrestados[i].preco;
	} return lucro;
}