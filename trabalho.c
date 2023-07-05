#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void limparTela () {
    system ("cls || clear");
}

void pausarTela () {
    printf ("Pressione ENTER para continuar...");
    //fflush(stdout);
    
    // int c;
    // while ((c = getchar()) != '\n' && c != EOF) {
    //     // Discard characters from the input buffer
    // }

    getchar();
    getchar();
}

// A função isInt retorna um valor diferente de zero (true) se a string for um inteiro.
int isInt (char *str) {
    int i = 0;
    int isInt = 1;

    // Enquanto o char não for o caractere nulo (\0), verifica se é um dígito.
    while (str[i] != '\0') {
        // A função isdigit retorna um valor diferente de zero (true) se o char for um dígito (0-9).
        if (!isdigit(str[i])) {
            isInt = 0;
            break; // Se o char não for um dígito, então não tem porque continuar o loop.
        }
        i++;
    }
    return isInt;
}

// A função validarCNPJ retorna um valor diferente de 0 (true) se o CNPJ for inválido.
int validarCNPJ (char *CNPJ) {
    int i = 0;

    // Um CNPJ válido tem 14 dígitos, então se a string não tiver 14 dígitos, não é um CNPJ válido.
    if (strlen(CNPJ) != 14) {
        // printf ("CNPJ inválido por tamanho\n");
        return 1;
    }

    // Um CNPJ válido é composto apenas por números, então se a string não for um inteiro, não é um CNPJ válido.
    if (!isInt(CNPJ)) {
        // printf ("CNPJ inválido por não ser inteiro\n");
        return 1;
    }

    // Verificar os dois últimos dígitos do CNPJ
    int digito1 = 0;
    int digito2 = 0;

    // Adicionar os 12 primeiros dígitos do CNPJ em um vetor de inteiros
    int vetorCNPJ[14];
    for (i = 0; i < 14; i++) {
        vetorCNPJ[i] = CNPJ[i] - '0';
        // printf ("vetorCNPJ[%d] = %d\n", i, vetorCNPJ[i]);
    }

    // O primeiro dígito é calculado com base nos 12 primeiros dígitos do CNPJ
    // O primeiro passo é:
    // Multiplicar cada dígito do CNPJ pelo peso, que vai de 5 a 2, depois de 9 a 2. Exemplo:
    // Para o CNPJ 12.345.678/0001-00, o cálculo é:
    // 1x5 + 2x4 + 3x3 + 4x2 + 5x9 + 6x8 + 7x7 + 8x6 + 0x5 + 0x4 + 0x3 + 1x2
    int peso = 5;
    for (i = 0; i < 12; i++) {
        // printf ("Digito 1 = %d + (%d * %d = %d) = %d\n", digito1, vetorCNPJ[i], peso, vetorCNPJ[i] * peso, digito1 + (vetorCNPJ[i] * peso));
        digito1 += vetorCNPJ[i] * peso;
        peso--;
        if (peso == 1) {
            peso = 9;
        }
    }
    //printf ("digito1 = %d\n", digito1);

    // O segundo passo é:
    // O resto da divisão do somatório por 11
    digito1 %= 11;

    // O terceiro, e último, passo para calcular o primeiro dígito é:
    // Se o resto da divisão for menor que 2, o primeiro dígito é 0, senão é 11 menos o resto da divisão
    if (digito1 < 2) {
        digito1 = 0;
    }
    else {
        digito1 = 11 - digito1;
    }

    // Se o primeiro dígito calculado for diferente do décimo terceiro dígito do CNPJ, então o CNPJ não é válido
    if (digito1 != vetorCNPJ[12]) {
        // printf ("CNPJ inválido por primeiro dígito, deu %d\n", digito1);
        return 1;
    }

    // O segundo dígito é calculado com base nos 13 primeiros dígitos do CNPJ
    // O primeiro passo é praticamente o mesmo do primeiro dígito, porém o peso vai de 6 a 2, depois de 9 a 2
    // Isso porque o segundo dígito é calculado com base nos 13 primeiros dígitos do CNPJ, incluindo o digito1

    peso = 6;
    for (i = 0; i < 13; i++) {
        digito2 += vetorCNPJ[i] * peso;
        peso--;
        if (peso == 1) {
            peso = 9;
        }
    }

    // O segundo e o terceiro passo são os mesmos do primeiro dígito
    digito2 %= 11;
    if (digito2 < 2) {
        digito2 = 0;
    }
    else {
        digito2 = 11 - digito2;
    }

    // Se o segundo dígito calculado for diferente do décimo quarto dígito do CNPJ, então o CNPJ não é válido
    if (digito2 != vetorCNPJ[13]) {
        // printf ("CNPJ inválido por segundo dígito, deu %d\n", digito2);
        return 1;
    }

    return 0;
}

