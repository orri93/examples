# Image processing with Python and SciPy
# https://prancer.physics.louisville.edu/astrowiki/index.php/Image_processing_with_Python_and_SciPy

import astropy.io.fits as pyfits

img = pyfits.getdata('test.fits')
print('Size: ', img.size)
print('Shape: ', img.shape)
