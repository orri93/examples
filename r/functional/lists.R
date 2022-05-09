# Functional programming
# http://adv-r.had.co.nz/Functional-programming.html
#

compute_mean <- list(
  base = function(x) mean(x),
  sum = function(x) sum(x) / length(x),
  manual = function(x) {
    total <- 0
    n <- length(x)
    for (i in seq_along(x)) {
      total <- total + x[i] / n
    }
    total
  }
)


x <- runif(1e5)
system.time(compute_mean$base(x))
system.time(compute_mean[[2]](x))
system.time(compute_mean[["manual"]](x))

lapply(compute_mean, function(f) f(x))
lapply(compute_mean, function(f) system.time(f(x)))


x <- 1:10
funs <- list(
  sum = sum,
  mean = mean,
  median = median
)
lapply(funs, function(f) f(x))
lapply(funs, function(f) f(x, na.rm = TRUE))


simple_tag <- function(tag) {
  force(tag)
  function(...) {
    paste0("<", tag, ">", paste0(...), "</", tag, ">")
  }
}
tags <- c("p", "b", "i")
html <- lapply(setNames(tags, tags), simple_tag)
html$p("This is ", html$b("bold"), " text.")
