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

#include "window.h"

extern int screenWidth;
extern int screenHeight;

WindowTeleco::WindowTeleco(QWidget *parent)
    : QMainWindow(parent)
{

tabs = new QTabWidget;
tabs->setStyleSheet("QTabBar::tab           { color: white; background : transparent; margin : 10px;}"
                    "QTabBar::tab:selected  { color: white;font-weight: bold;}"
                    "QTabBar::tab:!selected { color:silver;font-weight: normal;}");
tabs->setFocusPolicy(Qt::NoFocus  );
tabs->addTab(new QWidget(),"Osc"  );
tabs->addTab(new QWidget(),"Home" );
tabs->addTab(new QWidget(),"Subs" );
tabs->addTab(new QWidget(),"Scene");
tabs->addTab(new QWidget(),"Patch");

OSCTab =   tabs->widget(0);
HomeTab =  tabs->widget(1);
SUBsTab =  tabs->widget(2);
SceneTab = tabs->widget(3);
PatchTab = tabs->widget(4);




//// OSC ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

cadre1 = new QFrame;
cadre1->setStyleSheet("QFrame {border :2px outset purple}");
cadre1->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

labelIpT = new QLabel;
labelIpT->setText("D::Luz IP Adress");
labelIpT->setStyleSheet("QLabel {border:transparent}");
//labelIpT->setVisible(false);

refresh = new QPushButton;
refresh->setText(" Refresh ");
refresh->setFocusPolicy(Qt::NoFocus);
refresh->setStyleSheet("QPushButton {height: 25px;border-color:silver;}");
refresh->setFixedWidth(screenWidth/2.5);
//refresh->setVisible(false);

iPTeleco = new QComboBox;
iPTeleco->setStyleSheet("QComboBox                   { background: lightblue; color: black;}"
                        "QComboBox::drop-down        { border-width: 0px; width: 0px; border-style: none;}"
                        "QComboBox QAbstractItemView { font-size: 15pt;}");
//iPTeleco->setVisible(false);

labelPortT = new QLabel;
labelPortT->setStyleSheet("QLabel {border:transparent}");
labelPortT->setText("D::Luz port");

portTeleco = new QLineEdit;
portTeleco->setText("7001");
#if !defined(Q_OS_IOS)
portTeleco->setInputMethodHints(Qt::ImhDigitsOnly);
#endif
portTeleco->setFixedWidth(screenWidth/5);

QGridLayout *layoutTeleco = new QGridLayout(cadre1);
layoutTeleco->addWidget(refresh,    0, 1);
layoutTeleco->addWidget(labelIpT,   1, 0);
layoutTeleco->addWidget(iPTeleco,   1, 1);
layoutTeleco->addWidget(labelPortT, 2, 0);
layoutTeleco->addWidget(portTeleco, 2, 1);


cadre2 = new QFrame;
cadre2->setStyleSheet("QFrame {border : 2px outset purple}");
cadre2->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);


labelIPDl = new QLabel;
labelIPDl->setStyleSheet("QLabel {border:transparent}");
labelIPDl->setText("D::Light IP Adress");
//labelIPDl->setVisible(false);

iPDLight = new QLineEdit;
iPDLight->setText("127.0.0.1");
iPDLight->setFixedWidth(screenWidth/2.5);
//iPDLight->setVisible(false);

labelPortDl = new QLabel;
labelPortDl->setStyleSheet("QLabel {border:transparent}");
labelPortDl->setText("D::Light port");

portDlight = new QLineEdit;
portDlight->setText("7000");
#if !defined(Q_OS_IOS)
portDlight->setInputMethodHints(Qt::ImhDigitsOnly);
#endif
portDlight->setFixedWidth(screenWidth/5);

request = new QPushButton;
request->setText(" Request ");
request->setFocusPolicy(Qt::NoFocus);
request->setStyleSheet("QPushButton {height: 25px;border-color:silver;}");
request->setFixedWidth(screenWidth/2.5);

checkConnected = new QRadioButton;
checkConnected->setText(" connected ");
checkConnected->setDisabled(true);
checkConnected->setStyleSheet("QRadioButton:disabled                       { color : white}"
                              "QRadioButton::indicator::checked:disabled   { border: 1px outset green; border-radius: 6px; background-color: lightgreen;"
                                                                            "width: 10px; height: 10px; margin-left: 5px;}"
                              "QRadioButton::indicator::unchecked:disabled { border: 1px outset darkgray; border-radius: 6px; background-color: black;"
                                                                            "width: 10px; height: 10px; margin-left: 5px;}");

QGridLayout *layoutDl = new QGridLayout(cadre2);
layoutDl->addWidget(labelIPDl,      0, 0);
layoutDl->addWidget(iPDLight,       0, 1);
layoutDl->addWidget(labelPortDl,    1, 0);
layoutDl->addWidget(portDlight,     1, 1);
layoutDl->addWidget(checkConnected, 2, 0);
layoutDl->addWidget(request,        2, 1);


scanReseau = new QPushButton;
scanReseau->setText("Go OSC");
scanReseau->setFocusPolicy(Qt::NoFocus);
//scanReseau->setFixedHeight(screenWidth/5);

castButton = new QPushButton;
castButton->setText("Mode = Unicast");
castButton->setFocusPolicy(Qt::NoFocus);
castButton->setVisible(false);

QVBoxLayout *layoutO = new QVBoxLayout(OSCTab);
layoutO->addWidget(cadre1);
layoutO->addWidget(cadre2);
layoutO->addStretch(1);
layoutO->addWidget(scanReseau);
layoutO->addWidget(castButton);

OSCTab->setLayout(layoutO);


/////Home///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

padPoint = new QPushButton;
padPoint->setText("  .  ");
padPoint->setFocusPolicy(Qt::NoFocus);
padPoint->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

padAT = new QPushButton;
padAT->setText("@");
padAT->setFocusPolicy(Qt::NoFocus);
padAT->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

padPlus = new QPushButton;
padPlus->setText("+");
padPlus->setFocusPolicy(Qt::NoFocus);
padPlus->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

padMoins = new QPushButton;
padMoins->setText("-");
padMoins->setFocusPolicy(Qt::NoFocus);
padMoins->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

padNext = new QPushButton;
padNext->setText("Next");
padNext->setFocusPolicy(Qt::NoFocus);
padNext->setStyleSheet("QPushButton         {background-color:dimgrey; color:white; border-color:dimgrey;}"
                      "QPushButton:disabled {background-color:black; color:grey;}");

padPrev = new QPushButton;
padPrev->setText("Prev");
padPrev->setFocusPolicy(Qt::NoFocus);
padPrev->setStyleSheet("QPushButton          {background-color:dimgrey; color:white;border-color:dimgrey;}"
                       "QPushButton:disabled {background-color:black; color:grey;}");

padTHRU = new QPushButton;
padTHRU->setText("Thru");
padTHRU->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);
padTHRU->setFocusPolicy(Qt::NoFocus);

padALL = new QPushButton;
padALL->setText("ALL");
padALL->setFocusPolicy(Qt::NoFocus);
padALL->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

padFULL = new QPushButton;
padFULL->setText(" FULL ");
padFULL->setFocusPolicy(Qt::NoFocus);
padFULL->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

padEnter = new QPushButton;
padEnter->setText(" Enter ");
padEnter->setFocusPolicy(Qt::NoFocus);
padEnter->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

padClear = new QBouton("Clr");
padClear->setText("Clr");
padClear->setFocusPolicy(Qt::NoFocus);
padClear->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);


padCH = new QPushButton;
padCH->setStyleSheet("QPushButton          {background-color:purple; color:white; border-color:purple;}"
                     "QPushButton:disabled {background-color:black; color:grey;}");
padCH->setText("CH");
padCH->setFocusPolicy(Qt::NoFocus);
padCH->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

padSub = new QPushButton;
padSub->setStyleSheet("QPushButton          {background-color:purple; color:white; border-color:purple;}"
                      "QPushButton:disabled {background-color:black; color:grey;}");
padSub->setText("Sub");
padSub->setFocusPolicy(Qt::NoFocus);
padSub->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

padGrp = new QPushButton;
padGrp->setStyleSheet("QPushButton          {background-color:purple; color:white; border-color:purple;}"
                      "QPushButton:disabled {color:grey;background-color:black;}");
