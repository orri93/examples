# Introduction to the QGraphics framework
# https://www.pythonguis.com/tutorials/pyqt-qgraphics-vector-graphics/

#
# A simple scene
#

import sys
from PyQt5.QtWidgets import QGraphicsScene, QGraphicsView, QApplication

app = QApplication(sys.argv)

# Defining a scene rect of 400x200, with it's origin at 0,0.
# If we don't set this on creation, we can set it later with .setSceneRect
scene = QGraphicsScene(0, 0, 400, 200)

view = QGraphicsView(scene)
view.show()
app.exec_()
