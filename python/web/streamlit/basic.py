import streamlit as st
import pandas as pd
import numpy as np

st.title('Hello Streamlit!')

# User input widgets
name = st.text_input('What is your name?')
fav_num = st.number_input('Favorite number', min_value=0, max_value=100, value=7)

# Greet user
if name:
  st.write(f'Hi, {name}! Your favorite number is {fav_num}.')

# Show a simple chart
data = pd.DataFrame(
  np.random.randn(20, 3),
  columns=['a', 'b', 'c']
)
st.line_chart(data)

# Checkbox example
if st.checkbox('Show raw data'):
  st.write(data)
