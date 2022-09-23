# Astrology MAST Queries
# This module can be used to query the Barbara A. Mikulski Archive for Space Telescopes (MAST).
# https://astroquery.readthedocs.io/en/latest/mast/mast.html

from astroquery.mast import Observations

# Positional queries can be based on a sky position or a target name.
# The observation fields are documented here:
# https://mast.stsci.edu/api/v0/_c_a_o_mfields.html
obs_table = Observations.query_region("322.49324 12.16683")
print(obs_table[:10])

# Radius is an optional parameter and the default is 0.2 degrees.
obs_table = Observations.query_object("M8",radius=".02 deg")
print(obs_table[:10])
