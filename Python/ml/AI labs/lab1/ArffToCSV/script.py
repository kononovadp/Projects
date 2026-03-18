import os
def toCsv(content): 
    data = False
    header = ""
    newContent = []
    for line in content:
        if not data:
            if "@attribute" in line:
                attri = line.split()
                columnName = attri[attri.index("@attribute")+1]
                header = header + columnName + ","
            elif "@data" in line:
                data = True
                header = header[:-1]
                header += '\n'
                newContent.append(header)
        else:
            newContent.append(line)
    return newContent

inFile=open("titanic.arff", "r")
content = inFile.readlines()
name,ext = os.path.splitext(inFile.name)
new = toCsv(content)
outFile=open(name+".csv", "w")
outFile.writelines(new)