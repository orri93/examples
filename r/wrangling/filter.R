# Example of using a Filter
#

data <- c(0, 1, 2, 3, 4, 1, 2, 3, 4, 3, 2, 1, 0, 3, 0, 0, 0, 4, 5, 4,6 )

isgrthzero <- function(x) {
  return(x > 0)
}


fdata <- Filter(isgrthzero, data)
print(fdata)
