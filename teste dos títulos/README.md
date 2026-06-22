#### É o seguinte...  

Tentei fazer isso na pressa, e acabei utilizando junto aquele **trie.cpp** pra dar certo.  

> Rapaz, quando executei aqui o código da criação da árvore, deu só 64 segundos!!! Loucura, não? Ainda não sei se é por causa do disco rígido ser um SSD ou por causa do processador. Outro negócio maneiro é que ficou quase 4GB gasta na RAM. Interessante...  

Pois então, os pré-requisitos pra isso dar certo é ter aquela pasta das palavras (o **sorted_words**) neste mesmo diretório e também aquela outra pasta dos títulos (a **titles**).  

> Também renomeei as frases, pois a acentuação no meu prompt estava toda zuada. Se for só no meu, mostra o em português mesmo.  

Pois bem, fiz mudanças na pasta **titles** adicionando linhas brancas em index que não existe, assim, podemos ver o título com index 100430 diretamente na linha 100430 do documento (pois reparei que às vezes não existe um certo index, aí ele pula pra outro, o que seria um tanto chato pois precisaríamos, além de ir até a linha, comparar cada index). A nova pasta chama-se **aNewTitles**, e ela é criada pelo script **aTitles.py**.  

E então... E... Pera... Essa... O negócio nun vai funfá. Ok. Fiz isso: o script **opa.cpp** é o equivalente ao **trie_construct**, com a diferença na apresentação do programa (no prompt).