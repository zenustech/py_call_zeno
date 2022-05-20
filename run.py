import build.embedtest as m

def main():
    m.createScene()
    m.load_scene('test.json')
    for f in range(10):
        m.setNodeInputFloat("f8a42c58-PackNumericVec", "x", float(f));
        m.applyGraph()
    v = m.getGraphOutputVec3("output1")
    print(v)


if __name__ == '__main__':
    main()
