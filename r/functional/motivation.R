# Functional programming
# http://adv-r.had.co.nz/Functional-programming.html
#

# Generate a sample dataset
set.seed(1014)
df <- data.frame(replicate(6, sample(c(1:10, -99), 6, rep = TRUE)))
names(df) <- letters[1:6]
df

df$a[df$a == -99] <- NA
df$b[df$b == -99] <- NA
df

fix_missing <- function(x) {
  x[x == -99] <- NA
  x
}
df$a <- fix_missing(df$a)
df$b <- fix_missing(df$b)
df

# The next step is to remove this possible source of error
# by combining two functions. One function, fix_missing(),
# knows how to fix a single vector; the other, lapply(),
# knows how to do something to each column in a data frame.
df[1:3] <- lapply(df[1:3], fix_missing)
df
df[] <- lapply(df, fix_missing)
df
v <- c(5, -99, 2, -99, 2)
v
v <- lapply(v, fix_missing)
v

# Closures are functions that make and return functions.
# Closures allow us to make functions based on a template:
missing_fixer <- function(na_value) {
  function(x) {
    x[x == na_value] <- NA
    x
  }
}
fix_missing_99 <- missing_fixer(-99)
fix_missing_999 <- missing_fixer(-999)
fix_missing_99(c(-99, -999))
fix_missing_999(c(-99, -999))

mysummary <- function(x) {
  c(mean(x), median(x), sd(x), mad(x), IQR(x))
}
lapply(df, mysummary)

mysummary <- function(x) {
  c(mean(x, na.rm = TRUE),
    median(x, na.rm = TRUE),
    sd(x, na.rm = TRUE),
    mad(x, na.rm = TRUE),
    IQR(x, na.rm = TRUE))
}
lapply(df, mysummary)

mysummary <- function(x) {
  funs <- c(mean, median, sd, mad, IQR)
  lapply(funs, function(f) f(x, na.rm = TRUE))
}
lapply(df, mysummary)
