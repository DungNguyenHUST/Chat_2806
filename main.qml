import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick 2.0
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480

   Rectangle
   {
       id : title
       width : 640
       height : 48
       x:0
       y:0
       color : "#0084ff"
       anchors.fill: parent.top
       Text
       {
           id: name
           text: qsTr("Chat Example")
           font.italic: true
           font.pointSize: 20
           anchors.centerIn: parent
       }
   }
   // inbox rect
   Rectangle
   {
       id : inbox
       width: 640
       height: 336
       x:0
       y:48
       color: "#e6f3e6"
       anchors.fill:parent.top
       ListModel
       {
           id : messageModel
           ListElement
           {
               message : qsTr("Press Enter to send your message")
           }
       }
       Component
       {
           id:messageDelegate
           Row
           {
               spacing: 12
               Text
               {
                   text:message
                   wrapMode: Text.WordWrap
                   width: parent-10
               }
               width :parent.width
           }
       }

       ListView
       {
           x: parent
           y: parent/2
           id:messageView
           anchors.fill:parent
           model:messageModel
           delegate: messageDelegate
       }
   }
   Connections
   {
       target: chat
       onSendToQml:
       {
           messageModel.append({username:username,message:message,time:time});
       }
   }

     Rectangle
       {
           id : edit_text
           width: 640
           height : 48
           color: "#f0f9f6"
           x:0
           y:384
           anchors.fill: parent.top
           TextInput
           {
             id : displayText
             text : "Write your message in here"
             cursorVisible: true
             focus : true
             Keys.onReturnPressed:
             {
                 if (this.text != "")
                 {
                     chat.receiveFromQml(this.text);
                     console.log(this.text);
                     this.text ="";
                 }
             }

           }
           Button
           {
               text : "Send"
               anchors.right: parent.right
               width : 66
               height : 48
           }
       }

   Rectangle
   {
       id : slidebar
       width : 640
       height : 48
       color: "#8fc3d3"
       x:0
       y:432
       anchors.fill : parent.top


           Button
           {
               text : "Chat"
              x:250
              y:12
              onClicked:about.visible =! about.visible

           }
           Button
           {
               text : "About"
               x:320
               y:12
               onClicked: about.visible =! about.visible
           }

   }
   // about screen
   Rectangle
   {
       id : about
       visible: false
       width :640
       height:432
       x:0
       y:0
       Image {
           id: logo_LG
           source: "qrc:/../Downloads/lg-logo-300x300.png"
           width : 300
           height :300
           x:180
           y:80
       }
       Text
       {
           text: qsTr(" LG Number One!"+" \n IVI VietNam Development Center ")
           horizontalAlignment: Text.AlignHCenter
           font.pointSize: 16
           x : 140
           y : 30
       }
       Text
       {
           text: qsTr("(this application is used for tranning purpose )")
           horizontalAlignment: Text.AlignHCenter
           font.pointSize: 12

           x:135
           y :80

       }
    }
}