// A função validarCPF retorna um valor diferente de 0 (true) se o CPF for inválido.
int validarCPF (char *CPF) {
    int i = 0;

    // Um CPF válido tem 11 dígitos, então se a string não tiver 11 dígitos, não é um CPF válido.
    if (strlen(CPF) != 11) {
        // printf ("CPF inválido por tamanho\n");
        return 1;
    }

    // Um CPF válido é composto apenas por números, então se a string não for um inteiro, não é um CPF válido.
    if (!isInt(CPF)) {
        // printf ("CPF inválido por não ser inteiro\n");
        return 1;
    }

    // Verificar os dois últimos dígitos do CPF
    int digito1 = 0;
    int digito2 = 0;

    // Adicionar os 9 primeiros dígitos do CPF em um vetor de inteiros
    int vetorCPF[11];
    for (i = 0; i < 11; i++) {
        vetorCPF[i] = CPF[i] - '0';
        // printf ("vetorCPF[%d] = %d\n", i, vetorCPF[i]);
    }

    // O primeiro dígito é calculado com base nos 9 primeiros dígitos do CPF
    // O primeiro passo é:
    // Multiplicar cada dígito do CPF pelo peso, que vai de 10 a 2. Exemplo:
    // Para o CPF 123.456.789-09, o cálculo é:
    // 1x10 + 2x9 + 3x8 + 4x7 + 5x6 + 6x5 + 7x4 + 8x3 + 9x2
    int peso = 10;
    for (i = 0; i < 9; i++) {
        // printf ("Digito 1 = %d + (%d * %d = %d) = %d\n", digito1, vetorCPF[i], peso, vetorCPF[i] * peso, digito1 + (vetorCPF[i] * peso));
        digito1 += vetorCPF[i] * peso;
        peso--;
    }
    //printf ("digito1 = %d\n", digito1);

    // O segundo passo é:
    // O resto da divisão do somatório por 11
    digito1 %= 11;

    // O terceiro, e último, passo para calcular o primeiro dígito é:
    // Se o resto da divisão for menor que 2, o primeiro dígito é 0, senão é 11 menos o resto da divisão
    if (digito1 < 2) {
        digito1 = 0;
    }
    else {
        digito1 = 11 - digito1;
    }

    // Se o primeiro dígito calculado for diferente do décimo dígito do CPF, então o CPF não é válido
    if (digito1 != vetorCPF[9]) {
        // printf ("CPF inválido por primeiro dígito, deu %d\n", digito1);
        return 1;
    }

    // O segundo dígito é calculado com base nos 10 primeiros dígitos do CPF
    // O primeiro passo é praticamente o mesmo do primeiro dígito, porém o peso vai de 11 a 2
    // Isso porque o segundo dígito é calculado com base nos 10 primeiros dígitos do CPF, incluindo o digito1

    peso = 11;
    for (i = 0; i < 10; i++) {
        digito2 += vetorCPF[i] * peso;
        peso--;
    }

    // O segundo e o terceiro passo são os mesmos do primeiro dígito
    digito2 %= 11;
    if (digito2 < 2) {
        digito2 = 0;
    }
    else {
        digito2 = 11 - digito2;
    }

    // Se o segundo dígito calculado for diferente do décimo primeiro dígito do CPF, então o CPF não é válido
    if (digito2 != vetorCPF[10]) {
        // printf ("CPF inválido por segundo dígito, deu %d\n", digito2);
        return 1;
    }

    return 0;
}

void printarRA (int RA) {
    if (RA == 20) printf ("Águas Claras");
    else if (RA == 33) printf ("Arniqueira");
    else if (RA == 4) printf ("Brazlândia");
    else if (RA == 19) printf ("Candangolândia");
    else if (RA == 9) printf ("Ceilândia");
    else if (RA == 11) printf ("Cruzeiro");
    else if (RA == 31) printf ("Fercal");
    else if (RA == 2) printf ("Gama");
    else if (RA == 10) printf ("Guará");
    else if (RA == 28) printf ("Itapoã");
    else if (RA == 27) printf ("Jardim Botânico");
    else if (RA == 18) printf ("Lago Norte");
    else if (RA == 16) printf ("Lago Sul");
    else if (RA == 8) printf ("Núcleo Bandeirante");
    else if (RA == 7) printf ("Paranoá");
    else if (RA == 24) printf ("Park Way");
    else if (RA == 6) printf ("Planaltina");
    else if (RA == 1) printf ("Plano Piloto");
    else if (RA == 15) printf ("Recanto das Emas");
    else if (RA == 17) printf ("Riacho Fundo");
    else if (RA == 21) printf ("Riacho Fundo II");
    else if (RA == 12) printf ("Samambaia");
    else if (RA == 13) printf ("Santa Maria");
    else if (RA == 14) printf ("São Sebastião");
    else if (RA == 25) printf ("Estrutural");
    else if (RA == 29) printf ("SIA");
    else if (RA == 5) printf ("Sobradinho");
    else if (RA == 26) printf ("Sobradinho II");
    else if (RA == 32) printf ("Sol Nascente/Pôr do Sol");
    else if (RA == 22) printf ("Sudoeste/Octogonal");
    else if (RA == 3) printf ("Taguatinga");
    else if (RA == 23) printf ("Varjão");
    else if (RA == 30) printf ("Vicente Pires");
}

