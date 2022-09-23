# AplPy Beginner Tutorial
# https://aplpy.readthedocs.io/en/stable/fitsfigure/quickstart.html

import aplpy
import numpy

gc = aplpy.FITSFigure('fits/2MASS_k.fits')
gc.show_rgb('graphics/2MASS_arcsinh_color.png')

gc.tick_labels.set_font(size='small')

gc.show_contour('fits/mips_24micron.fits', colors='white')

ra, dec = numpy.loadtxt('data/yso_wcs_only.txt', unpack=True)

gc.show_markers(
  ra,
  dec,
  layer='marker_set_1',
  edgecolor='red',
  facecolor='none',
  marker='o',
  s=10,
  alpha=0.5)

gc.save('myfirstplot.png')
