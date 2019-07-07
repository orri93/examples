import QtQuick 2.0

Rectangle {
  property string myText: "The quick brown fox jumps over the lazy dog."

  width: 320; height: 480
  color: "steelblue"

  FontLoader { id: digitalFont; source: "fonts/digital-7.ttf"}

  Column {
    anchors { fill: parent; leftMargin: 10; rightMargin: 10; topMargin: 10 }
    spacing: 15
    Text {
      text: myText
      color: "lightsteelblue"
      width: parent.width
      wrapMode: Text.WordWrap
      font {
        family: digitalFont.name;
        pixelSize: 20;
        capitalization: Font.Capitalize
      }
    }
  }
}
