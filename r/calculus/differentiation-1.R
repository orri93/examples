# Differentiation in R
# https://rpubs.com/venkatritch/333327
#

f=expression(x^2+3*x)
D(f,'x')
D(D(f,'x'),'x')

ff<-D(f,'x')
D(ff,'x')

x <- 1:5
eval(f)
eval(ff)


f <- expression(x^3 - 2 * x^2 + 3)
df <- D(f, 'x')
for(x in seq(-3,3,0.1)) print(paste(x,eval(f),eval(df)))


f<-expression(x^2+y^2+2*x*y-3*x+4*y+4)
D(f,'x')
D(f,'y')


exp<- expression(sin(cos(x + y^2)))
dx<-D(exp,"x"); dx
dy<-D(exp,"y"); dy
# Calculate all the (partial) derivatives of an equation using deriv() function.
# It returns the result as an expression
dxy<-deriv(exp,c("x","y"));dxy;typeof(dxy)
x<-seq(-pi,pi,pi/4)
y<-pi
eval(dxy)

# Using an option func=T with derive function such that it returns all
# the derivatives of the expression as a function which we can invoke
# at any time.
pp<-deriv(exp,c("x","y"),func=T)
pp(x,y)

# Computing higher order derivatives (recursive)
DD<-function(expr,name,order=1){
  if(order<1) stop("Order must be >=1")
  if(order==1) D(expr,name)
  else DD(D(expr,name),name,order-1)
}

exp<-expression(x^3)
DD(exp,'x',1)
DD(exp,"x",2)
DD(exp,"x",3)


# Differentiating discrete data (not functions)
x<-c(10,20,30,20,12,20,20)  # N = 7
diff(x)                     # diff always gives n - 1 (here N = 6)
