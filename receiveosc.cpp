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

#include "receiveosc.h"
#include "oscpkt.hh"

int         iarg;
int         iarg2;
std::string sarg;
std::string sarg2;
QString     qarg;



QVector<int> chSceneSelected;
QVector<QString> chSceneSelectedLevels;

QVector<int> chPrepaSelected;
QVector<QString> chPrepaSelectedLevels;

QVector<int> subsSelected;
QVector<QString> subsSelectedLevels;


void Listener::requestWork()
{
    emit workRequested();
}

void Listener::goOSC()
{
extern bool multiCastOn;
extern int  PORT;
if (multiCastOn)
              {
              groupAddress = QHostAddress("225.9.99.9");
              udpSocket = new QUdpSocket(this);
              udpSocket->bind(QHostAddress::AnyIPv4, PORT, QUdpSocket::ShareAddress);
              udpSocket->joinMulticastGroup(groupAddress);

              connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
              emit connexionOk(true);
              }

else if (!multiCastOn)
              {
              udpSocket = new QUdpSocket(this);
              udpSocket->bind( PORT, QUdpSocket::ShareAddress);

              connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
              emit connexionOk(true);
              }

}

void Listener::processPendingDatagrams()
{
extern QString onglet;
PacketReader pr;
while (udpSocket->hasPendingDatagrams()) {
    oscpkt::Message *msg;
    QByteArray datagram;
    datagram.resize(udpSocket->pendingDatagramSize());
    udpSocket->readDatagram(datagram.data(), datagram.size());
    pr.init(datagram.data(), datagram.size());



    while (pr.isOk() && (msg = pr.popMessage()) != 0) {

//OSC ////////////////////////////////////////////////////////////////////////////
        if (msg->partialMatch("/setup/"))
        {
             if (msg->match("/setup/login").popStr(sarg).popInt32(iarg).isOkNoMoreArgs()) {
             emit answer(QString::fromStdString(sarg), iarg);
                }
             if (msg->match("/setup/gotoMode").popStr(sarg).isOkNoMoreArgs()) {
             emit gotoMode(QString::fromStdString(sarg));
                }
        }

// Home ////////////////////////////////////////////////////////////////////////////

    if (msg->partialMatch("/pad/"))
    {
              if (msg->match("/pad/errorSignal").popInt32(iarg).isOkNoMoreArgs()) {
              emit error(iarg);}}

    if ((onglet=="home")&(msg->partialMatch("/pad/")))
    {
              if (msg->match("/pad/saisieText").popStr(sarg).isOkNoMoreArgs()) {
              emit txtHome(QString::fromStdString(sarg));}

              if (msg->match("/pad/selection").popStr(sarg).popStr(sarg2).isOkNoMoreArgs()) {
              qarg = QString::fromStdString(sarg);
              emit txtSelect(QString::fromStdString(sarg), QString::fromStdString(sarg2));}

              if (msg->match("/pad/info").popStr(sarg).isOkNoMoreArgs()) {
              emit padInfo(QString::fromStdString(sarg));}

              if (msg->match("/pad/scene").popInt32(iarg).isOkNoMoreArgs()) {
                  if (iarg == 1) {emit scene(true);}
                  else           {emit scene(false);}}

    }


              if ((onglet=="home")&(msg->partialMatch("/circ/")))

              {
                  if (msg->match("/circ/level").popInt32(iarg).popInt32(iarg2).isOkNoMoreArgs()) {
                      for (int i=0 ; i<chSceneSelected.count() ; i++)
                      {if (iarg==chSceneSelected[i])
                      {iarg2=qRound(iarg2/2.55);
                      chSceneSelectedLevels[i]=QString::number(iarg2);}}
                      emit majNiveauxSelection();}



                  if (msg->match("/circ/prepalevel").popInt32(iarg).popInt32(iarg2).isOkNoMoreArgs()) {
                      for (int i=0 ; i<chPrepaSelected.count() ; i++)
                      {if (iarg==chPrepaSelected[i])
                      {iarg2=qRound(iarg2/2.55);
                      chPrepaSelectedLevels[i]=QString::number(iarg2);}}
                      emit majNiveauxSelection();}
               }

              if ((msg->match("/seq/master").popInt32(iarg).isOkNoMoreArgs())&(onglet=="home")) {
              emit mscLvl(iarg);}





// Subs ////////////////////////////////////////////////////////////////////////////

    if ((onglet=="home")&(msg->partialMatch("/sub/")))

    {

        if (msg->match("/sub/level").popInt32(iarg).popInt32(iarg2).isOkNoMoreArgs()) {
            for (int i=0 ; i<subsSelected.count() ; i++)
            {if (iarg==subsSelected[i])
            {iarg2=qRound(iarg2/2.55);
            subsSelectedLevels[i]=QString::number(iarg2);}}
            emit majNiveauxSelection();}

        if (msg->match("/sub/master").popInt32(iarg).isOkNoMoreArgs()) {
       emit msubLvl(iarg);}
    }

    if ((onglet=="subs")&(msg->partialMatch("/sub/")))
    {
              if (msg->match("/sub/pageText").popStr(sarg).isOkNoMoreArgs()) {
               QString qarg = QString::fromStdString(sarg);
             emit subPageText(qarg);}

              if (msg->match("/sub/page").popInt32(iarg).isOkNoMoreArgs()) {
                  qarg = QString::number(iarg);
             emit subPageNo(qarg);}
    }

    if ((onglet=="subs")&(msg->partialMatch("/subStick/")))
    {
             if (msg->match("/subStick/numb").popInt32(iarg).popInt32(iarg2).isOkNoMoreArgs()) {
               qarg = QString::number(iarg2);
             emit subNo(qarg, iarg);}


              if (msg->match("/subStick/mode").popInt32(iarg).popStr(sarg).isOkNoMoreArgs()) {
               QString qarg = QString::fromStdString(sarg);
               if (qarg == "TIME")
                { emit subMode("  " +qarg+"   ", iarg);}
               if (qarg == "INHIB")
                { emit subMode("  " +qarg+"  ", iarg);}
               if (qarg == "FLASH")
               { emit subMode(" " +qarg+" ", iarg);}}



    extern bool nameAndNotContent;

    if (nameAndNotContent)
        {   if (msg->match("/subStick/text").popInt32(iarg).popStr(sarg).isOkNoMoreArgs()) {
               QString qarg = QString::fromStdString(sarg);
             emit subName(qarg, iarg);}
            }


        if (!nameAndNotContent)
        {   if (msg->match("/subStick/content").popInt32(iarg).popStr(sarg).isOkNoMoreArgs()) {
               QString qarg = QString::fromStdString(sarg);
             emit subName(qarg, iarg);}
            }


            if (msg->match("/subStick/level").popInt32(iarg).popInt32(iarg2).isOkNoMoreArgs()) {
             emit subLvl(iarg2, iarg);
                if (iarg2==255) {emit flashFullOn(iarg);}
                else emit flashFullOff(iarg);}
    }






// Scene ////////////////////////////////////////////////////////////////////////////

          if ((onglet=="seq")&(msg->match("/joystick").popInt32(iarg).isOkNoMoreArgs())) {
              float levelDb = iarg/2.55;
              int iarg2=qRound(levelDb);
           emit joystickLevelText(QString::number(iarg2));
           emit joystickLevel(iarg);}

    if ((onglet=="seq")&(msg->partialMatch("/seq")))
    {
              if (msg->match("/seq/fadeX1").popInt32(iarg).isOkNoMoreArgs()) {
             emit lvlX1(iarg);}
              if (msg->match("/seq/fadeX2").popInt32(iarg).isOkNoMoreArgs()) {
             emit lvlX2(iarg);}
              if (msg->match("/seq/X1").popInt32(iarg).isOkNoMoreArgs()) {
                  qarg = QString::number(iarg);
             emit noX1(qarg);}
              if (msg->match("/seq/X2").popInt32(iarg).isOkNoMoreArgs()) {
                  qarg = QString::number(iarg);
             emit noX2(qarg);}
              if (msg->match("/seq/X1ActiveCue").popStr(sarg).isOkNoMoreArgs()) {
                  qarg = QString::fromStdString(sarg);
             emit cueX1(qarg);}
              if (msg->match("/seq/X2ActiveCue").popStr(sarg).isOkNoMoreArgs()) {
                  qarg = QString::fromStdString(sarg);
             emit cueX2(qarg);}
              if (msg->match("/seq/X1text").popStr(sarg).isOkNoMoreArgs()) {
               QString qarg = QString::fromStdString(sarg);
              emit X1text(qarg);}
              if (msg->match("/seq/X2text").popStr(sarg).isOkNoMoreArgs()) {
               QString qarg = QString::fromStdString(sarg);
              emit X2text(qarg);}
              if (msg->match("/seq/go_signal").popInt32(iarg).isOkNoMoreArgs()) {
             emit goSignal(iarg);}
              if (msg->match("/seq/goback_signal").popInt32(iarg).isOkNoMoreArgs()) {
             emit goBackSignal(iarg);}
              if (msg->match("/seq/pause_signal").popInt32(iarg).isOkNoMoreArgs()) {
             emit pauseSignal(iarg);}
    }






// Patch ////////////////////////////////////////////////////////////////////////////

    if ((onglet=="patch")&(msg->partialMatch("/patch/")))
    {
              if (msg->match("/patch/saisieText").popStr(sarg).isOkNoMoreArgs()) {
               QString qarg = QString::fromStdString(sarg);
              emit txtPatch(qarg);}
              if (msg->match("/patch/errorSignal").popInt32(iarg).isOkNoMoreArgs()) {
              emit errorPatch(iarg);}
              if (msg->match("/patch/displayLevel").popInt32(iarg).isOkNoMoreArgs()) {
             emit testLvl(iarg);}
              if (msg->match("/patch/displayChannel").popStr(sarg).isOkNoMoreArgs()) {
                  qarg = QString::fromStdString(sarg);
             emit chantest("<center>"+qarg+"</center>");}
              if (msg->match("/patch/displayDimmer").popStr(sarg).isOkNoMoreArgs()) {
                  qarg = QString::fromStdString(sarg);
             emit dimtest("<center>"+qarg+"</center>");}
              if (msg->match("/patch/testChannel").popInt32(iarg).isOkNoMoreArgs()) {
                  if (iarg == 1) {
                  emit testChan(true);}
                  else {emit testChan(false);}}
              if (msg->match("/patch/testDimmer").popInt32(iarg).isOkNoMoreArgs()) {
                  if (iarg == 1) {
                  emit testDim(true);}
                  else {emit testDim(false);}}
              if (msg->match("/patch/activeSelectorIsChannel").popInt32(iarg).isOkNoMoreArgs()) {
                  if (iarg == 1) {
                  emit chan(true);}
                  else {emit chan(false);}}
              if (msg->match("/patch/activeSelectorIsDimmer").popInt32(iarg).isOkNoMoreArgs()) {
                  if (iarg == 1) {
                  emit dim(true);}
                  else {emit dim(false);}}
   }
  }
 }
}

void Listener::reStart()
{
 emit connexionOk(false);
 udpSocket->deleteLater();
 emit reboot();
}