padGrp->setText("Grp");
padGrp->setFocusPolicy(Qt::NoFocus);
padGrp->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

padGoto = new QBouton("goto");
padGoto->setText(" Goto ");
padGoto->setFocusPolicy(Qt::NoFocus);
padGoto->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

padGotoCombo = new QComboBox(padGoto);
padGotoCombo->setStyleSheet("QComboBox {height : 50px; background: transparent; color: transparent;border:transparent;}");
padGotoCombo->setView(new QListView());
padGotoCombo->addItem("Cue");
padGotoCombo->addItem("Step");
padGotoCombo->addItem("StepID");
padGotoCombo->setEnabled(false);

padRec = new QPushButton;
padRec->setStyleSheet("QPushButton          {background-color:darkred; color:white; border-color:darkred;}"
                      "QPushButton:disabled {background-color:black; color:grey;}");
padRec->setText("Rec");
padRec->setFocusPolicy(Qt::NoFocus);
padRec->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

padUpdate = new QBouton("Update");
padUpdate->setStyleSheet("QPushButton          {background-color:orange; color:white; border-color:orange;}"
                         "QPushButton:disabled {background-color:black; color:grey;}");
padUpdate->setText("Up\n date ");
padUpdate->setFocusPolicy(Qt::NoFocus);
padUpdate->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

padScene = new QPushButton;
padScene->setText("X1");
padScene->setCheckable(true);
padScene->setChecked(true);
padScene->setStyleSheet("QPushButton:checked  {background-color: red; border-color: red;} "
                        "QPushButton          {background-color: green; border-color: green;}"
                        "QPushButton:disabled {background-color: black; color:grey;}");
padScene->setFocusPolicy(Qt::NoFocus);
padScene->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

pad0 = new QPushButton;
pad0->setText("0");
pad0->setFocusPolicy(Qt::NoFocus);
pad0->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

pad1 = new QPushButton;
pad1->setText("1");
pad1->setFocusPolicy(Qt::NoFocus);
pad1->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

pad2 = new QPushButton;
pad2->setText("2");
pad2->setFocusPolicy(Qt::NoFocus);
pad2->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

pad3 = new QPushButton;
pad3->setText("3");
pad3->setFocusPolicy(Qt::NoFocus);
pad3->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

pad4 = new QPushButton;
pad4->setText("4");
pad4->setFocusPolicy(Qt::NoFocus);
pad4->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

pad5 = new QPushButton;
pad5->setText("5");
pad5->setFocusPolicy(Qt::NoFocus);
pad5->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

pad6 = new QPushButton;
pad6->setText("6");
pad6->setFocusPolicy(Qt::NoFocus);
pad6->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

pad7 = new QPushButton;
pad7->setText("   7   ");
pad7->setFocusPolicy(Qt::NoFocus);
pad7->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

pad8 = new QPushButton;
pad8->setText("8");
pad8->setFocusPolicy(Qt::NoFocus);
pad8->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

pad9 = new QPushButton;
pad9->setText("9");
pad9->setFocusPolicy(Qt::NoFocus);
pad9->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

chiffresPad = new QButtonGroup(this);
chiffresPad->addButton(pad0);
chiffresPad->addButton(pad1);
chiffresPad->addButton(pad2);
chiffresPad->addButton(pad3);
chiffresPad->addButton(pad4);
chiffresPad->addButton(pad5);
chiffresPad->addButton(pad6);
chiffresPad->addButton(pad7);
chiffresPad->addButton(pad8);
chiffresPad->addButton(pad9);


magicSliderT = new SlideH;
magicSliderT->setAttribute(Qt::WA_AcceptTouchEvents);
magicSliderT->setSizePolicy(QSizePolicy::MinimumExpanding , QSizePolicy::MinimumExpanding);
magicSliderT->setEnabled(true);
magicSliderT->setStyleSheet("QFrame {border :0px outset transparent}");

magicSlider = new QSlider(magicSliderT);
magicSlider->setMaximum(100);
magicSlider->setValue(50);
magicSlider->setEnabled(false);
magicSlider->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);
magicSlider->setStyleSheet("QSlider::groove:disabled   { border: 1px outset indigo; background: indigo; border-radius: 4px;}"
                           "QSlider::sub-page:disabled { border: 1px outset indigo; background: indigo; border-radius: 4px;}"
                           "QSlider::handle:disabled   { border: 3px outset fuchsia;border-radius: 10px; background: transparent;color : fushia;}");

QVBoxLayout *magSl = new QVBoxLayout(magicSliderT);
magSl->setContentsMargins(0,0,0,0);
magSl->addWidget(magicSlider);

textMagicSlider = new QLabel(magicSlider);
textMagicSlider->setText("S\nL\nI\nD\nE");
textMagicSlider->setStyleSheet("QLabel:disabled        {color:white; font:bold; font-size:18pt;}");
textMagicSlider->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);

QVBoxLayout *magicS = new QVBoxLayout(magicSlider);
magicS->addWidget(textMagicSlider);

modele = new QStandardItemModel(0,2);


ecranSelect = new QTableView;
ecranSelect->setModel(modele);
ecranSelect->verticalHeader()->hide();
ecranSelect->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
ecranSelect->setStyleSheet("QTableView                  { border-color:transparent;}"
                           "QHeaderView::section        { background:transparent;}"
                           "QHeaderView                 { border-color : black; color : black; }"
                           "QTableCornerButton::section { background-color:transparent;border-color:transparent;}");
ecranSelect->setFocusPolicy(Qt::NoFocus);
ecranSelect->setSelectionMode(QAbstractItemView::NoSelection);
ecranSelect->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
ecranSelect->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
QScroller::grabGesture(ecranSelect, QScroller::LeftMouseButtonGesture);


// //////

ecrantxt = new QLineEdit;
ecrantxt->setSizePolicy(QSizePolicy:: Minimum , QSizePolicy::Expanding);
ecrantxt->setStyleSheet("QLineEdit{background: lightblue; color:black; font-size: 20px }");
ecrantxt->setReadOnly(true);
ecrantxt->setAlignment(Qt::AlignCenter|Qt::AlignLeading|Qt::AlignLeft);


yes = new QPushButton;
yes->setText("YES");
yes->setFocusPolicy(Qt::NoFocus);
yes->setFixedWidth(screenWidth/6.5);
yes->setStyleSheet("QPushButton {height: 30px;}");
yes->setEnabled(false);

no = new QPushButton;
no->setText(" NO ");
no->setFocusPolicy(Qt::NoFocus);
yes->setFixedWidth(screenWidth/6.5);
no->setStyleSheet("QPushButton {height: 30px;}");
no->setEnabled(false);


// ///////

masterSceneT = new SlideH;
masterSceneT->setAttribute(Qt::WA_AcceptTouchEvents);
masterSceneT->setFixedHeight(screenHeight/15);
masterSceneT->setStyleSheet("QFrame {border :0px outset transparent}");
masterSceneT->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);


masterScene = new QProgressBar(masterSceneT);
masterScene->setMaximum(255);
masterScene->setValue(255);
masterScene->setTextVisible(false);
masterScene->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);
masterScene->setOrientation(Qt::Horizontal);
masterScene->setStyleSheet("QProgressBar                 {border: 1px outset darkred;} "
                           "QProgressBar::chunk          {background: darkred;} "
                           "QProgressBar::chunk:disabled {background: darkgray; border: grey;}");

QVBoxLayout *mastSc = new QVBoxLayout(masterSceneT);
mastSc->setContentsMargins(0,0,0,0);
mastSc->addWidget(masterScene);

textMasterScene = new QLabel(masterScene);
textMasterScene->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
textMasterScene->setText("MASTER SCENE");
textMasterScene->setStyleSheet("QLabel:disabled { color:grey }");

QVBoxLayout *mastScTxt = new QVBoxLayout(masterScene);
mastScTxt->setContentsMargins(0,0,0,0);
mastScTxt->addWidget(textMasterScene);

masterSubsT = new SlideH;
masterSubsT->setAttribute(Qt::WA_AcceptTouchEvents);
masterSubsT->setFixedHeight(screenHeight/15);
masterSubsT->setStyleSheet("QFrame {border :0px outset transparent}");
masterSubsT->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

