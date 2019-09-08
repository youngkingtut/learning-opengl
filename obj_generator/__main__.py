from collections import namedtuple

WORLD_SIZE_WIDTH = 120
WORLD_SIZE_HEIGHT = 90
Z_DEPTH = 0.0
LINE_THICKNESS = 0.2

VERTEX = namedtuple("VERTEX", "x y z")
ELEMENT = namedtuple("ELEMENT", "uno dos tres")


if __name__ == "__main__":
    vertices = []
    elements = []

    for line in xrange(-WORLD_SIZE_WIDTH, WORLD_SIZE_WIDTH, 10):
        upper_left = VERTEX(line - LINE_THICKNESS, WORLD_SIZE_HEIGHT, Z_DEPTH)
        upper_right = VERTEX(line + LINE_THICKNESS, WORLD_SIZE_HEIGHT, Z_DEPTH)
        lower_left = VERTEX(line - LINE_THICKNESS, -WORLD_SIZE_HEIGHT, Z_DEPTH)
        lower_right = VERTEX(line + LINE_THICKNESS, -WORLD_SIZE_HEIGHT, Z_DEPTH)

        offset = 338 + len(vertices)
        vertices.append(upper_left)
        vertices.append(upper_right)
        vertices.append(lower_left)
        vertices.append(lower_right)

        elements.append(ELEMENT(offset + 0, offset + 2, offset + 1))
        elements.append(ELEMENT(offset + 3, offset + 1, offset + 2))

    for line in xrange(-WORLD_SIZE_HEIGHT, WORLD_SIZE_HEIGHT, 10):
        upper_left = VERTEX(-WORLD_SIZE_WIDTH, line + LINE_THICKNESS, Z_DEPTH)
        upper_right = VERTEX(WORLD_SIZE_WIDTH, line + LINE_THICKNESS, Z_DEPTH)
        lower_left = VERTEX(-WORLD_SIZE_WIDTH, line - LINE_THICKNESS, Z_DEPTH)
        lower_right = VERTEX(WORLD_SIZE_WIDTH, line - LINE_THICKNESS, Z_DEPTH)

        offset = 338 + len(vertices)
        vertices.append(upper_left)
        vertices.append(upper_right)
        vertices.append(lower_left)
        vertices.append(lower_right)

        elements.append(ELEMENT(offset + 0, offset + 2, offset + 1))
        elements.append(ELEMENT(offset + 3, offset + 1, offset + 2))

    with open("..\\src\\Resources\\Models\\grid.obj", "w") as f:
        for vertex in vertices:
            f.write("v {} {} {}\n".format(vertex.x, vertex.y, vertex.z))

        for element in elements:
            f.write("f {} {} {}\n".format(element.uno, element.dos, element.tres))
