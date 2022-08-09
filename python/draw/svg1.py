# Creating vector graphics with Python
# https://blog.damavis.com/en/creating-vector-graphics-with-python

import pandas as pd
import pygal

data = pd.read_csv("https://www2.cs.arizona.edu/classes/cs120/fall17/ASSIGNMENTS/assg02/Pokemon.csv")
# data.head()


# Pie Chart
pie_chart = pygal.Pie()
pie_chart.title = 'Pokemon by Generation'
for id, row in data.groupby(["Generation"]).size().reset_index().iterrows():
  pie_chart.add("Generation %s" % row["Generation"], row[0])
pie_chart.render_to_file('pie_chart_by_generation.svg')


# Box plots
for this_attribute in ["HP", "Attack", "Defense"]:
  box_plot = pygal.Box(box_mode="tukey")
  box_plot.title = 'Pokemon Attribute: %s' % this_attribute

  for this_type in data["Type 1"].unique():
    box_plot.add(this_type, data[data["Type 1"]==this_type]["HP"].values)
  
  box_plot.render_to_file('box_plot_attribute_%s.svg' % this_attribute)


# Radar plots
x_labels = ['HP', 'Attack', 'Defense', 'Sp. Atk', 'Sp. Def', 'Speed']

radar_chart = pygal.Radar(width=600, height=500)
radar_chart.title = 'Pokemon Attributes'
radar_chart.x_labels = x_labels
radar_chart.add('Bulbasaur', data[data["Name"]=="Bulbasaur"][x_labels].values[0])
radar_chart.render_to_file('radar_plot_attribute_Bulbasaur.svg') 
# display(SVG('radar_plot_attribute_Bulbasaur.svg'))


# Dot charts
x_labels = ['HP', 'Attack', 'Defense', 'Sp. Atk', 'Sp. Def', 'Speed']
dot_chart = pygal.Dot(x_label_rotation=30, width=600, height=600)
dot_chart.title = 'Pokemon attributes by Type'
dot_chart.x_labels = x_labels
for id, row in data.groupby(["Type 1"])[x_labels].mean().reset_index().iterrows():
  dot_chart.add(row["Type 1"], row[x_labels])

dot_chart.render_to_file('dot_chart_attribute_by_type.svg')


# Gauges
pokemon_names = ["Pikachu", "Dragonite"]
x_labels = ['HP', 'Attack', 'Defense', 'Sp. Atk', 'Sp. Def', 'Speed']

for pokemon_name in pokemon_names:
  this_pokemon = data[data["Name"]==pokemon_name]

  gauge = pygal.SolidGauge(inner_radius=0.70)
  gauge.title = '%s stats vs others Pokemon' % pokemon_name
  for this_label in x_labels:
    gauge.add(this_label, [{'value': this_pokemon[this_label].values[0], 'max_value': data[this_label].max()}])

  gauge.render_to_file('gauge_%s_vs_all.svg' % pokemon_name)
