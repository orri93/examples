# Functional programming
# http://adv-r.had.co.nz/Functional-programming.html
#

library(pryr)  # For unenclose

power <- function(exponent) {
  function(x) {
    x ^ exponent
  }
}

square <- power(2)
square(2)
square(4)
square
as.list(environment(square))
unenclose(square)

cube <- power(3)
cube(2)
cube(4)
cube
as.list(environment(cube))
unenclose(cube)


power <- function(exponent) {
  print(environment())
  function(x) x ^ exponent
}
zero <- power(0)
environment(zero)

# Mutable state
new_counter <- function() {
  i <- 0
  function() {
    i <<- i + 1
    i
  }
}
counter_one <- new_counter()
counter_two <- new_counter()
counter_one()
counter_one()
counter_two()
