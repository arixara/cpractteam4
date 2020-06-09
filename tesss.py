import random

def generateO(myline):
    na = random.uniform(-2, 2)
    nb = random.uniform(-10, 10)
    nc = random.uniform(-10, 10)
    nd = random.uniform(-15, 15)
    myline = str(na) + ',' + str(nb) + ',' + str(nc) + ',' + str(nd)
    return myline

def generateD(a, k, myline):
    i = random.randint(1, k - 1)
    a[i][i] = 0
    i = random.randint(1, k - 1)
    j = random.randint(0, k - 1)
    a[i][j] = 0
    for i in range(1, k + 1):
        for j in range(0, k):
            if a[i][j] == 'o':
                a[i][j] = random.randint(-10, 10)
        myline += str(*a[i]) + ' /n'
    myline += ' /n'
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
    print("Величина файла (количество задач)", i, " = ")
    n = int(input())
    file.write(str(n) + '\n')
    if p == 1:
        print("Максимальная величина матрицы для файла ", i)
        k = int(input())
    for j in range (n):
        myline = ''
        if p == 2:
            myline = generateO(myline)
        else:
            a = [['o','o','o'],['o'] * k] * k
            nb = random.randint(1, k)
            nc = random.randint(1, k)
            while (nb == nc):
                nc = random.randint(1, k)
            a[0] = str(k) + ' ' + str(nb) + ' ' + str(nc)
            myline += str(a[0]) + ' /n'
            myline = generateD(a, k, myline)
        print(myline)
        file.write(myline + ' \n')
    print()
    print("Запись файла ", i, " завершена.")
    print()
print()
print()
print("Удачи!")
file.close()

