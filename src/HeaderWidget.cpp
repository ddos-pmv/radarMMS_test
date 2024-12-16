// src/HeaderWidget.cpp
#include "../include/HeaderWidget.h"

/**
 * @brief Constructor for HeaderWidget.
 * @param parent Parent widget.
 */
HeaderWidget::HeaderWidget(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(2, 0, 2, 0);
    layout->setSpacing(2);

    powerBtn = new HeaderButton(this);
    powerBtn->setImage(":resources/images/btns/powerBtnBlack.png", ":resources/images/btns/powerBtnBlack.png");
    powerBtn->setPadding(2);
    powerBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    powerBtn->setFlat(true);

    themeBtn = new ThemeButton(this);
    themeBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    themeBtn->setImage(":resources/images/btns/moon.png", ":resources/images/btns/sun.png");
    themeBtn->setFlat(true);

    settingsBtn = new SettingsButton(this);
    settingsBtn->setImage(":resources/images/btns/settingsBtn.png", ":resources/images/btns/settingsBtn.png");
    settingsBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    settingsBtn->setFlat(true);

    powerBtn->setPadding(15);
    themeBtn->setPadding(15);
    settingsBtn->setPadding(15);

    layout->addWidget(powerBtn);
    layout->addStretch();
    layout->addWidget(themeBtn);
    layout->addWidget(settingsBtn);

    setLayout(layout);

    connect(settingsBtn, &SettingsButton::settingsBtnClicked, InterfaceManager::instance(), &InterfaceManager::settingsBtnClicked);
    connect(powerBtn, &HeaderButton::clicked, InterfaceManager::instance(), []() {
        InterfaceManager::instance()->togglePower();
    });
}

/**
 * @brief Handles the resize event.
 * @param event Resize event.
 */
void HeaderWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);

    int buttonHeight = height() - contentsMargins().top();
    int buttonWidth = buttonHeight + 15;

    powerBtn->setFixedSize(buttonWidth, buttonHeight);
    settingsBtn->setFixedSize(buttonWidth, buttonHeight);
    themeBtn->setFixedSize(buttonWidth, buttonHeight);
}