# -*- coding: utf-8 -*-

# Adaptee: 定义一个已经存在的接口，这个接口需要适配
class Dog(object):
    def bark(self):
        print 'woof!'


class Cat(object):
    def meow(self):
        print 'meow!'


# Target: 定义Client使用的与特定领域相关的接口
class Target(object):
    def make_noise(self):
        raise NotImplementedError


# Adapter: 对Adaptee的接口与Target接口进行适配
class Pet(Target):
    def __init__(self, obj):
        self.obj = obj

    def make_noise(self):
        if isinstance(self.obj, Dog):
            self.obj.bark()
        elif isinstance(self.obj, Cat):
            self.obj.meow()
        else:
            pass


# 将一个类的接口转换成客户希望的另外一个接口。一般可通过组合或者继承的方式来实现
if __name__ == '__main__':
    cat = Cat()
    Pet(cat).make_noise()

