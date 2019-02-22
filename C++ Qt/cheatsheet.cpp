/****/// Notes
/******************************************/

QMainWindow window;
window.setCentralWidget(widget);
window.resize(900, 600);
window.show();
this->setCentralWidget(ui->@widgetName);

// QMessageAuthenticationCode
QByteArray key = "key";
 QByteArray message = "The quick brown fox jumps over the lazy dog";
 ...
 QMessageAuthenticationCode code(QCryptographicHash::Sha1);
 code.setKey(key);
 code.addData(message);
 code.result().toHex();
 QMessageAuthenticationCode::hash(message, key, QCryptographicHash::Sha1).toHex();
// get Text
bool ok;
QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                     tr("User name:"), QLineEdit::Normal,
                                     QDir::home().dirName(), &ok);
if (ok && !text.isEmpty())
    textLabel->setText(text);
// getItem
QStringList items;
   items << tr("Spring") << tr("Summer") << tr("Fall") << tr("Winter");

   bool ok;
   QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem()"),
                                        tr("Season:"), items, 0, false, &ok);
   if (ok && !item.isEmpty())
       itemLabel->setText(item);


/****/// project.pro
// Print support
QT += core gui // add printsupport
QT += core gui printsupport

/****/// includes
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>

/****/// types
QString filename = QFileDialog::getOpenName((this, "Open sometinhg"));
QFile file(fileName);
currentFile = fileName;
if(!file.open(QIODevice::ReadOnly || QFile::Text)) {
    QMessageBox::warning(this, "Warning", "Msg" + file.errorString());
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}
