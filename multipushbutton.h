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
#ifndef MULTIPUSHBUTTON_H
#define MULTIPUSHBUTTON_H
#include <QPushButton>
#include <QTouchEvent>

class multiPushButton : public QPushButton
{Q_OBJECT
    public:
        multiPushButton(QWidget* parent=0): QPushButton(parent) {}

protected:

        bool  event(QEvent *event)
        {
             if (event->type()==QMouseEvent::MouseButtonPress)
                {emit buttonPressed();this->setChecked(true);return true;}

             if (event->type()==QMouseEvent::MouseButtonRelease)
                {emit buttonReleased();this->setChecked(false);return true;}

             if (event->type()==QTouchEvent::QEvent::TouchBegin)
                {emit buttonPressed();this->setChecked(true);return true;}

             if (event->type()==QTouchEvent::QEvent::TouchEnd)
                {emit buttonReleased();this->setChecked(false);return true;}

             return QPushButton::event(event);
}


signals:
        void buttonPressed();
        void buttonReleased();
};
#endif // MULTIPUSHBUTTON_H
