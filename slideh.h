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

#ifndef SLIDEH_H
#define SLIDEH_H

#include <QFrame>
#include <QTouchEvent>



class SlideH : public QFrame
{Q_OBJECT
    public:
        SlideH(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags()): QFrame(parent, f)
        {
        }

protected:

        bool  event(QEvent *event)
        {
#if  defined (Q_OS_OSX)
            if (event->type()==QMouseEvent::MouseMove)
              {
                QMouseEvent *moved = static_cast<QMouseEvent*>(event);
                int dep;
                if ((this->width())>(this->height()))
                dep =(moved->x()*255)/(this->width());
                else
                dep =(moved->y()*100)/(this->height());
                emit slideValue(dep);
               }
            if (event->type()==QMouseEvent::MouseButtonRelease)
             {
                emit sliderReleased();
              }
#else
             if (event->type()==QTouchEvent::TouchUpdate)
               {
                 QTouchEvent *touchEvent = static_cast<QTouchEvent*>(event);
                 QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();
                 const QTouchEvent::TouchPoint &touchPoint0 = touchPoints.first();
                 int mv;
                 if ((this->width())>(this->height()))
                 mv =(touchPoint0.lastPos().x()*255)/(this->width());
                 else
                 mv =(touchPoint0.lastPos().y()*100)/(this->height());
                 emit slideValue(mv);
               }

             if (event->type()==QTouchEvent::QEvent::TouchEnd)
              {
                 emit sliderReleased();
               }
#endif
             return true;
        }

signals:
        void slideValue(int);
        void sliderReleased();
};

#endif // SLIDEH_H