void consultarMiniusina () {
    printf ("Consultar miniusina\n");
    printf ("\n");
    printf ("Digite o CNPJ da miniusina (apenas números): ");

    char auxCNPJ[15];
    scanf ("%s", auxCNPJ);

    fimValidarCNPJ:
    if (validarCNPJ(auxCNPJ) == 1) {
        printf ("----------------\n");
        printf ("CNPJ inválido\n");
        printf ("\n");
        printf ("Você deseja consultar outro CNPJ?\n");
        printf ("1 - Sim\n");
        printf ("2 - Não\n");
        printf ("\n");
        printf ("Digite a opção desejada: ");

        char auxOpcao[2];
        scanf ("%s", auxOpcao);

        limparTela();

        if (isInt(auxOpcao)) {
            int opcao = atoi(auxOpcao);
            switch (opcao) {
                case 1:
                    consultarMiniusina();
                    break;
                case 2:
                    printf ("Voltando ao menu principal.\n");
                    break;
                default:
                    printf ("Opção inválida\n");
                    goto fimValidarCNPJ;
                    break;
            }
        } else {
            printf ("Opção inválida\n");
            goto fimValidarCNPJ;
        }
    }
    else {
        // Transformar o CNPJ de "inteiro" para o formato de CNPJ
        // Exemplo: 12345678901234 para 12.345.678/9012-34
        char CNPJFormatado[19];
        int j = 0;
        for (int i = 0; i < 19; i++) {
            if (i == 2 || i == 6) {
                CNPJFormatado[i] = '.';
            }
            else if (i == 10) {
                CNPJFormatado[i] = '/';
            }
            else if (i == 15) {
                CNPJFormatado[i] = '-';
            }
            else {
                CNPJFormatado[i] = auxCNPJ[j];
                j++;
            }
        }
        // printf ("CNPJ: %s\n", CNPJFormatado);


        // Procurar os dados da miniusina no arquivo
        FILE *arquivo = fopen("miniusinas.csv", "r");

        if (arquivo == NULL) {
            printf ("Erro ao abrir o arquivo\n");
        }

        // Ler as linhas do arquivo
        char linha[100];
        int cnpjNaoEncontrado = 1;

        while (fgets(linha, 100, arquivo) != NULL) {
            // printf ("%s", linha);

            // Separar os dados da linha
            // A função strtok separa uma string em várias strings menores
            char *token = strtok(linha, ";");
            char *dados[5];
            int i = 0;
            while (token != NULL) {
                dados[i] = token;
                token = strtok(NULL, ";");
                i++;
            }

            // Verificar se o CNPJ da linha é igual ao CNPJ digitado
            // A função strcmp retorna 0 se as strings forem iguais
            if (strcmp(dados[0], CNPJFormatado) == 0) {
                printf ("CNPJ: %s\n", dados[0]);
                printf ("RA: %s\n", dados[1]);
                printf ("Capacidade de geração total: %s\n", dados[2]);
                printf ("RA (Região Administrativa): %s\n", dados[3]);
                printf ("Status: %s\n", dados[4]);
                printf ("\n");
                cnpjNaoEncontrado = 0;
                break;
            }
        }

        if (cnpjNaoEncontrado == 1) {
            printf ("Miniusina não existe.\n");
        }
        
        fclose(arquivo);

    }
}

