# TP1-Trabalho2 – Arquitetura e Design Patterns

Este projeto é um aplicativo de terminal desenvolvido como parte da disciplina **Técnicas de Programação 1 (TP1)** da **Universidade de Brasília (UnB)**. Seu objetivo principal é aplicar princípios de **arquitetura de software** e **design patterns**, especialmente o padrão **Command**, além de seguir os princípios do **SOLID**.

## 📐 Arquitetura

O projeto é estruturado em camadas modulares:

- **Presentation:** Interface de terminal (em desenvolvimento)
- **Service:** Camada de serviços usando o padrão Command (em fase final)
- **Libs:** Tipos e entidades básicas reutilizáveis
- **Main:** Ponto de entrada do sistema (a ser implementado)
- **Interfaces:** Interfaces entre as camadas
- **Docs:** Diagramas, documentação Doxygen, etc.

## ⚙️ Tecnologias Utilizadas

- **C++17**
- **Makefile** para automação
- **SQLite3** para persistência
- **Doxygen** para documentação técnica (gerada em `/Docs/html/`)

## 🧪 Estado Atual

Atualmente, o projeto **não possui uma execução completa**, pois a camada de apresentação ainda está sendo implementada. No entanto, é possível:

- Rodar os **testes unitários**
- Executar funções de gerenciamento do banco de dados
- Navegar pela **documentação Doxygen**

## 🚀 Como Rodar

### Requisitos

- Compilador C++ (g++ com suporte a C++17)
- SQLite3 instalado

### Comandos disponíveis

```bash
# Compila e executa os testes
make test

# Atualiza o banco de dados com dados de teste
make updateData

# Gera a documentação Doxygen
make docs

```

> README redigido com auxílio do ChatGPT para padronização e clareza.