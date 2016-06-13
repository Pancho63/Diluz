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

#ifndef RECEIVEOSC_H
#define RECEIVEOSC_H

#include <QDebug>
#include <QUdpSocket>
#include "oscpkt.hh"
#include "window.h"

using namespace oscpkt;


class Listener : public QObject
        {
            Q_OBJECT
     void requestWork();

signals:
     void workRequested();
     void finished();
     void reboot();
     void changeIpDl(QString);
     void connexionOk(bool);

// OSC
    void answer(QString, int);
    void gotoMode(QString);

// Home
    void mscLvl(int);
    void msubLvl(int);
    void txtHome(QString);
    void txtSelect(QString, QString);
    void selection(QString);
    void levelSelect(QString);
    void padInfo(QString);

    void error(int);
    void prepa(bool);
    void scene(bool);


// Subs
    void majNiveauxSelection();
    void subPageText(QString);
    void subPageNo(QString);


    void subNo(QString, int);
    void subMode(QString, int);
    void subName(QString, int);
    void subLvl(int, int);
    void flashFullOn(int);
    void flashFullOff(int);


// Scene
    void lvlX1(int);
    void lvlX2(int);
    void noX1(QString);
    void noX2(QString);
    void cueX1(QString);
    void cueX2(QString);
    void X1text(QString);
    void X2text(QString);
    void goSignal(int);
    void goBackSignal(int);
    void pauseSignal(int);
    void joystickLevelText(QString);
    void joystickLevel(int);


// Patch
    void errorPatch(int);
    void txtPatch(QString);
    void testLvl(int);
    void chantest(QString);
    void dimtest(QString);
    void testChan(bool);
    void testDim(bool);
    void chan(bool);
    void dim(bool);



public slots:
    void goOSC();
    void reStart();

private :

    QUdpSocket *udpSocket;
    QHostAddress groupAddress;

private slots:
    void processPendingDatagrams();


};

#endif // RECEIVEOSC_H

