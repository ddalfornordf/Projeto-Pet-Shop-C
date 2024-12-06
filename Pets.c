#include "Pets.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO_INICIAL 5

int tamanhoAlocadoPets = TAMANHO_INICIAL;
int novoTamanhoPets = 0;

Pet* pets = NULL;
int qtdPets = 0;

int VerificaTamanhoAlocacaoPets(){
	return tamanhoAlocadoPets;
}

bool InicializarPets(){
	pets = (Pet*) malloc(tamanhoAlocadoPets*sizeof(Pet));
	
	if(pets == NULL){
		return false;
	}
	
	Pet p1 = {11, 1, "Gato", "Gato"};
    Pet p2 = {12, 2, "Cachorro", "Cachorro"};
    Pet p3 = {13, 1, "Gato", "Gato"};
    Pet p4 = {14, 3, "Jaca", "Jacare"};
    
    pets[0] = p1;
    pets[1] = p2;
    pets[2] = p3;
    pets[3] = p4;
    
    qtdPets = 4;
	
	return true;
}

bool EncerraPets(){
	free(pets);
	if(pets == NULL){
		return false;
	}
	return true;	
}

bool SalvarPets(Pet* petTemp){
	int i;
	for(i = 0; i < qtdPets; i++){
		if(petTemp->codigoPet == pets[i].codigoPet){
			return false;	
		} 
	}
	
	if(AtualizarPets()){
		pets[qtdPets] = *petTemp;
		qtdPets++;
		return true;	
	} else return false;
}
int QuantidadePets(){
	return qtdPets;
}

Pet* ObterPetPeloIndice(int indice){
	Pet* petTemp = (Pet*) malloc(sizeof(Pet));
    if (indice >= 0 && indice < qtdPets) {
        *petTemp = pets[indice];
		return petTemp;
    } else return NULL;
}

Pet* ObterPetPeloCodigo(int codigo){
	int i;
    Pet* petTemp = (Pet*) malloc(sizeof(Pet));
	for (i = 0; i < qtdPets; i++) {
        if (pets[i].codigoPet == codigo) {
            *petTemp = pets[i];
			return petTemp;
        }
    }
    return NULL;
}

Pet* ObterPetPeloCodigoDoCliente(int codigo){
	int i;
    Pet* petTemp = (Pet*) malloc(sizeof(Pet));
	for (i = 0; i < qtdPets; i++) {
        if (pets[i].codigoPetCliente == codigo) {
            *petTemp = pets[i];
			return petTemp;
        }
    }
    return NULL;
}

Pet* ObterPetPeloNome(char* nome){
	int i;
	Pet* petTemp = (Pet*) malloc(sizeof(Pet));
    for (i = 0; i < qtdPets; i++) {
        if (strcmp(nome, pets[i].nomePet) == 0) {
            *petTemp = pets[i];
            return petTemp;
			}
        }
        return NULL;
}
Pet* ObterPetPelaEspecie(char* especie) {
    static int indice = 0; 
	int i;
	Pet* petTemp = (Pet*) malloc(sizeof(Pet));
    for (i = indice; i < QuantidadePets(); i++) {
        if (strcmp(pets[i].especiePet, especie) == 0) {
            indice = i + 1; 
            *petTemp = pets[i];
            return petTemp;
        }
    }

    indice = 0; 
    return NULL; 
}

bool AtualizarPets(){
    if (qtdPets >= tamanhoAlocadoPets) {
        novoTamanhoPets = tamanhoAlocadoPets * 2;
    } else if (qtdPets <= tamanhoAlocadoPets / 2 && tamanhoAlocadoPets > 5) {
        novoTamanhoPets = tamanhoAlocadoPets / 2;
    } else {
        return true;
    }

    Pet* temp = (Pet*) realloc(pets, novoTamanhoPets * sizeof(Pet));

    if (temp == NULL) {
        return false;
    }

    pets = temp;
    tamanhoAlocadoPets = novoTamanhoPets;
    return true;
}

bool ApagarPetPeloCodigo(int codigo){
	int i, j;
    bool encontrado = false;
    if(ObterPetPeloCodigo(codigo)){
    	for (i = 0; i < qtdPets; i++) {
        	if (pets[i].codigoPet == codigo) {
	            encontrado = true;
	            for (j = i; j < qtdPets - 1; j++) {
	                pets[j] = pets[j + 1];
	            }
	        qtdPets--;
    		} 
        }
    }
    
    if (!encontrado) {
        return false;
    } 
    else
    {
    	if(AtualizarPets()){
        	return true;
		} else if(AtualizarPets()){
			qtdPets++;
			return false;
		}
	}
}
bool ApagarPetPeloNome(char* nome){
	int i, j = 0;
    bool encontrado = false;
    
    for (i = 0; i < qtdPets; i++) {
        if (strcmp(nome, pets[i].nomePet) == 0) {
            encontrado = true;
            for (j = i; j < qtdPets - 1; j++) {
                pets[j] = pets[j + 1];
            }
            qtdPets--;
        }
    }
    
    if (!encontrado) {
        return false;
    }else{
	 
	if(AtualizarPets()){
        	return true;	
		} else if(AtualizarPets()){
			qtdPets++;
			return false;
		}
	}
}