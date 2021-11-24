import websocket
import _thread
import time

def ws_message(ws, message):
  print("WebSocket message: %s" % message)

def ws_open(ws):
  print("WebSocket Opened sending message")
  ws.send('{"name": "Orri"}')

ws = websocket.WebSocketApp("ws://localhost:8080/gs-guide-websocket/903/kyr3jqge/websocket", on_open = ws_open, on_message = ws_message)

def ws_thread(*args):
  print("The WebSocket Thread")
  ws.run_forever()

print("Starting the WebSocket Thread")
wst = _thread.start_new_thread(ws_thread, ())

print("Waiting")
time.sleep(5)

print("Closing the WebSocket connection")
ws.close()
