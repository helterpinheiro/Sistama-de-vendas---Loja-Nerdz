
/*
	***************************************
	trabalho de logica de programacao
   	Aluno: Helter Bruno da Paixao Pinheiro
   	Sistema loja NERDZ
	Data de criacao 20/10/2018

   	***************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "lista.h"
/*
fun?es declaradas implicitamente
*/
int compIdCliente(void *a, void *b);
int compNomeCliente(void *a, void *b);
int compNomeProduto(void *a, void *b);
int compIdProduto(void *a, void *b);
void listaMenu(Sllist *l1, Sllist *l2,Sllist *l3, FILE *f);
void imprimirDataCliente(void *a);
void imprimirDataProduto(void *a);
void imprimirDataRelatorio(void *a);
void imprimirDataClienteArquivo(void *a,FILE *f);
void preencherListaArquivo(Sllist *l, FILE *f);
void preencherListaProduto(Sllist *l, FILE *f);
void preencherListaRelatorio(Sllist *l,FILE *f);
void imprimirDataProdutoArquivo(void *a, FILE *f);
void imprimirDataRelatorio(void *a);

/* a main fica aqui*/
int main()
{
    Sllist *l1 = sllCreate();
    Sllist *l2 = sllCreate();
    Sllist *l3 = sllCreate();
    FILE *arq;
    FILE *arq2;
    FILE *arq3;
    preencherListaArquivo(l1,arq);
    preencherListaProduto(l2,arq2);
    preencherListaRelatorio(l3,arq3);
    //arq = fopen("Clientes.txt","a");
    listaMenu(l1,l2,l3,arq);
    fclose(arq);
    fclose(arq2);
    fclose(arq3);
    return 0;
}
/*olha a mais aqui em cima*/

/* struct para produtos variados*/
typedef struct _produto_{
	char nome[50];
	char tipo[50];/*descri?o do produto*/
	float preco; /*pre? do produto*/
	int qtd;
	int id;
}Produto;
/* struct para clientes*/
typedef struct _cliente_{
	char nome[50];
	char sobrenome[50];
	int id;
}Cliente;

typedef struct _relatorio_{
    char nome[50];
    char data[50];
    //char meio[50];
    char nomepr[50];
    float porcec;
    float vfinal;
    int unidades;
    float troco;

}Relatorio;

/*
*
Funcoes
*
*/

void preencherListaArquivo(Sllist *l, FILE *f){
    Cliente *pb;

    char aux[20];
    char aux2[20];
     f = fopen("Clientes.txt","r");
     pb = (Cliente *)malloc(sizeof(Cliente));
    while(fscanf(f,"%s %s %s %s %d",&aux,&pb->nome,pb->sobrenome,&aux2,&pb->id)!=EOF){
        sllInsertFirst(l,(void *)pb);
        pb = (Cliente *)malloc(sizeof(Cliente));
    }
}
void preencherListaRelatorio(Sllist *l, FILE *f)
{
    Relatorio *r;
    char aux[15],aux2[15],aux3[15];
    r = (Relatorio *)malloc(sizeof(Relatorio));
    f = fopen("Relatorio.txt","r");
    while(
        fscanf(f,"%s %[^\n]s",&aux,r->nome)&&
        fscanf(f,"%s %s %s %[^\n]s",&aux,&aux2,&aux3,r->data)&&
        fscanf(f,"%s %[^\n]s",&aux,&r->nomepr)&&
        fscanf(f,"%s %f",&aux,&r->porcec)&&
        fscanf(f,"%s %f",&aux,&r->vfinal)&&
        fscanf(f,"%s %s %d",&aux,&aux2,&r->unidades)&&
        fscanf(f,"%s %f",&aux,&r->troco)!=EOF){
        sllInsertFirst(l,(void *)r);
        r = (Relatorio *)malloc(sizeof(Relatorio));
    }
}

