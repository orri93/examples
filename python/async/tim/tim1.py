# Built into python
import asyncio

"""
COROUTINES
Coroutines are computer program components that generalize subroutines for
non-preemptive multitasking, by allowing execution to be suspended and resumed
https://en.wikipedia.org/wiki/Coroutine
"""

"""
ASYNC EVENT-LOOP
In computer science, the event loop is a programming construct or
design pattern that waits for and dispatches events or messages in a program.
https://en.wikipedia.org/wiki/Event_loop
"""

# Defined as a coroutine
async def main():
  print('tim')
  await foo('text')
  print('finished')

async def foo(text):
  print(text)
  await asyncio.sleep(1)

mainco = main()     # main returns a coroutine
asyncio.run(mainco) # executes the coroutine
