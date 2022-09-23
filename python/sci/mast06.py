# Astrology MAST Queries
# This module can be used to query the Barbara A. Mikulski Archive for Space Telescopes (MAST).
# https://astroquery.readthedocs.io/en/latest/mast/mast.html

import os
from astroquery.mast import Observations

# Cloud Data Access
# Public datasets from the Hubble, Kepler and TESS telescopes
# are also available for free on Amazon Web Services in public S3 buckets.

# Getting a list of S3 URIs:
# Simply call the `enable_cloud_dataset` method from `Observations`. The default provider is `AWS`, but we will write it in manually for this example:
Observations.enable_cloud_dataset(provider='AWS')

# Getting the cloud URIs
obs_table = Observations.query_criteria(
  obs_collection='HST',
  filters='F606W',
  instrument_name='ACS/WFC',
  proposal_id=['12062'],
  dataRights='PUBLIC')
products = Observations.get_product_list(obs_table)
filtered = Observations.filter_products(
  products,
  productSubGroupDescription='DRZ')
s3_uris = Observations.get_cloud_uris(filtered)
print(s3_uris)

# Downloading from the cloud
obs_table = Observations.query_criteria(
  obs_collection=['Kepler'],
  objectname="Kepler 12b",
  radius=0)
products = Observations.get_product_list(obs_table[0])
manifest = Observations.download_products(
  products[:10],
  cloud_only=True)
print(manifest["Status"])

Observations.disable_cloud_dataset()
