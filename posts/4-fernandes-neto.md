---
title: "Tratamento de Erros"
lang: pt-BR
toc-title: Conteúdo
description: Tratamento de erros usando `errno`
author:
  - Lyrian Fernandes 
  - Manoel Nascimento
date: 2025-11-04
categories:
  - Modularização e I/O
  - Fundamentos C
---

 

## Tratamento de Erros

O **tratamento de erros** em C é um mecanismo fundamental para garantir que o programa possa responder adequadamente a situações inesperadas, como falhas de leitura de arquivos, problemas de alocação de memória ou erros de comunicação. Ao contrário de linguagens modernas que possuem estruturas específicas de exceção, como _try/catch_, a linguagem C utiliza um conjunto de ferramentas baseadas em códigos de erro. 

As principais entre elas são a variável global `errno`, declarada em `errno.h`, e as funções auxiliares `perror()` e `strerror()`, declaradas em `stdio.h` e `string.h`, respectivamente.


## Tratamento Manual

O cabeçalho `errno.h` é responsável por definir a variável global `errno`, usada pelas funções da biblioteca padrão e pelas chamadas de sistema para indicar o tipo de erro que ocorreu. Em `errno.h` também exist um conjunto de constantes simbólicas que representam os códigos de erro retornados por chamadas de sistema e funções de biblioteca.

Exemplo de macros definidos em `errno.h`:

| Macro    | Significado                         | Valor  |
| -------- | ----------------------------------- | ------ |
| `EPERM`  | Operação não permitida              | 1      |
| `ENOENT` | Arquivo ou diretório não encontrado | 2      |
| `ESRCH`  | Processo inexistente                | 3      |
| `EINTR`  | Chamada de sistema interrompida     | 4      |
| `EIO`    | Erro de entrada/saída               | 5      |
| `ENOMEM` | Memória insuficiente                | 12     |
| `EACCES` | Permissão negada                    | 13     |
| `EINVAL` | Argumento inválido                  | 22     |
| `EEXIST` | Arquivo já existe                   | 17     |


Quando uma função falha, por exemplo, ao tentar abrir um arquivo que não existe, ela normalmente retorna um valor especial (como `NULL`, `-1` ou `EOF`) e define errno com um código numérico que representa o erro.

```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    // força uma tentativa absurda de alocação
    size_t tamanho = (size_t)-1; // número enorme
    void *p = malloc(tamanho);

    if (p == NULL) 
       fprintf(stderr, "[errno] Código: %d (ENOMEM)\n", errno);
    else 
        printf("Alocação bem-sucedida!\n");
    
    free(p);
     
    return 0;
}
```

Saída

```{.console code-line-numbers="false" }
[errno] Código: 12 (ENOMEM)
```

Tratar erros assim não é muito vantajoso, pois temos de consultar uma tabela enorme de códigos de erros para tratá-los. Precisamos de algo mais sistemático que `perror()` trará para nós. 


## Tratamento Automático

A função `perror()`, declarada em `stdio.h`, é usada para exibir uma mensagem descritiva do último erro que ocorreu no programa. Ela imprime o texto correspondente a `errno`.

Seu protótipo é:

```{.c code-line-numbers="false" }
void perror (const char *mensagem)
```

Ela imprime no terminal a mensagem passada como argumento, seguida de uma explicação gerada pelo sistema, de acordo com o valor atual de errno.

``` c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void) {
    // força uma tentativa absurda de alocação
    size_t tamanho = (size_t)-1; // número enorme
    void *p = malloc(tamanho);

    if (p == NULL) 
        perror("[perror] Falha ao alocar memória");
    else 
        printf("Alocação bem-sucedida!\n");
    
    free(p);

    return 0;
}
```

Saída

```{.console code-line-numbers="false" }
[perror] Falha ao alocar memória: Cannot allocate memory
```

A função `perror()` usa o valor de `errno` para traduzir o erro em uma mensagem compreensível para o usuário.

Já a função `strerror()` converte o código numérico contido em errno para uma string descritiva. Portanto, ela retorna um ponteiro para string com texto do erro. Isso permite personalizar mensagens de erro dentro do código, o que pode ser útil em programas maiores.

``` c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(void) {
    // força uma tentativa absurda de alocação
    size_t tamanho = (size_t)-1; // número enorme
    void *p = malloc(tamanho);

    if (p == NULL) 
        fprintf(stderr, "[strerror] %s: %s (errno = %d)\n",
         "falha ao alocar memória", strerror(errno), errno);
    else 
        printf("Alocação bem-sucedida!\n");
    
    free(p);

    return 0;
}
```

Saída:

```{.console code-line-numbers="false" }
[strerror] falha ao alocar memória: Cannot allocate memory (errno = 12)
```


O exemplo a seguir mostra as três ferramentas trabalhando juntas:

```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *f = fopen("arquivo_inexistente.txt", "r");

    if (f == NULL) {
        // Mostra código numérico
        fprintf(stderr, "Código do erro: %d\n", errno); 
        // Mostra mensagem automática
        perror("Erro ao abrir o arquivo"); 
        // Mostra texto do erro
        fprintf(stderr, "Descrição detalhada: %s\n", strerror(errno)); 

        return 1;
    }

    fclose(f);
    return 0;
} 
```

Saída típica:

```{.console code-line-numbers="false" }
Código do erro: 2
Erro ao abrir o arquivo: No such file or directory
Descrição detalhada: No such file or directory
```

Esse tipo de saída é extremamente útil em aplicações reais, pois ajuda a identificar rapidamente o problema e a sua causa.

> Além disso, `errno` é definido por _thread_, ou seja, cada fluxo de execução mantém seu próprio valor de erro, algo importante em aplicações que utilizam paralelismo.

Lembre-se que o sistema apenas informa o erro, mas a decisão do que fazer com ele é responsabilidade do programador.
Isso garante controle total, mas também exige atenção, pois um erro não tratado pode comprometer todo o funcionamento do programa.

---

Nesta unidade, você aprendeu

✅ a utilizar a variável global `errno` para identificar erros do sistema  
✅ a usar `perror()` para imprimir mensagens de erro padronizadas  
✅ a usar `strerror()` para personalizar mensagens de erro  

---

::: callout-note
## Aviso da Redação
Este artigo foi revisado e editado pela equipe do blog em **07 de novembro de 2025**. 
:::

