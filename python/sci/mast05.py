# Astrology MAST Queries
# This module can be used to query the Barbara A. Mikulski Archive for Space Telescopes (MAST).
# https://astroquery.readthedocs.io/en/latest/mast/mast.html

from astroquery.mast import Observations

# Downloading Data

# Getting Product Lists
# Each observation returned from a MAST query can have one or more associated data products.
obs_table = Observations.query_object("M8",radius=".02 deg")
data_products_by_obs = Observations.get_product_list(obs_table[0:2])
print(data_products_by_obs)

obsids = obs_table[0:2]['obsid']
data_products_by_id = Observations.get_product_list(obsids)
print(data_products_by_id)

print((data_products_by_obs == data_products_by_id).all())


# Filtering
# Filter keyword arguments can be applied to download only data products that meet the given criteria.
Observations.download_products(
  '25119363',
  productType=["SCIENCE", "PREVIEW"],
  extension="fits")
