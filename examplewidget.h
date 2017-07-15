/*
** Copyright 2007-2013, 2017 S�lyom Zolt�n
** This file is part of zkanji, a free software released under the terms of the
** GNU General Public License version 3. See the file LICENSE for details.
**/

#ifndef EXAMPLEWIDGET_H
#define EXAMPLEWIDGET_H

#include <QWidget>

namespace Ui {
    class ExampleWidget;
}

class Dictionary;
struct ExampleSentenceData;
class QXmlStreamWriter;
class QXmlStreamReader;
enum class ExampleDisplay : uchar;
class ExampleWidget : public QWidget
{
    Q_OBJECT
signals:
    void wordSelected(ushort block, uchar line, int wordpos, int wordform);
public:
    ExampleWidget(QWidget *parent = nullptr);
    ~ExampleWidget();

    //// Saves widget state to the passed xml stream.
    //void saveXMLSettings(QXmlStreamWriter &writer) const;
    //// Loads widget state from the passed xml stream.
    //void loadXMLSettings(QXmlStreamReader &reader);

    // Notifies the example strip that the examples for the passed dictionary and word index
    // should be shown.
    void setItem(Dictionary *d, int windex);

    // Calling setItem() will have no effect until unlock is called.
    void lock();

    ExampleDisplay displayed() const;
    void setDisplayed(ExampleDisplay disp);

    // Allows changes to the displayed sentence after calling lock(). If the dictionary and
    // word indexes are specified, tries to update the display of the current sentence to use
    // that word as a base. If the current sentence is not found for that word, equals to
    // calling this without arguments and then calling setItem().
    void unlock(Dictionary *d = nullptr, int windex = -1, int wordpos = -1, int wordform = -1);
private slots:
    void onReset();
    void stripChanged();
    void on_jptrButton_clicked(bool checked);

    void on_prevButton_clicked();
    void on_nextButton_clicked();
    void on_indexEdit_textEdited(const QString &text);
private:
    Ui::ExampleWidget *ui;

    // When set calling setItem or any other function won't change the
    // displayed sentence. Call lock() to set and unlock() to unset.
    bool locked;

    typedef QWidget base;
};

#endif // EXAMPLEWIDGET_H
