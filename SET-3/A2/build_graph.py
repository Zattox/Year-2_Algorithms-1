import os, sys
import numpy as np
import matplotlib.pyplot as plt

_, algo1, algo2, gen = sys.argv
arr_x = []
arr_algo1 = []
arr_algo2 = []
for i in range(500, 10001, 100):
    print(i)
    with open('for_gen.txt', 'w') as f:
        print(i, file=f)
    os.popen('python %s < for_gen.txt' % gen)

    v1 = float(*os.popen('%s < test.txt' % algo1).readlines())
    v2 = float(*os.popen('%s < test.txt' % algo2).readlines())
    with open("result.txt", "a") as f:
        print(f"N = {i}", file = f)
        print(f"Time for MergeSort: ", "{:.10f}".format(v1), file = f)
        print(f"Time for MergeSortHybrid: ", "{:.10f}".format(v2), file = f)
        print("===============================", file = f)

    arr_x.append(i)
    arr_algo1.append(float(v1))
    arr_algo2.append(float(v2))

plt.figure(figsize=(20,10))
plt.axis([500, 10000, 0, 10000])
plt.title('Рандомные массивы')
plt.xlabel('Количество элементов')
plt.ylabel('Время (микросекунды)')
plt.plot(arr_x, arr_algo1, color='g', label = 'MergeSort')
plt.plot(arr_x, arr_algo2, color='b', label = 'MergeSortHybrid')
plt.legend(loc='best')
plt.savefig('graph.jpg')