#include "barrageedit.h"
#include "barragecore.h"

#include <QMenu>
#include <QKeyEvent>

BarrageEdit::BarrageEdit(QWidget *parent)
    : QLineEdit(parent)
{
    setStyleSheet(BarrageCore::LineEditStyle02);
}

void BarrageEdit::addFilterText(const QString &text)
{
    m_filterText = text;
    setText(text);
}

void BarrageEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    blockSignals(true);
    if(text() == m_filterText)
    {
        setText({});
    }
    blockSignals(false);
}

void BarrageEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    blockSignals(true);
    if(text().isEmpty())
    {
        setText(m_filterText);
    }
    blockSignals(false);
}

void BarrageEdit::contextMenuEvent(QContextMenuEvent *event)
{
    QLineEdit::contextMenuEvent(event);

    QMenu menu(this);
    menu.setStyleSheet(BarrageCore::MenuStyle02);

    QAction *shearM = menu.addAction(tr("Shear"), this, SLOT(cut()));
    QAction *copyM = menu.addAction(tr("Copy"), this, SLOT(copy()));
    menu.addAction(tr("Paste"), this, SLOT(paste()));
    QAction *deleteM = menu.addAction(tr("Delete"), this, SLOT(clear()));
    menu.addSeparator();
    QAction *selectM = menu.addAction(tr("SelectAll"), this, SLOT(selectAll()));

    bool state = hasSelectedText();
    shearM->setEnabled(state);
    copyM->setEnabled(state);
    deleteM->setEnabled(state);
    selectM->setEnabled(!text().trimmed().isEmpty());

    menu.exec(QCursor::pos());
}

void BarrageEdit::keyPressEvent(QKeyEvent *event)
{
    QLineEdit::keyPressEvent(event);
}

void BarrageEdit::keyReleaseEvent(QKeyEvent *event)
{
    QLineEdit::keyReleaseEvent(event);
    switch( event->key() )
    {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            if(!text().isEmpty())
            {
                Q_EMIT enterFinished(text());
            }
            break;
    }
}
