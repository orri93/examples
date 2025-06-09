from langchain_openai import ChatOpenAI
from langchain.chains import LLMChain
from langchain.prompts import PromptTemplate
from dotenv import load_dotenv
import os

# Load environment variables from .env file
load_dotenv()
openai_api_key = os.getenv("OPENAI_API_KEY")

# Initialize the OpenAI Chat model using LangChain's new integration
llm = ChatOpenAI(
    model="gpt-4o", 
    temperature=0.7,
    api_key=openai_api_key,
    max_tokens=150
)

# Define a simple prompt for the agent
prompt_template = """
You are an AI assistant with expertise in data analysis and automation. Answer the following question:
Question: {question}
"""

# Setup the prompt and LLM chain
prompt = PromptTemplate(input_variables=["question"], template=prompt_template)
chain = LLMChain(llm=llm, prompt=prompt)

# Example usage of the AI agent
query = "What is the impact of AI in healthcare?"
response = chain.run(question=query)
print("AI Agent Response:", response)
