# -*- coding: utf-8 -*-

# Subject: 定义RealSubject和Proxy的共用接口，这样在任何使用RealSubject的地方都可以使用Proxy
class Image(object):
    def display(self):
        raise NotImplementedError


# RealSubject: 定义Proxy所代表的实体
class RealImage(Image):
    def __init__(self, filename):
        self.filename = filename
        self._load_from_disk()

    def _load_from_disk(self):
        print('loading realimage: %s' % self.filename)

    def display(self):
        print('display realimage: %s' % self.filename)


# Proxy: 保存一个引用使得代理可以访问实体
class ProxyImage(Image):
    def __init__(self, filename):
        self.filename = filename
        self.real_image = None

    def display(self):
        if self.real_image is None:
            self.real_image = RealImage(self.filename)
        self.real_image.display()

# 代理模式可以实现copy-on-write，refrence-counting等，代理复杂对象时可以和享元模式
# 结合使用来减少内存
if __name__ == '__main__':
    image = ProxyImage('test.jpg')
    image.display()
    print
    image.display()