masterSubs = new QProgressBar(masterSubsT);
masterSubs->setMaximum(255);
masterSubs->setValue(255);
masterSubs->setTextVisible(false);
masterSubs->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);
masterSubs->setOrientation(Qt::Horizontal);
masterSubs->setStyleSheet("QProgressBar                 {border: 1px outset darkblue;} "
                          "QProgressBar::chunk          {background: darkblue;} "
                          "QProgressBar::chunk:disabled {background: darkgray; border: grey;}");

QVBoxLayout *mastSu = new QVBoxLayout(masterSubsT);
mastSu->setContentsMargins(0,0,0,0);
mastSu->addWidget(masterSubs);

textMasterSubs = new QLabel(masterSubs);
textMasterSubs->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
textMasterSubs->setText("MASTER SUBS");
textMasterSubs->setStyleSheet("QLabel:disabled { color:grey }");

QVBoxLayout *mastSuTxt = new QVBoxLayout(masterSubs);
mastSuTxt->setContentsMargins(0,0,0,0);
mastSuTxt->addWidget(textMasterSubs);

layoutpad = new QGridLayout;
layoutpad->setSpacing(1);
layoutpad->addWidget(padScene,     0, 2);
layoutpad->addWidget(padTHRU,      0, 3);
layoutpad->addWidget(padCH,        0, 4);
layoutpad->addWidget(magicSliderT, 0, 5, 6, 1);
layoutpad->addWidget(padMoins,     1, 2);
layoutpad->addWidget(padALL,       1, 3);
layoutpad->addWidget(padSub,       1, 4);
layoutpad->addWidget(padPlus,      2, 2);
layoutpad->addWidget(padEnter,     2, 3);
layoutpad->addWidget(padGrp,       2, 4);
layoutpad->addWidget(pad7,         3, 2);
layoutpad->addWidget(pad8,         3, 3);
layoutpad->addWidget(pad9,         3, 4);
layoutpad->addWidget(pad4,         4, 2);
layoutpad->addWidget(pad5,         4, 3);
layoutpad->addWidget(pad6,         4, 4);
layoutpad->addWidget(pad1,         5, 2);
layoutpad->addWidget(pad2,         5, 3);
layoutpad->addWidget(pad3,         5, 4);
layoutpad->addWidget(padClear,     6, 2);
layoutpad->addWidget(pad0,         6, 3);
layoutpad->addWidget(padPoint,     6, 4);
layoutpad->addWidget(padFULL,      6, 5);
layoutpad->addWidget(padGoto,      7, 2);
layoutpad->addWidget(padRec,       7, 3);
layoutpad->addWidget(padUpdate,    7, 4);
layoutpad->addWidget(padAT,        7, 5);


layoutH = new QGridLayout;
layoutH->setSpacing(5);
layoutH->addWidget(ecranSelect,  0, 0, 1, 2);
layoutH->addItem(layoutpad,      0, 2, 2, 5);
layoutH->addWidget(padPrev,      1, 0);
layoutH->addWidget(padNext,      1, 1);
layoutH->addWidget(ecrantxt,    2, 0, 2, 6);
layoutH->addWidget(yes,          2, 6);
layoutH->addWidget(no,           3, 6);
layoutH->addWidget(masterSceneT, 4, 0, 1, 3);
layoutH->addWidget(masterSubsT,  4, 3, 1, 4);


HomeTab->setLayout(layoutH);





//// SUBS ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

QLabel *page = new QLabel;
page->setText("page");

subnumpage = new QComboBox;
subnumpage->setStyleSheet("QComboBox                   { background: transparent; color: transparent;border:transparent;}"
                          "QComboBox::drop-down        { border-width: 0px; width: 0px; border-style: none;} "
                          "QComboBox QAbstractItemView { font-size: 17pt;}");
subnumpage->setView(new QListView());
for (int i=1 ; i<26 ; i++) {subnumpage->addItem(QString::number(i));}
subnumpage->setMaximumWidth(screenWidth/10);
subnumpage->setMaximumHeight(screenHeight/16);

subnumpageLabel = new QLabel(subnumpage);
subnumpageLabel->setStyleSheet("QLabel { background: lightblue; color: black;}");
subnumpageLabel->setFixedWidth(screenWidth/10);
subnumpageLabel->setFixedHeight(screenHeight/16);

nameOrContent = new QPushButton;
nameOrContent->setText("  Name   ");
nameOrContent->setStyleSheet("QPushButton { background-color:navy; color:white; border-color:navy;font-size: 20pt;}");
nameOrContent->setFocusPolicy(Qt::NoFocus);
nameOrContent->setMaximumHeight(screenHeight/16);

nomPageSub = new QLineEdit;
nomPageSub->setReadOnly(true);
nomPageSub->setStyleSheet("QLineEdit { font : bold; border:transparent;font-size: 24pt;}");
nomPageSub->setText("                                  ");
nomPageSub->setAlignment(Qt::AlignHCenter);
nomPageSub->setMinimumHeight(screenHeight/12);

masterpagemoins = new QPushButton;
masterpagemoins->setText("<");
masterpagemoins->setFixedWidth(screenWidth/7.5);
masterpagemoins->setFocusPolicy(Qt::NoFocus);
masterpagemoins->setStyleSheet("QPushButton         { background-color:dimgrey; color:white;border-color:dimgrey;}"
                               "QPushButton:disabled{ background-color:black; color:grey;}");
masterpagemoins->setMaximumHeight(screenHeight/15);

masterpageplus = new QPushButton;
masterpageplus->setText(">");
masterpageplus->setFixedWidth(screenWidth/7.5);
masterpageplus->setFocusPolicy(Qt::NoFocus);
masterpageplus->setStyleSheet("QPushButton         { background-color:dimgrey; color:white;border-color:dimgrey;}"
                              "QPushButton:disabled{ background-color:black; color:grey;}");
masterpageplus->setMaximumHeight(screenHeight/15);


// ///////

subnum1 = new  QLineEdit ;
subnum1->setFixedWidth(screenWidth/7.6);
subnum1->setSizePolicy(QSizePolicy:: Minimum , QSizePolicy::Expanding);
subnum1->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
subnum1->setReadOnly(true);
subnum1->setText("1");

subnum2 = new  QLineEdit ;
subnum2->setFixedWidth(screenWidth/7.6);
subnum2->setSizePolicy(QSizePolicy:: Minimum , QSizePolicy::Expanding);
subnum2->setAlignment(Qt::AlignCenter |Qt::AlignHCenter);
subnum2->setReadOnly(true);
subnum2->setText("2");

subnum3 = new  QLineEdit ;
subnum3->setFixedWidth(screenWidth/7.6);
subnum3->setSizePolicy(QSizePolicy:: Minimum , QSizePolicy::Expanding);
subnum3->setAlignment(Qt::AlignCenter |Qt::AlignHCenter);
subnum3->setReadOnly(true);
subnum3->setText("3");

subnum4 = new  QLineEdit ;
subnum4->setFixedWidth(screenWidth/7.6);
subnum4->setSizePolicy(QSizePolicy:: Minimum , QSizePolicy::Expanding);
subnum4->setAlignment(Qt::AlignCenter |Qt::AlignHCenter);
subnum4->setReadOnly(true);
subnum4->setText("4");

subnum5 = new  QLineEdit ;
subnum5->setFixedWidth(screenWidth/7.6);
subnum5->setSizePolicy(QSizePolicy:: Minimum , QSizePolicy::Expanding);
subnum5->setAlignment(Qt::AlignCenter |Qt::AlignHCenter);
subnum5->setReadOnly(true);
subnum5->setText("5");

subnum6 = new  QLineEdit ;
subnum6->setFixedWidth(screenWidth/7.6);
subnum6->setSizePolicy(QSizePolicy:: Minimum , QSizePolicy::Expanding);
subnum6->setAlignment(Qt::AlignCenter |Qt::AlignHCenter);
subnum6->setReadOnly(true);
subnum6->setText("6");

subnum7 = new  QLineEdit ;
subnum7->setFixedWidth(screenWidth/7.6);
subnum7->setSizePolicy(QSizePolicy:: Minimum , QSizePolicy::Expanding);
subnum7->setAlignment(Qt::AlignCenter |Qt::AlignHCenter);
subnum7->setReadOnly(true);
subnum7->setText("7");

subnum8 = new  QLineEdit ;
subnum8->setFixedWidth(screenWidth/7.6);
subnum8->setSizePolicy(QSizePolicy:: Minimum , QSizePolicy::Expanding);
subnum8->setAlignment(Qt::AlignCenter |Qt::AlignHCenter);
subnum8->setReadOnly(true);
subnum8->setText("8");

