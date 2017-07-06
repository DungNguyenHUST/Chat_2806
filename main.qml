import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick 2.2
import QtQuick.Dialogs 1.1

Window {
    visible: true
    width: 640
    height: 480
    // edit nick name screen
    Item
    {
    id : editNickname
    width : parent
    height: parent
    Text
    {
        text : "Input your Nickname. Press OK to continue"
        font.pointSize: 12
        x: 150
        y: 200
    }
    TextField
    {
        x : 120
        y : 230
        placeholderText: "Write your nick name in here"
        width: 320
        height : 50
        font.pointSize: 12
        id : nickName
        color: "gray"
        horizontalAlignment: Text.AlignHCenter
        cursorVisible: true
        focus : true
    }
    // send
    Button
    {
        text : "OK"
        x: 440
        y: 230
        width : 80
        height : 50
        onClicked:
        {
            chatMain.loadDataFromSQL("load data")
            chatWindow.visible =! chatWindow.visible
            editNickname.visible =! editNickname.visible
            if (nickName.text != "")
            {
               chatMain.receiveUserNameFromQml(nickName.text);
                console.log(nickName.text);
            }
        }
    }
    }
Rectangle
{
    id : chatWindow
    visible:  false
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
       height: 300
       x:0
       y:60
       color: "#ffffff"
       anchors.fill:parent.top
       ListModel
       {
           id : messageModel
           ListElement
           {
               message : qsTr("Press Enter or click Send button to send your message")
           }
       }
       Component
       {
           id:messageDelegate
           Row
           {
               spacing: 10
               Text
               {
                   text:message
                   font.pointSize: 9.5
                   wrapMode: Text.WordWrap
                   width: parent -10
               }
               width :parent.width
           }
       }
       ListView
       {
          id:messageView
           x: parent
           y: parent/2
           anchors.fill:parent
           model:messageModel
           delegate: messageDelegate
           onCountChanged:
           {
               messageView.positionViewAtEnd()
           }
       }
   }
   Connections
   {
       target: chatMain
       onSendDataToQml:
       {
           messageModel.append({message:data});
       }
   }
     Rectangle
       {
           id : edit_text
           width: 640
           height : 48
           color: "#f2f9f7"
           x:0
           y:384
           anchors.fill: parent.top
           TextField
           {
             id : displayText
             placeholderText: "Write your message in here"
             width: 640 -80
             height: 48
             font.pointSize: 10
             cursorVisible: true
             focus : true
             autoScroll: true
             activeFocusOnPress: true
             Keys.onReturnPressed:
             {
                 if (this.text != "")
                 {
                     chatMain.receiveMessageFromQml(this.text);
                     console.log(this.text);
                     displayText.clear();
                 }
             }
           }
           Button
           {
               id: sendButton
               text : "Send"
               anchors.right: parent.right
               width : 80
               height : 48
               onClicked:
               {
                   if (displayText.text != "")
                   {
                       chatMain.receiveMessageFromQml(displayText.text);
                       console.log(displayText.text);
                       displayText.clear();
                   }
               }
           }
       }

   Rectangle
   {
       id : slidebar
       width : 640
       height : 48
       color: "#2e96ca"
       x:0
       y:432
       anchors.fill : parent.top
           ToolBar
           {
               anchors.centerIn: parent

               Row{
               TabButton
               {
                   id:chatButton
                   text :"Chat"
                   width: 100
                   height: 40
                   enabled: false
                   onClicked:
                   {
                       about.visible =! about.visible
                       chatButton.enabled= false
                       aboutButton.enabled=true
                   }

               }
               TabButton
               {
                   id:aboutButton
                   text: "About"
                   width: 100
                   height: 40
                   enabled: true
                   onClicked:
                   {
                       about.visible =! about.visible
                       aboutButton.enabled=false
                       chatButton.enabled=true
                   }
               }
              }
           }
   }
   // about screen
   Rectangle
   {
       id : about
       visible: false
       width :640
       height:432
       color: "#f9f9f9"
       x:0
       y:0
       AnimatedImage {
           id: logo_LG
           source: "qrc:/../Downloads/LG1.gif"
           width : 320
           height :180
           x:160
           y:150
       }
       Text
       {
           text: qsTr(" LG Number One !!!"+" \n IVI VietNam Development Center ")
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
       Rectangle
       {
           x: 147
           y: 308
           width: 342
           height: 31
           color: "#f9f9f9"
       }

       Rectangle {
           x: 101
           y: 140
           width: 80
           height: 199
           color: "#f9f9f9"
       }

       Rectangle {
           x: 138
           y: 128
           width: 342
           height: 31
           color: "#f9f9f9"
       }

       Rectangle {
           x: 457
           y: 141
           width: 80
           height: 199
           color: "#f9f9f9"
       }
    }
  }
}
