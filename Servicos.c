#include "Servicos.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO_INICIAL 5

int tamanhoAlocadoServico = TAMANHO_INICIAL;
int novoTamanhoServico = 0;

Servico* servicos = NULL;
int qtdServicos = 0;

int VerificaTamanhoAlocacaoServicos(){
	return tamanhoAlocadoServico;
}

bool InicializarServicos() {
    servicos = (Servico*) malloc(tamanhoAlocadoServico * sizeof(Servico));
    
    if (servicos == NULL) {
        return false;
    }

    Servico s1 = {1, "Tosa", 50.00};
    Servico s2 = {2, "Banho", 30.00};
    Servico s3 = {3, "Tosa Higienica", 100.00};
    Servico s4 = {4, "Hidratacao de pelo", 80.00};
    
    servicos[0] = s1;
    servicos[1] = s2;
    servicos[2] = s3;
    servicos[3] = s4;
    
    qtdServicos = 4;

    return true;
}
bool EncerraServicos(){
	free(servicos);
	if(servicos == NULL){
		return false;
	}
	return true;
}
bool SalvarServico(Servico* servicoTemp){
	int i;
	for(i = 0; i < qtdServicos; i++){
		if(servicoTemp->codigoServico == servicos[i].codigoServico){
			return false;	
		}
	}

	if(AtualizarServico()){
		servicos[qtdServicos] = *servicoTemp;
		qtdServicos++;
		return true;	
	} else return false;
	
}
bool MudarServico(Servico* servicoTemp){
	int i;
	for(i = 0; i < qtdServicos; i++){
		if(servicoTemp->codigoServico == servicos[i].codigoServico){
			servicos[i] = *servicoTemp;
			return true;	
		}
	}
	return false;
}
int QuantidadeServicos(){
	return qtdServicos;
}
Servico* ObterServicoPeloIndice(int indice) {
	Servico* servicoTemp = (Servico*) malloc(sizeof(Servico));
    if (indice >= 0 && indice < qtdServicos) {
        *servicoTemp = servicos[indice];
		return servicoTemp;
    } else return NULL;
}

Servico* ObterServicoPeloCodigo(int codigo) {
    int i;
    Servico* servicoTemp = (Servico*) malloc(sizeof(Servico));
	for (i = 0; i < qtdServicos; i++) {
        if (servicos[i].codigoServico == codigo) {
            *servicoTemp = servicos[i];
			return servicoTemp;
        }
    }
    return NULL;
}
Servico* ObterServicoPeloNome(char* nome){
	int i;
	Servico* servicoTemp = (Servico*) malloc(sizeof(Servico));
    for (i = 0; i < qtdServicos; i++) {
        if (strcmp(nome, servicos[i].nome) == 0) {
            *servicoTemp = servicos[i];
            return servicoTemp;
			}
        }
        return NULL;
}

bool AtualizarServico() {
    if (qtdServicos >= tamanhoAlocadoServico) {
        novoTamanhoServico = tamanhoAlocadoServico * 2;
    } else if (qtdServicos <= tamanhoAlocadoServico / 2 && tamanhoAlocadoServico > 5) {
        novoTamanhoServico = tamanhoAlocadoServico / 2;
    } else {
        return true; 
    }
    
    Servico* temp = (Servico*) realloc(servicos, novoTamanhoServico * sizeof(Servico));
    
    if (temp == NULL) {
        return false; 
    }
    
    servicos = temp;
    tamanhoAlocadoServico = novoTamanhoServico;
    return true;
}

bool ApagarServicoPeloCodigo(int codigo) {
    int i, j;
    bool encontrado = false;
    if(ObterServicoPeloCodigo(codigo)){
    	for (i = 0; i < qtdServicos; i++) {
        	if (servicos[i].codigoServico == codigo) {
	            encontrado = true;
	            for (j = i; j < qtdServicos - 1; j++) {
	                servicos[j] = servicos[j + 1];
	            }
    		}
    		qtdServicos--;
            if(AtualizarServico()){
            	return true;	
			} else if(AtualizarServico()){
				qtdServicos++;
				return false;
			}
        }
    }
    if (!encontrado) {
        return false;
    } 
}