void preencherListaProduto(Sllist *l, FILE *f)
{
    Produto *pb;
    char aux[20],aux2[20],aux3[20],aux4[20],aux5[20];
    f = fopen("Produtos.txt","r");
    pb = (Produto *)malloc(sizeof(Produto));
    /*while(fscanf(f,"%s %s %s %s %s %f %s %d %s %d",&aux,&pb->nome,&aux2,&pb->tipo,&aux3,&pb->preco,&aux4,&pb->qtd,&aux5,&pb->id)!=EOF){
         sllInsertFirst(l,(void *)pb);
        pb = (Produto *)malloc(sizeof(Produto));
    }
    */
    while(fscanf(f,"%s %[^\n]s",&aux,&pb->nome)&&
        fscanf(f,"%s %[^\n]s",&aux2,&pb->tipo)&&
        fscanf(f,"%s %f",&aux3,&pb->preco)&&
        fscanf(f,"%s %d",&aux4,&pb->qtd)&&
        fscanf(f,"%s %d",&aux5,&pb->id)!=EOF){

        sllInsertFirst(l,(void *)pb);
        pb=(Produto *)malloc(sizeof(Produto));
    }

}
void inserirListaProduto(Sllist *l,FILE *f)
{
	Produto *p;
	if(l!=NULL){
        f = fopen("Produtos.txt","a");
		p = (Produto *)malloc(sizeof(Produto));
		if(p!=NULL){ /*caso aloca?o ocorra normalmente*/
            fflush(stdin);
			printf("%s\n","Insira o nome do produto:" );
			scanf("%[^\n]s",p->nome);
			fflush(stdin);
			printf("%s\n","Insira o tipo do produto: ");
			scanf("%[^\n]s",p->tipo);
			//fflush(stdin);
			printf("%s\n","Insira o preco do produto: ");
			scanf("%f",&p->preco);
			printf("%s\n", "Insira a quantidade: ");
			scanf("%d",&p->qtd);
			//fflush(stdin);
			printf("%s\n","Insira o ID do produto: ");
			scanf("%d",&p->id);

			if(sllInsertFirst(l,(void*)p)== TRUE){ /*funcao inserir retorna um boolean*/
				printf("%s\n","Produto inserido com sucesso!");
				fprintf(f,"%s %s\n%s %s\n%s %f\n%s %d\n%s %d\n\n","NOME:",p->nome,"TIPO:",p->tipo,"PRECO:",p->preco,"QTD:",p->qtd,"ID:",p->id);
			}else{
				printf("%s\n","Erro na insercao!");
			}
		}else{
			free(p);
		}
	}
}



/*funcao responsavel por inserir um cliente na lista*/
void inserirListaCliente(Sllist *l,FILE *f)
{
	Cliente *c;
	//char nome[100];
	if(l!=NULL){
        f = fopen("Clientes.txt","a");
		c = (Cliente *)malloc(sizeof(Cliente));
		if(c!=NULL){/*caso aloca?o ocorra normalmente*/
			printf("%s\n","Insira o nome do cliente:" );
			scanf("%s",c->nome);

			printf("%s\n","Insira o sobrenome:");
			scanf("%s",c->sobrenome);

			printf("%s\n","Insira o id do cliente: ");
			scanf("%d",&c->id);
			//fflush(stdin);

			if(sllInsertFirst(l,(void *)c)== TRUE){ /*funcao inserir retorna um boolean*/
				printf("%s\n","Clinete inserido com sucesso!");
				printf("%s","Bem vindo senhor: ");
				printf("%s %s",c->nome,c->sobrenome);
				fprintf(f,"Nome: %s %s ID: %d\n",c->nome,c->sobrenome,c->id);

			}else{
				printf("%s\n","Erro na insercao!");
			}
		}else{
			free(c);
		}
	}
}
/*funcao responsavel por remover cliente*/
void removerCliente(Sllist *l)
{
	int id;
	printf("%s\n","Informe o id do cliente: ");
	scanf("%d",&id);
	if(sllRemoveSpec(l,(void *)id,compIdCliente)!=NULL){
        printf("Cliente removido!\n");

	}else{
		printf("%s\n","Erro ao remover cliente!");
	}
}

/* funcao responsavel por remover produto*/
void removerProduto(Sllist *l)
{
	char nome[50];
	fflush(stdin);
	printf("%s\n","Informe o nome do produto: ");
	scanf("%[^\n]s",nome);
	if(sllRemoveSpec(l,(void *)nome,compNomeProduto)!=NULL){
		printf("%s\n","Produto removido!");
	}else{
		printf("%s\n","Erro ao remover produto!");
	}
}



