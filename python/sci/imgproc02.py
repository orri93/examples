# AplPy Beginner Tutorial
# https://aplpy.readthedocs.io/en/stable/fitsfigure/quickstart.html

import aplpy

gc = aplpy.FITSFigure('test.fits')
gc.show_grayscale()
gc.save('test.png')
