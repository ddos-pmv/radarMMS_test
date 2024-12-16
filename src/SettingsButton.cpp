// src/SettingsButton.cpp

#include "../include/SettingsButton.h"

/**
 * @brief Constructor for SettingsButton.
 * @param parent Parent widget.
 */
SettingsButton::SettingsButton(QWidget* parent) : HeaderButton(parent) {
    connect(this, &QPushButton::clicked, this, &SettingsButton::settingsBtnClicked);
}