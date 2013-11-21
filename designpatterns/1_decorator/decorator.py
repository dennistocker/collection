# -*- coding: utf-8 -*-

# Component:定义一个对象接口，可以给这些对象动态地添加职责
class VisualComponent(object):
    def draw(self):
        raise NotImplementedError

    def resize(self):
        raise NotImplementedError


# ConcreteCompnent:定义一个对象，可以给这个对象动态添加职责
class TextView(VisualComponent):
    def draw(self):
        print('draw a textview')

    def resize(self):
        print('resize a textview')


# Decorator:维持一个指向Component对象的指针，并定义一个与Component接口一致的接口
class Decorator(VisualComponent):
    def __init__(self, visual_component):
        self.component = visual_component

    def draw(self):
        self.component.draw()

    def resize(self):
        self.component.resize()


# ConcreteDecorator:向组件添加职责
class BorderDecorator(Decorator):
    def draw(self):
        super(BorderDecorator, self).draw()
        print('draw border')

    def resize(self):
        super(BorderDecorator, self).resize()
        print('border resize')


# 装饰者模式动态地给一个对象添加一些额外的职责
if __name__ == '__main__':
    tv = TextView()
    bd = BorderDecorator(tv)
    bd.draw()
    bd.resize()

