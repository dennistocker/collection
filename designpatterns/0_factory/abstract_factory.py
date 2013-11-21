# -*- coding: utf-8 -*-

# AbstrctProduct:为一类产品对象声明一个接口
class Keyboard(object):
    def type(self):
        raise NotImplementedError


class Mouse(object):
    def click(self):
        raise NotImplementedError


# ConcreteProduct: 定义一个将被相应的具体工厂创建的产品对象
class MicrosoftKeyboard(Keyboard):
    def type(self):
        print('type MicrosoftKeyboard')


class AppleKeyboard(Keyboard):
    def type(self):
        print('type AppleKeyboard')


class MicrosoftMouse(Mouse):
    def click(self):
        print('click MicrosoftMouse')


class AppleMouse(Mouse):
    def click(self):
        print('click AppleKeyboard')


# AbstractFactory: 声明一个创建抽象产品对象的接口
class AbstractFactory(object):
    def getKeyboard(self):
        raise NotImplementedError

    def getMouse(self):
        raise NotImplementedError


# ConcreteFactory: 实现创建具体产品对象的操作
class MiscrosoftFactory(AbstractFactory):
    def getKeyboard(self):
        return MicrosoftKeyboard()

    def getMouse(self):
        return MicrosoftMouse()


class AppleFactory(AbstractFactory):
    def getKeyboard(self):
        return AppleKeyboard()

    def getMouse(self):
        return AppleMouse()


# Client:仅使用由AbstractFactory和AbstractProduct类声明的接口

# 抽象工厂跟工厂方法相比，适用于产品族，可以方便的增加和减少产品族
# 对于产品类型的增加和减少无能为力
if __name__ == '__main__':
    MiscrosoftFactory().getKeyboard().type()
    MiscrosoftFactory().getMouse().click()

    AppleFactory().getKeyboard().type()
    AppleFactory().getMouse().click()

