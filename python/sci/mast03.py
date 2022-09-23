# Astrology MAST Queries
# This module can be used to query the Barbara A. Mikulski Archive for Space Telescopes (MAST).
# https://astroquery.readthedocs.io/en/latest/mast/mast.html

from astroquery.mast import Observations

# Getting Observation Counts
# To get the number of observations and not the observations themselves,
# query_counts functions are available. 

print(Observations.query_region_count("322.49324 12.16683"))

print(Observations.query_object_count("M8",radius=".02 deg"))

print(Observations.query_criteria_count(
  dataproduct_type="image",
  filters=["NUV","FUV"],
  t_max=[52264.4586,54452.8914]))
