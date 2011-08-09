#ifndef TEXTBLOCKDATA_H
#define TEXTBLOCKDATA_H

#include <QtCore>
#include <QtGui>

#include "interfaces/lexemtype.h"
#include "interfaces/analizerinterface.h"

namespace Editor {

class InsertCommand:
        public QUndoCommand
{
public:
    explicit InsertCommand(class TextDocument * doc,
                           class TextCursor * cursor,
                           Shared::AnalizerInterface * analizer,
                           int line,
                           int pos,
                           const QString & text
                           );
    void redo();
    void undo();
    inline int id() const { return 1; }
    bool mergeWith(const QUndoCommand *other);

private:
    class TextDocument * doc;
    class TextCursor * cursor;
    Shared::AnalizerInterface * analizer;
    int line;
    int pos;
    QString text;
    int blankLines;
    int blankChars;
    int cursorRow;
    int cursorCol;

};

class RemoveCommand:
        public QUndoCommand
{
public:
    explicit RemoveCommand(class TextDocument * doc,
                           class TextCursor * cursor,
                           Shared::AnalizerInterface * analizer,
                           int line,
                           int pos,
                           int count,
                           bool keepCursor
                           );
    void redo();
    void undo();
    inline int id() const { return 2; }
    bool mergeWith(const QUndoCommand *other);

private:
    class TextDocument * doc;
    class TextCursor * cursor;
    Shared::AnalizerInterface * analizer;
    int line;
    int pos;
    int count;
    bool keepKursor;
    QString removedText;
    int cursorRow;
    int cursorCol;

};

class InsertBlockCommand:
        public QUndoCommand
{
public:
    explicit InsertBlockCommand(class TextDocument * doc,
                                class TextCursor * cursor,
                                Shared::AnalizerInterface * analizer,
                                int row,
                                int column,
                                const QStringList & block);
    void redo();
    void undo();

private:
    class TextDocument * doc;
    class TextCursor * cursor;
    Shared::AnalizerInterface * analizer;
    int row;
    int column;
    QStringList block;
    int cursorRow;
    int cursorCol;
    QStringList previousLines;
    int addedLines;
};

class RemoveBlockCommand:
        public QUndoCommand
{
public:
    explicit RemoveBlockCommand(class TextDocument * doc,
                                class TextCursor * cursor,
                                Shared::AnalizerInterface * analizer,
                                const QRect & block);
    void redo();
    void undo();

private:
    class TextDocument * doc;
    class TextCursor * cursor;
    Shared::AnalizerInterface * analizer;
    QRect block;
    int cursorRow;
    int cursorCol;
    QStringList previousLines;
};

struct TextLine
{
    inline explicit TextLine() {
        indentStart = indentEnd = 0;
        lineEndSelected = false;
    }
    int indentStart;
    int indentEnd;
    QList<Shared::LexemType> highlight;
    QList<bool> selected;
    bool lineEndSelected;
    QString text;
    QStringList errors;
    QString marginText;
};

class TextDocument
        : public QObject
{
    Q_OBJECT
    friend class InsertCommand;
    friend class RemoveCommand;
    friend class InsertBlockCommand;
    friend class RemoveBlockCommand;
public:
    explicit TextDocument(QObject * parent);
    int documentId;
    int indentAt(int lineNo) const;
    inline int linesCount() const { return data.size(); }
    QString toPlainText() const;
    inline QString textAt(int index) const { return data[index].text; }
    inline QString marginTextAt(int index) const { return data[index].marginText; }
    inline QList<bool> selectionMaskAt(int index) const { return data[index].selected; }
    inline void setSelectionMaskAt(int index, const QList<bool> mask) { data[index].selected = mask; }
    inline bool lineEndSelectedAt(int index) const { return data[index].lineEndSelected; }
    inline QList<Shared::LexemType> highlightAt(int index) { return data[index].highlight; }
    inline void setMarginTextAt(int index, const QString & text) { data[index].marginText = text; }
    inline void setIndentRankAt(int index, const QPoint & rank) { data[index].indentStart = rank.x(); data[index].indentEnd = rank.y(); }
    inline void setHighlightAt(int index, const QList<Shared::LexemType> & highlight) { data[index].highlight = highlight; }
    inline void setErrorsAt(int index, const QStringList & errs) { data[index].errors = errs; }
    inline QStringList errorsAt(int index) const { return data[index].errors; }
    inline void clearErrorsAt(int index) { data[index].errors.clear(); }
    void setPlainText(const QString &text);
    inline void setSelected(int line, int pos, bool v) { data[line].selected[pos] = v; }
    inline void setEndOfLineSelected(int line, bool v) { data[line].lineEndSelected = v; }
    void evaluateCommand(const QUndoCommand & cmd);
    inline QUndoStack * undoStack() { return m_undoStack; }
    void removeSelection();
    void flushChanges();
    void flushTransaction();
signals:
    void compilationRequest(const QStack<Shared::ChangeTextTransaction> & changes);
protected:
    void insertText(const QString & text, const Shared::AnalizerInterface * analizer, int line, int pos, int &blankLines, int &blankChars);
    void removeText(QString &removedText, const Shared::AnalizerInterface * analizer, int line, int pos, int  blankLines, int  blankChars, int count);
    void checkForCompilationRequest(const QPoint & cursorPosition);
private:
    QSet<int> m_removedLines;
    QSet<int> m_newLines;
    QStack<Shared::ChangeTextTransaction> changes;
    QPoint lastCursorPos;
    QUndoStack * m_undoStack;
    QList<TextLine> data;
};


}

#endif // TEXTBLOCKDATA_H
