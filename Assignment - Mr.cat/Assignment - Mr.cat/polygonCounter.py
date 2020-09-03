import re
import itertools

# Put the file you want to count here
file_list = [
    "source.cpp"
]

# put the name of ur customer function, and how many polygon it contains
custom_function = {
    'draw_cuboid': 6,
    'draw_cylinder': 1,
}

d = dict.fromkeys(file_list, 0)
totalCount = 0

for file in file_list:
    cppFile = open(file, "r")
    fileContent = cppFile.read()
    cppFile.close()

    matched = re.split(r"\s*glEnd\(\);\s*", fileContent)

    for primitive in matched:
        
        type = re.findall(r"\s*(?<=glBegin\().*(?=\);\s*)", primitive)
        if type:
            count = len(re.findall(r"\s*glVertex(2f|3f)\(.*\)\s*",primitive))
            type = type[0]
            if type == 'GL_TRIANGLES':
                count = count / 3
            elif type == 'GL_QUADS':
                count = count / 4
            elif type == 'GL_QUAD_STRIP':
                count = (count - 2) / 2
            elif type == 'GL_TRIANGLE_STRIP':
                count = count - 2
            elif type == 'GL_POLYGON':
                count = 1
            elif type == 'GL_TRIANGLE_FAN':
                count = count - 2

        gluCount = len(re.findall(r"\s*(gluCylinder|gluDisk|gluSpheres)\(.*\);\s*",primitive))

        for custom, value in custom_function.items():
            custom_regex = re.compile(custom)
            funcCount = len(re.findall(custom_regex, primitive)) * value

            d[file] = d[file] + funcCount

        d[file] = d[file] + count + gluCount

print(d)
for num in d.values():
    totalCount += num

print(totalCount)