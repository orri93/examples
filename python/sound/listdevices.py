import sounddevice as sd

devices = sd.query_devices()

print("i\tindex\tinput\toutput\tsamplerate\thostapi: name")
for i, d in enumerate(devices):
  name = d['name']
  hostapi = d['hostapi']
  index = d['index']
  max_input_channels = d['max_input_channels']
  max_output_channels = d['max_output_channels']
  default_samplerate = d['default_samplerate']
  hostapi_name = sd.query_hostapis(hostapi)['name']
  print(f"{i}\t{index}\t{max_input_channels}\t{max_output_channels}\t{default_samplerate}\t\t{hostapi_name}: {name}")