subnum9 = new  QLineEdit ;
subnum9->setFixedWidth(screenWidth/7.6);
subnum9->setSizePolicy(QSizePolicy:: Minimum , QSizePolicy::Expanding);
subnum9->setAlignment(Qt::AlignCenter |Qt::AlignHCenter);
subnum9->setReadOnly(true);
subnum9->setText("9");

subnum10 = new  QLineEdit ;
subnum10->setFixedWidth(screenWidth/7.6);
subnum10->setSizePolicy(QSizePolicy:: Minimum , QSizePolicy::Expanding);
subnum10->setAlignment(Qt::AlignCenter |Qt::AlignHCenter);
subnum10->setReadOnly(true);
subnum10->setText("10");

subsNumList = new  QList<QLineEdit*>;
subsNumList->append(subnum1);
subsNumList->append(subnum2);
subsNumList->append(subnum3);
subsNumList->append(subnum4);
subsNumList->append(subnum5);
subsNumList->append(subnum6);
subsNumList->append(subnum7);
subsNumList->append(subnum8);
subsNumList->append(subnum9);
subsNumList->append(subnum10);

Flash01 = new multiPushButton;
Flash01->setAttribute(Qt::WA_AcceptTouchEvents);
Flash01->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
Flash01->setText(" FLASH ");
Flash01->setFocusPolicy(Qt::NoFocus);
Flash01->setStyleSheet("QPushButton        { height: 40px;font-size:17px;}"
                       "QPushButton:pressed{ background-color: navy; border: none;}"
                       "QPushButton:checked{ background-color: navy; border: none;}");
Flash01->setCheckable(true);

Flash02 = new multiPushButton;
Flash02->setAttribute(Qt::WA_AcceptTouchEvents);
Flash02->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
Flash02->setText(" FLASH ");
Flash02->setFocusPolicy(Qt::NoFocus);
Flash02->setStyleSheet("QPushButton        { height: 40px;font-size:17px;}"
                       "QPushButton:pressed{ background-color: navy; border: none;}"
                       "QPushButton:checked{ background-color: navy; border: none;}");
Flash02->setCheckable(true);

Flash03 = new multiPushButton;
Flash03->setAttribute(Qt::WA_AcceptTouchEvents);
Flash03->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
Flash03->setText(" FLASH ");
Flash03->setFocusPolicy(Qt::NoFocus);
Flash03->setStyleSheet("QPushButton        { height: 40px;font-size:17px;}"
                       "QPushButton:pressed{ background-color: navy; border: none;}"
                       "QPushButton:checked{ background-color: navy; border: none;}");
Flash03->setCheckable(true);

Flash04 = new multiPushButton;
Flash04->setAttribute(Qt::WA_AcceptTouchEvents);
Flash04->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
Flash04->setText(" FLASH ");
Flash04->setFocusPolicy(Qt::NoFocus);
Flash04->setStyleSheet("QPushButton        { height: 40px;font-size:17px;}"
                       "QPushButton:pressed{ background-color: navy; border: none;}"
                       "QPushButton:checked{ background-color: navy; border: none;}");
Flash04->setCheckable(true);

Flash05 = new multiPushButton;
Flash05->setAttribute(Qt::WA_AcceptTouchEvents);
Flash05->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
Flash05->setText(" FLASH ");
Flash05->setFocusPolicy(Qt::NoFocus);
Flash05->setStyleSheet("QPushButton        { height: 40px;font-size:17px;}"
                       "QPushButton:pressed{ background-color: navy; border: none;}"
                       "QPushButton:checked{ background-color: navy; border: none;}");
Flash05->setCheckable(true);

Flash06 = new multiPushButton;
Flash06->setAttribute(Qt::WA_AcceptTouchEvents);
Flash06->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
Flash06->setText(" FLASH ");
Flash06->setFocusPolicy(Qt::NoFocus);
Flash06->setStyleSheet("QPushButton        { height: 40px;font-size:17px;}"
                       "QPushButton:pressed{ background-color: navy; border: none;}"
                       "QPushButton:checked{ background-color: navy; border: none;}");
Flash06->setCheckable(true);

Flash07 = new multiPushButton;
Flash07->setAttribute(Qt::WA_AcceptTouchEvents);
Flash07->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
Flash07->setText(" FLASH ");
Flash07->setFocusPolicy(Qt::NoFocus);
Flash07->setStyleSheet("QPushButton        { height: 40px;font-size:17px;}"
                       "QPushButton:pressed{ background-color: navy; border: none;}"
                       "QPushButton:checked{ background-color: navy; border: none;}");
Flash07->setCheckable(true);

Flash08 = new multiPushButton;
Flash08->setAttribute(Qt::WA_AcceptTouchEvents);
Flash08->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
Flash08->setText(" FLASH ");
Flash08->setFocusPolicy(Qt::NoFocus);
Flash08->setStyleSheet("QPushButton        { height: 40px;font-size:17px;}"
                       "QPushButton:pressed{ background-color: navy; border: none;}"
                       "QPushButton:checked{ background-color: navy; border: none;}");
Flash08->setCheckable(true);

Flash09 = new multiPushButton;
Flash09->setAttribute(Qt::WA_AcceptTouchEvents);
Flash09->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
Flash09->setText(" FLASH ");
Flash09->setFocusPolicy(Qt::NoFocus);
Flash09->setStyleSheet("QPushButton        { height: 45px;font-size:17px;}"
                       "QPushButton:pressed{ background-color: navy; border: none;}"
                       "QPushButton:checked{ background-color: navy; border: none;}");
Flash09->setCheckable(true);

Flash10 = new multiPushButton;
Flash10->setAttribute(Qt::WA_AcceptTouchEvents);
Flash10->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
Flash10->setText(" FLASH ");
Flash10->setFocusPolicy(Qt::NoFocus);
Flash10->setStyleSheet("QPushButton        { height: 40px;font-size:17px;}"
                       "QPushButton:pressed{ background-color: navy; border: none;}"
                       "QPushButton:checked{ background-color: navy; border: none;}");
Flash10->setCheckable(true);

subsFlashList = new QList<multiPushButton*>;
subsFlashList->append(Flash01);
subsFlashList->append(Flash02);
subsFlashList->append(Flash03);
subsFlashList->append(Flash04);
subsFlashList->append(Flash05);
subsFlashList->append(Flash06);
subsFlashList->append(Flash07);
subsFlashList->append(Flash08);
subsFlashList->append(Flash09);
subsFlashList->append(Flash10);

Sub01T = new SlideH;
Sub01T->setAttribute(Qt::WA_AcceptTouchEvents);
Sub01T->setEnabled(true);
Sub01T->setStyleSheet("QFrame {border :0px outset transparent}");
Sub01 = new QSlider(Sub01T);
Sub01->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
Sub01->setMaximum(255);
Sub01->setOrientation(Qt::Horizontal);
Sub01->setEnabled(false);
Sub01->setStyleSheet(" QSlider::sub-page:disabled {background: navy; border: grey;}");
Sub01txt = new QLabel(Sub01);
Sub01txt->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
Sub01txt->setText("                                   ");
Sub01txt->setStyleSheet("QLabel{font-size:17px;}");

Sub02T = new SlideH;
Sub02T->setAttribute(Qt::WA_AcceptTouchEvents);
Sub02T->setEnabled(true);
Sub02T->setStyleSheet("QFrame {border :0px outset transparent}");
Sub02 = new QSlider(Sub02T);
Sub02->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
Sub02->setMaximum(255);
Sub02->setOrientation(Qt::Horizontal);
Sub02->setEnabled(false);
Sub02->setStyleSheet(" QSlider::sub-page:disabled {background: navy; border: grey;}");
Sub02txt = new QLabel(Sub02);
Sub02txt->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
Sub02txt->setText("                                   ");
Sub02txt->setStyleSheet("QLabel{font-size:17px;}");