void consultarConsumidor () {
    int isValid = 0;

    printf ("Consultar consumidor\n");
    printf ("\n");
    printf ("Digite o CPF/CNPJ do consumidor (apenas números): ");

    char auxID[15];
    scanf ("%s", auxID);

    char IDFormatado[18];

    // Verificar se o ID é um CPF ou um CNPJ
    // Se o ID tiver 11 dígitos, então é um CPF
    if (strlen(auxID) == 11) {
        if (validarCPF(auxID) == 1) {
            isValid = 1;
        }
        else {
            // Transformar o CPF de "inteiro" para o formato de CPF
            // Exemplo: 12345678901 para 123.456.789-01
            int j = 0;

            for (int i = 0; i < 14; i++) {
                if (i == 3 || i == 7) {
                    IDFormatado[i] = '.';
                }
                else if (i == 11) {
                    IDFormatado[i] = '-';
                }
                else {
                    IDFormatado[i] = auxID[j];
                    j++;
                }
            }
        }  
    }
    // Se o ID tiver 14 dígitos, então é um CNPJ
    else if (strlen(auxID) == 14) {
        if (validarCNPJ(auxID) == 1) {
            isValid = 1;
        }
        else {
            // Transformar o CNPJ de "inteiro" para o formato de CNPJ
            // Exemplo: 12345678901234 para 12.345.678/9012-34
            int j = 0;

            for (int i = 0; i < 18; i++) {
                if (i == 2 || i == 6) {
                    IDFormatado[i] = '.';
                }
                else if (i == 10) {
                    IDFormatado[i] = '/';
                }
                else if (i == 15) {
                    IDFormatado[i] = '-';
                }
                else {
                    IDFormatado[i] = auxID[j];
                    j++;
                }
            }
        }
    }
    // Se ID for nenhum dos dois, então é inválido
    else {
        isValid = 1;
    }

    fimValidarID:
    if (isValid == 1) {
        printf ("CPF/CNPJ inválido\n");
        printf ("\n");
        printf ("Deseja tentar novamente?\n");
        printf ("1 - Sim\n");
        printf ("2 - Não\n");
        printf ("\n");
        printf ("Digite a opção desejada: ");
        
        char auxOpcao[2];
        scanf ("%s", auxOpcao);

        limparTela();

        if (isInt(auxOpcao)) {
            int opcao = atoi(auxOpcao);
            switch (opcao) {
                case 1:
                    consultarConsumidor();
                    break;
                case 2:
                    printf ("Voltando ao menu principal.\n");
                    break;
                default:
                    printf ("Opção inválida\n");
                    goto fimValidarID;
                    break;
            }
        } 
        else {
            printf ("Opção inválida\n");
            goto fimValidarID;
        }
    }
    else {
        // Procurar os dados do consumidor no arquivo
        FILE *arquivo = fopen("consumidores.csv", "r");

        if (arquivo == NULL) {
            printf ("Erro ao abrir o arquivo\n");
        }

        // Ler as linhas do arquivo
        char linha[100];
        int idNaoEncontrado = 1;

        while (fgets(linha, 100, arquivo) != NULL) {
            // printf ("%s", linha);

            // Separar os dados da linha
            // A função strtok separa uma string em várias strings menores
            char *token = strtok(linha, ";");
            char *dados[3];
            int i = 0;
            while (token != NULL) {
                dados[i] = token;
                token = strtok(NULL, ";");
                i++;
            }

            // Verificar se o ID da linha é igual ao ID digitado
            // A função strcmp retorna 0 se as strings forem iguais
            if (strcmp(dados[0], IDFormatado) == 0) {
                printf ("CPF/CNPJ: %s\n", dados[0]);
                printf ("Nome: %s\n", dados[1]);
                printf ("RA (Região Administrativa): %s\n", dados[2]);
                printf ("\n");
                idNaoEncontrado = 0;
                break; // Parar de ler o arquivo
            }
        }

        if (idNaoEncontrado == 1) {
            printf ("Consumidor não existe.\n");
        }

        fclose(arquivo);
    }
}

void listarMiniusinas () {
    printf ("Listar miniusinas cadastradas\n");
    printf ("\n");

    // Procurar os dados da miniusina no arquivo
    FILE *arquivo = fopen("miniusinas.csv", "r");

    if (arquivo == NULL) {
        printf ("Erro ao abrir o arquivo\n");
    }

    // Ler as linhas do arquivo
    char linha[100];
    int count = 0;

    while (fgets(linha, 100, arquivo) != NULL) {
        // printf ("%s", linha);

        // Separar os dados da linha
        // A função strtok separa uma string em várias strings menores
        char *token = strtok(linha, ";");
        char *dados[5];
        int i = 0;
        while (token != NULL) {
            dados[i] = token;
            token = strtok(NULL, ";");
            i++;
        }

        // Printar todos os dados das miniusinas, irá ignorar a primeira linha
        if (count != 0) {
            printf ("Miniusina %d\n", count);
            printf ("CNPJ: %s\n", dados[0]);
            printf ("RA: %s\n", dados[1]);
            printf ("Capacidade de geração total: %s\n", dados[2]);
            printf ("RA (Região Administrativa): %s\n", dados[3]);
            printf ("Status: %s\n", dados[4]);
            printf ("\n\n");
        }

        count++;
    }

    fclose(arquivo);
}

