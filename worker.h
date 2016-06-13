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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QThread>
#include <QUdpSocket>
#include <QMessageBox>
#include <QTimer>
//#include <QSpacerItem>
#include <QHostInfo>
//#include <QStandardItem>


#include "receiveosc.h"
#include "window.h"


using std::string;



class Worker : public QObject
{
    Q_OBJECT


public :
    explicit Worker(QObject *parent = 0);
    ~Worker();

private slots :
    void connexionIsOk(bool);
    void majNiveauxSelection();
    void sendOSC(Message);
    void supensionEtReveil(Qt::ApplicationState);

//OSC
    void IPTelecoChanged(QString);
    void valideIpDlight();
    void validePortSend();
    void validePortIn();
    void startOSC();
    void scan();
    void freshIp();
    void castModeSelect();
    void answerDlight(QString, int);

//home
    void pad(int);

    void padPoint();
    void padclear();
    void paddoubleclear();
    void padplus();
    void padmoins();
    void padthru();
    void padchannel();
    void padlevel();
    void padenter();
    void padfull();
    void padall();
    void padPrev();
    void padNext();


    void padSub();
    void padGrp();
    void padRec();
    void padUpdate();
    void padDoubleUpdate();
    void afficheUpdate();
    void padGoto();
    void padDoubleGoto();
    void envoiGoto();
    void gotoMode(QString);
    void gotoCombo(int);

    void textSelect(QString, QString);
    void padInfo(QString);
    void erase();

    void scene(bool);

    void yES();
    void nO();

    void masterSubs(int);
    void masterScene(int);

    void errorIN(int);

    void freescale();
    void valueMS(int);
    void endMSlider();

//SUBS
    void subNumPage(int);
    void sub01(int);
    void sub02(int);
    void sub03(int);
    void sub04(int);
    void sub05(int);
    void sub06(int);
    void sub07(int);
    void sub08(int);
    void sub09(int);
    void sub10(int);

    void setSubFlashOn(int);
    void setSubFlashOff(int);

    void flashOn1();
    void flashOn2();
    void flashOn3();
    void flashOn4();
    void flashOn5();
    void flashOn6();
    void flashOn7();
    void flashOn8();
    void flashOn9();
    void flashOn10();

    void flashOff1();
    void flashOff2();
    void flashOff3();
    void flashOff4();
    void flashOff5();
    void flashOff6();
    void flashOff7();
    void flashOff8();
    void flashOff9();
    void flashOff10();

    void mpmoins();
    void mpplus();
    void nameOrContent(bool);

    void setSubNum(QString, int);
    void chgText(QString, int);
    void setSubName(QString, int);
    void setSubValue(int, int);



//scene
    void seqplus();
    void seqmoins();
    void seqpause();
    void seqgoback();
    void seqgo();
    void goButton(int);
    void goBackButton(int);
    void pauseButton(int);
    void slideX1(int);
    void slideX2(int);
    void joystick(int);

//patch
    void tabindex(int);
    void errorINPatch(int);
    void padPatch(int);

    void padPointp();
    void padclearp();
    void padplusp();
    void padmoinsp();
    void padthrup();
    void padenterp();

    void patch();
    void unpatch();
    void patchchannel(bool);
    void patchdimmer(bool);
    void prev();
    void next();
    void channeltest(bool);
    void dimmertest(bool);

    void testlevel(int);
    void affichelevel(int);

    void yESp();
    void nOp();


private:

    bool isConnectedToNetwork();

    WindowTeleco *ui;

    QThread *thread;

    Listener *listener;

    QUdpSocket *udpSocketSend;
    QHostAddress groupAddress;
    QHostAddress IpSend;
    QTimer *timer;
    QTimer *timer1;
    QTimer *timer2;

};

#endif // MAINWINDOW_H
