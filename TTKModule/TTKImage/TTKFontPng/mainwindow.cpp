#include "mainwindow.h"
#include "ttkdesktopwrapper.h"

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

    return TTKDesktopWrapper::grabWidget(&widget, widget.rect());
}


QPixmap MainWindow::saveIcon(const QString &fontPath, int w, int h, int fontSize, int iconIndex)
{
    const int fontId = QFontDatabase::addApplicationFont(fontPath);
    const QString &fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    return transFontToPixmap(QFont(fontName), w, h, fontSize, iconIndex);
}
