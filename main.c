#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Clientes.h"
#include "Pets.h"
#include "Servicos.h"
#include "ServicoPrestado.h"

int subOpcao = -1;
int opcao = -1;

int VerificaPets;
int VerificaClientes;
int VerificaServicos;
int VerificaServicosPrestados;

int escolha, codigo, indice;

char nome[50];

char especie[50];

int lucro;

int main(int argc, char *argv[]) {
	if(!InicializarClientes()){
		printf("  Nao foi possivel alocar memoria dos clientes\n");
		return 1;
	}
	if(!InicializarPets()){
		printf("  Nao foi possivel alocar memoria dos pets\n");
		return 1;
	} 
	if(!InicializarServicos()){
		printf("  Nao foi possivel alocar memoria para os servicos\n");
	} 
	if (!InicializarServicosPrestados()){
		printf("  Nao foi possivel alocar memoria para os servicos prestados\n");
	}
	else {
		do{
		printf("\n======= MENU =======\n");
		printf(" O - Sair\n");
		printf("  1 - Clientes\n");
		printf("  2 - Pets\n");
		printf("  3 - Servicos\n");
		printf("  4 - Verifica alocacoes\n--> ");
		scanf("%d", &opcao);
		
			switch (opcao){
				case 0:
					printf("  \nEncerrando o programa...");
					break;
				case 1:
	        		do{
	        			printf("\n======= SUBMENU CLIENTES =======\n");
						printf(" 0 - Voltar\n");
						printf("  1 - Listar clientes\n");
						printf("  2 - Cadastrar cliente pelo codigo\n");
	        			printf("  3 - Pesquisar cliente\n");
	        			printf("  4 - Excluir cliente\n--> ");
	        			scanf("%d", &subOpcao);
	        			
	        			switch(subOpcao) {
						    case 0:
						        printf("  \nVoltando para o MENU\n");
								system("cls");
						        break;
						    case 1:
						        if (QuantidadeClientes() == 0) {
						            printf("\n  Nenhum cliente cadastrado ainda...\n");
						        } else {
						            int i;
						            for (i = 0; i < QuantidadeClientes(); i++) {
						                Cliente* clienteAtual = ObterClientePeloIndice(i);
						                if (clienteAtual != NULL) {
						                    printf("\n  Cliente #%d\n", i + 1);
						                    printf("  Indice: %d\n", i);
						                    printf("  Codigo: %d\n", clienteAtual->codigoCliente);
						                    printf("  Nome: %s\n", clienteAtual->nome);
						                    printf("  CPF: %s\n", clienteAtual->cpf);
						                    printf("  Telefone: %s\n", clienteAtual->telefone);
						                    free(clienteAtual); // Libera a memória alocada para clienteAtual
						                } else {
						                    printf("\n  Cliente #%d não encontrado.\n", i + 1);
						                }
						            }
						        }
						        break;
						    case 2: {
						        Cliente* clienteTemp = (Cliente*) malloc(sizeof(Cliente));
						        if (clienteTemp) {
						            printf("\n  Digite o codigo do cliente:\n--> ");
						            scanf("%d", &codigo);
						            
						            Cliente* clientePeloCodigo = ObterClientePeloCodigo(codigo);
						            if (clientePeloCodigo != NULL && clientePeloCodigo->codigoCliente == codigo) {
						                printf("\n Codigo de cliente ja existe\n ");
						                free(clienteTemp);  
						            } else {
						                clienteTemp->codigoCliente = codigo;
						                printf("  Digite o nome do cliente:\n--> ");
						                scanf(" %49[^\n]", clienteTemp->nome);
						                printf("  Digite o CPF do cliente:\n--> ");
						                scanf("%s", clienteTemp->cpf);
						                printf("  Digite o telefone do cliente:\n--> ");
						                scanf("%s", clienteTemp->telefone);
						                    
						                if (SalvarCliente(clienteTemp)) {
						                    printf("\n  Cliente cadastrado com sucesso!\n");
						                } else {
						                    printf("\n Erro ao cadastrar cliente!\n");
						                }
						                    
						                free(clienteTemp); // Libera a memória do cliente temporário
						            }
						            if (clientePeloCodigo != NULL) free(clientePeloCodigo); // Libera clientePeloCodigo, se necessário
						        } else {
						            printf("\n  Nao foi possivel fazer a alocacao\n");
						        }
						        break;
						    }
						    case 3:
						        printf("\n  Digite o metodo de pesquisa (0 - Codigo) ( 1 - Indice):\n--> ");
						        scanf("%d", &escolha);
						        switch(escolha) {
						            case 0:
						                printf("\n  Digite o codigo do cliente:\n--> ");
						                scanf("%d", &codigo);
						                Cliente* clientePeloCodigo = ObterClientePeloCodigo(codigo);
						                if (clientePeloCodigo != NULL) {
						                    printf("\n  Cliente encontrado:\n");
						                    printf("  Codigo: %d\n", clientePeloCodigo->codigoCliente);
						                    printf("  Nome: %s\n", clientePeloCodigo->nome);
						                    printf("  CPF: %s\n", clientePeloCodigo->cpf);
						                    printf("  Telefone: %s\n", clientePeloCodigo->telefone);
						                    free(clientePeloCodigo); // Libera a memória
						                } else {
						                    printf("  Cliente do codigo %d, nao encontrado.\n", codigo);
						                }
						                break;
						            case 1:
						                printf("\n  Digite o indice do cliente:\n--> ");
						                scanf("%d", &indice);
						                Cliente* clientePeloIndice = ObterClientePeloIndice(indice);
						                if (clientePeloIndice != NULL) {
						                    printf("\n  Cliente encontrado:\n");
						                    printf("  Codigo: %d\n", clientePeloIndice->codigoCliente);
						                    printf("  Nome: %s\n", clientePeloIndice->nome);
						                    printf("  CPF: %s\n", clientePeloIndice->cpf);
						                    printf("  Telefone: %s\n", clientePeloIndice->telefone);
						                    free(clientePeloIndice); // Libera a memória
						                } else {
						                    printf("  Indice invalido.\n");
						                }
						                break;
						            default:
						                printf("\n  Opcao de pesquisa invalida\n");
						                break;
						        }
						        break;
						    case 4:
						        printf("\n  Escolha como voce deseja apagar o cliente: (0 - codigo) (1 - nome):\n--> ");
						        scanf("%d", &escolha);
						        switch(escolha) {
						            case 0:
						                printf("\n  Digite o codigo do cliente para apagar:\n--> ");
						                scanf("%d", &codigo);
						                
						                Cliente* clientePeloCodigo = ObterClientePeloCodigo(codigo);
						                if (clientePeloCodigo == NULL) {
						                    printf("\n  Cliente não encontrado.\n");
						                } else {
						                    Pet* petPeloCodigoDoCliente = ObterPetPeloCodigoDoCliente(clientePeloCodigo->codigoCliente);
						                    ServicoPrestado* servicoPeloPet = (petPeloCodigoDoCliente != NULL)
						                        ? ObterServicoPrestadoPeloCodigoDoPet(petPeloCodigoDoCliente->codigoPet)
						                        : NULL;
						
						                    if (servicoPeloPet != NULL) {
						                        printf("\n  Nao e possível apagar o cliente, ha servicos associados.\n");
						                        free(servicoPeloPet); // Libera memória de servicoPeloPet
						                    } else {
						                        if (ApagarClientePeloCodigo(codigo)) {
						                            if (petPeloCodigoDoCliente != NULL) ApagarPetPeloCodigo(petPeloCodigoDoCliente->codigoPet);
						                            printf("\n  Cliente com o codigo %d removido com sucesso.\n", codigo);
						                        } else {
						                            printf("\n  Nao foi possivel apagar o cliente com o codigo %d\n", codigo);
						                        }
						                    }
						                    if (petPeloCodigoDoCliente != NULL) free(petPeloCodigoDoCliente); // Libera memória
						                }
						                if (clientePeloCodigo != NULL) free(clientePeloCodigo); // Libera memória
						                break;
						
						            // Repita lógica similar para o caso "1" e libere memória apropriadamente
						        }
						        break;
						
						    default:
						        printf("\n Opcao invalida\n");
						        break;
						}
						
					} while(subOpcao != 0);
					break;
					
					case 2:
						do{
							printf("\n======= SUBMENU PETS =======\n");
							printf(" 0 - Voltar\n");
							printf("  1 - Listar Pets\n");
							printf("  2 - Cadastrar pet pelo codigo\n");
		        			printf("  3 - Pesquisar pet pela especie\n");
		        			printf("  4 - Excluir pet\n--> ");
		        			scanf("%d", &subOpcao);
	        			
	        				switch(subOpcao){
						    case 0:
						        printf("\n  Voltando para o MENU...\n");
						        break;
						    case 1:
						        if(QuantidadePets() == 0){
						            printf("\n  Nenhum pet cadastrado ainda...\n");
						        } else {
						            int i;
						            for(i = 0; i < QuantidadePets(); i++){
						                Pet* petAtual = ObterPetPeloIndice(i);
						                printf("\n  Pet #%d\n", i+1);
						                printf("  Codigo do pet: %d\n", petAtual->codigoPet);
						                printf("  Nome do pet: %s\n", petAtual->nomePet);
						                printf("  Especie do pet: %s\n", petAtual->especiePet);
						                codigo = petAtual->codigoPetCliente;
						                Cliente* clientePeloCodigo = ObterClientePeloCodigo(codigo);
						                if (clientePeloCodigo != NULL) {
						                    printf("  Codigo do dono do pet: %d\n", clientePeloCodigo->codigoCliente);
						                    printf("  Pet de %s\n", clientePeloCodigo->nome);
						                    printf("  CPF de %s: %s\n", clientePeloCodigo->nome, clientePeloCodigo->cpf);
						                    printf("  Telefone de %s: %s\n", clientePeloCodigo->nome, clientePeloCodigo->telefone);
						                }
						                // Liberar a memória alocada para os ponteiros
						                free(clientePeloCodigo);  
						            }
						        }
						        break;
						    case 2:
						        if(QuantidadeClientes() == 0){
						            printf("\n  Nenhum cliente cadastrado ainda.\n");
						        } else {
						            Pet* petTemp = (Pet*) malloc(sizeof(Pet));
						            if(petTemp){
						                printf("\n  Digite o codigo do dono pet:\n--> ");
						                scanf("%d", &codigo);
						
						                Cliente* clientePeloCodigo = ObterClientePeloCodigo(codigo);
						
						                if(clientePeloCodigo){
						                    petTemp->codigoPetCliente = codigo;
						                    printf("\n Digite o codigo do pet:\n--> ");
						                    scanf("%d", &codigo);
						
						                    Pet* petPeloCodigo = ObterPetPeloCodigo(codigo);
						
						                    if(petPeloCodigo != NULL && petPeloCodigo->codigoPet == codigo){
						                        printf("\n Ja existe pet com esse codigo\n");
						                        free(petTemp);
						                    } else {
						                        petTemp->codigoPet = codigo;
						                        printf("  Digite o nome do pet:\n--> ");
						                        scanf(" %49[^\n]", petTemp->nomePet);
						                        printf("  Digite a especie do pet:\n--> ");
						                        scanf(" %49[^\n]", petTemp->especiePet);
						
						                        if(SalvarPets(petTemp)){
						                            printf("\n Pet cadastrado com sucesso!\n");
						                        } else printf("\n Nao foi possivel Cadastrar o pet\n");
						                        free(petTemp);  // Liberar após o uso
						                    }
						                } else {
						                    printf("\n  Cliente nao encontrado.\n");
						                    free(petTemp);  // Liberar caso o cliente não seja encontrado
						                }
						            } else printf("\n Nao foi possivel alocar memoria\n");
						        }
						        break;
						    case 3:
						        printf("\n  Digite a especie do pet:\n--> ");
						        scanf(" %49[^\n]", especie);
						
						        int encontrou = 0;
						        Pet* petPelaEspecie;
						
						        while ((petPelaEspecie = ObterPetPelaEspecie(especie)) != NULL) {
						            printf("\n  Pet encontrado!\n");
						            printf("\n  Codigo do pet: %d\n", petPelaEspecie->codigoPet);
						            printf("  Nome do pet: %s\n", petPelaEspecie->nomePet);
						            printf("  Especie do pet: %s\n", petPelaEspecie->especiePet);
						
						            Cliente* clientePeloCodigo = ObterClientePeloCodigo(petPelaEspecie->codigoPetCliente);
						
						            if (clientePeloCodigo != NULL) {
						                printf("  Codigo do dono do pet: %d\n", clientePeloCodigo->codigoCliente);
						                printf("  Pet de %s\n", clientePeloCodigo->nome);
						                printf("  CPF de %s: %s\n", clientePeloCodigo->nome, clientePeloCodigo->cpf);
						                printf("  Telefone de %s: %s\n", clientePeloCodigo->nome, clientePeloCodigo->telefone);
						                free(clientePeloCodigo);  // Liberar a memória do cliente após o uso
						            }
						            encontrou = 1;
						            free(petPelaEspecie);  // Liberar a memória do pet após o uso
						            
						            
						        }
						
						        if (!encontrou) {
						            printf("\n Nenhum pet da especie '%s' foi encontrado.\n", especie);
						        }
						        break;
						    case 4:
						        printf("\n  Escolha como voce deseja apagar o pet: (0 - codigo) (1 - nome):\n--> ");
						        scanf("%d", &escolha);
						
						        switch(escolha){
						            case 0:
						                printf("\n  Digite o codigo do pet para apagar:\n--> ");
						                scanf("%d", &codigo);
						
						                Pet* petPeloCodigo = ObterPetPeloCodigo(codigo);
						                if(petPeloCodigo == NULL){
						                    printf("\n  Pet nao encontrado.\n");
						                    break;
						                }
						                ServicoPrestado* servicoPrestadoPeloCodigoDoPet = ObterServicoPrestadoPeloCodigoDoPet(petPeloCodigo->codigoPet);
						
						                if(servicoPrestadoPeloCodigoDoPet != NULL){
						                    printf("\n  Nao foi possivel apagar o pet, servico associado.\n");
						                    break;
						                } else if(petPeloCodigo){
						                    printf("\n  Codigo do pet: %d\n", petPeloCodigo->codigoPet);
						                    printf("  Nome do pet: %s\n", petPeloCodigo->nomePet);
						                    printf("  Especie do pet: %s\n", petPeloCodigo->especiePet);
						                    Cliente* clientePeloCodigo = ObterClientePeloCodigo(petPeloCodigo->codigoPetCliente);
						                    if (clientePeloCodigo != NULL) {
						                        printf("  Codigo do dono do pet: %d\n", clientePeloCodigo->codigoCliente);
						                        printf("  Pet de %s\n", clientePeloCodigo->nome);
						                        printf("  CPF de %s: %s\n", clientePeloCodigo->nome, clientePeloCodigo->cpf);
						                        printf("  Telefone de %s: %s\n", clientePeloCodigo->nome, clientePeloCodigo->telefone);
						                        free(clientePeloCodigo);  // Liberar o cliente após o uso
						                    }
						                    printf("\n  Tem certeza que deseja apagar?\n");
						                    printf("\n  [0]Nao [1]Sim\n--> ");
						                    scanf("%d", &escolha);
						                    if(escolha == 1){
						                        if(ApagarPetPeloCodigo(codigo) == true){
						                            printf("\n  Pet com o codigo %d removido com sucesso.\n", codigo);
						                        } else printf("\n  Nao foi possivel apagar o Pet com o codigo %d\n", codigo);
						                    } else printf("\n  Cancelando operacao.\n");
						                    free(petPeloCodigo);  // Liberar a memória do pet após o uso
						                } else printf("\n  Pet com o codigo %d nao encontrado.\n", codigo);
						                break;
						            case 1:
						                printf("\n  Digite o nome do pet para apagar:\n--> ");
						                scanf(" %49[^\n]", nome);
						                Pet* petPeloNome = ObterPetPeloNome(nome);
						                if(petPeloNome){
						                    printf("\n  Pet encontrado\n");
						                    printf("\n  Codigo do pet: %d\n", petPeloNome->codigoPet);
						                    printf("  Nome do pet: %s\n", petPeloNome->nomePet);
						                    printf("  Especie do pet: %s\n", petPeloNome->especiePet);
						                    Cliente* clientePeloCodigo = ObterClientePeloCodigo(petPeloNome->codigoPetCliente);
						                    if (clientePeloCodigo != NULL) {
						                        printf("  Codigo do dono do pet: %d\n", clientePeloCodigo->codigoCliente);
						                        printf("  Pet de %s\n", clientePeloCodigo->nome);
						                        printf("  CPF de %s: %s\n", clientePeloCodigo->nome, clientePeloCodigo->cpf);
						                        printf("  Telefone de %s: %s\n", clientePeloCodigo->nome, clientePeloCodigo->telefone);
						                        free(clientePeloCodigo);  // Liberar o cliente após o uso
						                    }
						                    printf("\n  Tem certeza que deseja apagar?\n");
						                    printf("\n  [0]Nao [1]Sim\n--> ");
						                    scanf("%d", &escolha);
						                    if(escolha == 1){
						                        if(ApagarPetPeloNome(nome) == true){
						                            printf("\n  Pet com o nome %s removido com sucesso.\n", nome);
						                        } else printf("\n  Nao foi possivel apagar o Pet com o nome %s\n", nome);
						                    } else printf("\n  Cancelando operacao.\n");
						                    free(petPeloNome);  // Liberar a memória do pet após o uso
						                } else printf("\n  Pet com o nome %s nao encontrado.\n", nome);
						                break;
						            default:
						                printf("\n  Opcao invalida!\n");
						        }
						        break;
						    default:
						        printf("\n  Opcao invalida!\n");
						}
						

						}while(subOpcao != 0);
	        			break;
	        		case 3:
	        			do{
	        				printf("\n======= SUBMENU SERVICOS =======\n");
							printf(" 0 - Voltar\n");
							printf("  1 - Listar servicos\n");
							printf("  2 - Listar servicos prestados\n");
							printf("  3 - Cadastrar servico pelo codigo\n");
							printf("  4 - Atualizar servico\n");
							printf("  5 - Prestar servico\n");
		        			printf("  6 - Excluir servico pelo codigo\n");
		        			printf("  7 - Ver lucro dos servicos\n--> ");		        			
							scanf("%d", &subOpcao);
	
							switch (subOpcao) {
							    case 0:
							        printf("\n Voltando ao menu...\n");
							        break;
							    case 1:
							        if (QuantidadeServicos() == 0) {
							            printf("\n  Nenhum servico cadastrado ainda...\n");
							        } else {
							            int i;
							            for (i = 0; i < QuantidadeServicos(); i++) {
							                Servico* servicoAtual = ObterServicoPeloIndice(i); // Não precisa de malloc porque recebemos o endereço da função.
							                if (servicoAtual != NULL) { 
							                    printf("\n  Servico #%d\n", i + 1);
							                    printf("  Indice: %d\n", i);
							                    printf("  Codigo: %d\n", servicoAtual->codigoServico); // Como é retornado um ponteiro para cliente, usa-se ->
							                    printf("  Nome: %s\n", servicoAtual->nome);
							                    printf("  Preco: %.2f\n", servicoAtual->preco);
							                    free(servicoAtual);  // Libera a memória após o uso
							                } else {
							                    printf("\n  Servico #%d não encontrado.\n", i + 1);
							                }
							            }
							        }
							        break;
							    case 2: {
							        if (QuantidadeServicos() == 0) {
							            printf("\n  Nenhum servico cadastrado ainda...\n");
							        } else if (QuantidadeServicosPrestados() == 0) {
							            printf("\n  Nenhum servico prestado ainda...\n");
							        } else {
							            int i;
							            for (i = 0; i < QuantidadeServicosPrestados(); i++) {
							                ServicoPrestado* servicoPrestadoAtual = ObterServicoPrestadoPeloIndice(i);
							                Pet* petPeloCodigo = ObterPetPeloCodigo(servicoPrestadoAtual->codigoPet);
							                Cliente* clientePeloCodigo = ObterClientePeloCodigo(petPeloCodigo->codigoPetCliente);
							                if (servicoPrestadoAtual == NULL) {
							                    printf("\n  Servico nao encontrado.\n\n");
							                }
							                if (petPeloCodigo == NULL) {
							                    printf("\n  Pet nao encontrado.\n");
							                }
							                if (clientePeloCodigo == NULL) {
							                    printf("\n  Cliente nao encontrado.\n");
							                } else {
							                    printf("\n  Servico #%d\n", i + 1);
							                    printf("  Indice: %d\n", i);
							                    printf("  Nome: %s\n", servicoPrestadoAtual->nome);
							                    printf("  Preco: %.2f\n", servicoPrestadoAtual->preco);
							                    printf("\n  Codigo do pet: %d\n", petPeloCodigo->codigoPet);
							                    printf("  Nome do pet: %s\n", petPeloCodigo->nomePet);
							                    printf("  Especie do pet: %s\n", petPeloCodigo->especiePet);
							                    printf("\n  Codigo do dono do pet: %d\n", clientePeloCodigo->codigoCliente);
							                    printf("  Nome do dono do pet: %s\n", clientePeloCodigo->nome);
							                    printf("  CPF do %s: %s\n", clientePeloCodigo->nome, clientePeloCodigo->cpf);
							                    printf("  Telefone do %s: %s\n", clientePeloCodigo->nome, clientePeloCodigo->telefone);
							                    free(servicoPrestadoAtual); // Libera a memória
							                    free(petPeloCodigo);       // Libera a memória
							                    free(clientePeloCodigo);   // Libera a memória
							                }
							            }
							        }
							        break;
							    }
							    case 3: {
							        Servico* servicoTemp = (Servico*) malloc(sizeof(Servico));
							        if (servicoTemp) {
							            printf("\n  Digite o codigo do servico:\n--> ");
							            scanf("%d", &codigo);
							
							            Servico* servicoPeloCodigo = ObterServicoPeloCodigo(codigo);
							
							            if (servicoPeloCodigo != NULL && servicoPeloCodigo->codigoServico == codigo) {
							                printf("\n Codigo de servico ja existe\n ");
							                free(servicoTemp);  
							            } else {
							                servicoTemp->codigoServico = codigo;
							                printf("  Digite o nome do servico:\n--> ");
							                scanf(" %49[^\n]", servicoTemp->nome);
							                printf("  Digite o preco do servico:\n--> ");
							                scanf("%f", &servicoTemp->preco);
							
							                if (SalvarServico(servicoTemp)) {
							                    printf("\n  Servico cadastrado com sucesso!\n");
							                } else {
							                    printf("\n Erro ao cadastrar servico!\n");
							                }
							
							                free(servicoTemp);
							            }
							        } else {
							            printf("\n  Nao foi possivel fazer a alocacao\n");
							        }
							        break;
							    }
							    case 4: {
							        if (QuantidadeServicos() == 0) {
							            printf("\n  Nenhum servico cadastrado ainda...\n");
							        } else {
							            printf("\n  Servicos:\n");
							            int i;
							            for (i = 0; i < QuantidadeServicos(); i++) {
							                Servico* servicoAtual = ObterServicoPeloIndice(i);
							                if (servicoAtual != NULL) { 
							                    printf("\n  Servico #%d\n", i + 1);
							                    printf("  Indice: %d\n", i);
							                    printf("  Codigo: %d\n", servicoAtual->codigoServico);
							                    printf("  Nome: %s\n", servicoAtual->nome);
							                    printf("  Preco: %.2f\n", servicoAtual->preco);
							                    free(servicoAtual);  // Libera a memória após o uso
							                } else {
							                    printf("\n  Servico #%d não encontrado.\n", i + 1);
							                }
							            }
							        }
							        printf("\n  Digite o codigo do servico que deseja atualizar?\n-->  ");
							        scanf("%d", &codigo);
							
							        Servico* servicoAtualizar = ObterServicoPeloCodigo(codigo);
							
							        if (servicoAtualizar == NULL) {
							            printf("\n  Servico nao encontrado.\n");
							            break;
							        } else {
							            servicoAtualizar->codigoServico = codigo;
							            printf("\n  Digite o novo nome do servico:\n--> ");
							            scanf(" %49[^\n]", servicoAtualizar->nome);
							
							            Servico* servicoPeloNome = ObterServicoPeloNome(servicoAtualizar->nome);
							
							            if (servicoPeloNome) {
							                printf("\n  Nome de servico ja existe\n");
							                break;
							            } else {
							                printf("\n  Digite o novo preco do servico:\n--> ");
							                scanf("%f", &servicoAtualizar->preco);
							            }
							        }
							
							        if (MudarServico(servicoAtualizar)) {
							            printf("\n  Servico atualizado com sucesso!\n");
							        } else {
							            printf("\n  Nao foi possivel atualizar o servico.\n");
							        }
							
							        free(servicoAtualizar);  // Libera a memória
							        break;
							    }
							    case 5: {
							        if (QuantidadeServicos() == 0) {
							            printf("\n  Nenhum servico cadastrado ainda...\n");
							        }
							        printf("\n  Digite o codigo do pet para quem quer prestar servico\n--> ");
							        scanf("%d", &codigo);
							
							        Pet* petServico = ObterPetPeloCodigo(codigo);
							
							        if (petServico == NULL) {
							            printf("\n  Pet nao encontrado.\n");
							        } else {
							            int i;
							            for (i = 0; i < QuantidadeServicos(); i++) {
							                Servico* servicoAtual = ObterServicoPeloIndice(i);
							                if (servicoAtual != NULL) { 
							                    printf("\n  Servico #%d\n", i + 1);
							                    printf("  Indice: %d\n", i);
							                    printf("  Codigo: %d\n", servicoAtual->codigoServico);
							                    printf("  Nome: %s\n", servicoAtual->nome);
							                    printf("  Preco: %.2f\n", servicoAtual->preco);
							                    free(servicoAtual);  // Libera a memória
							                } else {
							                    printf("\n  Servico #%d não encontrado.\n", i + 1);
							                }
							            }
							            printf("\n  Digite o codigo do servico que quer prestar?\n--> ");
							            scanf("%d", &codigo);
							
							            Servico* servicoPrestar = ObterServicoPeloCodigo(codigo);
							
							            if (servicoPrestar == NULL) {
							                printf("\n  Servico nao encontrado\n");
							            } else {
							                ServicoPrestado* servicoPrestado = servicoPrestar;
							                servicoPrestado->codigoPet = petServico->codigoPet;
							                if (SalvarServicoPrestado(servicoPrestar)) {
							                    printf("\n  Servico prestado com sucesso\n");
							                } else {
							                    printf("\n  Nao foi possivel prestar o servico\n");
							                }
							            }
							        }
							        break;
							    }
								case 6: {
								    if (QuantidadeServicos() == 0) {
								        printf("\n  Nenhum servico cadastrado ainda...\n");
								    } else {
								        printf("\n  Digite o codigo do servico para apagar:\n--> ");
								        scanf("%d", &codigo);
								
								        Servico* servicoPeloCodigo = ObterServicoPeloCodigo(codigo);
								        if (servicoPeloCodigo == NULL) {
								            printf("\n  Servico nao encontrado.\n");
								        } else {
								            ServicoPrestado* servicoPeloNome = ObterServicoPrestadoPeloNome(servicoPeloCodigo->nome);
								            if (servicoPeloNome != NULL) {
								                printf("\n  Nao foi possivel apagar, servico ja prestado.\n");
								            } else {
								                if (ApagarServicoPeloCodigo(codigo)) {
								                    printf("\n  Servico apagado com sucesso.\n");
								                } else {
								                    printf("\n  Nao foi possivel apagar o servico.\n");
								                }
								            }
								            free(servicoPeloCodigo);  // Libera a memória alocada para o serviço
								        }
								    }
								    break;
								}
								case 7:{
									printf("\n  Lucro total R$%.2f\n", CalcularLucro());
									break;
								}
								default:
									printf("\n  Opcao invalida.\n");
									break;
							}
						}while(subOpcao != 0);
	        			break;
					case 4:
						VerificaClientes = VerificaTamanhoAlocacaoClientes();
						VerificaPets = VerificaTamanhoAlocacaoPets();
						VerificaServicos = VerificaTamanhoAlocacaoServicos();
						VerificaServicosPrestados = VerificaTamanhoAlocacaoServicosPrestados();
						printf("\n  Alocacao clientes: %d\n", VerificaClientes);
						printf("\n  Alocacao pets: %d\n", VerificaPets);
						printf("\n  Alocacao servicos: %d\n", VerificaServicos);
						printf("\n  Alocacao servicos prestados: %d\n", VerificaServicosPrestados);
						break;
					default:
						printf("\n  Opcao invalida\n");
						break;
			}
		}while(opcao != 0);
		EncerraClientes();
		EncerraPets();
		EncerraServicos();
		EncerraServicosPrestados();
	}
	return 0;
}