/* Copyright (C) 2016  François Blondel

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  (this is the zlib license)
*/

#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QSlider>
#include <QButtonGroup>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QListView>
#include <QFrame>
#include <QRadioButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
//#include <QScrollArea>
#include <QScroller>
#include <QTabWidget>
#include <QBoxLayout>
#include <QDebug>
//#include <QTouchEvent>

#include "qbouton.h"
#include "slideh.h"
#include "multipushbutton.h"


class WindowTeleco : public QMainWindow
{
    Q_OBJECT

public:
    WindowTeleco(QWidget *parent = 0);
//    ~WindowTeleco();

    QTabWidget *tabs;

    QPushButton *castButton;

    QLabel *labelIpT;
    QLabel *labelPortT;
    QLabel *labelIPDl;
    QLabel *labelPortDl;
    QFrame* cadre1;
    QFrame* cadre2;
    QFrame* line;
    QPushButton *refresh;
    QComboBox *iPTeleco;
    QLineEdit *portTeleco;
    QLineEdit *iPDLight;
    QLineEdit *portDlight;
    QPushButton *request;
    QPushButton *scanReseau;
    QRadioButton *checkConnected;


    QPushButton *pad0;
    QPushButton *pad1;
    QPushButton *pad2;
    QPushButton *pad3;
    QPushButton *pad4;
    QPushButton *pad5;
    QPushButton *pad6;
    QPushButton *pad7;
    QPushButton *pad8;
    QPushButton *pad9;
    QPushButton *padPoint;
    QPushButton *padCH;
    QPushButton *padAT;
    QPushButton *padPlus;
    QPushButton *padMoins;
    QPushButton *padNext;
    QPushButton *padPrev;
    QPushButton *padTHRU;
    QPushButton *padALL;
    QPushButton *padFULL;
    QPushButton *padEnter;
    QPushButton *padGrp;
    QPushButton *padSub;
    QPushButton *padRec;
    QBouton *padUpdate;
    QBouton *padGoto;
    QComboBox *padGotoCombo;
    QPushButton *padScene;
    QButtonGroup *chiffresPad;
    SlideH *magicSliderT;
    QSlider *magicSlider;
    QLabel *textMagicSlider;
    QLineEdit *ecrantxt;
    QTableView *ecranSelect;
    QStandardItemModel *modele;
    QPushButton *view;
    QPushButton *yes;
    QPushButton *no;
    SlideH *masterSceneT;
    QProgressBar *masterScene;
    SlideH *masterSubsT;
    QProgressBar *masterSubs;
    QLabel *textMasterScene;
    QLabel *textMasterSubs;
    QBouton *padClear;


    QComboBox  *subnumpage;
    QLabel *subnumpageLabel;
    QLineEdit *nomPageSub;
    QPushButton *nameOrContent;
    QPushButton *masterpagemoins;
    QPushButton *masterpageplus;
    QLineEdit  *subnum1;
    QLineEdit  *subnum2;
    QLineEdit  *subnum3;
    QLineEdit  *subnum4;
    QLineEdit  *subnum5;
    QLineEdit  *subnum6;
    QLineEdit  *subnum7;
    QLineEdit  *subnum8;
    QLineEdit  *subnum9;
    QLineEdit  *subnum10;
    multiPushButton *Flash01;
    multiPushButton *Flash02;
    multiPushButton *Flash03;
    multiPushButton *Flash04;
    multiPushButton *Flash05;
    multiPushButton *Flash06;
    multiPushButton *Flash07;
    multiPushButton *Flash08;
    multiPushButton *Flash09;
    multiPushButton *Flash10;
    QSlider *Sub01;
    QSlider *Sub02;
    QSlider *Sub03;
    QSlider *Sub04;
    QSlider *Sub05;
    QSlider *Sub06;
    QSlider *Sub07;
    QSlider *Sub08;
    QSlider *Sub09;
    QSlider *Sub10;
    SlideH *Sub01T;
    SlideH *Sub02T;
    SlideH *Sub03T;
    SlideH *Sub04T;
    SlideH *Sub05T;
    SlideH *Sub06T;
    SlideH *Sub07T;
    SlideH *Sub08T;
    SlideH *Sub09T;
    SlideH *Sub10T;
    QLabel *Sub01txt;
    QLabel *Sub02txt;
    QLabel *Sub03txt;
    QLabel *Sub04txt;
    QLabel *Sub05txt;
    QLabel *Sub06txt;
    QLabel *Sub07txt;
    QLabel *Sub08txt;
    QLabel *Sub09txt;
    QLabel *Sub10txt;
    QList<multiPushButton*> *subsFlashList;
    QList<QLabel*> *subsTextList;
    QList<QLineEdit*> *subsNumList;
    QList<QSlider*> *subsList;
    QList<SlideH*> *subsListT;

    QPushButton *Pause;
    QPushButton *GoBack;
    QPushButton *GO;
    QPushButton *stepMoins;
    QPushButton *stepPlus;
    SlideH *sliderX1T;
    SlideH *sliderX2T;
    QSlider *sliderX1;
    QSlider *sliderX2;
    QLineEdit *nStepX1;
    QLineEdit *nCueX1;
    QTextEdit *textStepX1;
    QLineEdit *nStepX2;
    QLineEdit *nCueX2;
    QTextEdit *textStepX2;
    QLabel *joystickLevel;
    SlideH *joystickT;
    QSlider *joystick;


    QPushButton *p0;
    QPushButton *p1;
    QPushButton *p2;
    QPushButton *p3;
    QPushButton *p4;
    QPushButton *p5;
    QPushButton *p6;
    QPushButton *p7;
    QPushButton *p8;
    QPushButton *p9;
    QButtonGroup *chiffresPatch;
    QPushButton *padPoint_2;
    QPushButton *padTHRU_2;
    QPushButton *padPlus_2;
    QPushButton *padMoins_2;
    QPushButton *padClear_2;
    SlideH *testLevelT;
    QProgressBar *testLevel;
//    QLineEdit *level;
    QPushButton *padPATCH;
    QPushButton *padUNPATCH;
    QPushButton *padPREV;
    QPushButton *padNEXT;
    QPushButton *padEnter_2;
    QPushButton *channelTest;
    QPushButton *dimmerTest;
    QPushButton *dimmer;
    QPushButton *padCh_2;
    QTextEdit *nChannel;
    QTextEdit *nDimmer;
    QLineEdit *ecrantxt_2;
    QPushButton *yes_2;
    QPushButton *no_2;

protected:

 //    bool eventFilter(QObject *obj, QEvent *ev);
};


#endif // WINDOW_H
