# -*- coding: utf-8 -*-

# Handler: 定义处理请求的接口
class Logger(object):

    (ERR, NOTICE, DEBUG) = (3, 5, 7)

    def __init__(self):
        self.mask = 0
        self._next = None

    def set_next(self, logger):
        self._next = logger
        return self

    def message(self, msg, priority):
        if priority <= self.mask:
            self._write_message(msg);
        elif self._next is not None:
            self._next.message(msg, priority)

    def _write_message(self, msg):
        raise NotImplementedError


# ConcreteHandler: 处理它所负责的请求并将不处理的请求转发给后继者
class StdoutLogger(Logger):
    def __init__(self, mask):
        super(StdoutLogger, self).__init__()
        self.mask = mask

    def _write_message(self, msg):
        print('Writing to stdout: %s' % msg)


class EmailLogger(Logger):
    def __init__(self, mask):
        super(EmailLogger, self).__init__()
        self.mask = mask

    def _write_message(self, msg):
        print('Sending var email: %s' % msg)


class StderrLogger(Logger):
    def __init__(self, mask):
        super(StderrLogger, self).__init__()
        self.mask = mask

    def _write_message(self, msg):
        print('Writing to stderr: %s' % msg)

# 职责链模式：使多个对象都有机会处理请求，从而避免请求的发送者和接受者之间的耦合关系
# 将这些对象连城一条链，并沿这条链传递该请求，知道有一个对象处理它为止
# Client
if __name__ == '__main__':
    l = StderrLogger(Logger.ERR).set_next(
            EmailLogger(Logger.NOTICE).set_next(
            StdoutLogger(Logger.DEBUG)))
    l.message('Normal', Logger.DEBUG)
    l.message('Exception', Logger.NOTICE)
    l.message('Fatal Error', Logger.ERR)

