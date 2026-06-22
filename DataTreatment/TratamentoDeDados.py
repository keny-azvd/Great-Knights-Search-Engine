# -*- coding: utf-8 -*-
import re
import os

def aChange(aOld, aNew):
    arquivo = open(aOld, 'r',encoding='utf-8', errors='ignore') # arquivo original
    # abrir o arquivo em modo leitura
    arquivo2 = open(aNew, 'w')
    
    for linha in arquivo:
        lista = re.findall('[a-zA-Z0-9]+',linha) # simplificando para
                                                 # a criação da árvore
        linha = (" ").join(lista)
        
        if linha == "ENDOFARTICLE":
            arquivo2.write('\n')
        elif linha == 'doc':
            arquivo2.write('\n')
        elif len(lista) > 1 and lista[0] == "doc":
            l = lista[-2:]
            linha = (" ").join(l)
            arquivo2.write(linha+'\n')
        else:        
            arquivo2.write(linha.lower()+' ')
       
    arquivo2.close()
    arquivo.close()

if not os.path.exists('arch.en'):
    os.mkdir('arch.en')
    
for i in range(164):
    aInt = i*10000
    os.system('clear')
    print("Limpando arquivo nº "+str(i+1)+"/164")

    aOne = 'raw.en/englishText_' + str(aInt) + '_' + str(aInt + 10000)
    aTwo = 'arch.en/archText_' + str(aInt) + '_' + str(aInt + 10000)

    aChange(aOne, aTwo) # criando os arquivos auxiliares
