#include "../include/HeaderButton.h"

HeaderButton::HeaderButton(QWidget* parent) : QPushButton(parent) {
    setObjectName("headerBtn");
    setAttribute(Qt::WA_StyledBackground, true);
    themeChanged(InterfaceManager::instance()->currentTheme());

    connect(InterfaceManager::instance(), &InterfaceManager::themeChanged, this, &HeaderButton::themeChanged);
}

void HeaderButton::setImage(const QString& lightThemePath, const QString& darkThemePath) {
    lightThemeImagePath = lightThemePath;
    darkThemeImagePath = darkThemePath;

    QString curTheme = InterfaceManager::instance()->currentTheme();
    if (curTheme == "dark") {
        currImage.load(darkThemeImagePath);
    } else {
        currImage.load(lightThemeImagePath);
    }

    setIcon(currImage);
}

void HeaderButton::setPadding(int padding) {
    m_padding = padding;
}

void HeaderButton::resizeEvent(QResizeEvent *event) {
    QPushButton::resizeEvent(event);

    int minSizeWithPadding = qMin(width(), height()) - m_padding;
    QSize iconSize(minSizeWithPadding, minSizeWithPadding);
    setIconSize(iconSize);
}

void HeaderButton::themeChanged(const QString& themeName) {
    if (themeName == "dark") {
        currImage.load(darkThemeImagePath);
    } else {
        currImage.load(lightThemeImagePath);
    }
    setIcon(currImage);
}