void listarPorCapacidade () {
    printf ("Listar as miniusinas em operação por ordem decrescente de capacidade de geração de energia\n");
    printf ("\n");

    // Procurar os dados da miniusina no arquivo
    FILE *arquivo = fopen("miniusinas.csv", "r");

    if (arquivo == NULL) {
        printf ("Erro ao abrir o arquivo\n");
    }

    struct Miniusina {
        char cnpj_miniusina[19];
        char nome_miniusina[50];
        float capacidade_total; // em kWh
        int ra; // região administrativa do DF onde a miniusina está instalada
        char status_usina[15]; // em operação ou em implantação
    };

    struct Miniusina miniusinas[100];
    int i = 0;

    // Ler o cabeçalho do arquivo
    char cabecalho[100];
    fgets(cabecalho, 100, arquivo);

    // Ler os dados do arquivo e armazenar em um vetor de miniusinas
    while (!feof(arquivo)) {
        struct Miniusina miniusina;
        fscanf(arquivo, "%[^;];%[^;];%f;%d;%s\n", miniusina.cnpj_miniusina, miniusina.nome_miniusina, &miniusina.capacidade_total, &miniusina.ra, miniusina.status_usina);
        if (miniusina.capacidade_total != 0) {
            miniusinas[i] = miniusina;
        }
        i++;
    }

    // Ordenar as miniusinas por capacidade de geração, de forma decrescente;
    int j, k;
    struct Miniusina aux;

    for (j = 0; j < i; j++) {
        for (k = j + 1; k < i; k++) {
            if (miniusinas[j].capacidade_total < miniusinas[k].capacidade_total) {
                aux = miniusinas[j];
                miniusinas[j] = miniusinas[k];
                miniusinas[k] = aux;
            }
        }
    }

    // Printar as miniusinas ordenadas
    for (j = 0; j < i; j++) {
        if (strcmp(miniusinas[j].status_usina, "operacao") != 0) {
            continue;
        }
        printf ("Miniusina %d\n", j + 1);
        printf ("CNPJ: %s\n", miniusinas[j].cnpj_miniusina);
        printf ("Nome: %s\n", miniusinas[j].nome_miniusina);
        printf ("Capacidade de geração total: %.2f\n", miniusinas[j].capacidade_total);
        printf ("RA (Região Administrativa): %d\n", miniusinas[j].ra);
        // printf ("Status: %s\n", miniusinas[j].status_usina);
        printf ("\n\n");
    }


    fclose(arquivo);
}

void listarPorQuantidade () {
    printf ("Listar as Regiões Administrativas por ordem decrescente de quantidade de miniusinas\n");
    printf ("\n");

    // Procurar os dados da miniusina no arquivo
    FILE *arquivo = fopen("miniusinas.csv", "r");

    if (arquivo == NULL) {
        printf ("Erro ao abrir o arquivo\n");
    }

    struct Miniusina {
        char cnpj_miniusina[19];
        char nome_miniusina[50];
        float capacidade_total; // em kWh
        int ra; // região administrativa do DF onde a miniusina está instalada
        char status_usina[15]; // em operação ou em implantação
    };

    struct RA {
        int ra;
        int quantidade;
    };

    // Criar um vetor de RAs e inicializar a quantidade de miniusinas em cada RA
    struct RA ras[33];
    for (int i = 0; i < 33; i++) {
        ras[i].ra = i + 1;
        ras[i].quantidade = 0;
    }

    // Ler o cabeçalho do arquivo
    char cabecalho[100];
    fgets(cabecalho, 100, arquivo);

    // Ler os dados do arquivo e armazenar em um vetor de miniusinas
    while (!feof(arquivo)) {
        struct Miniusina miniusina;
        fscanf(arquivo, "%[^;];%[^;];%f;%d;%s\n", miniusina.cnpj_miniusina, miniusina.nome_miniusina, &miniusina.capacidade_total, &miniusina.ra, miniusina.status_usina);
        if (miniusina.capacidade_total != 0) {
            ras[miniusina.ra - 1].quantidade++;
        }
    }

    fclose(arquivo);

    // Ordenar as RAs por quantidade de miniusinas, de forma decrescente;
    int j, k;
    struct RA aux;

    for (j = 0; j < 33; j++) {
        for (k = j + 1; k < 33; k++) {
            if (ras[j].quantidade < ras[k].quantidade) {
                aux = ras[j];
                ras[j] = ras[k];
                ras[k] = aux;
            }
        }
    }

    // Printar as RAs ordenadas
    for (j = 0; j < 33; j++) {
        if (ras[j].quantidade == 0) {
            continue;
        }
        printf ("RA %d - ", ras[j].ra);
        printarRA(ras[j].ra);
        printf ("\n");
        printf ("Quantidade de miniusinas: %d\n", ras[j].quantidade);
        printf ("\n\n");
    }
}

