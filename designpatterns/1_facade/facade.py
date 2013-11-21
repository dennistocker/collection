# -*- coding: utf-8 -*-

# Subsystem classes
# 实现子系统的功能
# 处理由Facade对象指派的任务
class Power(object):
    def on(self):
        print('power on')


class Bios(object):
    def selfTest(self):
        print('bios self-test')


class  Os(object):
    def start(self):
        print('os start')


# Facade
# 知道哪些子系统负责处理请求
# 将客户的请求代理给适当的子系统对象
class Computer(object):
    def powerOn(self):
        Power().on()
        Bios().selfTest()
        Os().start()


# Client:使用Facade提供的接口
if __name__ == '__main__':
    Computer().powerOn()

