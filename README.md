É uma ferramenta simples para extrair logins de URLs em um arquivo de texto. O projeto categoriza as URLs em dois tipos: `android` e `normais`, e organiza os logins a partir das URLs normais, salvando-os em arquivos separados por letra inicial.

## Funcionalidades

- Lê URLs de um arquivo de texto.
- Separa URLs que começam com `android://` e URLs normais.
- Extrai logins das URLs normais e os organiza em um mapa baseado na letra inicial.
- Salva os logins em arquivos de texto separados por letra inicial em um diretório de saída.

## Pré-requisitos

- Um compilador C++ (C++11 ou superior).
- Biblioteca `<filesystem>` disponível (C++17).

## Instalação

1. Clone o repositório:

   ```bash
   git clone https://github.com/gsmatheus/login-categorizer.git
   cd login-categorizer
   ```

2. Compile o projeto:

   ```bash
   g++ -std=c++17 main.cpp -o login-categorizer
   ```

## Uso

1. Coloque seu arquivo de log (ex: `logs.txt`) no mesmo diretório do executável.
2. Execute o programa:

   ```bash
   ./login-categorizer
   ```

3. Os logins extraídos serão salvos no diretório `output`, organizados por letra inicial.
