# -*- coding: utf-8 -*-

# Command: 声明执行操作的接口
class Command(object):
    def __init__(self, receiver):
        self._receiver = receiver

    def execute(self):
        raise NotImplementedError


# ConcreteCommand:
# 1. 将一个接收者对象绑定于一个动作
# 2. 调用接收者相应的操作，以实现Execute
class ConcreteCommand(Command):
    def execute(self):
        print 'execute'
        self._receiver.action()


# Receiver：知道如何实施与执行一个请求相关的操作，任何类都可以作为一个接收者
class Receiver(object):
    def action(self):
        print('receiver action')

# Invoker：要求该命令执行这个请求, 存储ConcreteCommand对象
class Invoker(object):
    def __init__(self, command):
        self._command = command

    def execute_command(self):
        print('execute_command')
        self._command.execute()

# Client: 创建一个具体命令对象并设定它的接收者
def main():
    i = Invoker(ConcreteCommand(Receiver()))
    i.execute_command()

# 命令模式: 将一个请求封装为一个对象，从而使你可以用不同的请求对客户进行参数化；
# 对请求排队或记录请求日志，以及支持可撤销的操作
if __name__ == '__main__':
    main()

