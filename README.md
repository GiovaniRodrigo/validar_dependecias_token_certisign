# Validador de Dependências para Certificado Digital A3

Este repositório contém scripts para **Windows** e **Linux** que verificam e validam as dependências necessárias para o funcionamento de certificados digitais A3, especialmente para tokens Certisign.

---

## Descrição

O objetivo deste projeto é fornecer uma ferramenta simples que automatize a checagem de bibliotecas, drivers e configurações essenciais para o uso de certificados digitais A3 em diferentes ambientes operacionais.

### Scripts Disponíveis

- **`valida_dependencias.exe`**: Executável para Windows
- **`valida_dependencias.sh`**: Script para Linux

Ambos realizam verificações como:

- Presença dos drivers necessários do token Certisign
- Instalação das bibliotecas requeridas (ex: OpenSC, PCSC, etc.)
- Verificação de dispositivos conectados
- Informações sobre possíveis erros ou ausência de dependências

---

## Como Usar

### Windows

1. Baixe o arquivo `valida_dependencias.exe`.
2. Execute o programa como **administrador**:
   ```sh
   valida_dependencias.exe
   ```
3. Siga as instruções exibidas na tela.

### Linux

1. Baixe o arquivo `valida_dependencias.sh`.
2. Dê permissão de execução:
   ```sh
   chmod +x valida_dependencias.sh
   ```
3. Execute o script:
   ```sh
   ./valida_dependencias.sh
   ```
4. Siga as instruções exibidas no terminal.

---

## Requisitos

- Permissões de administrador/root para instalar/verificar drivers
- Token Certisign conectado ao computador
- Internet (caso seja necessário baixar dependências)

---

## Observações

- O programa **apenas verifica e informa** as dependências, não instala automaticamente os drivers.
- Para instalação dos drivers Certisign, consulte a página oficial: [Certisign Drivers](https://www.certisign.com.br/)

---

## Licença

Este projeto está sob a licença MIT.

---

Se precisar de alguma personalização adicional ou tradução para outro idioma, me avise!
