import random

def generate():
    myline = ''
    na = random.uniform(-2, 2)
    nb = random.uniform(-10, 10)
    nc = random.uniform(-10, 10)
    nd = random.uniform(-15, 15)
    myline = str(na) + ',' + str(nb) + ',' + str(nc) + ',' + str(nd)
    return myline

file = open(r"C:\Users\User\Downloads\9.txt", "w", encoding='utf-8')
print("Величина = ")
n = int(input())
file.write(str(n) + '\n')

for i in range (n):
    myline = ''
    myline = generate()
    print(myline)
    file.write(myline + '\n')
print()
print()
print("Удачи!")
file.close()

