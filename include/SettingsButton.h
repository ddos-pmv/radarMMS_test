// include/SettingsButton.h

#ifndef SETTINGSBUTTON_H
#define SETTINGSBUTTON_H

#include "HeaderButton.h"
#include "InterfaceManager.h"

/**
 * @class SettingsButton
 * @brief A button to open the settings dialog.
 */
class SettingsButton : public HeaderButton {
    Q_OBJECT

public:
    /**
     * @brief Constructor for SettingsButton.
     * @param parent Parent widget.
     */
    explicit SettingsButton(QWidget* parent = nullptr);

    signals:
        /**
         * @brief Signal emitted when the settings button is clicked.
         */
        void settingsBtnClicked();
};

#endif // SETTINGSBUTTON_H