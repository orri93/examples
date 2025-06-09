from langchain_openai import ChatOpenAI
from langchain.prompts import PromptTemplate
from dotenv import load_dotenv
import os

# Load environment variables from .env file
load_dotenv()
openai_api_key = os.getenv("OPENAI_API_KEY")

# Initialize the OpenAI Chat model
llm = ChatOpenAI(
    model="gpt-4o",
    temperature=0.7,
    api_key=openai_api_key,
    max_tokens=150
)

# Define a prompt template
prompt_template = PromptTemplate(
    input_variables=["question"],
    template="""
You are an AI assistant with expertise in data analysis and automation. Answer the following question:
Question: {question}
"""
)

# Create a runnable chain using LangChain Expression Language (pipe-style)
chain = prompt_template | llm

# Example usage
query = "What is the impact of AI in healthcare?"
response = chain.invoke({"question": query})

print("AI Agent Response:", response.content)
