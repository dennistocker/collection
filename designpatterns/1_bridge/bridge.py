# -*- coding: utf-8 -*-

# Abstraction: 定义抽象类的接口
class AbstractMessage(object):
    def __init__(self, impl):
        self.impl = impl

    def sendMessage(self, msg, to):
        self.impl.send(msg, to)


# RefinedAbstraction: 扩充由Abstraction定义的接口
class CommonMessage(AbstractMessage):
    def sendMessage(self, msg, to):
        msg = '[common]%s' % msg
        super(CommonMessage, self).sendMessage(msg, to)


class UrgencyMessage(AbstractMessage):
    def sendMessage(self, msg, to):
        msg = '[Urgency]%s' % msg
        super(UrgencyMessage, self).sendMessage(msg, to)



# Implementor: 定义实现类的接口
class MessageImplementor(object):
    def send(self, msg, to):
        raise NotImplementedError


# ConcreteImplementor: 实现Implementor接口
class MessageSMS(MessageImplementor):
    def send(self, msg, to):
        print('send sms msg, msg: %s, to: %s' % (msg, to))


class MessageEmail(MessageImplementor):
    def send(self, msg, to):
        print('send email msg, msg: %s, to: %s' % (msg, to))

# 桥接模式分离抽象和实现，使得两部分都可独立变化
if __name__ == '__main__':
    sms = MessageSMS()
    common_sms = CommonMessage(sms)
    common_sms.sendMessage('hello', 'dst')
    urgency_sms = UrgencyMessage(sms)
    urgency_sms.sendMessage('hello', 'dst')

    email = MessageEmail()
    common_email = CommonMessage(email)
    common_email.sendMessage('hello', 'dst')
    urgency_email = UrgencyMessage(email)
    urgency_email.sendMessage('hello', 'dst')

