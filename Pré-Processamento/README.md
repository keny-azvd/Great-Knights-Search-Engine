# Dinâmica do pré-processamento:

- Gerar um (ou vários) arquivo(s) contendo as palavras únicas, os respectivos documentos em que ela aparece, e a frequência em que aparece. (Esse passo vai faciliar o processo de inserção na árvore, e guardar a frequência de repetições ajudará num possível rankeamento de páginas)

essa lista terá apenas palavras sem acentos, com letras minúsculas e considerará apenas as 26 letras do alfabeto inglês mais os 10 algarismos.
- Gerar um arquivo que associa os ID's dos documentos aos títulos (para exibir os resultados finais no terminal)
- Organizar os arquivos brutos, de forma que tendo o ID do documento, retornar o conteúdo seja uma tarefa rápida. (possivelmente faremos um arquivo para cada documento e os organizaremos em pastas com uma quantidade fixa deles)

> Na pasta **arvore** está uma ideia inicial da árvore. Nela, está um projeto criado no Code::Blocks.
>> Observação: a função *insert* (ainda) não faz o que deveria fzer, hehe.