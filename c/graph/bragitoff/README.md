# Plotting with C and GNUPLot

[Plotting exercises for C and GNUPlot](https://www.bragitoff.com/2017/08/plotting-exercises-c-gnuplot/)

## Compiling with Visual Studio C/C++

```
cl circle.c
```

## Create the output

```
circle 5 5 10 > circle.tsv
```

## Plotting the output with GNUPlot

```
plot 'circle.tsv' w l
```
