# Functions example
# This example demonstrates how to create a simple agent that uses a function tool to get the weather in a specified city.

# import httpx
import asyncio
# from openai import AsyncOpenAI
from agents import Agent, Runner, function_tool, set_default_openai_client

@function_tool
def get_weather(city: str) -> str:
  return f"The weather in {city} is sunny."

# Create a custom AsyncOpenAI client with SSL verification disabled
# custom_client = AsyncOpenAI(http_client=httpx.AsyncClient(verify=False))
# set_default_openai_client(custom_client)

agent = Agent(
  name="Hello world",
  instructions="You are a helpful agent.",
  tools=[get_weather],
)

async def main():
  result = await Runner.run(agent, input="What's the weather in Tokyo?")
  print(result.final_output)
  # The weather in Tokyo is sunny.

if __name__ == "__main__":
  asyncio.run(main())
