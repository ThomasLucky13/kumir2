#ifndef EDITORPLANE_H
#define EDITORPLANE_H

#include <QtGui>

#include "interfaces/lexemtype.h"

namespace Editor {

class EditorPlane : public QWidget
{
    Q_OBJECT
public:
    explicit EditorPlane(class TextDocument * doc
                         , class TextCursor * cursor
                         , class Clipboard * clipboard
                         , QSettings * settings
                         , QWidget *parent = 0);
    int widthInChars() const;
    int charWidth() const;
    int lineHeight() const;
    QRect cursorRect() const;
public slots:
    void selectAll();
    void copy();
    void paste();
    void cut();
    void removeLine();
    void removeLineTail();
protected:
    void paintEvent(QPaintEvent *);
    QPoint offset() const;
    void paintBackground(QPainter *p, const QRect &rect);
    void paintCursor(QPainter *p, const QRect &rect);
    void paintText(QPainter *p, const QRect &rect);
    void paintSelection(QPainter *p, const QRect &rect);
    void paintRectSelection(QPainter *p, const QRect &rect);
    void paintLineNumbers(QPainter *p, const QRect &rect);
    void keyPressEvent(QKeyEvent *);
    void setProperFormat(QPainter * p, Shared::LexemType type, const QChar &c);
protected slots:
    void updateCursor();
    void updateText(int fromLine, int toLine);

private:
    int i_marginWidth;
    int i_timerId;
    class TextDocument * m_document;
    class TextCursor * m_cursor;
    class Clipboard * m_clipboard;
    QSettings * m_settings;


};

} // namespace Editor

#endif // EDITORPLANE_H
