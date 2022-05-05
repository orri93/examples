# R Resample Time Series
# https://koalatea.io/r-resample-timeseries
#

require(zoo) # For time series
require(data.table) # High performance data frame
require(curl) # To load from url for data.table's fread


df.ts <- fread('https://raw.githubusercontent.com/ourcodingclub/CC-time-series/master/monthly_milk.csv')
df.ts[, month := as.Date(month)]

# Index by our date file since this is a time series
setkey(df.ts, month)


# Downsampling in R
ts.indexes = seq.int(from = 1, to = nrow(df.ts), by = 12)
ts.indexes

df.ts[ts.indexes]

df.ts[, mean(milk_prod_per_cow_kg), by = format(month, "%Y")]


# Upsampling in R
start = df.ts$month[1]
end = tail(df.ts$month, 1)

date.indexes = seq(
  from = start,
  to = end,
  by = "days")
head(date.indexes)

df.ts[J(date.indexes), roll = 31]