Sub03T = new SlideH;
Sub03T->setAttribute(Qt::WA_AcceptTouchEvents);
Sub03T->setEnabled(true);
Sub03T->setStyleSheet("QFrame {border :0px outset transparent}");
Sub03 = new QSlider(Sub03T);
Sub03->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
Sub03->setMaximum(255);
Sub03->setOrientation(Qt::Horizontal);
Sub03->setEnabled(false);
Sub03->setStyleSheet(" QSlider::sub-page:disabled {background: navy; border: grey;}");
Sub03txt = new QLabel(Sub03);
Sub03txt->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
Sub03txt->setText("                                   ");
Sub03txt->setStyleSheet("QLabel{font-size:17px;}");

Sub04T = new SlideH;
Sub04T->setAttribute(Qt::WA_AcceptTouchEvents);
Sub04T->setEnabled(true);
Sub04T->setStyleSheet("QFrame {border :0px outset transparent}");
Sub04 = new QSlider(Sub04T);
Sub04->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
Sub04->setMaximum(255);
Sub04->setOrientation(Qt::Horizontal);
Sub04->setEnabled(false);
Sub04->setStyleSheet(" QSlider::sub-page:disabled {background: navy; border: grey;}");
Sub04txt = new QLabel(Sub04);
Sub04txt->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
Sub04txt->setText("                                   ");
Sub04txt->setStyleSheet("QLabel{font-size:17px;}");

Sub05T = new SlideH;
Sub05T->setAttribute(Qt::WA_AcceptTouchEvents);
Sub05T->setEnabled(true);
Sub05T->setStyleSheet("QFrame {border :0px outset transparent}");
Sub05 = new QSlider(Sub05T);
Sub05->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
Sub05->setMaximum(255);
Sub05->setOrientation(Qt::Horizontal);
Sub05->setEnabled(false);
Sub05->setStyleSheet(" QSlider::sub-page:disabled {background: navy; border: grey;}");
Sub05txt = new QLabel(Sub05);
Sub05txt->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
Sub05txt->setText("                                   ");
Sub05txt->setStyleSheet("QLabel{font-size:17px;}");

Sub06T = new SlideH;
Sub06T->setAttribute(Qt::WA_AcceptTouchEvents);
Sub06T->setEnabled(true);
Sub06T->setStyleSheet("QFrame {border :0px outset transparent}");
Sub06 = new QSlider(Sub06T);
Sub06->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
Sub06->setMaximum(255);
Sub06->setOrientation(Qt::Horizontal);
Sub06->setEnabled(false);
Sub06->setStyleSheet(" QSlider::sub-page:disabled {background: navy; border: grey;}");
Sub06txt = new QLabel(Sub06);
Sub06txt->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
Sub06txt->setText("                                   ");
Sub06txt->setStyleSheet("QLabel{font-size:17px;}");

Sub07T = new SlideH;
Sub07T->setAttribute(Qt::WA_AcceptTouchEvents);
Sub07T->setEnabled(true);
Sub07T->setStyleSheet("QFrame {border :0px outset transparent}");
Sub07 = new QSlider(Sub07T);
Sub07->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
Sub07->setMaximum(255);
Sub07->setOrientation(Qt::Horizontal);
Sub07->setEnabled(false);
Sub07->setStyleSheet(" QSlider::sub-page:disabled {background: navy; border: grey;}");
Sub07txt = new QLabel(Sub07);
Sub07txt->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
Sub07txt->setText("                                   ");
Sub07txt->setStyleSheet("QLabel{font-size:17px;}");

Sub08T = new SlideH;
Sub08T->setAttribute(Qt::WA_AcceptTouchEvents);
Sub08T->setEnabled(true);
Sub08T->setStyleSheet("QFrame {border :0px outset transparent}");
Sub08 = new QSlider(Sub08T);
Sub08->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
Sub08->setMaximum(255);
Sub08->setOrientation(Qt::Horizontal);
Sub08->setEnabled(false);
Sub08->setStyleSheet(" QSlider::sub-page:disabled {background: navy; border: grey;}");
Sub08txt = new QLabel(Sub08);
Sub08txt->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
Sub08txt->setText("                                   ");
Sub08txt->setStyleSheet("QLabel{font-size:17px;}");

Sub09T = new SlideH;
Sub09T->setAttribute(Qt::WA_AcceptTouchEvents);
Sub09T->setEnabled(true);
Sub09T->setStyleSheet("QFrame {border :0px outset transparent}");
Sub09 = new QSlider(Sub09T);
Sub09->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
Sub09->setMaximum(255);
Sub09->setOrientation(Qt::Horizontal);
Sub09->setEnabled(false);
Sub09->setStyleSheet(" QSlider::sub-page:disabled{background: navy; border: grey;}");
Sub09txt = new QLabel(Sub09);
Sub09txt->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
Sub09txt->setText("                                   ");
Sub09txt->setStyleSheet("QLabel{font-size:17px;}");

Sub10T = new SlideH;
Sub10T->setAttribute(Qt::WA_AcceptTouchEvents);
Sub10T->setEnabled(true);
Sub10T->setStyleSheet("QFrame {border :0px outset transparent}");
Sub10 = new QSlider(Sub10T);
Sub10->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
Sub10->setMaximum(255);
Sub10->setOrientation(Qt::Horizontal);
Sub10->setEnabled(false);
Sub10->setStyleSheet(" QSlider::sub-page:disabled{background: navy; border: grey;}");
Sub10txt = new QLabel(Sub10);
Sub10txt->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
Sub10txt->setText("                                   ");
Sub10txt->setStyleSheet("QLabel{font-size:17px;}");

QVBoxLayout *sub1Lay = new QVBoxLayout(Sub01T);
sub1Lay->setContentsMargins(0,0,0,0);
sub1Lay->addWidget(Sub01);
QVBoxLayout *sub2Lay = new QVBoxLayout(Sub02T);
sub2Lay->setContentsMargins(0,0,0,0);
sub2Lay->addWidget(Sub02);
QVBoxLayout *sub3Lay = new QVBoxLayout(Sub03T);
sub3Lay->setContentsMargins(0,0,0,0);
sub3Lay->addWidget(Sub03);
QVBoxLayout *sub4Lay = new QVBoxLayout(Sub04T);
sub4Lay->setContentsMargins(0,0,0,0);
sub4Lay->addWidget(Sub04);
QVBoxLayout *sub5Lay = new QVBoxLayout(Sub05T);
sub5Lay->setContentsMargins(0,0,0,0);
sub5Lay->addWidget(Sub05);
QVBoxLayout *sub6Lay = new QVBoxLayout(Sub06T);
sub6Lay->setContentsMargins(0,0,0,0);
sub6Lay->addWidget(Sub06);
QVBoxLayout *sub7Lay = new QVBoxLayout(Sub07T);
sub7Lay->setContentsMargins(0,0,0,0);
sub7Lay->addWidget(Sub07);
QVBoxLayout *sub8Lay = new QVBoxLayout(Sub08T);
sub8Lay->setContentsMargins(0,0,0,0);
sub8Lay->addWidget(Sub08);
QVBoxLayout *sub9Lay = new QVBoxLayout(Sub09T);
sub9Lay->setContentsMargins(0,0,0,0);
sub9Lay->addWidget(Sub09);
QVBoxLayout *sub10Lay = new QVBoxLayout(Sub10T);
sub10Lay->setContentsMargins(0,0,0,0);
sub10Lay->addWidget(Sub10);

QVBoxLayout *sub1Laytxt = new QVBoxLayout(Sub01);
sub1Laytxt->setContentsMargins(0,0,0,0);
sub1Laytxt->addWidget(Sub01txt);
QVBoxLayout *sub2Laytxt = new QVBoxLayout(Sub02);
sub2Laytxt->setContentsMargins(0,0,0,0);
sub2Laytxt->addWidget(Sub02txt);
QVBoxLayout *sub3Laytxt = new QVBoxLayout(Sub03);
sub3Laytxt->setContentsMargins(0,0,0,0);
sub3Laytxt->addWidget(Sub03txt);
QVBoxLayout *sub4Laytxt = new QVBoxLayout(Sub04);
sub4Laytxt->setContentsMargins(0,0,0,0);
sub4Laytxt->addWidget(Sub04txt);
QVBoxLayout *sub5Laytxt = new QVBoxLayout(Sub05);
sub5Laytxt->setContentsMargins(0,0,0,0);
sub5Laytxt->addWidget(Sub05txt);
QVBoxLayout *sub6Laytxt = new QVBoxLayout(Sub06);
sub6Laytxt->setContentsMargins(0,0,0,0);
sub6Laytxt->addWidget(Sub06txt);
QVBoxLayout *sub7Laytxt = new QVBoxLayout(Sub07);
sub7Laytxt->setContentsMargins(0,0,0,0);
sub7Laytxt->addWidget(Sub07txt);
QVBoxLayout *sub8Laytxt = new QVBoxLayout(Sub08);
sub8Laytxt->setContentsMargins(0,0,0,0);
sub8Laytxt->addWidget(Sub08txt);
QVBoxLayout *sub9Laytxt = new QVBoxLayout(Sub09);
sub9Laytxt->setContentsMargins(0,0,0,0);
sub9Laytxt->addWidget(Sub09txt);
QVBoxLayout *sub10Laytxt = new QVBoxLayout(Sub10);
sub10Laytxt->setContentsMargins(0,0,0,0);
sub10Laytxt->addWidget(Sub10txt);

