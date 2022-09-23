# Astrology MAST Queries
# This module can be used to query the Barbara A. Mikulski Archive for Space Telescopes (MAST).
# https://astroquery.readthedocs.io/en/latest/mast/mast.html

from astroquery.mast import Observations

# Metadata Queries

# To list data missions archived by MAST and avaiable through astroquery.mast,
# use the list_missions function.
print(Observations.list_missions())

# To get a table of metadata associated with observation or product lists use
# the get_metadata function.
meta_table = Observations.get_metadata("observations")
print(meta_table[:5])  

meta_table = Observations.get_metadata("products")
print(meta_table[:3])  
