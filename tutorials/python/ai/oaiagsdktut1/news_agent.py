from agents import Agent, Runner, WebSearchTool

agent = Agent(
    name="News Agent",
    instructions="You are a news agent that can search the web for the latest news on a given topic. " +
                 "Compile the information you find into a concise summary. No markdown, just plain text.",
    tools=[WebSearchTool()],
    model="o4-mini"
)

while True:
  query = input("Enter your news query (or type 'exit' to quit): ")
  if query.lower() == 'exit':
    break

  result = Runner.run_sync(agent, input=query)
  print("\nResult:")
  print(result.final_output)
  print("\n" + "-" * 80 + "\n")