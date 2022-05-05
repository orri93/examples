# Aggregate Examples
#
#

# Dependencies
library(data.table)

# Aggregate data.frame Function
aggregatendf <- function(df, n = 5, FUN = mean) {
  aggregate(df,
    by = list(gl(ceiling(nrow(df)/n), n)[1:nrow(df)]),
    FUN = FUN)[-1]
}

df <- data.frame(a = 1:12, b = 13:24)
df <- aggregatendf(df)

df <- copy(cars)
df <- aggregatendf(df, n = 10)

df <- fread('https://raw.githubusercontent.com/ourcodingclub/CC-time-series/master/monthly_milk.csv')
df[, month := as.Date(month)]
#dfmm <- df[, mean(milk_prod_per_cow_kg), by = format(month, "%Y-%m")]
dfmy <- df[, mean(milk_prod_per_cow_kg), by = format(month, "%Y")]
