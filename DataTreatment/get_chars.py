#!/usr/local/bin/python
# coding: ISO-8859-1
import re
import os
## Este arquivo printa todos os caracteres encontrados nos textos
cur=os.getcwd()
raw_dir=cur+"/raw.en"
f=[]
for (dirpath, dirnames, filenames) in os.walk(raw_dir):
    f.extend(filenames)
    f=sorted(f)

chars=set()
print(chars)
i=0
for file in f:
    i+=1
    print("Arquivo "+str(i)+"/164")
    with open(raw_dir+"/"+file,'r',encoding='ISO-8859-1') as eng:
        for line in eng.readline():
            chars.update(line)
print(sorted(list(chars)))
            
# ['\n', ' ', '!', '"', "'", '(', ')', ',', '-', '0', '1', '2', '3', '4', '5', '6', '7', '8',
# '9', ':', '<', '=', '>', '?', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
#  'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
#   'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '¨',
#    'â', 'ç', 'é', 'ú', 'ü']