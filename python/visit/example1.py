OpenDatabase("localhost:C:\\Users\\SigurdssonGO\\Documents\\tutorial_data\\example.silo", 0)
# Clear any previous plots
DeleteAllPlots()

# Create a plot of the scalar field 'temp'
AddPlot("Pseudocolor", "temp")
AddPlot("Mesh", "Mesh")
DrawPlots()
