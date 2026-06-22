import os
def printProgressBar (iteration, total, prefix = '', suffix = '', decimals = 1, length = 100, fill = '█', printEnd = "\r"):
    """
    Font: StackOverflow
    Call in a loop to create terminal progress bar
    @params:
        iteration   - Required  : current iteration (Int)
        total       - Required  : total iterations (Int)
        prefix      - Optional  : prefix string (Str)
        suffix      - Optional  : suffix string (Str)
        decimals    - Optional  : positive number of decimals in percent complete (Int)
        length      - Optional  : character length of bar (Int)
        fill        - Optional  : bar fill character (Str)
        printEnd    - Optional  : end character (e.g. "\r", "\r\n") (Str)
    """
    
    percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
    filledLength = int(length * iteration // total)
    bar = fill * filledLength + '-' * (length - filledLength)
    print('\r%s |%s| %s%% %s' % (prefix, bar, percent, suffix), end = printEnd)
    # Print New Line on Complete
    if iteration == total: 
        print()

aTextsDir=os.getcwd()+"/aTexts/"
f=[]
for (dirpath, dirnames, filenames) in os.walk(aTextsDir):
    f.extend(filenames)
    break
d={}
i=0
printProgressBar(0, len(f), prefix = 'Salvando Dicionário:', suffix = '', length = 50)
for file in f:
    i+=1
    printProgressBar(i, len(f), prefix = 'Progresso:', suffix = 'Arquivos Lidos', length = 50)
    m=0
    c=0
    with open(aTextsDir+file,'r',encoding='utf-8') as aDoc:
        for line in aDoc:
            if line[0:20]=="Marked: low fidelity ":
                c=0
            else:
                for char in line:
                    c+=1
                m=max(m,c)
            
    d[file]=m
print(d)

