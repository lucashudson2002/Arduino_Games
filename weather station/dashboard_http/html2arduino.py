with open('index.html', 'r') as arquivo:
    conteudo = arquivo.readlines()
    
for i in range(len(conteudo)):
    conteudo[i] = 'html += "' + conteudo[i].rstrip() + '";'
    print(conteudo[i])