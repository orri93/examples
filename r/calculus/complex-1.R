# Complex numbers in R
# https://www.r-tutor.com/r-introduction/basic-data-types/complex
# https://stat.ethz.ch/R-manual/R-devel/library/base/html/complex.html
#

z = 1 + 2i     # create a complex number
z              # print the value of z
class(z)       # print the class name of z
is.complex(z)
as.complex(1)  # 1 + 0i

Re(z)
Im(z)
Mod(z)         # The modulus (sqrt(x^2 + y^2))
Arg(z)         # The Argument (theta = Arg, where x = r * cos(theta) and y = r * sin(theta))
Conj(z)

# The following gives an error as −1 is not a complex value.
sqrt(-1)       # square root of −1

# Instead, use the complex value −1 + 0i.
sqrt(-1+0i)    # square root of −1+0i

# An alternative is to coerce −1 into a complex value.
sqrt(as.complex(-1))
