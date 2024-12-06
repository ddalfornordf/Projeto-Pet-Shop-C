#include "Clientes.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO_INICIAL 5

int tamanhoAlocadoClientes = TAMANHO_INICIAL;
int novoTamanhoClientes = 0;

Cliente* clientes = NULL;
int qtdClientes = 0;

int VerificaTamanhoAlocacaoClientes(){
	return tamanhoAlocadoClientes;
}

bool InicializarClientes() {
    clientes = (Cliente*) malloc(tamanhoAlocadoClientes * sizeof(Cliente));
    
    if (clientes == NULL) {
        return false;
    }

    Cliente c1 = {1, "Joao", "11111111111", "11111111111"};
    Cliente c2 = {2, "Maria", "22222222222", "22222222222"};
    Cliente c3 = {3, "Eduardo", "33333333333", "33333333333"};
    Cliente c4 = {4, "Felipe", "44444444444", "44444444444"};
    
    clientes[0] = c1;
    clientes[1] = c2;
    clientes[2] = c3;
    clientes[3] = c4;
    
    qtdClientes = 4;
    return true;
}
bool EncerraClientes (){
	free(clientes);
	if(clientes == NULL){
		return false;
	}
	return true;
}
bool SalvarCliente(Cliente* clienteTemp){
	int i;
	for(i = 0; i < qtdClientes; i++){
		if(clienteTemp->codigoCliente == clientes[i].codigoCliente){
			return false;	
		}
	}
	
	if(AtualizarCliente()){
		clientes[qtdClientes] = *clienteTemp;
		qtdClientes++;
		return true;	
	} else return false;
	
}
int QuantidadeClientes(){
	return qtdClientes;
}
Cliente* ObterClientePeloIndice(int indice) {
	Cliente* clienteTemp = (Cliente*) malloc(sizeof(Cliente));
    if (indice >= 0 && indice < qtdClientes) {
        *clienteTemp = clientes[indice];
		return clienteTemp;
    } else return NULL;
}

Cliente* ObterClientePeloCodigo(int codigo) {
    int i;
    Cliente* clienteTemp = (Cliente*) malloc(sizeof(Cliente));
	for (i = 0; i < qtdClientes; i++) {
        if (clientes[i].codigoCliente == codigo) {
            *clienteTemp = clientes[i];
			return clienteTemp;
        }
    }
    return NULL;
}
Cliente* ObterClientePeloNome(char* nome){
	int i;
	Cliente* clienteTemp = (Cliente*) malloc(sizeof(Cliente));
    for (i = 0; i < qtdClientes; i++) {
        if (strcmp(nome, clientes[i].nome) == 0) {
            *clienteTemp = clientes[i];
            return clienteTemp;
			}
        }
        return NULL;
}

bool AtualizarCliente() {
    if (qtdClientes >= tamanhoAlocadoClientes) {
        novoTamanhoClientes = tamanhoAlocadoClientes * 2;
    } else if (qtdClientes <= tamanhoAlocadoClientes / 2 && tamanhoAlocadoClientes > 5) {
        novoTamanhoClientes = tamanhoAlocadoClientes / 2;
    } else {
        return true; 
    }
    
    Cliente* temp = (Cliente*) realloc(clientes, novoTamanhoClientes * sizeof(Cliente));
    
    if (temp == NULL) {
        return false; 
    }
    
    clientes = temp;
    tamanhoAlocadoClientes = novoTamanhoClientes;
    return true;
}

bool ApagarClientePeloCodigo(int codigo) {
    int i, j;
    bool encontrado = false;
    if(ObterClientePeloCodigo(codigo)){
    	for (i = 0; i < qtdClientes; i++) {
        	if (clientes[i].codigoCliente == codigo) {
	            encontrado = true;
	            for (j = i; j < qtdClientes - 1; j++) {
	                clientes[j] = clientes[j + 1];
	            }
    		}
    		qtdClientes--;
            if(AtualizarCliente()){
            	return true;	
			} else if(AtualizarCliente()){
				qtdClientes++;
				return false;
			}
        }
    }
    if (!encontrado) {
        return false;
    } 
}
bool ApagarClientePeloNome(char* nome) {
    int i, j = 0;
    bool encontrado = false;
    
    for (i = 0; i < qtdClientes; i++) {
        if (strcmp(nome, clientes[i].nome) == 0) {
            encontrado = true;
            for (j = i; j < qtdClientes - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            qtdClientes--;
            if(AtualizarCliente()){
            	return true;	
			} else if(AtualizarCliente()){
				qtdClientes++;
				return false;
			}
        }
    }
    
    if (!encontrado) {
        return false;
    }
}