void listarListaCliente(Sllist *l)
{
    void *data;
    if(l!=NULL){
    data = sllFirst(l);
        if(data == NULL){
            printf("\n%s\n","Nao ha clientes!");
        }else{
            while(data!=NULL){
                imprimirDataCliente(data);
                data=sllGetNext(l);
            }
        }
    }
}

void listarListaProduto(Sllist *l)
{
    void *data;
    if(l!=NULL){
    data = sllFirst(l);
        if(data==NULL){
                printf("\n%s\n","Nao ha produtos cadastrados!");
        }else{
            while(data!=NULL){
                imprimirDataProduto(data);
                data=sllGetNext(l);
            }
        }
    }
}

void listarListaRelatorio(Sllist *l)
{
    void *data;
    if(l!=NULL){
        data = sllFirst(l);
        if(data == NULL){
            printf("\n%s\n","Nao ha nada no relatorio!");
        }else{
            while(data!=NULL){
                imprimirDataRelatorio(data);
                data = sllGetNext(l);
            }
        }
    }

}




void listaMenu(Sllist *l1, Sllist *l2,Sllist *l3, FILE *f)
{
	char opc,ch,ch2,nome[50],tipo[50];
	//char auxNome[50],auxTipo[50];
	int id,qtd1,idzinho=0;
	float preco;
	void *aux;

	while(opc!=7){


    	/*printf("\n\n%s\n","  ************************************************************");
    	printf("        ************************************************************\n");
    	*/printf("\n        **                                                        **\n");
    	printf("        **   ****   **  ******   *****     ******     *********   **\n");
    	printf("        **   *** *  **  ***      ***   *   ***   **   ****** *    **\n");
    	printf("        **   ***  * **  ******   *****     ***    **      *       **\n");
    	printf("        **   ***   ***  ***      ***  **   ***   **    * ******   **\n");
    	printf("        **   ***    **  ******   ***   **  ******     *********   **\n");
    	printf("        **                                                        **\n");
    	/*printf("        ************************************************************\n");
    	printf("        ************************************************************\n");
		*/
    	printf("        ____________________________________________________________\n");
    	printf("       |                                                            |\n");
    	printf("       |    1 - CADASTRAR CLIENTE        6 - VENDER                 |\n");
    	printf("       |    2 - CADASTRAR PRODUTO        7 - RELATORIO              |\n");
    	printf("       |    3 - REMOVER CLIENTE          8 - LISTAR PRODUTOS        |\n");
    	printf("       |    4 - REMOVER PRODUTO          9 - LISTAR CLIENTES        |\n");
    	printf("       |    5 - EDITAR                   0 - SAIR                   |\n");
    	printf("       |____________________________________________________________|\n");
    	printf("        ============================================================\n");
    	scanf("%s",&opc);


    	switch(opc)
    	{
    		case '1':
    			if(l1!=NULL){
    				system("cls");
    				inserirListaCliente(l1,f);

    			}else{
    				printf("%s\n","Erro ao acessar lista!");
    			}
    			break;

    		case '2':
    			if(l2!=NULL){
    				system("cls");
    				inserirListaProduto(l2,f);
    			}else{
    				printf("%s\n","Erro ao acessar lista!");
    			}
    			break;

    		case '3':
    			system("cls");
    			removerCliente(l1);
    			f = fopen("Clientes.txt","w");
    			void *data;
    			data = sllFirst(l1);
    			if(data == NULL){
                    printf("Nao ha clientes!\n");
    			}else{
                    while(data!=NULL){
                        imprimirDataClienteArquivo(data,f);
                        data = sllGetNext(l1);
                    }
    			}

    			break;

    		case '4':
    			system("cls");
    			removerProduto(l2);
    			f = fopen("Produtos.txt","w");
    			if(f!=NULL){
    			void *data1;
    			data1 = sllFirst(l2);
    			if(data1 == NULL){
                    printf("Nao ha produtos!\n");
    			}else{
                    while(data1!=NULL){
                        imprimirDataProdutoArquivo(data1,f);
                        data1 = sllGetNext(l2);
                    }
    			}
    			}else{
                    return 1;
    			}
    			break;

    		case '5':
    			system("cls");
    			printf("\n%s\n","=================================================");
    			printf("%s\n","===                 EDITAR                    ===");
    			printf("%s\n","=================================================");
    			printf("%s\n","             1 - Editar cliente");
    			printf("%s\n","             2 - Editar Produto");
    			printf("Escolha uma opcao: \n");
    			scanf("%s",&ch);
    			switch(ch)
    			{
    				case '1':
    					system("cls");
    					printf("\n%s\n","Informe o ID do cliente:");
    					scanf("%d",&id);
    					aux = sllQuery(l1,(void *)id,compIdCliente);
    					if(aux!=NULL){
    						Cliente *c;
    						c = (Cliente *)aux;
    						system("cls");
    						printf("\n%s\n"," **************************************************");
    						printf("%s\n"," ***                 EDITOR CLIENTE             ***");
    						printf("%s\n"," **************************************************");
    						printf("%s\n","                   1 - Nome do cliente");
    						printf("%s\n","                   2 - ID do cliente");
    						scanf("%s",&ch2);
    						switch(ch2){
    							case '1':
    								//char nome;
    								printf("\n%s\n","Informe o novo nome do cliente: ");
    								scanf("%s",nome);
    								strcpy(c->nome,nome);
    								printf("\n%s\n","Informe o novo sobrenome do cliente: ");
    								scanf("%s",nome);
    								strcpy(c->sobrenome,nome);
    								printf("\n%s\n","Nome do cliente alterado com sucesso!");
    								void *data;
                                    data = sllFirst(l1);
                                    f = fopen("Clientes.txt","w");
                                    if(data == NULL){
                                        printf("Nao ha clientes!\n");
                                    }else{
                                        while(data!=NULL){
                                            imprimirDataClienteArquivo(data,f);
                                            data = sllGetNext(l1);
                                        }
                                    }



    							break;

    							case '2':
    								//int id;
    								printf("\n%s\n","Informe o novo id do cliente: ");
    								scanf("%d",&id);
    								c->id = id;
    								printf("%s\n","id do cliente alterado com sucesso!");
    								void *data8;
                                    data8 = sllFirst(l1);
                                    f = fopen("Clientes.txt","w");
                                    if(data8 == NULL){
                                        printf("Nao ha clientes!\n");
                                    }else{
                                        while(data8!=NULL){
                                            imprimirDataClienteArquivo(data8,f);
                                            data8 = sllGetNext(l1);
                                        }
                                    }
    							break;

    							default:
    								printf("%s\n","Opcao Invalida");
    						}
    						break;

    					} else{
    						printf("Informe um cliente valido\n");
    					}
    					break;
    				case '2':
    					system("cls");
    					printf("%s\n","Informe o id do produto: ");
    					scanf("%d",&id);
    					aux = sllQuery(l2,(void *)id, compIdProduto);
    					if(aux!=NULL){
    						Produto *p;
    						p = (Produto *)aux;
    						printf("\n%s\n"," ===================================================");
    						printf("%s\n"," ===                 Editar Produto              ===");
    						printf("%s\n"," ===================================================");
    						printf("%s\n","                   1 - Nome do Produto");
    						printf("%s\n","                   2 - Tipo do Produto");
    						printf("%s\n","                   3 - preco do Produto");
    						printf("%s\n","                   4 - Quantidade do produto");
    						printf("%s\n","                   5 - ID do produto");
    						scanf("%s",&ch2);
    						switch(ch2)
    						{
                                case '1':
                                    printf("\n%s\n","Informe o novo nome do produto: ");
                                    fflush(stdin);
                                    scanf("%[^\n]s",&nome);
                                    strcpy(p->nome,nome);
                                    printf("%s\n","nome do produto alterado com sucesso! ");
                                    void *data9;
                                    data9 = sllFirst(l2);
                                    f = fopen("Produtos.txt","w");
                                    if(data9 == NULL){
                                        printf("Nao ha Produto!\n");
                                    }else{
                                        while(data9!=NULL){
                                            imprimirDataProdutoArquivo(data9,f);
                                            data9 = sllGetNext(l2);
                                        }
                                    }
                                break;

                                case '2':
                                    printf("\n%s\n","Informe o novo tipo do produto");
                                    fflush(stdin);
                                    scanf("%[^\n]s",&tipo);
                                    strcpy(p->tipo,tipo);
                                    printf("%s\n","Tipo do produto alterado com sucesso! ");
                                    void *data11;
                                    data11 = sllFirst(l2);
                                    f = fopen("Produtos.txt","w");
                                    if(data11 == NULL){
                                        printf("Nao ha Produto!\n");
                                    }else{
                                        while(data11!=NULL){
                                            imprimirDataProdutoArquivo(data11,f);
                                            data11 = sllGetNext(l2);
                                        }
                                    }
                                break;

                                case '3':
                                    printf("\n%s\n","Informe o novo preco do produto: ");
                                    scanf("%f",&preco);
                                    p->preco = preco;
                                    printf("%s\n","Preco do produto alterado com sucesso! ");
                                    void *data12;
                                    data12 = sllFirst(l2);
                                    f = fopen("Produtos.txt","w");
                                    if(data12 == NULL){
                                        printf("Nao ha Produto!\n");
                                    }else{
                                        while(data12!=NULL){
                                            imprimirDataProdutoArquivo(data12,f);
                                            data12= sllGetNext(l2);
                                        }
                                    }
                                break;

                                case '4':
                                    printf("\n%s\n","Informe a nova quantidade do produto: ");
                                    scanf("%d",&qtd1);
                                    p->qtd = qtd1;
                                    printf("Produto alterado com sucesso!\n");
                                    void *data13;
                                    data13 = sllFirst(l2);
                                    f = fopen("Produtos.txt","w");
                                    if(data13 == NULL){
                                        printf("Nao ha Produto!\n");
                                    }else{
                                        while(data13!=NULL){
                                            imprimirDataProdutoArquivo(data13,f);
                                            data13 = sllGetNext(l2);
                                        }
                                    }
                                    break;
                                case '5':

                                    printf("\n%s \n","Informe o novo ID do produto:");
                                    scanf("%d",&idzinho);
                                    p->id = idzinho;
                                    printf("id do produto alterado com sucesso!\n");
                                    void *data15;
                                    data15 = sllFirst(l2);
                                    f = fopen("Produtos.txt","w");
                                    if(data15 == NULL){
                                        printf("Nao ha produto!\n");
                                    }else{
                                        while(data15!=NULL){
                                            imprimirDataProdutoArquivo(data15,f);
                                            data15 = sllGetNext(l2);
                                        }
                                    }
                                    break;

                            default:
                                printf("informe uma opcap valida!\n");

    						}
    						break;

    					}else{
                            printf("Informe um produto valido!");
    					}

                }
    			break;
    		case '6':
    		    system("cls");
    		    /* arquivo do relatorio*/
    		    FILE *arquivo;
    		    arquivo = fopen("Relatorio.txt","a");
    		    /*
    		    *
    		    */
    		    /*variaveis*/
    		    char nome[50];
    		    int qtd=0,choice = 0, senha = 0, dig = 0,aux = 0, aux2 = 0, auxid = 0;
    		    void *data5;
    		    float result = 0, desc = 0, descfinal = 0;
    		    Produto *p;
    		    Cliente *cliente;
    		    /*
    		    *
    		    */
    		    fflush(stdin);
    		    printf("%s: \n","Informe o id do Cliente: ");
    		    scanf("%d",&auxid);
    		    void *data88;
    		    data88 = sllFirst(l1);
    		    while(data88!=NULL){
                    cliente = (Cliente *)data88;
                    if(cliente->id == auxid){
                        break;
                    }
                    data88 = sllGetNext(l1);
    		    }
    		    if(data88 == NULL){
                    printf("cliente nem existe!\n");
                    break;
    		    }

    		    fflush(stdin);
    		    printf("%s:\n","Informe o nome do produto");
    		    scanf("%[^\n]s",nome);
    		    fflush(stdin);
    		    printf("%s:\n","Informe a quantidade a ser vendida");
    		    scanf("%d",&qtd);
    		    data5 = sllFirst(l2);
    		    if(data5 == NULL || qtd == 0){
                    printf("Sem produtos! ou quantidade informada pelo usuario irregular\n");
    		    }else{
                    while(data5!=NULL){
                        p = (Produto *)data5;
                        if(strcmp(nome,p->nome)==0){
                           if(p->qtd>qtd){
                            result = qtd * p->preco;
                            printf("%s: %.2f\n","A quantia total sai por",result);
                            printf("%s \n","Pagar em 1 - cartao ou 2 - dinheiro");
                            scanf("%d",&choice);
                            if(choice == 1){
                                printf("Digine a senha do cartao:\n");
                                scanf("%d",&senha);
                                printf("Digite os ultimos 3 numeros do seu cartao:\n");
                                scanf("%d",&dig);
                                printf("Desconto de quantos %% no valor altual?\n");
                                scanf("%f",&desc);
                                descfinal = (result*desc)/100;
                                result -= descfinal;
                                printf("%s: %.2f\n","Valor atualizado",result);
                                printf("%s: \n","Gostaria de continuar a transacao?");
                                printf("%s \n","1 - SIM 2 - NAO");
                                scanf("%d",&aux);
                                if(aux == 1){
                                    float temp = 0;
                                    char dateStr[9],timeStr[9];
                                    _strdate(dateStr);
                                    _strtime(timeStr);
                                    fprintf(arquivo,"%s: %s %s\n","Cliente",cliente->nome,cliente->sobrenome);
                                    fprintf(arquivo,"%s: %s","Compra efetuada em",dateStr);
                                    fprintf(arquivo," %s: %s\n","as",timeStr);
                                    fprintf(arquivo,"%s: %s\n","Produto",nome);
                                    fprintf(arquivo,"%s: %.2f%\n","Desconto%",desc);
                                    fprintf(arquivo,"%s: %.2f\n","Valor",result);
                                    fprintf(arquivo,"%s: %d\n","Unidades compradas",qtd);
                                    fprintf(arquivo,"%s: %f\n\n","Troco",temp);

                                    printf("compra efetivada!\n");
                                }else{
                                    if(aux == 2){
                                        break;
                                    }
                                }

                            }else{
                                if(choice == 2){
                                    printf("%s: \n","Informe a quantia informada pelo cliente");
                                    scanf("%d",&aux);
                                    if(aux<result){
                                        printf("Valor do produto e superior!\n");
                                        break;
                                    }
                                    printf("Desconto de quantos %% no valor atual?\n");
                                    scanf("%f",&desc);
                                    descfinal = (result * desc)/100;
                                    result -= descfinal;
                                    printf("%s: %.2f\n","Valor atualizado",result);
                                    printf("%s: \n","Gostaria de continuar a transacao?");
                                    printf("%s \n","1 - SIM 2 - NAO");
                                    scanf("%d",&aux2);
                                    if(aux2 == 1){
                                        float temp = aux - result;
                                        printf("%s: %.2f","Troco",temp);
                                         char dateStr[9],timeStr[9];
                                    _strdate(dateStr);
                                    _strtime(timeStr);
                                    fprintf(arquivo,"%s: %s %s\n","Cliente",cliente->nome,cliente->sobrenome);
                                    fprintf(arquivo,"%s: %s","Compra efetuada em",dateStr);
                                    fprintf(arquivo," %s: %s\n","as",timeStr);

                                    //fprintf(arquivo,"%s: %.2f\n","Dinheiro do cliente: ",temp + result);
                                    fprintf(arquivo,"%s: %s\n","Produto",nome);

                                    fprintf(arquivo,"%s: %.2f%\n","Desconto%",desc);
                                    fprintf(arquivo,"%s: %.2f\n","Valor",result);
                                    fprintf(arquivo,"%s: %d\n","Unidades compradas",qtd);
                                    fprintf(arquivo,"%s: %.2f\n\n","Troco",temp);
                                    }else{
                                        if(aux == 2){
                                            break;
                                        }
                                    }

                                }
                            }
                            p->qtd = p->qtd - qtd;
                            printf("Produto vendido!\n");
                           }else{
                                if(p->qtd < qtd){
                                    printf("Quantidade informada superior ao que temos no estoque!...\n");
                                }else{
                                    if(p->qtd == qtd){
                                        float result = qtd * p->preco;
                                        printf("%s: %.2f\n","A quantia total sai por",result);
                                        printf("%s \n","Pagar em 1 - cartao ou 2 - dinheiro");
                                        scanf("%d",&choice);
                                        if(choice == 1){
                                            printf("Digine a senha do cartao:\n");
                                            scanf("%d",&senha);
                                            printf("Digite os ultimos 3 numeros do seu cartao:\n");
                                            scanf("%d",&dig);
                                            printf("Desconto de quantos %% no valor altual?\n");
                                            scanf("%f",&desc);
                                            descfinal = (result*desc)/100;
                                            result -= descfinal;
                                            printf("%s: %.2f\n","Valor atualizado",result);
                                            printf("%s: \n","Gostaria de continuar a transacao?");
                                            printf("%s \n","1 - SIM 2 - NAO");
                                            scanf("%d",&aux);
                                            if(aux == 1){
                                                float temp = 0;
                                                 char dateStr[9],timeStr[9];
                                                _strdate(dateStr);
                                                _strtime(timeStr);
                                                fprintf(arquivo,"%s: %s %s\n","Cliente",cliente->nome,cliente->sobrenome);
                                                fprintf(arquivo,"%s: %s","Compra efetuada em",dateStr);
                                                fprintf(arquivo," %s: %s\n","as",timeStr);
                                                fprintf(arquivo,"%s: %s\n","Produto",nome);
                                                fprintf(arquivo,"%s: %.2f%\n","Desconto%",desc);
                                                fprintf(arquivo,"%s: %.2f\n","Valor",result);
                                                fprintf(arquivo,"%s: %d\n","Unidades compradas",qtd);
                                                fprintf(arquivo,"%s: %s\n\n","Troco",temp);
                                                printf("compra efetivada!\n");
                                            }else{
                                                if(aux == 2){
                                                break;
                                                }
                                            }

                                        }else{
                                            if(choice == 2){
                                                printf("%s: \n","Informe a quantia informada pelo cliente");
                                                scanf("%d",&aux);
                                                if(aux<result){
                                                    printf("Valor do produto e superior!\n");
                                                    break;
                                                }
                                                printf("Desconto de quantos % no valor atual?\n");
                                                scanf("%f",&desc);
                                                descfinal = (result * desc)/100;
                                                result -= descfinal;
                                                printf("%s: %.2f\n","Valor atualizado",result);
                                                printf("%s: \n","Gostaria de continuar a transacao?");
                                                printf("%s \n","1 - SIM 2 - NAO");
                                                scanf("%d",&aux2);
                                                if(aux2 == 1){
                                                    float temp = aux - result;
                                                    printf("%s: %.2f","Troco",temp);
                                                    char dateStr[9],timeStr[9];
                                                    _strdate(dateStr);
                                                    _strtime(timeStr);
                                                    fprintf(arquivo,"%s: %s %s\n","Cliente",cliente->nome,cliente->sobrenome);
                                                    fprintf(arquivo,"%s: %s","Compra efetuada em",dateStr);
                                                    fprintf(arquivo," %s: %s\n","as",timeStr);
                                                    fprintf(arquivo,"%s: %s\n","Produto",nome);

                                                    //fprintf(arquivo,"%s: %.2f\n","Dinheiro do cliente: ",temp + result);

                                                    fprintf(arquivo,"%s: %.2f%\n","Desconto%",desc);
                                                    fprintf(arquivo,"%s: %.2f\n","Valor",result);
                                                    fprintf(arquivo,"%s: %d\n","Unidades compradas",qtd);
                                                    fprintf(arquivo,"%s: %.2f\n\n","Troco",temp);
                                                }else{
                                                    if(aux == 2){
                                                    break;
                                                    }
                                                }

                                            }
                                        }
                                        p->qtd = 0;
                                        printf("Produto vendido!\n");
                                    }
                                }
                           }
                        }
                        data5 = sllGetNext(l2);

                    }
                }
                void *data6;
                FILE *g;
                g = fopen("Produtos.txt","w");
    			data6 = sllFirst(l2);
    			if(data == NULL){
                    printf("Nao ha produtos!\n");
    			}else{
                    while(data6!=NULL){
                        imprimirDataProdutoArquivo(data6,g);
                        data6 = sllGetNext(l2);
                    }
    			}
    			fclose(arquivo);

            break;

    		case '7':
    		    system("cls");
    		    listarListaRelatorio(l3);

    		break;

    		case '8':
    			system("cls");
    			listarListaProduto(l2);
    		break;

    		case '9':
    			system("cls");
    			listarListaCliente(l1);
    		break;

    		case '0':
    			exit(0);
    		default:
    			if(opc!='9'){
    				printf("\n%s\n","Informe uma opcao valida!");
    			}
    		break;
    	}
	}
}


