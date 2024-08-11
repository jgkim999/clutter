import random

i = 1
while i < 10:
    print('Hello!' + str(i))
    i += 1

i = 10
while i > 0:
    print('Reverse Hello', i)
    i -= 1

count = int(input('반복할 횟수를 입력 하세요: '))
i = 0
while i < count:  # i가 count보다 작을 때 반복
    print('Counter Hello, world!', i)
    i += 1

i = 0
while i != 3:    # 3이 아닐 때 계속 반복
    i = random.randint(1, 6)    # randint를 사용하여 1과 6 사이의 난수를 생성
    print('Dice', i)

dice = [1, 2, 3, 4, 5, 6]
j = random.choice(dice)
print('Random Choice: ' + str(j))
