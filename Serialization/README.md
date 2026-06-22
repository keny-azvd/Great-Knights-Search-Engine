# Serialization  

Nesta pasta, deve-se colocar a pasta **titles** e **sorted_words** (fruto da descompactação de **titles.zip** e **sorted_words.zip** [deste](https://bit.ly/36sinp3) link).  

Após isso, executamos o script **aTitles.py** (para criar a pasta configurada de títulos **aNewTitles**). O arquivo **trieSerial.cpp** possui poderes novos! A serialização para ~~.txt~~ arquivo foi incluída. Ainda em fase de testes de viabilidade...  

É meu consagrado, a viabilidade foi-se embora...  

> O arquivo **trie.cpp** é pré-requisito para **trieSerial.cpp**.  

### A filisofia do trieSerial.cpp  

Já vai preparando os 9GB de RAM meu bom...  

> Se quiser compilar o **trieSerial.cpp** com a construção da árvore com menos arquivos, certamente será um bom jeito de não arrebentar a memória (faz isso mudando para um número menor que 64 o número 64 da linha 48).  

> Outro jeito para não ser tão requisitivo, é comentar o código que cria a segunta árvore (a **SEGK**), para apenas serializar a árvore original. E após isso, fazer o contrário: comentar a criação da árvore original e descomentar a criação da segunda árvore (que vai ser criada por descerialização).  

> E se a sanidade para fazer tudo isso estiver escassa, podemos baixar o arquivo da serialização da árvore original completa (a **GKSE**) por [este link](https://gvmail-my.sharepoint.com/:f:/g/personal/b39394_fgv_edu_br/EoyEu1qrbGhDgC4pBXNaiKYBdwWKkWXB5wn0wKH40ol4eg?e=hmw0xU).  

É bem simples se prestar bastante atenção: construímos a árvore do modo arcaico (chamada **GKSE**), serializamos a árvore que construímos, criamos uma outra árvore (chamamos ela de **SEGK**), descerializamos o arquivo **trieSerial** na árvore **SEGK**, e pronto! Temos uma cópia perfeita da árvore original (tudo da Trie **GKSE** está em **SEGK**).  

> A última parte comentada de **trieSerial.cpp** era para serializar a árvore **SEGK** para comparar com a serialização da **GKSE** (o que foi válido, realmente...).  
