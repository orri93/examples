import math

f = open("regulargrid2d.csv", "wt")
f.write("density c2 c3 c4 c5 c6 c7 c8\n")

nx = 8
ny = 10
for iy in range(ny):
    y = float(iy)
    for ix in range(nx):
        x = float(ix)
        dist = math.sqrt((x - 3.5) * (x - 3.5) + (y - 4.5) * (y - 4.5))
        if (ix < nx - 1):
           f.write("%g " % dist)
        else:
           f.write("%g\n" % dist)

f.close()
