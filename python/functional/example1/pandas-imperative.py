import pandas_datareader as pdr
import pandas_datareader.wb
import requests

session = requests.Session()
# session.verify = False # SSL Verification turned OFF

df = pdr.wb.download(indicator="SP.POP.TOTL", country="all", start=2000, end=2020, session=session)
df = df.reset_index()
df = df.filter(["country", "SP.POP.TOTL"])
groups = df.groupby("country")
df = groups.mean()

print(df)
