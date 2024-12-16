// src/ThemeButton.cpp

#include "../include/ThemeButton.h"

/**
 * @brief Constructor for ThemeButton.
 * @param parent Parent widget.
 */
ThemeButton::ThemeButton(QWidget *parent) : HeaderButton(parent), isDarkTheme(false) {
    connect(this, &QPushButton::clicked, this, &ThemeButton::changeTheme);
}

/**
 * @brief Slot to change the theme when the button is clicked.
 */
void ThemeButton::changeTheme() {
    QString curTheme = InterfaceManager::instance()->currentTheme();
    if (curTheme == "light") {
        InterfaceManager::instance()->setTheme("dark");
    } else {
        InterfaceManager::instance()->setTheme("light");
    }
}