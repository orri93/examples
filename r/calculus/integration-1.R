# Integration in R
# https://rpubs.com/venkatritch/333327
#

require(cubature)

f<-function(x) x^2+3*x

integrate(f,0,1)
integrate(f,0,Inf)
integrate(f, lower=0, upper=Inf)


# Higher order integrals using cubature package
f<-function(x) 1
adaptIntegrate(f, lowerLimit = c(0,0,0), upperLimit = c(4,4,4))

# Triple integral example
f <- function(x) { 2/3 * (x[1] + x[2] + x[3]) } 
adaptIntegrate(f, lowerLimit = c(0, 0, 0), upperLimit = c(0.5, 0.5, 0.5))


# Integrating discrete data (not functions)
x<-c(10,20,30,20,12,20,20)  # N = 7
cumsum(x)
