import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
//import QtQuick.Controls 1.4


Window {
    id: window
    width: 900
    height: 700
    visible: true
    title: qsTr("Hello World")

    minimumHeight: 700
    minimumWidth: 900

    property color primaryColor: "#ffd52e"
    property color pressedPrimaryColor: "#e6bb10"
    property color gray: "#736c6c"
    property color dangerColor: "#e65069"
    property color greenColor: "#90fc03"

    property bool isGuiVisible: false
    property bool isLoginPageVisible: true


    component PrimaryButton: Button {
        id: button
        property alias color: background.color
        property alias impWidth: background.implicitWidth
        font.pixelSize: 14

        contentItem: Text {
            text: button.text
            font: button.font
            opacity: enabled ? 1.0 : 0.3
            color: button.down ? "#17a81a" : "#FFFFFF"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            id: background
            implicitWidth: 170
            implicitHeight: 40
            color: button.pressed ? pressedPrimaryColor : primaryColor
            opacity: enabled ? 1 : 0.3
            //border.width: 1
            radius: 2

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                acceptedButtons: Qt.NoButton
            }
        }

        DropShadow {
            anchors.fill: background
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8.0
            samples: 17
            color: "#80000000"
            source: background
        }

    }

    DropShadow {
        visible: loginPage.visible
        anchors.fill: loginPage
        horizontalOffset: 3
        verticalOffset: 3
        radius: 8.0
        //samples: 17
        color: "#80000000"
        source: loginPage
    }

    Rectangle {
        id: loginPage

        property bool successFullLogin: false

        visible: isLoginPageVisible
        anchors.centerIn: parent
        width: 400
        height: 300
        border.width: 1
        border.color: gray
        radius: 3

        ColumnLayout {
            visible: parent.visible
            anchors {
                margins: 20
                left: parent.left
                right: parent.right
                top: parent.top
            }

            Label {
                Layout.alignment: Qt.AlignHCenter
                font.pixelSize: 30
                text: qsTr("Authorization")
            }

            TextField {
                id: username
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                Layout.topMargin: 20
                Layout.alignment: Qt.AlignCenter | Qt.AlignTop
                placeholderText: qsTr("username")
            }

            TextField {
                id: password
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                Layout.topMargin: 10
                Layout.alignment: Qt.AlignCenter | Qt.AlignTop
                placeholderText: qsTr("password")
            }

            RowLayout {
                Layout.fillWidth: true
                Layout.topMargin: 20
                PrimaryButton {
                    id: loginButton
                    Layout.fillWidth: true
                    text: qsTr("Log In")
                    color: greenColor
                    onClicked: {
                       loginPage.successFullLogin = viewModel.dataBaseViewModel.login(username.text, password.text);
                        if (loginPage.successFullLogin) {
                            isLoginPageVisible = false
                            isGuiVisible = true
                            updateColumnLabels()
                            updateTable()
                            updateTables()
                            databases.model = viewModel.dataBaseViewModel.databaseNames().length
                        } else {
                            wrongInput.visible = true
                        }
                    }
                }

                PrimaryButton {
                    id: helpButton
                    Layout.fillWidth: true
                    text: qsTr("Help")
                    onClicked: {
                       loginPage.successFullLogin = viewModel.dataBaseViewModel.login("postgres", "root");
                        if (loginPage.successFullLogin) {
                            isLoginPageVisible = false
                            isGuiVisible = true
                            updateColumnLabels()
                            updateTable()
                            updateTables()
                            databases.model = viewModel.dataBaseViewModel.databaseNames().length
                        } else {
                            wrongInput.visible = true
                        }
                    }
                }
            }

            Label {
                id: wrongInput
                Layout.topMargin: 10
                visible: false
                Layout.alignment: Qt.AlignHCenter
                font.pixelSize: 20
                color: dangerColor
                text: qsTr("Wrong input")
            }

        }
    }

    ColumnLayout {
        visible: isGuiVisible
        anchors.fill: parent
        anchors.margins: 20
        spacing: 10

        Text {
            Layout.alignment: Qt.AlignCenter
            font.pixelSize: 22
            text: qsTr("Databases")
            horizontalAlignment: Qt.AlignCenter
        }

        Flickable {
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            interactive: implicitWidth < contentWidth
            contentHeight: 40
            contentWidth: rowDbs.width
            Row {
                id: rowDbs
                //anchors.fill: parent
                //Layout.fillWidth: true
                //Layout.preferredHeight: 40
                spacing: 8

                Repeater {
                    id: databases
                    model: viewModel.dataBaseViewModel.databaseNames().length
                    property int currentIndex: 0

                    delegate: PrimaryButton {
                        text: viewModel.dataBaseViewModel.databaseNames()[index]
                        color: index === databases.currentIndex ? "#80000000" : primaryColor

                        onClicked: {
                            databases.currentIndex = index
                            viewModel.dataBaseViewModel.setDatabase(this.text)
                            console.log("new headers:" + viewModel.dataBaseViewModel.headers())

                            updateColumnLabels();
                            updateTables()
                        }
                    }
                }
            }
        }

        Text {
            Layout.alignment: Qt.AlignCenter
            font.pixelSize: 22
            text: qsTr("Tables")
            horizontalAlignment: Qt.AlignCenter
        }

        Flickable {
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            interactive: implicitWidth < contentWidth
            contentHeight: 40
            contentWidth: tablesRow.width
            RowLayout {
                id: tablesRow
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                spacing: 8

                Repeater {
                    id: tables
                    model: viewModel.dataBaseViewModel.tableNames().length
                    property int currentIndex: 0

                    onModelChanged: currentIndex = 0

                    delegate: PrimaryButton {
                        text: viewModel.dataBaseViewModel.tableNames()[index]
                        color: index === tables.currentIndex ? "#80000000" : primaryColor

                        onClicked: {
                            tables.currentIndex = index
                            viewModel.dataBaseViewModel.setTable(this.text)
                            console.log("new headers:" + viewModel.dataBaseViewModel.headers())
                            updateColumnLabels();
                        }
                    }
                }
            }
        }

        TableView {
            id: tableView

            property int selectedRow;
            property int selectedColumn;

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 100
            Layout.maximumHeight: 400
            topMargin: columnsHeader.implicitHeight

            clip: true

            model: viewModel.dataBaseViewModel.table()

            columnWidthProvider: function (column) { return 140; }
            rowHeightProvider: function (column) { return 60; }

            Row {
                id: columnsHeader
                y: tableView.contentY
                z: 2
                Repeater {
                    id: columnLabels
                    model: viewModel.dataBaseViewModel.headers().length
                    Label {
                        width: tableView.columnWidthProvider(modelData)
                        height: 35
                        text: viewModel.dataBaseViewModel.headers()[index]
                        color: '#aaaaaa'
                        font.pixelSize: 15
                        padding: 10
                        verticalAlignment: Text.AlignVCenter

                        background: Rectangle { color: "#333333" }
                    }
                }
            }

            delegate: Rectangle {
                property bool isSelected: row === tableView.selectedRow && column === tableView.selectedColumn
                color: {
                    if (isSelected)
                        return "blue"
                    if (display === "")
                        return window.gray
                    return "white"
                }

                Text {
                    text: display
                    anchors.fill: parent
                    anchors.margins: 10
                    color: isSelected ? 'white' : 'black'
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WrapAnywhere
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("clicked " + row + ":" + column)
                        tableView.selectedRow = row
                        tableView.selectedColumn = column
                    }
                    cursorShape: Qt.PointingHandCursor
                }
            }
        }

        Text {
            Layout.alignment: Qt.AlignCenter
            font.pixelSize: 30
            text: qsTr("Available actions")
            horizontalAlignment: Qt.AlignCenter
        }

        RowLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            spacing: 20
            ColumnLayout {
                id: leftSideActions
                Layout.fillHeight: true
                Layout.fillWidth: true
                spacing: 25

                Text {
                    font.pixelSize: 14
                    text: "Change cell value"
                }

                RowLayout {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.maximumHeight: 30
                    TextField {
                        id: newValue
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        placeholderText: qsTr("New value")
                    }
                    PrimaryButton {
                        text: qsTr("Apply")
                        onClicked: {
                            viewModel.dataBaseViewModel.changeCell(tableView.selectedRow, tableView.selectedColumn, newValue.text)
                            updateTable();
                            newValue.text = ""
                        }
                    }
                }

                RowLayout {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.maximumHeight: 30
                    ComboBox {
                        id: headerToFind
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        model: viewModel.dataBaseViewModel.headers()
                    }

                    TextField {
                        id: valueToFind
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        placeholderText: qsTr("Value")
                    }

                    PrimaryButton {
                        text: qsTr("Find")
                        onClicked: {
                            viewModel.dataBaseViewModel.find(headerToFind.currentIndex, valueToFind.text)
                        }
                    }

                    PrimaryButton {
                        text: qsTr("Delete")
                        color: dangerColor
                        onClicked: {
                            viewModel.dataBaseViewModel.remove(headerToFind.currentIndex, valueToFind.text)
                        }
                    }
                }
            }

            ColumnLayout {
                id: rightSideActions
                Layout.fillHeight: true
                Layout.fillWidth: true
                spacing: 25

//                Text {
//                    font.pixelSize: 14
//                    text: "Add Empty Row"
//                }

                RowLayout {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.maximumHeight: 30
//                    TextField {
//                        Layout.fillHeight: true
//                        Layout.fillWidth: true
//                    }
                    PrimaryButton {
                        Layout.fillWidth: true
                        text: qsTr("Add Empty Row")
                        onClicked: {
                            viewModel.dataBaseViewModel.addEmptyRow()
                            updateTable()
                        }
                    }
                }

                RowLayout {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.maximumHeight: 30

                    PrimaryButton {
                        Layout.fillWidth: true
                        text: qsTr("Delete selected row")
                        color: dangerColor
                        onClicked: {
                            viewModel.dataBaseViewModel.removeRow(tableView.selectedRow)
                            updateTable()
                        }
                    }
                }

                RowLayout {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.maximumHeight: 30

                    PrimaryButton {
                        Layout.fillWidth: true
                        text: qsTr("Clear table")
                        onClicked: {
                            viewModel.dataBaseViewModel.clearTable()
                            updateTable()
                        }
                    }
                }

                RowLayout {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.maximumHeight: 30

                    PrimaryButton {
                        Layout.fillWidth: true
                        text: qsTr("Clear all tables")
                        color: dangerColor
                        onClicked: {
                            viewModel.dataBaseViewModel.addEmptyRow()
                            updateTable()
                        }
                    }
                }



            }
        }

    }

    function updateColumnLabels() {
        columnLabels.model = []
        columnLabels.model = viewModel.dataBaseViewModel.headers().length
        headerToFind.model = []
        headerToFind.model = viewModel.dataBaseViewModel.headers()
    }

    function updateTables() {
        tables.model = []
        tables.model = viewModel.dataBaseViewModel.tableNames().length
    }

    function updateTable() {
        tableView.model = []
        tableView.model = viewModel.dataBaseViewModel.table()
        viewModel.dataBaseViewModel.updateTable()
    }

}
