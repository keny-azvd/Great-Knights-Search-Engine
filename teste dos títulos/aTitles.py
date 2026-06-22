# -*- coding: utf-8 -*-
"""
Created on Mon May 25 23:59:45 2020

@author: thequietprogrammer
"""


import os

if not os.path.exists('aNewTitles'):
    os.mkdir('aNewTitles')

for i in range(164): # Fiz com 164 por causa do número de total de documentos.
    count = i*10000
    aOld = "titles/titles_" + str(count) + "_" + str((i+1)*10000) + ".txt"
    aNew = "aNewTitles/titles_" + str(count) + "_" + str((i+1)*10000) + ".txt"
    
    if not os.path.isfile(aOld): continue
    
    aFile = open(aOld, 'r')
    aNotherFile = open(aNew, 'w')
    
    for linha in aFile:
        if linha.split(",")[0] == str(count):
            aNotherFile.write(linha)
        else:
            while linha.split(",")[0] != str(count):
                aNotherFile.write("\n")
                count += 1
            aNotherFile.write(linha)
        count += 1
        
    aFile.close()
    aNotherFile.close()
