import math

f = open("curves.csv", "wt")
f.write("angle sine cosine\n")

npts = 73
for i in range(npts):
    angle_deg = float(i) * (360. / float(npts-1))
    angle_rad = angle_deg * (3.1415926535 / 180.)
    sine = math.sin(angle_rad)
    cosine = math.cos(angle_rad)
    f.write("%g %g %g\n" % (angle_deg, sine, cosine))

f.close()