int compNomeProduto(void *a, void *b)
{
	char *pa;
	Produto *pb;

	pa = (char *)a;
	pb = (Produto *)b;
	if(strcmp(pa,pb->nome) == 0){
		return TRUE;
	}else{
		return FALSE;
	}
}

int compIdCliente(void *a, void *b)
{
	int *pa;
	Cliente *pb;
	pa = (int*)a;
	pb = (Cliente*)b;
	if(pb->id == pa){
		return TRUE;
	}else{
		return FALSE;
	}
}

int compIdProduto(void *a, void *b)
{
	int *pa;
	Produto *pb;
	pa = (int*)a;
	pb = (Produto *)b;
	if(pb->id == pa){
		return TRUE;
	}else{
		return FALSE;
	}
}

int compNomeCliente(void *a, void *b)
{
	char *pa;
	Cliente *pb;
	pa = (char *)a;
	pb = (Cliente *)b;
	if(strcmp(pa,pb->nome) == 0){
		return TRUE;
	}else{
		return FALSE	;
	}
}

void imprimirDataCliente(void *a)
{
	Cliente *pb;
	pb = (Cliente *)a;
	printf("\n%s %s %s\n","Nome: ",pb->nome,pb->sobrenome);
	printf("%s %d\n","ID: ",pb->id);
	printf("\n ----------------------------\n");

}
void imprimirDataClienteArquivo(void *a,FILE *f)
{
	Cliente *pb;
	pb = (Cliente *)a;
	fprintf(f,"%s %s %s %s %d\n","Nome:",pb->nome,pb->sobrenome,"ID:",pb->id);

}