subsList = new QList<QSlider*>;
subsList->append(Sub01);
subsList->append(Sub02);
subsList->append(Sub03);
subsList->append(Sub04);
subsList->append(Sub05);
subsList->append(Sub06);
subsList->append(Sub07);
subsList->append(Sub08);
subsList->append(Sub09);
subsList->append(Sub10);

subsListT = new QList<SlideH*>;
subsListT->append(Sub01T);
subsListT->append(Sub02T);
subsListT->append(Sub03T);
subsListT->append(Sub04T);
subsListT->append(Sub05T);
subsListT->append(Sub06T);
subsListT->append(Sub07T);
subsListT->append(Sub08T);
subsListT->append(Sub09T);
subsListT->append(Sub10T);

subsTextList = new QList<QLabel*>;
subsTextList->append(Sub01txt);
subsTextList->append(Sub02txt);
subsTextList->append(Sub03txt);
subsTextList->append(Sub04txt);
subsTextList->append(Sub05txt);
subsTextList->append(Sub06txt);
subsTextList->append(Sub07txt);
subsTextList->append(Sub08txt);
subsTextList->append(Sub09txt);
subsTextList->append(Sub10txt);

layoutTitre = new QHBoxLayout;
layoutTitre->setContentsMargins(0, 0, 0, 5);
layoutTitre->addWidget(masterpagemoins);
layoutTitre->addWidget(masterpageplus);
layoutTitre->addWidget(page);
layoutTitre->addWidget(subnumpage);
layoutTitre->addStretch(1);
layoutTitre->addWidget(nameOrContent);


layoutSub1 = new QHBoxLayout;
layoutSub1->setContentsMargins(0,0,0,0);
layoutSub1->addWidget(Flash01);
layoutSub1->addWidget(subnum1);
layoutSub1->addWidget(Sub01T);

layoutSub2 = new QHBoxLayout;
layoutSub2->setContentsMargins(0,0,0,0);
layoutSub2->addWidget(Flash02);
layoutSub2->addWidget(subnum2);
layoutSub2->addWidget(Sub02T);

layoutSub3 = new QHBoxLayout;
layoutSub3->setContentsMargins(0,0,0,0);
layoutSub3->addWidget(Flash03);
layoutSub3->addWidget(subnum3);
layoutSub3->addWidget(Sub03T);

layoutSub4 = new QHBoxLayout;
layoutSub4->setContentsMargins(0,0,0,0);
layoutSub4->addWidget(Flash04);
layoutSub4->addWidget(subnum4);
layoutSub4->addWidget(Sub04T);

layoutSub5 = new QHBoxLayout;
layoutSub5->setContentsMargins(0,0,0,0);
layoutSub5->addWidget(Flash05);
layoutSub5->addWidget(subnum5);
layoutSub5->addWidget(Sub05T);

layoutSub6 = new QHBoxLayout;
layoutSub6->setContentsMargins(0,0,0,0);
layoutSub6->addWidget(Flash06);
layoutSub6->addWidget(subnum6);
layoutSub6->addWidget(Sub06T);

layoutSub7 = new QHBoxLayout;
layoutSub7->setContentsMargins(0,0,0,0);
layoutSub7->addWidget(Flash07);
layoutSub7->addWidget(subnum7);
layoutSub7->addWidget(Sub07T);

layoutSub8 = new QHBoxLayout;
layoutSub8->setContentsMargins(0,0,0,0);
layoutSub8->addWidget(Flash08);
layoutSub8->addWidget(subnum8);
layoutSub8->addWidget(Sub08T);

layoutSub9 = new QHBoxLayout;
layoutSub9->setContentsMargins(0,0,0,0);
layoutSub9->addWidget(Flash09);
layoutSub9->addWidget(subnum9);
layoutSub9->addWidget(Sub09T);

layoutSub10 = new QHBoxLayout;
layoutSub10->setContentsMargins(0,0,0,0);
layoutSub10->addWidget(Flash10);
layoutSub10->addWidget(subnum10);
layoutSub10->addWidget(Sub10T);


layoutSU = new QGridLayout;
layoutSU->setSpacing(0);
layoutSU->addItem(layoutTitre, 0, 0);
layoutSU->addItem(layoutSub1, 1, 0);
layoutSU->addItem(layoutSub2, 2, 0);
layoutSU->addItem(layoutSub3, 3, 0);
layoutSU->addItem(layoutSub4, 4, 0);
layoutSU->addItem(layoutSub5, 5, 0);
layoutSU->addItem(layoutSub6, 6, 0);
layoutSU->addItem(layoutSub7, 7, 0);
layoutSU->addItem(layoutSub8, 8, 0);
layoutSU->addItem(layoutSub9, 9, 0);
layoutSU->addItem(layoutSub10, 10, 0);
layoutSU->addWidget(nomPageSub, 11, 0);


SUBsTab->setLayout(layoutSU);

////// Scene ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


Pause = new QPushButton;
Pause->setText("PAUSE");
Pause->setFocusPolicy(Qt::NoFocus);
Pause->setStyleSheet("QPushButton {height: 32px; font-size:15pt;}");

GoBack = new QPushButton;
GoBack->setText("GOBACK");
GoBack->setFocusPolicy(Qt::NoFocus);
GoBack->setStyleSheet("QPushButton {height: 32px;font-size:13pt;}");

GO = new QPushButton;
GO->setText("GO");
GO->setFocusPolicy(Qt::NoFocus);
GO->setStyleSheet("QPushButton {height: 32px;font-size:15pt;}");

stepMoins = new QPushButton;
stepMoins->setText("STEP -");
stepMoins->setFixedWidth(screenWidth/3.75+10);
stepMoins->setFocusPolicy(Qt::NoFocus);
stepMoins->setStyleSheet("QPushButton          {font-size:20pt; background-color:dimgrey; color:white;border-color:dimgrey;}"
                         "QPushButton:disabled {color:grey;background-color:black;}");

stepPlus = new QPushButton;
stepPlus->setText("STEP +");
stepPlus->setFixedWidth(screenWidth/3.75+10);
stepPlus->setFocusPolicy(Qt::NoFocus);
stepPlus->setStyleSheet("QPushButton          {font-size:20pt; background-color:dimgrey; color:white;border-color:dimgrey;}"
                        "QPushButton:disabled {color:grey;background-color:black;}");

sliderX1T = new SlideH;
sliderX1T->setAttribute(Qt::WA_AcceptTouchEvents);
sliderX1T->setFixedWidth(screenWidth/6.3);
sliderX1T->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

sliderX1 = new QSlider(sliderX1T);
sliderX1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
sliderX1->setEnabled(false);
sliderX1->setRange(0,255);
sliderX1->setOrientation(Qt::Vertical);
sliderX1->setStyleSheet("QSlider           {border-color: outset white; padding: 1px 2px 2px 2px;}"
                        "QSlider::sub-page {background-color: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 red, stop: 0.5 lightred, stop: 1 darkred);border-radius:0px;}");

QVBoxLayout *X1 = new QVBoxLayout(sliderX1T);
X1->setContentsMargins(0,0,0,0);
X1->addWidget(sliderX1);

sliderX2T = new SlideH;
sliderX2T->setAttribute(Qt::WA_AcceptTouchEvents);
sliderX2T->setFixedWidth(screenWidth/6.3);
sliderX2T->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

