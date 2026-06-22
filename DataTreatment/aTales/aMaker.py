# -*- coding: utf-8 -*-
"""
Created on Tue May 26 03:19:31 2020

@author: thequietprogrammer
"""


import os, sys

if not os.path.exists('aNames'):
    os.mkdir('aNames')
    
for i in range(164):
    # Desse jeito, vamos direto ao arquivo bruto original.
    aOld = "../raw.en/englishText_"+str(i*10000)+"_"+str(10000*(i+1))
    aNew = "aNames/aTitles_"+str(i*10000)+"_"+str(10000*(i+1))+".txt"
    
    aFile = open(aOld, 'r',encoding='iso-8859-1')
    aNotherFile = open(aNew, 'w', encoding='utf8')
    aCount = i*10000
    for aLine in aFile:
        aLine = aLine.split(" ")
        
        # Aqui, ignoramos as linhas de texto, e selecionamos as que contém
        # um título e um index.
        if aLine[0] == "<doc" and aLine[-1][0:7] == "dbindex":
            
            # Por aqui, formatamos aLine para mostrar apenas index e título.
            aLine = [aLine[-1][9:-3]] + aLine[2:-3]
            aLine[1] = aLine[1][7:]
            aLine[-1] = aLine[-1][:-1]
            if int(aLine[0]) != aCount:
                aNotherFile.write("\n"*(int(aLine[0])-aCount))
                aCount += int(aLine[0]) - aCount
            aNotherFile.write(" ".join(aLine)+"\n")
            aCount += 1
    else: aNotherFile.write("\n\nWe all have an start...\n... and an end.")
    aFile.close()
    aNotherFile.close()
    
    # Coisinha para ficar melhor de visualizar.
    sys.stdout.write("\rMaking Files: "+str(i+1)+" of 164. ")
    sys.stdout.flush()
else: print("Finished.")
    