void imprimirDataProdutoArquivo(void *a, FILE *f)
{
    Produto *p;
    p = (Produto *)a;
    fprintf(f,"%s: %s\n","NOME",p->nome);
    fprintf(f,"%s: %s\n","TIPO",p->tipo);
    fprintf(f,"%s: %.2f\n","PRECO",p->preco);
    fprintf(f,"%s: %d\n","QTD",p->qtd);
    fprintf(f,"%s: %d\n\n","ID",p->id);
}

void imprimirDataRelatorio(void *a)
{
    Relatorio *pb;
    pb = (Relatorio *)a;
    printf("\n%s %s","Nome do comprador: ",pb->nome);
    printf("\n%s %s","Compra efetuada em: ",pb->data);
    //printf("\n%s %s","Por: ",pb->meio);
    printf("\n%s %s", "Produto: ",pb->nomepr);
    printf("\n%s %.2f%%","Desconto de: ",pb->porcec);
    printf("\n%s %.2f","Valor final de: ",pb->vfinal);
    printf("\n%s %d","Unidade compradas: ",pb->unidades);
    printf("\n%s %.2f","Troco de:",pb->troco);
    printf(" \n-------------------------------------");
}

void imprimirDataProduto(void *a)
{
	Produto *pb;
	pb = (Produto *)a;
	printf("\n%s %s\n","Nome: ",pb->nome);
	printf("%s %s\n","Tipo: ",pb->tipo);
	printf("%s %.2f\n","Preco: ",pb->preco);
	printf("%s %d\n","Quantidade: ",pb->qtd);
	printf("%s %d\n","ID: ",pb->id);
	printf("\n ----------------------------\n");
}


