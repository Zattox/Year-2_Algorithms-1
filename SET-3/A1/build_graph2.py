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
    v2 = float(*os.popen('%s < input.txt' % f2).readlines())
    with open("big_result2.txt", "a") as f:
        print(f"N = {i}", file = f)
        print(f"Difference: {v2 - true_sq}", file = f)
        print("===============================", file = f)

    arr_x.append(i)
    arr_y.append(v2 - true_sq)

plt.figure(figsize=(20,10))
plt.axis([100, 1000000, -0.05, 0.05])
plt.title('The dependence of the difference on the number of points')
plt.xlabel('Number of points')
plt.ylabel('Area')
plt.plot(arr_x, arr_y, label = 'Approximate square')
plt.axhline(y = 0, color='r', linestyle='--')

plt.savefig('big_graph2.jpg')