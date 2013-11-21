# -*- coding: utf-8 -*-

# Flyweight:描述一个接口，通过这个接口flyweight可以接受并作用于外部状态
class ICoffee(object):
    def serve_coffee(self, ctx):
        raise NotImplementedError


# ConcreteFlyweight：实现Flyweight接口,必须是可共享的
class Coffee(ICoffee):
    def __init__(self, flavor):
        self.flavor = flavor # 共享属性

    def serve_coffee(self, ctx):
        print('serve coffee %s to table %s' % (self.flavor, ctx.table_num))


# UnsharedConcreteFlyweight: 不共享的部分，通常将ConcreteFlyweight对象作为子节点
class CoffeeContext(object):
    def __init__(self, table_num):
        self.table_num = table_num


# FlyweightFactory: 创建并管理flyweight对象
class CoffeeFactory(object):
    coffes = {}

    def get_coffee(self, flavor):
        if flavor not in self.coffes:
            self.coffes[flavor] = Coffee(flavor)
        return self.coffes[flavor]

    def get_total_flavors(self):
        return len(self.coffes)


# Client
class Waitress(object):
    def __init__(self):
        self.factory = CoffeeFactory()

    def take_order(self, flavor, table_num):
        coffee = self.factory.get_coffee(flavor)
        coffee.serve_coffee(CoffeeContext(table_num))


if __name__ == '__main__':
    w = Waitress()
    w.take_order('Cappuccino', 2)
    w.take_order('Regular', 1)

