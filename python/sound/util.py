import curses
import time
import numpy as np
import numpy.typing as npt
import sounddevice as sd
from typing import Optional


def list_input_devices() -> list[tuple[int, str]]:
  """
  Return a list of (index, name) for all available input devices, deduplicated by name.
  """
  devices = sd.query_devices()
  seen = set()
  result: list[tuple[int, str]] = []
  for i, d in enumerate(devices):
    name = d['name']
    if d['max_input_channels'] > 0 and name not in seen:
      seen.add(name)
      result.append((i, name))
  return result


def list_output_devices() -> list[tuple[int, str]]:
  """
  Return a list of (index, name) for all available output devices, deduplicated by name.
  """
  devices = sd.query_devices()
  seen = set()
  result: list[tuple[int, str]] = []
  for i, d in enumerate(devices):
    name = d['name']
    if d['max_output_channels'] > 0 and name not in seen:
      seen.add(name)
      result.append((i, name))
  return result


def _record_audio(screen: curses.window, device: int) -> npt.NDArray[np.float32]:
  """
  Internal curses-based recording. Press space to start/stop.
  """
  recording = False
  audio_buffer: list[npt.NDArray[np.float32]] = []

  def _audio_callback(indata, frames, time_info, status):
    if status:
      screen.addstr(f"Status: {status}\n")
      screen.refresh()
    if recording:
      audio_buffer.append(indata.copy())

  screen.nodelay(True)
  screen.clear()
  screen.addstr(
    "Press <spacebar> to start recording. Press <spacebar> again to stop recording.\n"
  )
  screen.refresh()

  with sd.InputStream(device=device, samplerate=24000, channels=1, dtype=np.float32, callback=_audio_callback):
    while True:
      key = screen.getch()
      if key == ord(' '):
        recording = not recording
        if recording:
          screen.addstr("Recording started...\n")
        else:
          screen.addstr("Recording stopped.\n")
          screen.refresh()
          break
        screen.refresh()
      time.sleep(0.05)

  if audio_buffer:
    return np.concatenate(audio_buffer, axis=0)
  else:
    return np.empty((0,), dtype=np.float32)


def record_audio(device: int) -> npt.NDArray[np.float32]:
  """
  Wrapper for curses recording. Returns recorded float32 audio.
  """
  return curses.wrapper(lambda scr: _record_audio(scr, device))


class AudioPlayer:
  """
  Context manager for playback.
  Usage:
    with AudioPlayer(device=<index>) as player:
      player.add_audio(data)
  """
  def __init__(self, device: Optional[int] = None):
    self.device = device
    self.stream: sd.OutputStream

  def __enter__(self):
    self.stream = sd.OutputStream(
      device=self.device,
      samplerate=24000,
      channels=1,
      dtype=np.int16,
      blocksize=1024
    )
    self.stream.start()
    return self

  def add_audio(self, audio_data: npt.NDArray[np.int16]):
    """
    Write int16 audio data to the stream.
    """
    self.stream.write(audio_data)

  def __exit__(self, exc_type, exc_value, traceback):
    self.stream.stop()
    self.stream.close()
