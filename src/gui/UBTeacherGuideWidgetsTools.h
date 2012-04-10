/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UBTEACHERGUIDEWIDGETSTOOLS_H
#define UBTEACHERGUIDEWIDGETSTOOLS_H

#include <QObject>
#include <QTreeWidgetItem>
#include <QTextEdit>
#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QLineEdit>
#include <QMimeData>
#include <QStackedWidget>
#include <QWebView>

#include "customWidgets/UBMediaWidget.h"

class QTreeWidget;
class QVBoxLayout;
class QComboBox;
class QTextEdit;
class QWidget;
class UBTGAdaptableText;
class QDomElement;

typedef struct
{
    QString type;
    QMap<QString,QString> attributes;
}tUBGEElementNode;


class iUBTGSavableData
{
public:
    virtual tUBGEElementNode* saveData() = 0;
};


class UBAddItem : public QTreeWidgetItem
{
public:
    explicit UBAddItem(const QString &strings, int addSubItemWidgetType, QTreeWidget* parent = 0);
    ~UBAddItem();

signals:

public slots:
};

class UBTGActionWidget : public QWidget, public iUBTGSavableData
{
    Q_OBJECT
public:
    explicit UBTGActionWidget(QTreeWidgetItem* widget, QWidget* parent = 0,const char* name = "UBActionWidget");
    ~UBTGActionWidget();
    void update();
    tUBGEElementNode* saveData();
public slots:
    void onOwnerChange(int ownerId);
private:
    QVBoxLayout* mpLayout;
    QComboBox* mpOwner;
    UBTGAdaptableText* mpTask;
protected:
    QTreeWidgetItem* mpTreeWidgetItem;
};


class UBTGAdaptableText : public QTextEdit
{
    Q_OBJECT
public:
    explicit UBTGAdaptableText(QTreeWidgetItem* widget = 0, QWidget *parent = 0, const char* name = "UBTGAdaptableText");
    void showText(const QString & text);
    void bottomMargin(int newValue);
signals:

public slots:
    void onTextChanged();
private:
    int mBottomMargin;
    QTreeWidgetItem* mpTreeWidgetItem;
};


class UBTGMediaWidget : public QStackedWidget , public iUBTGSavableData
{
    Q_OBJECT
public:
    UBTGMediaWidget(QTreeWidgetItem* widget = 0, QWidget* parent = 0, const char* name = "UBTGMediaWidget");
    UBTGMediaWidget(QString relativePath, QTreeWidgetItem* widget = 0, QWidget* parent = 0, const char* name = "UBTGMediaWidget");
    ~UBTGMediaWidget();
    tUBGEElementNode* saveData();
protected:
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);
    void mousePressEvent(QMouseEvent* event);
private:
    void parseMimeData(const QMimeData* pMimeData);
    void createWorkWidget(QString& path);
    void updateSize();

    QTreeWidgetItem* mpTreeWidgetItem;
    QLabel* mpDropMeWidget;
    QWidget* mpWorkWidget;
    QVBoxLayout* mpLayout;
    UBTGAdaptableText* mpTitle;
    QLabel* mpMediaLabelWidget;
    UBMediaWidget* mpMediaWidget;
    QWebView* mpWebView;
    QString mRelativePath;
    bool mIsPresentationMode;
};

class UBTGUrlWidget : public QWidget , public iUBTGSavableData
{
    Q_OBJECT
public:
    UBTGUrlWidget(QWidget* parent = 0, const char* name = "UBTGUrlWidget");
    ~UBTGUrlWidget();
    tUBGEElementNode* saveData();
private:
    QVBoxLayout* mpLayout;
    QLineEdit* mpTitle;
    QLineEdit* mpUrl;
};


#endif // UBTEACHERGUIDEWIDGETSTOOLS_H