void listarPorContratos () {
    printf ("Listar as Regiões Administrativas por ordem crescente de número de contratos\n");
    printf ("\n");

    struct Miniusina {
        char cnpj_miniusina[19];
        char nome_miniusina[50];
        float capacidade_total; // em kWh
        int ra; // região administrativa do DF onde a miniusina está instalada
        char status_usina[15]; // em operação ou em implantação
    };

    struct RA {
        int ra;
        int quantidade;
    };

    // Criar um vetor de RAs e inicializar a quantidade de miniusinas em cada RA
    struct RA ras[33];
    for (int i = 0; i < 33; i++) {
        ras[i].ra = i + 1;
        ras[i].quantidade = 0;
    }

    // Procurar os dados da miniusina do arquivo de contratos no arquivo de miniusinas
    FILE *arquivoContratos = fopen("contratos.csv", "r");
    if (arquivoContratos == NULL) {
        printf ("Erro ao abrir o arquivo\n");
    }

    // Ler o cabeçalho do arquivo
    char cabecalho[100];
    fgets(cabecalho, 100, arquivoContratos);

    char linha[100];
    // Ler os dados do arquivo de contratos e procurar CNPJ das miniusinas
    while (fgets(linha, 100, arquivoContratos) != NULL) {
        // printf ("%s", linha);

        // Separar os dados da linha
        // A função strtok separa uma string em várias strings menores
        char *token = strtok(linha, ";");
        char *dados[6];
        int i = 0;
        while (token != NULL) {
            dados[i] = token;
            token = strtok(NULL, ";");
            i++;
        }

        // O CNJPJ está na posição 2 do vetor de dados
        // Procurar o CNPJ da miniusina no arquivo de miniusinas
        FILE *arquivoMiniusinas = fopen("miniusinas.csv", "r");
        if (arquivoMiniusinas == NULL) {
            printf ("Erro ao abrir o arquivo\n");
        }

        while (!feof(arquivoMiniusinas)) {
            struct Miniusina miniusina;
            fscanf(arquivoMiniusinas, "%[^;];%[^;];%f;%d;%s\n", miniusina.cnpj_miniusina, miniusina.nome_miniusina, &miniusina.capacidade_total, &miniusina.ra, miniusina.status_usina);
            if (strcmp(miniusina.cnpj_miniusina, dados[2]) == 0) {
                ras[miniusina.ra - 1].quantidade++;
                break;
            }
        }

        fclose(arquivoMiniusinas);
    }

    fclose(arquivoContratos);

    // Ordenar as RAs por quantidade de miniusinas, de forma crescente;
    int j, k;
    struct RA aux;

    for (j = 0; j < 33; j++) {
        for (k = j + 1; k < 33; k++) {
            if (ras[j].quantidade > ras[k].quantidade) {
                aux = ras[j];
                ras[j] = ras[k];
                ras[k] = aux;
            }
        }
    }

    // Printar as RAs ordenadas
    for (j = 0; j < 33; j++) {
        if (ras[j].quantidade == 0) {
            continue;
        }
        printf ("RA %d - ", ras[j].ra);
        printarRA(ras[j].ra);
        printf ("\n");
        printf ("Quantidade de contratos: %d\n", ras[j].quantidade);
        printf ("\n\n");
    }
}

