# -*- coding: utf-8 -*-
"""
Created on Wed May 27 15:29:25 2020

@author: thequietprogrammer
"""


import os, sys

if not os.path.exists("aTexts"):
    os.mkdir("aTexts")
    
for i in range(164):
    # Desse jeito, vamos direto ao arquivo bruto original.
    aOld = "../raw.en/englishText_"+str(i*10000)+"_"+str(10000*(i+1))
    aNew = "aTexts/aDocs_"+str(i*10000)+"_"+str(10000*(i+1))+".txt"
    
    aFile = open(aOld, 'r',encoding='iso-8859-1')
    aNotherFile = open(aNew, 'w', encoding='utf8')
    
    # Esse aBlank serve para retirar linhas vazias do texto. No sentido de que
    # no final de alguns artigos têm muitas linhas em branco no final. E achei
    # um tanto deselegante fazer o cliente ver um vazio na tela do prompt.
    aBlank = True
    
    for aLine in aFile:
        aLine = aLine.split(" ")
        if aLine == ["\n"]:
            if aBlank == True:
                aNotherFile.write("\n")
            aBlank = False
        elif aLine[0] == "ENDOFARTICLE.\n" or aLine[0] == "</doc>\n":
            continue
        elif aLine[0] == "<doc" and aLine[-1][0:7] == "dbindex":
            aLine = aLine[-1][9:-3]
            aNotherFile.write("Marked: low fidelity " + aLine + "\n")
            aBlank = True
        else:
            aNotherFile.write(" ".join(aLine))
            aBlank = True
            
    aFile.close()
    aNotherFile.close()
    
    # Coisinha para ficar melhor de visualizar.
    sys.stdout.write("\rTaking Files: "+str(i+1)+" of 164. ")
    sys.stdout.flush()
else: print("Finished.")
            