sliderX2 = new QSlider(sliderX2T);
sliderX2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
sliderX2->setEnabled(false);
sliderX2->setRange(0,255);
sliderX2->setValue(255);
sliderX2->setOrientation(Qt::Vertical);
sliderX2->setStyleSheet("QSlider         {border-color: outset white;  padding: 1px 2px 2px 2px; background-color: black;}"
                        "QSlider::groove {background:QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 green, stop: 0.5 lightgreen,"
                                                                           "stop: 1 darkgreen); border-radius:0px;}");

QVBoxLayout *X2 = new QVBoxLayout(sliderX2T);
X2->setContentsMargins(0,0,0,0);
X2->addWidget(sliderX2);

QLabel *labelStep = new QLabel;
labelStep->setText("Step");
labelStep->setFixedWidth((screenWidth/7.5)-5);
labelStep->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
labelStep->setStyleSheet("QLabel{font-size:14pt;}");

QLabel *labelCue = new QLabel;
labelCue->setText("Cue");
labelCue->setFixedWidth((screenWidth/7.5)+5);
labelCue->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
labelCue->setStyleSheet("QLabel{font-size:14pt;}");

nStepX1 = new QLineEdit;
nStepX1->setFixedWidth((screenWidth/7.5)-5);
nStepX1->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
nStepX1->setReadOnly(true);
nStepX1->setStyleSheet("QLineEdit {color : red; border-color : red;}");

nCueX1 = new QLineEdit;
nCueX1->setFixedWidth((screenWidth/7.5)+10);
nCueX1->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
nCueX1->setReadOnly(true);
nCueX1->setStyleSheet("QLineEdit {color : red; border-color : red;font-size:14pt;}");

textStepX1 = new QTextEdit;
textStepX1->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
textStepX1->setReadOnly(true);
//textStepX1->setFixedHeight(screenHeight/4);
textStepX1->setStyleSheet("QTextEdit {color : red; border: 2px outset red;}");
textStepX1->setText("                                                                                                                                                                                                                                                                ");

nStepX2 = new QLineEdit;
nStepX2->setFixedWidth((screenWidth/7.5)-5);
nStepX2->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
nStepX2->setReadOnly(true);
nStepX2->setStyleSheet("QLineEdit {color : green; border-color : green;}");

nCueX2 = new QLineEdit;
nCueX2->setFixedWidth((screenWidth/7.5)+10);
nCueX2->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
nCueX2->setReadOnly(true);
nCueX2->setStyleSheet("QLineEdit {color : green; border-color : green;font-size:14pt;}");

textStepX2 = new QTextEdit;
textStepX2->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
//textStepX2->setFixedHeight(screenHeight/5.5);
textStepX2->setReadOnly(true);
textStepX2->setStyleSheet("QTextEdit {color : green; border: 2px outset green;}");
textStepX2->setText("                                                                                                                                                                                                                                                                ");

joystickT = new SlideH;
joystickT->setAttribute(Qt::WA_AcceptTouchEvents);
joystickT->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
joystickT->setStyleSheet("QFrame {border :0px outset transparent}");

joystick = new QSlider(joystickT);
joystick->setMaximum(255);
joystick->setValue(127);
joystick->setEnabled(false);
joystick->setSizePolicy(QSizePolicy:: Expanding , QSizePolicy::Expanding);

joystick->setStyleSheet("QSlider::groove   {border: 1px outset indigo; background: indigo; border-radius: 4px;}"
                        "QSlider::sub-page {border: 1px outset indigo; background: indigo; border-radius: 4px;}"
                        "QSlider::handle   {border: 3px outset fuchsia;border-radius: 10px; background: transparent;}");

QVBoxLayout *joyT = new QVBoxLayout(joystickT);
joyT->setMargin(0);
joyT->addWidget(joystick);

joystickLevel = new QLabel(joystick);
joystickLevel->setStyleSheet("QLabel {border-color : transparent; background-color : transparent}");
joystickLevel->setText("50");
joystickLevel->setAlignment(Qt::AlignTop|Qt::AlignHCenter);

QLabel *textJoystick = new QLabel(joystick);
textJoystick->setText("J\nO\nY\nS\nT\nI\nC\nK");
textJoystick->setStyleSheet("QLabel {color:white; font : bold;font-size:14pt}");
textJoystick->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);

QVBoxLayout *joy = new QVBoxLayout(joystick);
joy->addWidget(joystickLevel);
joy->addWidget(textJoystick);

layoutGo = new QVBoxLayout;
layoutGo->addStretch(1);
layoutGo->setSpacing(5);
layoutGo->addWidget(Pause);
layoutGo->addWidget(GoBack);
layoutGo->addWidget(GO);
layoutGo->addStretch(1);

layoutSeq = new QGridLayout;
layoutSeq->addWidget(stepMoins, 0, 0, 1, 2);
layoutSeq->addWidget(nStepX1,   1, 0);
layoutSeq->addWidget(nCueX1,    1, 1);
layoutSeq->addWidget(labelStep, 2, 0);
layoutSeq->addWidget(labelCue,  2, 1);
layoutSeq->addWidget(nStepX2,   3, 0);
layoutSeq->addWidget(nCueX2,    3, 1);
layoutSeq->addWidget(stepPlus,  4, 0, 1, 2);

layoutS = new QGridLayout;
layoutS->setSpacing(15);
layoutS->addWidget(textStepX1, 0, 0, 1, 3);
layoutS->addLayout(layoutGo,   0, 3);
layoutS->addLayout(layoutSeq,  1, 0);
layoutS->addWidget(sliderX1T,  1, 1);
layoutS->addWidget(sliderX2T,  1, 2);
layoutS->addWidget(joystickT,  1, 3);
layoutS->addWidget(textStepX2, 2, 0, 1, 4);

SceneTab->setLayout(layoutS);





////// Patch //////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

p0 = new QPushButton;
p0->setText("   0   ");
p0->setFocusPolicy(Qt::NoFocus);
p1 = new QPushButton;
p1->setText("1");
p1->setFocusPolicy(Qt::NoFocus);
p2 = new QPushButton;
p2->setText("2");
p2->setFocusPolicy(Qt::NoFocus);
p3 = new QPushButton;
p3->setText("3");
p3->setFocusPolicy(Qt::NoFocus);
p4 = new QPushButton;
p4->setText("4");
p4->setFocusPolicy(Qt::NoFocus);
p5 = new QPushButton;
p5->setText("5");
p5->setFocusPolicy(Qt::NoFocus);
p6 = new QPushButton;
p6->setText("6");
p6->setFocusPolicy(Qt::NoFocus);
p7 = new QPushButton;
p7->setText("7");
p7->setFocusPolicy(Qt::NoFocus);
p8 = new QPushButton;
p8->setText("8");
p8->setFocusPolicy(Qt::NoFocus);
p9 = new QPushButton;
p9->setText("9");
p9->setFocusPolicy(Qt::NoFocus);

chiffresPatch = new QButtonGroup(this);
chiffresPatch->addButton(p0);
chiffresPatch->addButton(p1);
chiffresPatch->addButton(p2);
chiffresPatch->addButton(p3);
chiffresPatch->addButton(p4);
chiffresPatch->addButton(p5);
chiffresPatch->addButton(p6);
chiffresPatch->addButton(p7);
chiffresPatch->addButton(p8);
chiffresPatch->addButton(p9);

padPoint_2 = new QPushButton;
padPoint_2->setText("   .   ");
padPoint_2->setFocusPolicy(Qt::NoFocus);

padClear_2 = new QPushButton;
padClear_2->setText(" Clr ");
padClear_2->setFocusPolicy(Qt::NoFocus);

padPlus_2 = new QPushButton;
padPlus_2->setText(" + ");
padPlus_2->setFocusPolicy(Qt::NoFocus);

padMoins_2 = new QPushButton;
padMoins_2->setText(" - ");
padMoins_2->setFocusPolicy(Qt::NoFocus);

padTHRU_2 = new QPushButton;
padTHRU_2->setText("Thru");
padTHRU_2->setFocusPolicy(Qt::NoFocus);

padEnter_2 = new QPushButton;
padEnter_2->setText("Enter");
padEnter_2->setFocusPolicy(Qt::NoFocus);

padPATCH = new QPushButton;
padPATCH->setText("Patch");
padPATCH->setFocusPolicy(Qt::NoFocus);
padPATCH->setStyleSheet("QPushButton        {background-color:darkred; color:white;border-color:darkred;}"
                      "QPushButton:disabled {background-color:black; color:grey;}");

