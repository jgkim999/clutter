for i in range(1, 101):
    if i % 3 == 0 and i % 5 != 0:
        print('Fizz:', str(i))
    elif i % 3 != 0 and i % 5 == 0:
        print('Buzz', str(i))
    elif i % 3 == 0 and i % 5 == 0:
        print('FizzBuzz:', str(i))
    else:
        continue

