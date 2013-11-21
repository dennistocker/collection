# -*- coding: utf-8 -*-
import copy

# ProtoType: 声明一个克隆自身的接口
class Cloneable(object):
    def clone(self):
        raise NotImplementedError


# ConcretePrototype:实现一个克隆自身的操作
class Man(Cloneable):
    def __init__(self, name, height, weight):
        self.name = name
        self.height = height
        self.weight = weight

    def __str__(self):
        return 'name: %s, height: %s, weight: %s' % (self.name, self.height, self.weight)

    def clone(self):
        return copy.deepcopy(self)


# 用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象
if __name__ == '__main__':
    jack = Man('Jack', 180, 70)
    mike = jack.clone()
    mike.name = 'Mike'
    print(jack)
    print(mike)

    jack = Man('Jack', 180, 70)
    mike = jack
    mike.name = 'Mike'
    print(jack)
    print(mike)

