# Functional programming
# http://adv-r.had.co.nz/Functional-programming.html
#

# You use an anonymous function when it’s not worth
# the effort to give it a name:
lapply(mtcars, function(x) length(unique(x)))
Filter(function(x) !is.numeric(x), mtcars)
integrate(function(x) sin(x) ^ 2, 0, pi)

# Like all functions in R, anonymous functions
# have formals(), a body(), and a parent environment():
formals(function(x = 4) g(x) + h(x))
body(function(x = 4) g(x) + h(x))
environment(function(x = 4) g(x) + h(x))

#
# Calling an anonymous function without giving it a name
#
# With appropriate parenthesis, the function is called:
(function(x) 3)()
# Calling an anonymous function syntax with arguments
(function(x) x + 3)(10)
# behaves exactly the same as
f <- function(x) x + 3
f(10)