padUNPATCH = new QPushButton;
padUNPATCH->setText("Un\npatch");
padUNPATCH->setFocusPolicy(Qt::NoFocus);
padUNPATCH->setStyleSheet("QPushButton      {background-color:darkred; color:white;border-color:darkred;}"
                      "QPushButton:disabled {color:grey;background-color:black;}");

padPREV = new QPushButton;
padPREV->setText("Prev");
padPREV->setFocusPolicy(Qt::NoFocus);
padPREV->setStyleSheet("QPushButton         {background-color:dimgrey; color:white;border-color:dimgrey;}"
                      "QPushButton:disabled {color:grey;background-color:black;}");

padNEXT = new QPushButton;
padNEXT->setText("Next");
padNEXT->setFocusPolicy(Qt::NoFocus);
padNEXT->setStyleSheet("QPushButton          {background-color:dimgrey; color:white;border-color:dimgrey;}"
                       "QPushButton:disabled {color:grey;background-color:black;}");



/////////

channelTest = new QPushButton;
channelTest->setStyleSheet("QPushButton:checked          { background-color: purple; border-color: purple; }"
                           "QPushButton:checked:disabled { background-color: black; border: none; }");
channelTest->setText("Ch.TEST");
channelTest->setCheckable(true);
channelTest->setFocusPolicy(Qt::NoFocus);

dimmerTest = new QPushButton;
dimmerTest->setStyleSheet("QPushButton:checked          { background-color: purple; border-color: purple; }"
                          "QPushButton:checked:disabled { background-color: black; border: none; }");
dimmerTest->setText("Dim.TEST");
dimmerTest->setCheckable(true);
dimmerTest->setFocusPolicy(Qt::NoFocus);

dimmer = new QPushButton;
dimmer->setStyleSheet("QPushButton:checked          { background-color: red; border-color: red; }"
                      "QPushButton:checked:disabled { background-color: black; border: none; }");
dimmer->setText("Dimmer");
dimmer->setCheckable(true);
dimmer->setFocusPolicy(Qt::NoFocus);

padCh_2 = new QPushButton;
padCh_2->setStyleSheet("QPushButton:checked          { background-color: red; border-color: red; }"
                       "QPushButton:checked:disabled { background-color: black; border: none; }");
padCh_2->setText("Channel");
padCh_2->setCheckable(true);
padCh_2->setFocusPolicy(Qt::NoFocus);

nChannel = new QTextEdit;
//nChannel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
nChannel->setReadOnly(true);
nChannel->setStyleSheet("QTextEdit:disabled{color:silver}");
nChannel->setFocusPolicy(Qt::NoFocus);
nChannel->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
QScroller::grabGesture(nChannel, QScroller::LeftMouseButtonGesture);

nDimmer = new QTextEdit;
//nDimmer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
nDimmer->setReadOnly(true);
nDimmer->setStyleSheet("QTextEdit:disabled{color:silver}");
nDimmer->setFocusPolicy(Qt::NoFocus);
nDimmer->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
QScroller::grabGesture(nDimmer, QScroller::LeftMouseButtonGesture);

testLevelT = new SlideH;
testLevelT->setAttribute(Qt::WA_AcceptTouchEvents);
testLevelT->setStyleSheet("QFrame {border :0px outset transparent}");
testLevelT->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
testLevelT->setFixedWidth(screenWidth/7.5);

testLevel = new QProgressBar(testLevelT);
testLevel->setMaximum(100);
testLevel->setValue(50);
testLevel->setAlignment(Qt::AlignCenter);
testLevel->setFormat("%p");
testLevel->setOrientation(Qt::Vertical);
testLevel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
testLevel->setStyleSheet(" QProgressBar                 {background: black; border:1px outset purple; border-radius:5px}"
                         " QProgressBar::chunk          {background: purple; border-radius:0px}"
                         " QProgressBar:disabled        {background: darkgrey;}"
                         " QProgressBar::chunk:disabled {background: darkgrey;}"
                                                  );
testLevel->setFocusPolicy(Qt::NoFocus);

QVBoxLayout *testT = new QVBoxLayout(testLevelT);
testT->setMargin(0);
testT->addWidget(testLevel);

line = new QFrame;
line->setFrameStyle(QFrame::VLine | QFrame::Raised);
line->setStyleSheet("QFrame           {border :1px outset dimgrey; border-radius:5px; background:dimgrey;}"
                     "QFrame:disabled {border :1px outset grey; background:grey;}");



ecrantxt_2 = new QLineEdit;
ecrantxt_2->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
ecrantxt_2->setStyleSheet("QLineEdit {background: lightblue;color : black; font-size: 24px}");
ecrantxt_2->setReadOnly(true);
ecrantxt_2->setAlignment(Qt::AlignCenter|Qt::AlignLeading|Qt::AlignLeft);
//ecrantxt_2->setMinimumHeight(screenHeight/10);

yes_2 = new QPushButton;
yes_2->setText("YES");
yes_2->setFocusPolicy(Qt::NoFocus);
yes_2->setStyleSheet("QPushButton {height: 30px;}");
yes_2->setEnabled(false);

no_2 = new QPushButton;
no_2->setText("NO");
no_2->setFocusPolicy(Qt::NoFocus);
no_2->setStyleSheet("QPushButton {height: 30px;}");
no_2->setEnabled(false);

layoutChiffres = new QGridLayout;
layoutChiffres->setSpacing(1);
layoutChiffres->setContentsMargins(0, 0, 0, 5);
layoutChiffres->addWidget(p7,         0, 0);
layoutChiffres->addWidget(p8,         0, 1);
layoutChiffres->addWidget(p9,         0, 2);
layoutChiffres->addWidget(p4,         1, 0);
layoutChiffres->addWidget(p5,         1, 1);
layoutChiffres->addWidget(p6,         1, 2);
layoutChiffres->addWidget(p1,         2, 0);
layoutChiffres->addWidget(p2,         2, 1);
layoutChiffres->addWidget(p3,         2, 2);
layoutChiffres->addWidget(padClear_2, 3, 0);
layoutChiffres->addWidget(p0,         3, 1);
layoutChiffres->addWidget(padPoint_2, 3, 2);

layoutPad = new QGridLayout;
layoutPad->setSpacing(1);
layoutPad->setContentsMargins(0, 0, 0, 5);
layoutPad->addWidget(padMoins_2, 0, 0);
layoutPad->addWidget(padPATCH,   0, 1);
layoutPad->addWidget(padPlus_2,  1, 0);
layoutPad->addWidget(padUNPATCH, 1, 1);
layoutPad->addWidget(padTHRU_2,  2, 0);
layoutPad->addWidget(padPREV,    2, 1);
layoutPad->addWidget(padEnter_2, 3, 0);
layoutPad->addWidget(padNEXT,    3, 1);

layoutCh = new QGridLayout;
layoutCh->setSpacing(0);
layoutCh->setContentsMargins(5, 0, 5, 0);
layoutCh->addWidget(padCh_2,     0, 0);
layoutCh->addWidget(nChannel,    1, 0, 2, 1);
layoutCh->addWidget(channelTest, 3, 0);

layoutDim = new QGridLayout;
layoutDim->setSpacing(0);
layoutDim->setContentsMargins(5, 0, 0, 0);
layoutDim->addWidget(dimmer,      0, 0);
layoutDim->addWidget(nDimmer,     1, 0, 2, 1);
layoutDim->addWidget(dimmerTest,  3, 0);

layoutTxt = new QGridLayout;
layoutTxt->setSpacing(5);
layoutTxt->setContentsMargins(0, 5, 0, 0);
layoutTxt->addWidget(ecrantxt_2, 0, 0, 2, 5);
layoutTxt->addWidget(yes_2 ,     0, 5);
layoutTxt->addWidget(no_2,       1, 5);

layoutP = new QGridLayout;
layoutP->addLayout(layoutChiffres, 0, 0, 1, 2);
layoutP->addLayout(layoutPad,      0, 2, 1, 3);
layoutP->addWidget(testLevelT,     1, 0);
layoutP->addWidget(line,           1, 2);
layoutP->addLayout(layoutCh,       1, 1);
layoutP->addLayout(layoutDim,      1, 3);
layoutP->addLayout(layoutTxt,      2, 0, 1, 4);

PatchTab->setLayout(layoutP);




///////////////////////////////////////////////////////////////////////////////

setCentralWidget(tabs);
}