void listarPorCapacidadeGeracao () {
    printf ("Listar as Regiões Administrativas por ordem decrescente de capacidade de geração\n");
    printf ("\n");

    // Procurar os dados da miniusina no arquivo
    FILE *arquivo = fopen("miniusinas.csv", "r");

    if (arquivo == NULL) {
        printf ("Erro ao abrir o arquivo\n");
    }

    struct Miniusina {
        char cnpj_miniusina[19];
        char nome_miniusina[50];
        float capacidade_total; // em kWh
        int ra; // região administrativa do DF onde a miniusina está instalada
        char status_usina[15]; // em operação ou em implantação
    };

    struct RA {
        int ra;
        int quantidade;
    };

    // Criar um vetor de RAs e inicializar a quantidade de miniusinas em cada RA
    struct RA ras[33];
    for (int i = 0; i < 33; i++) {
        ras[i].ra = i + 1;
        ras[i].quantidade = 0;
    }

    // Ler o cabeçalho do arquivo
    char cabecalho[100];
    fgets(cabecalho, 100, arquivo);

    // Ler os dados do arquivo e armazenar em um vetor de miniusinas
    while (!feof(arquivo)) {
        struct Miniusina miniusina;
        fscanf(arquivo, "%[^;];%[^;];%f;%d;%s\n", miniusina.cnpj_miniusina, miniusina.nome_miniusina, &miniusina.capacidade_total, &miniusina.ra, miniusina.status_usina);
        if (miniusina.capacidade_total != 0) {
            ras[miniusina.ra - 1].quantidade += miniusina.capacidade_total;
        }
    }

    fclose(arquivo);

    // Ordenar as RAs por capacidade de geração de energia, de forma decrescente;
    int j, k;
    struct RA aux;

    for (j = 0; j < 33; j++) {
        for (k = j + 1; k < 33; k++) {
            if (ras[j].quantidade < ras[k].quantidade) {
                aux = ras[j];
                ras[j] = ras[k];
                ras[k] = aux;
            }
        }
    }

    // Printar as RAs ordenadas
    for (j = 0; j < 33; j++) {
        if (ras[j].quantidade == 0) {
            continue;
        }
        printf ("RA %d - ", ras[j].ra);
        printarRA(ras[j].ra);
        printf ("\n");
        printf ("Capacidade de geração de energia: %d kWh\n", ras[j].quantidade);
        printf ("\n\n");
    }
}

void listarPorPercentual () {
    printf ("Listar as Regiões Administrativas por ordem decrescente de percentual de energia disponível\n");
    printf ("\n");

    struct Miniusina {
        char cnpj_miniusina[19];
        char nome_miniusina[50];
        float capacidade_total; // em kWh
        int ra; // região administrativa do DF onde a miniusina está instalada
        char status_usina[15]; // em operação ou em implantação
    };

    struct RA {
        int ra;
        float quantidadeTotal;
        float quantidadeGasta;
        float quantidadeDisponivel;
    };

    struct contratos {
        int idContrato;
        char id_consumidor[19];
        char cnpj_miniusina[19];
        char data_inicio[11];
        char data_fim[11];
        float energia_contratada;
    };

    // Criar um vetor de RAs e inicializar ele
    struct RA ras[33];
    for (int i = 0; i < 33; i++) {
        ras[i].ra = i + 1;
        ras[i].quantidadeTotal = 0;
        ras[i].quantidadeGasta = 0;
        ras[i].quantidadeDisponivel = 0;
    }

    // Abrir os arquivos de miniusinas e de contratos
    FILE *arquivoMiniusinas = fopen("miniusinas.csv", "r");
    FILE *arquivoContratos = fopen("contratos.csv", "r");

    if (arquivoMiniusinas == NULL || arquivoContratos == NULL) {
        printf ("Erro ao abrir o arquivo\n");
    }

    // Ler capacidade total de cada miniusina e somar na quantidade total de cada RA
    struct Miniusina miniusina;
    while (!feof(arquivoMiniusinas)) {
        fscanf(arquivoMiniusinas, "%[^;];%[^;];%f;%d;%s\n", miniusina.cnpj_miniusina, miniusina.nome_miniusina, &miniusina.capacidade_total, &miniusina.ra, miniusina.status_usina);
        if (miniusina.capacidade_total != 0) {
            ras[miniusina.ra - 1].quantidadeTotal += miniusina.capacidade_total;
        }
    }

    // Ler a quantidade de energia gasta de cada miniusina e somar na quantidade gasta de cada RA
    struct contratos contrato;

    // Ler cabeçaçho do arquivo
    char linha[100];
    fgets(linha, 100, arquivoContratos);
    fgets(linha, 100, arquivoContratos);

    while (fgets(linha, 100, arquivoContratos) != NULL) {
        // Separar os dados da linha
        // A função strtok separa uma string em várias strings menores
        char *token = strtok(linha, ";");
        char *dadosContratos[6];
        int i = 0;
        while (token != NULL) {
            dadosContratos[i] = token;
            token = strtok(NULL, ";");
            i++;
        }
        
        // Procurar no arquivo de miniusinas a miniusina que tem o mesmo cnpj_miniusina do contrato
        char linhaMiniusina[100];
        // Mover o ponteiro do arquivo para o início
        fseek(arquivoMiniusinas, 0, SEEK_SET);
        while (fgets(linhaMiniusina, 100, arquivoMiniusinas) != NULL) {
            // Separar os dados da linha
            // A função strtok separa uma string em várias strings menores
            char *token2 = strtok(linhaMiniusina, ";");
            char *dadosMiniusinas[5];
            int ii = 0;
            while (token2 != NULL) {
                dadosMiniusinas[ii] = token2;
                token2 = strtok(NULL, ";");
                ii++;
            }
            if (strcmp(dadosMiniusinas[0], dadosContratos[2]) == 0) {
                int ra = atoi(dadosMiniusinas[3]);
                if (i == 6) {
                    ras[ra-1].quantidadeGasta += atof(dadosContratos[5]);
                }
                else {
                    ras[ra-1].quantidadeGasta += atof(dadosContratos[4]);
                }
                break;
            }
        }
    }

    // Fechar os arquivos
    fclose(arquivoMiniusinas);
    fclose(arquivoContratos);

    // Calcular o percentual de energia disponível de cada RA
    for (int i = 0; i < 33; i++) {
        if (ras[i].quantidadeTotal == 0) {
            continue;
        }
        ras[i].quantidadeDisponivel = ((ras[i].quantidadeTotal - ras[i].quantidadeGasta)/ras[i].quantidadeTotal)*100;
    }
    
    // Orderar as RAs por percentual de energia disponível, de forma decrescente;
    int j, k;
    struct RA aux;
    for (j = 0; j < 33; j++) {
        for (k = j + 1; k < 33; k++) {
            if (ras[j].quantidadeDisponivel < ras[k].quantidadeDisponivel) {
                aux = ras[j];
                ras[j] = ras[k];
                ras[k] = aux;
            }
        }
    }

    // Printar as RAs ordenadas
    for (j = 0; j < 33; j++) {
        if (ras[j].quantidadeTotal == 0) {
            break;
        }
        printf ("RA %d - ", ras[j].ra);
        printarRA(ras[j].ra);
        printf ("\n");
        printf ("Capacidade de geração de energia: %.1f kWh\n", ras[j].quantidadeTotal);
        printf ("Quantidade de energia gasta: %.1f kWh\n", ras[j].quantidadeGasta);
        printf ("Percentual de energia disponível: %.2f%%\n", ras[j].quantidadeDisponivel);
        printf ("\n\n");
    }
}
 
