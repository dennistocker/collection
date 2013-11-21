# -*- coding: utf-8 -*-

# a work-around for singleton, but __init__ will always be executed
class Singleton(object):
    _instance = None
    def __new__(cls, *args, **kwargs):
        if not cls._instance:
            cls._instance = super(Singleton, cls).__new__(cls, *args, **kwargs)
        return cls._instance

    def __init__(self):
        print('__init__')


# use metaclass
class Single(type):
    _instances = {}
    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            cls._instances[cls] = super(Single, cls).__call__(*args, **kwargs)
        # else:
            # cls._instances[cls].__init__(*args, **kwargs)
        return cls._instances[cls]


class MySingleton(object):
    __metaclass__ = Single

    def __init__(self):
        print('__init__')


if __name__ == '__main__':
    s1 = Singleton()
    s2 = Singleton()
    if id(s1) == id(s2):
        print('Same')
    else:
        print('Different')

    s1 = MySingleton()
    s2 = MySingleton()
    if id(s1) == id(s2):
        print('Same')
    else:
        print('Different')


