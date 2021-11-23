import requests

# See https://www.nylas.com/blog/use-python-requests-module-rest-apis/

try:
  response = requests.get("http://wbc_config_service:3000/portal-data/tag-query?task=get_units")
  print(response)
  print(response.ok)
  print(response.status_code)
  jr = response.json()
  # print(jr)
except requests.exceptions.HTTPError as error:
  print (error)
