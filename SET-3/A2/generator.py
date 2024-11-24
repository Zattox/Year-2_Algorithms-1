from random import randint

n = int(input())
arr = []
for i in range(0, n):
    arr.append(randint(0, 6001))

with open('test.txt', 'w') as destination_file:
    print(n, file=destination_file)
    print(*arr, file=destination_file)
with open('full_tests.txt', 'a') as destination_file:
    print(n, file=destination_file)
    print(*arr, file=destination_file)