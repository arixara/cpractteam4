import random

def generateO(myline):
    na = random.uniform(-2, 2)
    nb = random.uniform(-10, 10)
    nc = random.uniform(-10, 10)
    nd = random.uniform(-15, 15)
    myline = str(na) + ',' + str(nb) + ',' + str(nc) + ',' + str(nd)
    return myline

def generateD(k):
    myline = ''
    a = [['o'] * k] * k
    i = random.randint(0, k - 1)
    a[i][i] = 0
    i = random.randint(1, k - 1)
    j = random.randint(0, k - 1)
    a[i][j] = 0
    for i in range(k):
        for j in range(k):
            if a[i][j] != 0:
                a[i][j] = random.randint(-10, 10)
            myline += str(a[i][j]) + ' '
        myline += ' \n'
    myline += ' \n'
    return myline

print("Сгенерировать файлы для задачи: ")
print("1 - обход графов")
print("2 - дифференциальные уравнения")
p = int(input())
print("Желаемое количество тестовых файлов: ")
m = int(input())
for i in range(m):
    a = str(i) + '.txt'
    file = open(a, "w", encoding='utf-8')
    print("Величина файла", i, "(количество задач) = ")
    n = int(input())
    file.write(str(n) + '\n')
    if p == 1:
        print("Величина матрицы для файла", i)
        k = int(input())
    for j in range (n):
        myline = ''
        if p == 2:
            myline = generateO(myline)
        else:
            nb = random.randint(1, (k ** 2))
            nc = random.randint(1, (k ** 2))
            while (nb == nc):
                nc = random.randint(1, (k ** 2))
            b = str(k) + ' ' + str(nb) + ' ' + str(nc)
            mylinea = ''
            mylinea = b + '\n'
            mylineb = generateD(k)
            myline = mylinea + mylineb
        print(myline)
        file.write(myline + ' \n')
    print()
    print("Запись файла", i, "завершена.")
    file.close()
    print()
print()
print()
print("Удачи!")

