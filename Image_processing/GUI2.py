from PyQt5 import Qt, QtCore, QtGui, QtWidgets
import sys
import numpy as np
import cv2
import binarizator as b

file = "img.txt"

class Ui_MainWindow(QtWidgets.QWidget):
    def setupUi(self, MainWindow):
            MainWindow.setObjectName("MainWindow")
            MainWindow.resize(981, 778)
            MainWindow.setStyleSheet("background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(250, 80, 217, 255), stop:1 rgba(255, 255, 255, 255));")
            self.centralwidget = QtWidgets.QWidget(MainWindow)
            self.centralwidget.setObjectName("centralwidget")
            self.Upload = QtWidgets.QPushButton(self.centralwidget)
            self.Upload.setGeometry(QtCore.QRect(830, 30, 101, 41))
            font = QtGui.QFont()
            font.setFamily("Purisa")
            font.setBold(True)
            font.setWeight(75)
            self.Upload.setFont(font)
            self.Upload.setIconSize(QtCore.QSize(20, 20))
            self.Upload.setObjectName("Upload")
            self.Black_white = QtWidgets.QPushButton(self.centralwidget)
            self.Black_white.setGeometry(QtCore.QRect(830, 100, 101, 41))
            font = QtGui.QFont()
            font.setFamily("Purisa")
            font.setBold(True)
            font.setWeight(75)
            self.Black_white.setFont(font)
            self.Black_white.setIconSize(QtCore.QSize(20, 20))
            self.Black_white.setObjectName("Black_white")
            self.Otsu = QtWidgets.QPushButton(self.centralwidget)
            self.Otsu.setGeometry(QtCore.QRect(830, 170, 101, 41))
            font = QtGui.QFont()
            font.setFamily("Purisa")
            font.setBold(True)
            font.setWeight(75)
            self.Otsu.setFont(font)
            self.Otsu.setIconSize(QtCore.QSize(20, 20))
            self.Otsu.setObjectName("Otsu")
            self.Adaptive = QtWidgets.QPushButton(self.centralwidget)
            self.Adaptive.setGeometry(QtCore.QRect(830, 240, 101, 41))
            font = QtGui.QFont()
            font.setFamily("Purisa")
            font.setBold(True)
            font.setWeight(75)
            self.Adaptive.setFont(font)
            self.Adaptive.setIconSize(QtCore.QSize(20, 20))
            self.Adaptive.setObjectName("Adaptive")
            self.Three = QtWidgets.QPushButton(self.centralwidget)
            self.Three.setGeometry(QtCore.QRect(830, 310, 101, 41))
            font = QtGui.QFont()
            font.setFamily("Purisa")
            font.setBold(True)
            font.setWeight(75)
            self.Three.setFont(font)
            self.Three.setIconSize(QtCore.QSize(20, 20))
            self.Three.setObjectName("Three")
            self.Manual = QtWidgets.QPushButton(self.centralwidget)
            self.Manual.setGeometry(QtCore.QRect(830, 380, 101, 41))
            font = QtGui.QFont()
            font.setFamily("Purisa")
            font.setBold(True)
            font.setWeight(75)
            self.Manual.setFont(font)
            self.Manual.setIconSize(QtCore.QSize(20, 20))
            self.Manual.setShortcut("")
            self.Manual.setObjectName("Manual")
            self.Panel = QtWidgets.QLabel(self.centralwidget)
            self.Panel.setGeometry(QtCore.QRect(10, 10, 761, 761))
            self.Panel.setStyleSheet("background-color: qlineargradient(spread:reflect, x1:1, y1:0, x2:0, y2:0, stop:0 rgba(250, 80, 217, 255), stop:1 rgba(255, 255, 255, 255));")
            self.Panel.setText("")
            self.Panel.setObjectName("Panel")
            self.Manual_slider = QtWidgets.QSlider(self.centralwidget)
            self.Manual_slider.setEnabled(True)
            self.Manual_slider.setMaximum(255)
            self.Manual_slider.setValue(128)
            self.Manual_slider.setGeometry(QtCore.QRect(800, 480, 160, 16))
            self.Manual_slider.setMouseTracking(True)
            self.Manual_slider.setAccessibleDescription("")
            self.Manual_slider.setOrientation(QtCore.Qt.Horizontal)
            self.Manual_slider.setObjectName("Manual_slider")
            self.R_val_spin = QtWidgets.QSpinBox(self.centralwidget)
            self.R_val_spin.setEnabled(True)
            self.R_val_spin.setGeometry(QtCore.QRect(800, 540, 47, 24))
            self.R_val_spin.setMaximum(255)
            self.R_val_spin.setValue(255)
            self.R_val_spin.setWhatsThis("")
            self.R_val_spin.setStyleSheet("color: rgb(0, 255, 255);")
            self.R_val_spin.setWrapping(False)
            self.R_val_spin.setButtonSymbols(QtWidgets.QAbstractSpinBox.PlusMinus)
            self.R_val_spin.setSpecialValueText("")
            self.R_val_spin.setObjectName("R_val_spin")
            self.G_val_spin = QtWidgets.QSpinBox(self.centralwidget)
            self.G_val_spin.setEnabled(True)
            self.G_val_spin.setGeometry(QtCore.QRect(800, 590, 47, 24))
            self.G_val_spin.setMaximum(255)
            self.G_val_spin.setValue(255)
            self.G_val_spin.setStyleSheet("color: rgb(0, 255, 255);")
            self.G_val_spin.setButtonSymbols(QtWidgets.QAbstractSpinBox.PlusMinus)
            self.G_val_spin.setObjectName("G_val_spin")
            self.B_val_spin = QtWidgets.QSpinBox(self.centralwidget)
            self.B_val_spin.setEnabled(True)
            self.B_val_spin.setGeometry(QtCore.QRect(800, 640, 47, 24))
            self.B_val_spin.setMaximum(255)
            self.B_val_spin.setValue(255)
            self.B_val_spin.setStyleSheet("color: rgb(0, 255, 255);")
            self.B_val_spin.setButtonSymbols(QtWidgets.QAbstractSpinBox.PlusMinus)
            self.B_val_spin.setObjectName("B_val_spin")
            self.R_label = QtWidgets.QLabel(self.centralwidget)
            self.R_label.setGeometry(QtCore.QRect(870, 540, 71, 21))
            font = QtGui.QFont()
            font.setFamily("Purisa")
            self.R_label.setFont(font)
            self.R_label.setAutoFillBackground(False)
            self.R_label.setTextInteractionFlags(QtCore.Qt.NoTextInteraction)
            self.R_label.setObjectName("R_label")
            self.G_label = QtWidgets.QLabel(self.centralwidget)
            self.G_label.setGeometry(QtCore.QRect(870, 590, 71, 21))
            font = QtGui.QFont()
            font.setFamily("Purisa")
            self.G_label.setFont(font)
            self.G_label.setAutoFillBackground(False)
            self.G_label.setTextInteractionFlags(QtCore.Qt.NoTextInteraction)
            self.G_label.setObjectName("G_label")
            self.B_label = QtWidgets.QLabel(self.centralwidget)
            self.B_label.setGeometry(QtCore.QRect(870, 640, 71, 21))
            font = QtGui.QFont()
            font.setFamily("Purisa")
            self.B_label.setFont(font)
            self.B_label.setAutoFillBackground(False)
            self.B_label.setTextInteractionFlags(QtCore.Qt.NoTextInteraction)
            self.B_label.setObjectName("B_label")
            self.man_label = QtWidgets.QLabel(self.centralwidget)
            self.man_label.setGeometry(QtCore.QRect(810, 460, 150, 16))
            font = QtGui.QFont()
            font.setFamily("Purisa")
            self.man_label.setFont(font)
            self.man_label.setObjectName("man_label")
            font = QtGui.QFont()
            font.setFamily("Purisa")
            font.setBold(True)
            font.setWeight(75)
            MainWindow.setCentralWidget(self.centralwidget)
            self.statusbar = QtWidgets.QStatusBar(MainWindow)
            self.statusbar.setObjectName("statusbar")
            MainWindow.setStatusBar(self.statusbar)
            self.actionUpload = QtWidgets.QAction(MainWindow)
            self.actionUpload.setObjectName("actionUpload")

            self.retranslateUi(MainWindow)
            self.Upload.clicked.connect(self.UploadImage)
            self.Black_white.clicked.connect(self.toBlack_white)
            self.Otsu.clicked.connect(self.OtsuBin)
            self.Adaptive.clicked.connect(self.Adapt)
            self.Three.clicked.connect(self.ThreeBin)
            self.Manual.clicked.connect(self.Manual_bin)
            self.Manual_slider.valueChanged['int'].connect(self.Man_update)
            self.R_val_spin.valueChanged['int'].connect(self.Rgb_update)
            self.G_val_spin.valueChanged['int'].connect(self.Rgb_update)
            self.B_val_spin.valueChanged['int'].connect(self.Rgb_update)
            QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.Upload.setText(_translate("MainWindow", "Upload"))
        self.Upload.setShortcut(_translate("MainWindow", "Ctrl+U"))
        self.Black_white.setText(_translate("MainWindow", "Black/white"))
        self.Black_white.setShortcut(_translate("MainWindow", "Ctrl+B"))
        self.Otsu.setText(_translate("MainWindow", "OTSU"))
        self.Otsu.setShortcut(_translate("MainWindow", "Ctrl+O"))
        self.Adaptive.setText(_translate("MainWindow", "Adaptive"))
        self.Adaptive.setShortcut(_translate("MainWindow", "Ctrl+A"))
        self.Three.setText(_translate("MainWindow", "Three"))
        self.Three.setShortcut(_translate("MainWindow", "Ctrl+T"))
        self.Manual.setText(_translate("MainWindow", "Manual"))
        self.R_label.setText(_translate("MainWindow", " R value"))
        self.G_label.setText(_translate("MainWindow", " G value"))
        self.B_label.setText(_translate("MainWindow", " B value"))
        self.man_label.setText(_translate("MainWindow", "Manual threshold"))
        self.actionUpload.setText(_translate("MainWindow", "Upload"))

    def show(self,pximage):
        self.Panel.setPixmap(Qt.QPixmap(pximage))
        self.resize(pximage.width(), pximage.height())

    def get_path(self):
        f = open(file,"r")
        path = f.read()
        f.close()
        return path

    def set_path(self,path):
        f = open(file,"w")
        f.write(path)
        f.close()

    def Man_update(self):
        im = cv2.imread(self.path)
        im_grey = b.greyscale(im)
        im_bin = b.regular_bin(im_grey,self.Manual_slider.value())
        pximage = Qt.QPixmap.fromImage(Qt.QImage("george.jpg"))
        self.show(pximage)


    def Rgb_update(self):
        if self.rgb_picture:
            im = cv2.imread(self.path)
            image = b.rgbBin(im,self.R_val_spin.value(),self.G_val_spin.value(),self.B_val_spin.value())
            pximage = Qt.QPixmap.fromImage(Qt.QImage("george.jpg"))
            self.show(pximage)

    def ThreeBin(self):
        self.rgb_picture = True
        self.is_manual = False
        self.Rgb_update()

    def OtsuBin(self):
        self.rgb_picture = False
        self.is_manual = False
        im = cv2.imread(self.path)
        im_grey = b.greyscale(im)
        im_otsu = b.otsu(im_grey)
        pximage = Qt.QPixmap.fromImage(Qt.QImage("george.jpg"))
        self.show(pximage)

    def Manual_bin(self):
        self.is_manual = True
        self.rgb_picture = False


    # def img_to_qim(self,image2):
    #     self.curr_im = image2
    #     # print(image2.data)
    #     # data = image2.copy()

    #     qImg = Qt.QImage(data.tobytes(),image2.shape[1],image2.shape[0], image2.shape[1],QtGui.QImage.Format_Grayscale8)
    #     return qImg

    def UploadImage(self):
        fname = QtWidgets.QFileDialog.getOpenFileName(self, 'Open file','~', "Image files (*.jpg *.gif)")
        self.path = fname[0]

        self.curr_im = cv2.imread(self.path)
        self.Man_val = 128
        self.rgb_picture = False
        self.is_manual = False

        pximage = Qt.QPixmap(self.path)
        self.show(pximage)

    def toBlack_white(self):
        self.rgb_picture = False
        self.is_manual = False
        im = cv2.imread(self.path)
        imG = b.greyscale(im)
        im2 = Qt.QImage("george.jpg")
        pximage = Qt.QPixmap.fromImage(im2)
        self.show(pximage)

    def Adapt(self):
        self.rgb_picture = False
        self.is_manual = False
        im = cv2.imread(self.path)
        grey = b.greyscale(im)
        imG = b.adaptive_bin(grey)
        pximage = Qt.QPixmap.fromImage(Qt.QImage("george.jpg"))
        self.show(pximage)

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
