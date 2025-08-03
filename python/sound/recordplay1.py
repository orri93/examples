import numpy as np
import sounddevice as sd
from util import (
  list_input_devices,
  list_output_devices,
  record_audio,
  AudioPlayer,
)


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


def main():
  # List and select devices
  input_devices = list_input_devices()
  output_devices = list_output_devices()
  in_dev = choose_device(input_devices, "input")
  out_dev = choose_device(output_devices, "output")

  print("\nReady to record. Follow on-screen instructions...")
  audio = record_audio(device=in_dev)

  if audio.size == 0:
    print("No audio captured.")
    return

  # Convert float32 [-1,1] to int16
  int_audio = np.clip(audio * 32767, -32768, 32767).astype(np.int16)

  print("Playing back recorded audio...")
  with AudioPlayer(device=out_dev) as player:
    player.add_audio(int_audio)

  print("Done.")

if __name__ == '__main__':
  main()
