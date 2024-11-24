import os, sys
from math import sqrt
import matplotlib.pyplot as plt

def gen(N):
    f = open('input.txt', 'w')
    f.seek(0)
    f.write(f'1 1 1\n')
    f.write(f'1.5 2 {sqrt(5) / 2}\n')
    f.write(f'2 1.5 {sqrt(5) / 2}\n')
    f.write(f'{N}')
    f.close()

_, f1, f2 = sys.argv
arr_x = []
arr_y = []
true_sq = float(*os.popen('%s < input.txt' % f1).readlines())
for i in range(100, 1000000, 500):
    gen(i)
    v2 = os.popen('%s < input.txt' % f2).readlines()
    with open("big_result1.txt", "a") as f:
        print(f"N = {i}", file = f)
        print("True output:", file = f)
        print(true_sq, file = f)
        print("Approximate output:", file = f)
        print(*v2, file = f)
        print("===============================", file = f)

    arr_x.append(i)
    arr_y.append(float(*v2))

plt.figure(figsize=(20,10))
plt.axis([100, 1000000, 0.7, 1.2])
plt.title('The dependence of the area on the number of points')
plt.xlabel('Number of points')
plt.ylabel('Area')
plt.plot(arr_x, arr_y, label = 'Approximate square')
plt.axhline(y = true_sq, color='r', linestyle='--', label='True square')

plt.savefig('big_graph1.jpg')