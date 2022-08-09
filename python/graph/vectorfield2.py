# How to plot a simple vector field in Matplotlib
# https://www.geeksforgeeks.org/how-to-plot-a-simple-vector-field-in-matplotlib/

#
# Generating multiple vectors using quiver() method.
#

# Import libraries
import numpy as np
import matplotlib.pyplot as plt

# Meshgrid
x, y = np.meshgrid(np.linspace(-5, 5, 10), np.linspace(-5, 5, 10))

# Directional vectors
u = -y/np.sqrt(x**2 + y**2)
v = x/(x**2 + y**2)

# Plotting Vector Field with QUIVER
plt.quiver(x, y, u, v, color='g')
plt.title('Vector Field')

# Setting x, y boundary limits
plt.xlim(-7, 7)
plt.ylim(-7, 7)

# Show plot with grid
plt.grid()
plt.show()
