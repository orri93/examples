# Astrology MAST Queries
# This module can be used to query the Barbara A. Mikulski Archive for Space Telescopes (MAST).
# https://astroquery.readthedocs.io/en/latest/mast/mast.html

from astroquery.mast import Observations

# Observation Criteria Queries
# To search for observations based on parameters other than position or target name,
# use query_criteria. 

obs_table = Observations.query_criteria(
  dataproduct_type=["image"],
  proposal_pi="Osten*",
  s_dec=[43.5,45.5])
print(obs_table)

obs_table = Observations.query_criteria(
  filters=["*UV","Kepler"],
  objectname="M101")
print(obs_table)  
