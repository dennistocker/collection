# -*- coding: utf-8 -*-

# Component: 为组合中的对象声明接口
class Graphic(object):
    def __init__(self, name):
        self.name = name

    def draw(self):
        raise NotImplementedError

    def add(self, graph):
        raise NotImplementedError

    def remove(self, graph):
        raise NotImplementedError

    def getChild(self, n):
        raise NotImplementedError


# Leaf: 在组合中表示叶节点对象
class Line(Graphic):
    def draw(self):
        print('draw a line: %s' % self.name)

    def add(self, graph):
        print('cannot add to a leaf')

    def remove(self, graph):
        print('cannot remove from a leaf')

    def getChild(self, n):
        print('leaf has no child')


# Composite:定义有子部件的那些部件的行为
class Picture(Graphic):
    def __init__(self, name):
        super(Picture, self).__init__(name)
        self.graphs = []

    def draw(self):
        print('draw a picture: %s' % self.name)

    def add(self, graph):
        self.graphs.append(graph)

    def remove(self, graph):
        self.graphs.remove(graph)

    def getChild(self, n):
        if n >= len(self.graphs) or n < 0:
            return None
        return self.graphs[n]


# Client: 通过Component接口操作组合部件的对象

# 将对象组合成属性结构以表示“部分-整体”的层次结构，使得用户对单个对象和组合对象的使用具有一致性
if __name__ == '__main__':
    root = Picture('root')
    pic1 = Picture('pic1')
    pic2 = Picture('pic2')
    line1 = Line('line1')
    line2 = Line('line2')

    root.add(pic1)
    root.add(pic2)
    root.add(line1)
    root.add(line2)

    while True:
        g = root.getChild(0)
        if g is None:
            break
        root.remove(g)
        g.draw()

