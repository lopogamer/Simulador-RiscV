# Simulador RISC-V

Este projeto implementa um simulador do conjunto de instruções RISC-V em C++. Ele suporta um subconjunto do conjunto de instruções base RV32I e fornece funcionalidade para carregar e executar programas binários RISC-V.

## Características

- Suporta as principais instruções RV32I, incluindo:
  - Operações aritméticas (ADD, ADDI, SUB)
  - Operações lógicas (AND, OR, XOR)
  - Operações de memória (LW, SW, LB, SB)
  - Instruções de controle de fluxo (BEQ, BNE, JAL, JALR)
  - Instruções de imediato superior (LUI, AUIPC)
  - Chamadas de sistema (ECALL)
- Arquitetura com mapeamento de memória e segmentos separados para instruções e dados
- Banco de registradores com 32 registradores de uso geral
- Suporte para chamadas básicas de sistema através de ECALL

## Estrutura do Projeto

```
.
├── include/
│   ├── decode.h      # Cabeçalho do decodificador de instruções
│   ├── execute.h     # Cabeçalho do executor de instruções
│   └── global.h      # Definições globais e estruturas de dados
├── src/
│   ├── Main.cpp      # Ponto de entrada do programa principal
│   ├── decode.cpp    # Implementação do decodificador de instruções
│   ├── execute.cpp   # Implementação do executor de instruções
│   └── global.cpp    # Implementação das variáveis globais
├── teste/            # Diretório de arquivos de teste
└── Makefile         # Configuração de compilação
```

## Compilando o Projeto

O projeto utiliza Make para compilação. Para compilar o projeto:

```bash
make
```

Isso criará o executável chamado `trabalho` no diretório raiz.

## Executando o Simulador

Para executar o simulador:

```bash
make run
```

O simulador espera dois arquivos binários no diretório `teste`:
- `code.bin`: Contém as instruções do programa
- `data.bin`: Contém o segmento de dados inicial

## Layout de Memória

O simulador implementa um modelo simples de memória:
- Memória de Instruções: 0x00000000 - 0x00000FFC
- Memória de Dados: 0x00002000 - 0x00003FFF
- Ponteiro de Pilha (sp) inicializado em: 0x00003FFC
- Ponteiro Global (gp) inicializado em: 0x00001800

## Instruções Suportadas

O simulador suporta as seguintes instruções RISC-V:

### Instruções Tipo-R
- ADD, SUB
- AND, OR, XOR
- SLT, SLTU

### Instruções Tipo-I
- ADDI, ANDI, ORI
- SLLI, SRLI, SRAI
- LB, LBU, LW
- JALR

### Instruções Tipo-S
- SB, SW

### Instruções Tipo-B
- BEQ, BNE
- BLT, BGE
- BLTU, BGEU

### Instruções Tipo-U
- LUI, AUIPC

### Instruções Tipo-J
- JAL

### Instruções de Sistema
- ECALL (suporta saída, impressão de inteiros e impressão de strings)

## Testes

O projeto inclui uma suíte de testes no diretório `teste`. Os arquivos de teste verificam a implementação correta de cada instrução e fornecem exemplos de uso.

## Contribuindo

Sinta-se à vontade para contribuir com este projeto enviando issues ou pull requests.

## Licença

Este projeto está sob a licença MIT. Veja o arquivo LICENSE para mais detalhes.