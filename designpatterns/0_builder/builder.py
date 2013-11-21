# -*- coding: utf-8 -*-

# Product:被构造的复杂对象
class House(object):
    def __init__(self):
        self.wall = None
        self.door = None
        self.window = None

    def __str__(self):
        return 'wall: %s, door: %s, window: %s' % (self.wall, self.door, self.window)


# Abstract Builder: 为创建一个Product对象的各个部件制定抽象接口
class Builder(object):
    def __init__(self):
        self.house = None

    def buildWall(self):
        raise NotImplementedError

    def buildDoor(self):
        raise NotImplementedError

    def buildWindow(self):
        raise NotImplementedError


# Concrete Builder:实现Builder的接口以构造和装配该产品的各个部件
class RedHouseBuilder(Builder):
    def __init__(self):
        self.house = House()

    def buildWall(self):
        self.house.wall = 'red'

    def buildDoor(self):
        self.house.door = 'small'

    def buildWindow(self):
        self.house.window = 'sliding'

    def getHouse(self):
        return self.house


class WhiteHouseBuilder(Builder):
    def __init__(self):
        self.house = House()

    def buildWall(self):
        self.house.wall = 'white'

    def buildDoor(self):
        self.house.door = 'big'

    def buildWindow(self):
        self.house.window = 'double hung'

    def getHouse(self):
        return self.house


# Director: 构造一个使用Builder接口的对象
class Director(object):
    def BuildHouse(self, builder):
        builder.buildWall()
        builder.buildDoor()
        builder.buildWindow()
        return builder.getHouse()


# 生成器模式可以将一个复杂对象的构建和它的表示分离，使得同样的构建过程可以创建不同的表示
if __name__ == '__main__':
    director = Director()
    print(director.BuildHouse(RedHouseBuilder()))
    print(director.BuildHouse(WhiteHouseBuilder()))

