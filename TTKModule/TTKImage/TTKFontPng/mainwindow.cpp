#include "mainwindow.h"

#include <QLabel>
#include <QFontDatabase>

static QPixmap transFontToPixmap(const QFont &newFont, int w, int h, int fontSize, int iconIndex)
{
    QLabel widget;
    widget.setAttribute(Qt::WA_TranslucentBackground);
    widget.setFixedSize(w, h);
    widget.setAlignment(Qt::AlignCenter);
    widget.setText(QChar(iconIndex));

    QFont font = newFont;
    font.setPointSize(fontSize);
    widget.setFont(font);

#if TTK_QT_VERSION_CHECK(5,0,0)
    return widget.grab(widget.rect());
#else
    return QPixmap::grabWidget(&widget, widget.rect());
#endif
}

QPixmap MainWindow::saveIcon(const QString &fontPath, int w, int h, int fontSize, int iconIndex)
{
    const int fontId = QFontDatabase::addApplicationFont(fontPath);
    const QString &fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
#if TTK_QT_VERSION_CHECK(6,2,0)
    QFont font({fontName});
#else
    QFont font(fontName);
#endif
    return transFontToPixmap(font, w, h, fontSize, iconIndex);
}
