# -*- coding: utf-8 -*-
# AbstractProduct:定义工厂方法所创建的对象的接口
class Car(object):
    def drive(self):
        raise NotImplementedError


# ContreteProduct：实现Product接口
class Benz(Car):
    def drive(self):
        print('drive benz')


class Bmw(Car):
    def drive(self):
        print('drive bmw')


# Factory:根据不同的参数生产不同的产品
class Factory(object):
    @staticmethod
    def getCar(car):
        if car == 'benz':
            return Benz()
        elif car == 'bmw':
            return Bmw()
        else:
            raise


if __name__ == '__main__':
    Factory.getCar('benz').drive()
    Factory.getCar('bmw').drive()

