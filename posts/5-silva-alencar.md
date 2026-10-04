---
title: "WSL/Ubuntu"
lang: pt-BR
description: "Configurar ambiente de desenvolvimento C no Windows usando WSL (Ubuntu)"
author: ["João Victor Ferreira da Silva", "Francisco Vinícius de Brito Alencar"]
date: "2025-11-04" 
categories:
  - Ferramentas
---

## Subsistema Windows para Linux

O **WSL (Windows Subsystem for Linux)** é uma camada de compatibilidade criada pela _Microsoft_ que permite executar binários _Linux_ (como programas e ferramentas de linha de comando) diretamente no Windows. O WSL 2, versão mais recente, utiliza um kernel Linux real, oferecendo desempenho e compatibilidade quase nativos.

Nosso objetivo é executar o ambiente **Ubuntu** dentro do Windows, instalar as tecnologias necessárias para programar em C e configurar o VS Code para usar todo esse sistema. Com o VS Code rodando no Windows, poderemos se comunicar diretamente com os arquivos e ferramentas dentro do Ubuntu.

> Neste tutorial, assumimos que você já instalou o VS Code em sua máquina.

## Instalação e Configuração

Vamos configurar o ambiente do zero.

### Instalação do Ubuntu/WSL

::: {.callout-important}
Certifique-se que a virtualização por hardware esteja ativada.
:::   

1.  Abra o **PowerShell** ocomo **Administrador**.
2.  Digite o seguinte comando:

    ```{.bash code-line-numbers="false"}
    wsl --install
    ```

3.  Este comando fará tudo automaticamente: habilitará os recursos necessários do Windows, baixará o kernel Linux mais recente e instalará a distribuição **Ubuntu** por padrão.

4. **Uma distribuição Linux instalada** (ex: Ubuntu).  
   Você pode instalar pela Microsoft Store ou via terminal.

5.  Após a conclusão, **reinicie o seu computador**.

6.  Ao reiniciar, o Ubuntu será iniciado pela primeira vez para finalizar a configuração. Você precisará criar um **nome de usuário** e uma **senha** para o seu ambiente Linux. (Nota: Esta senha não tem relação com sua senha do Windows).

::: {.callout-important}
Caso você já tenha o WSL instalado execute o comando abaixo para instalar o Ubuntu.
```{.bash code-line-numbers="false"}
wsl --install -d Ubuntu
```
:::  

Para maiores informações acesse: <https://learn.microsoft.com/pt-br/windows/wsl/install>

### Instalação do Compilador C

Agora que temos o Ubuntu, precisamos instalar as ferramentas de desenvolvimento C.

1.  Abra o terminal do Ubuntu (pelo Menu Iniciar, procure por "Ubuntu").
2.  Primeiro, vamos atualizar os repositórios de pacotes:

    ```{.bash code-line-numbers="false"}
    sudo apt update && sudo apt upgrade
    ```
    > O comando **sudo** é usado para executar comandos com privilégios de administrador. Você precisará digitar a senha do Linux que acabou de criar.

3.  Agora, instale o `build-essential`. Este pacote inclui o `gcc`, o `make` e outras ferramentas essenciais para compilação.

    ```{.bash code-line-numbers="false"}
    sudo apt install build-essential
    ```
4.  Para verificar se o GCC foi instalado corretamente, execute:

    ```{.bash code-line-numbers="false"}
    gcc --version
    ```
    
    *Você deverá ver uma mensagem com a versão do GCC.*

### Configuração do VS Code

1.  Abra o VS Code.
2.  Vá até a aba de **Extensões** (ícone de blocos no menu lateral ou `Ctrl+Shift+X`).
3.  Procure e instale a extensão chamada **WSL** (publicada pela _Microsoft_).

### Teste

1.  **Feche** qualquer instância do VS Code que esteja aberta.
2.  Abra o seu **terminal do Ubuntu**.
3.  Vamos criar um diretório para nossos projetos C *dentro* do Linux:

    ```{.bash code-line-numbers="false"}
    mkdir ~/projetos_c  
    cd ~/projetos_c
    ```
  
  O comando `mkdir` cria um diretório chamado 'projetos_c' na sua pasta 'home'. Já com o comando `cd`, entramos no diretório recém-criado.
  

4.  Agora, dentro deste diretório no terminal do Ubuntu, digite o comando mágico:

    ```{.bash code-line-numbers="false"}
    code .
    ```
Dessa maneira o Windows abrirá o VS Code e se conectará ao seu ambiente Ubuntu. Você verá uma indicação "WSL: Ubuntu" no canto inferior esquerdo do editor. Dessa forma, o VS Code estará "enxergando" os arquivos de dentro do diretório `~/projetos_c` do Ubuntu.

5.  **Criando o "Hello, World!"**
    No explorador de arquivos do VS Code (menu lateral), crie um novo arquivo chamado `hello.c`.
    Digite o seguinte código:

```c   
#include <stdio.h> 
    
int main() {
    printf("Hello, WSL!\n");     
    return 0; 
}
```

7.  **Compilando e Executando**

Abra o terminal integrado do VS Code (`Ctrl+'` ou `Terminal > Novo Terminal`).
    
> Este *não* é um terminal do Windows. É um terminal `bash` rodando diretamente no seu Ubuntu!
  
Para compilar, digite:

```{.bash code-line-numbers="false"}
gcc hello.c -o hello
```
Para executar o programa, digite:

```{.bash code-line-numbers="false"}
./hello
```
Você verá a mensagem `Hello, WSL!` impressa no seu terminal.


---

Nesta tutorial, você aprendeu

✅ Instalar e configurar o WSL e Ubuntu

✅ Instalar ferrmanentas de desemvolvimento em C no Linux

✅ Executar seu primeiro program em C no Linux

--- 

::: callout-note
## Aviso da Redação
Este artigo foi revisado e editado pela equipe do blog em **12 de novembro de 2025**. 
:::