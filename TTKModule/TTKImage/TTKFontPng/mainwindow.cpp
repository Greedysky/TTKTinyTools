#include "mainwindow.h"
#include "ttkdesktopscreen.h"

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

    return TTKDesktopScreen::grabWidget(&widget, widget.rect());
}


QPixmap MainWindow::saveIcon(const QString &fontPath, int w, int h, int fontSize, int iconIndex)
{
    const int fontId = QFontDatabase::addApplicationFont(fontPath);
    const QStringList &fontNames = QFontDatabase::applicationFontFamilies(fontId);
    return fontNames.isEmpty() ? QPixmap() : transFontToPixmap(QFont(fontNames[0]), w, h, fontSize, iconIndex);
}
