#ifndef MARSDIALOG_H
#define MARSDIALOG_H
#include <qdialog.h>
#include "U2Panel.h"
#include <qlayout.h>
using namespace std;
class MarsDialog:public QDialog
{
        Q_OBJECT

        public:
                MarsDialog(QWidget *,QString);
                ~MarsDialog();
                QString getMarsText();

        private:
                U2Panel *u2p;
				QVBoxLayout *layout;

        protected:
                void keyPressEvent(QKeyEvent *);
                void keyReleaseEvent(QKeyEvent *);

};
#endif // MARSDIALOG_H
