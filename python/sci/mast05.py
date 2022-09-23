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

# Product filtering can also be applied directly to a table of products without proceeding to the download step.
data_products = Observations.get_product_list('25588063')
print(len(data_products))
products = Observations.filter_products(
  data_products,
  productType=["SCIENCE", "PREVIEW"],
  extension="fits")
print(len(products))


# Downloading Data Products
# Products can be downloaded by using download_products,
# with a Table of data products,
# or a list (or single) obsid as the argument.
single_obs = Observations.query_criteria(obs_collection="IUE", obs_id="lwp13058")
data_products = Observations.get_product_list(single_obs)
manifest = Observations.download_products(data_products, productType="SCIENCE")
print(manifest)

# As an alternative to downloading the data files now,
# the curl_flag can be used instead to instead get
# a curl script that can be used to download
# the files at a later time.
single_obs = Observations.query_criteria(obs_collection="IUE", obs_id="lwp13058")
data_products = Observations.get_product_list(single_obs)
table = Observations.download_products(data_products, productType="SCIENCE", curl_flag=True)   


# Downloading a Single File
# You can download a single data product file using
# the download_file method, and passing in a MAST Data URI.
single_obs = Observations.query_criteria(obs_collection="IUE",obs_id="lwp13058")
data_products = Observations.get_product_list(single_obs)
product = data_products[0]["dataURI"]
print(product)
result = Observations.download_file(product)
print(result)
