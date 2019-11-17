def random_item(n, ini, fin):
    import random
    
    with open(f'{n}_atividade.txt','w') as f:
        for i in range(1, n, 1):
            f.write( str((random.randint(ini, fin),random.randint(ini, fin)) ))
            f.write('\n')

for i in range(100, 600, 100):
    random_item(i, 1, 10)