int main () {
    int opcao = 0;

    while (opcao != 9) {
        limparTela();

        // Menu do programa
        printf ("Bem-vindo ao Sistema de Informações sobre Geração e Distribuição Fotovoltaica (SINGDF)\n");
        printf ("\n");
        printf ("Para acessar usar o sistema, escolha uma das opções abaixo:\n");
        printf ("\n");
        printf ("1 - Consultar miniusina cadastrada\n");
        printf ("2 - Consultar consumidor cadastrado\n");
        printf ("3 - Listar miniusinas cadastradas\n");
        printf ("4 - Listar as miniusinas em operação por ordem decrescente de capacidade de geração de energia\n");
        printf ("5 - Listar as RAs por ordem decrescente de quantidade de miniusinas\n");
        printf ("6 - Listar as RAs por ordem crescente de número de contratos\n");
        printf ("7 - Listar as RAs por ordem decrescente de capacidade de geração\n");
        printf ("8 - Listar as RAs por ordem decrescente de percentual de energia disponível\n");
        printf ("9 - Sair do programa\n");
        printf ("\n");
        printf ("Digite a opção desejada: ");

        // Foi escolhido o tipo char para a leitura da opção, pois se o usuário digitar uma string, o programa não quebra.
        char auxOpcao[2];
        scanf ("%s", auxOpcao);

        limparTela();
        
        // A função isInt retorna um valor diferente de zero (true) se a string for um inteiro.
        if (isInt(auxOpcao)) { 
            limparTela();
            // A função atoi converte uma string para um inteiro.
            opcao = atoi(auxOpcao);
            switch (opcao) {
                case 1:
                    consultarMiniusina();
                    break;
                case 2:
                    consultarConsumidor();
                    break;
                case 3:
                    listarMiniusinas();
                    break;
                case 4:
                    listarPorCapacidade();
                    break;
                case 5:
                    listarPorQuantidade();
                    break;
                case 6:
                    listarPorContratos();
                    break;
                case 7:
                    listarPorCapacidadeGeracao();
                    break;
                case 8:
                    listarPorPercentual();
                    break;
                case 9:
                    printf ("Saindo do programa...\n");
                    printf ("Obrigado por usar o SINGDF!\n");
                    break;
                // Caso o número digitado seja 10, 22, etc (não seja uma opção válida).
                default:
                    printf ("Opção inválida, não é um número válido\n");
                    break;
            }
        // Caso o usuário digite uma string que não seja um número inteiro.
        } else {
            printf ("Opção inválida\n");
        }

        pausarTela();
    }
    // Fim do while (do menu/programa)
    return 0;
}