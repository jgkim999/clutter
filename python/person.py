class Person:
    def __init__(self, name, age, address):
        self.name = name
        self.age = age
        self.address = address

    def greeting(self):
        print('안녕하세요. 저는 {0}입니다. 나이는 {1}살이고 사는 곳은 {2}입니다.'.format(self.name, self.age, self.address))


a = Person("Monster", 11, "USA")
a.greeting()