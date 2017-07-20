/*
** Copyright 2007-2013, 2017 S�lyom Zolt�n
** This file is part of zkanji, a free software released under the terms of the
** GNU General Public License version 3. See the file LICENSE for details.
**/

#ifndef WORDTODECKFORM_H
#define WORDTODECKFORM_H

#include <QHeaderView>
#include <vector>
#include "dialogwindow.h"
#include "zdictionarymodel.h"
#include "zui.h"

namespace Ui {
    class WordToDeckForm;
}

class Dictionary;
class WordDeck;
class QPushButton;

class WordsToDeckItemModel : public DictionaryWordListItemModel
{
    Q_OBJECT
public:
    WordsToDeckItemModel(WordDeck* deck, const std::vector<int> &list, QObject *parent = nullptr);
    ~WordsToDeckItemModel();

    // Returns whether there's a checkbox which is checked so the form enables the ok button.
    bool hasBoxChecked() const;

    WordDeck* wordDeck() const;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole) override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::DisplayRole) override;
protected slots:
    virtual void entryChanged(int windex, bool studydef) override;
    virtual void entryRemoved(int windex, int abcdeindex, int aiueoindex) override;
private:
    WordDeck* deck;

    // Bits for the checkbox states. Bit 1: kanji, 2: kana, 3: definition, 4: kanjidisabled, 5: kanadisabled, 6: defdisabled
    std::vector<char> checks;

    typedef DictionaryWordListItemModel base;
};

class ZListView;
// Simple header without column move or click, but with checkboxes left to the labels.
class WordsToDeckHeader : public QHeaderView
{
    Q_OBJECT
public:
    WordsToDeckHeader(ZListView *parent);
    ~WordsToDeckHeader();

protected:
    virtual void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
    virtual QSize sectionSizeFromContents(int logicalIndex) const;

    virtual void mouseMoveEvent(QMouseEvent *e) override;
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void mouseReleaseEvent(QMouseEvent *e) override;
    virtual void leaveEvent(QEvent *e) override;
private:
    // Returns the rectangle of the given section in the viewport.
    QRect sectionRect(int index) const;

    CheckBoxMouseState checkBoxMouseState(int index) const;

    Qt::CheckState checkState(int index) const;

    // Returns the rectangle of a checkbox drawn at index.
    QRect checkBoxRect(int index) const;
    // Returns the rectangle of a checkbox drawn at index that responds to mouse.
    QRect checkBoxHitRect(int index) const;
    // Paints a checkbox and returns the rectangle where it was drawn.
    QRect drawCheckBox(QPainter *p, int index) const;
    // Initializes the style option for drawing a checkbox.
    void initCheckBoxOption(int index, QStyleOptionButton *opt) const;

    int mousecell;
    bool hover;
    bool pressed;

    typedef QHeaderView base;
};

class WordToDeckForm : public DialogWindow
{
    Q_OBJECT
public:
    WordToDeckForm(QWidget *parent = nullptr);
    virtual ~WordToDeckForm();

    void exec(WordDeck* deck, const std::vector<int> &indexes);
protected slots:
    // Connected to the model's dataChanged to look for CheckState changes.
    void checkStateChanged(const QModelIndex &first, const QModelIndex &last, const QVector<int> roles = QVector<int>());

    void selChanged();

    void okButtonClicked(bool);

    void on_decksCBox_currentIndexChanged(int index);
private:
    // Updates the enabled state of the ok button depending on the check boxes.
    void updateOkButton();

    Ui::WordToDeckForm *ui;

    QPushButton *okbutton;
    QPushButton *cancelbutton;

    WordsToDeckItemModel *model;
    WordDeck *deck;

    std::vector<int> indexes;

    // Only set to true when the user clicked on a checkbox inside the selection and the rest
    // of the boxes in the selection should also be set. Prevents handling dataChanged.
    //bool checking;

    typedef DialogWindow base;
};


#endif // WORDTODECKFORM_H
