import numpy as np
import sounddevice as sd
from util import (
  list_input_devices,
  list_output_devices,
  record_audio,
  AudioPlayer,
)

COMMON_SR = [8000, 16000, 22050, 24000, 32000, 44100, 48000, 96000]


def choose_device(devices: list[tuple[int, str]], kind: str) -> int:
  print(f"Available {kind} devices (deduplicated):")
  for idx, name in devices:
    print(f"  [{idx}] {name}")
  while True:
    choice = input(f"Select {kind} device index: ")
    try:
      i = int(choice)
      if any(i == idx for idx, _ in devices):
        return i
    except ValueError:
      pass
    print("Invalid choice, try again.")


def choose_samplerate(device: int) -> float:
  default_sr = int(sd.query_devices(device, 'input')['default_samplerate'])
  options = [default_sr] + [sr for sr in COMMON_SR if sr != default_sr]
  print("Available sample rates (Hz):")
  for sr in options:
    print(f"  {sr}")
  while True:
    choice = input(f"Select sample rate (default {default_sr}): ") or str(default_sr)
    try:
      sr = float(choice)
      # check if supported
      sd.check_input_settings(device=device, samplerate=sr, channels=1)
      return sr
    except Exception as e:
      print(f"Invalid rate or unsupported: {e}")
      print("Please choose a different sample rate.")


def main():
  # Select devices
  in_dev = choose_device(list_input_devices(), "input")
  out_dev = choose_device(list_output_devices(), "output")
  # Select samplerate
  sr = choose_samplerate(in_dev)

  print(f"\nRecording at {int(sr)} Hz...")
  audio = record_audio(device=in_dev, samplerate=sr)

  if audio.size == 0:
    print("No audio captured.")
    return

  # Convert float32 [-1,1] to int16
  int_audio = np.clip(audio * 32767, -32768, 32767).astype(np.int16)

  print("Playing back recorded audio...")
  with AudioPlayer(device=out_dev, samplerate=sr) as player:
    player.add_audio(int_audio)

  print("Done.")

if __name__ == '__main__':
  main()
