# -*- coding: utf-8 -*-

# AbstractProduct:定义工厂方法所创建的对象的接口
class Car(object):
    def drive(self):
        raise NotImplementedError


# ConcreteProduct: 实现Product接口
class Benz(Car):
    def drive(self):
        print('drive benz')


class Bmw(Car):
    def drive(self):
        print('drive bmw')


# AbstractFactory:声明工厂方法，返回一个Product类型的对象
class Factory(object):
    def getCar(self):
        raise NotImplementedError


# ConcreteFactory:重定义工厂方法，返回一个ConcreteProduct实例
class BenzFactory(Factory):
    def getCar(self):
        return Benz()


class BmwFactory(Factory):
    def getCar(self):
        return Bmw()


# 工厂方法跟简单工厂相比，将实例化的逻辑判断从工厂内部移到了使用者
# 这样增加子类时只用增加对应的对象类和工厂类, 而不用修改以前的实现代码
# 但是也使得类的数量急剧增长
if __name__ == '__main__':
    BenzFactory().getCar().drive()
    BmwFactory().getCar().drive()

