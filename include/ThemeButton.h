// include/ThemeButton.h

#ifndef THEMEBUTTON_H
#define THEMEBUTTON_H

#include <QDebug>
#include "HeaderButton.h"

/**
 * @class ThemeButton
 * @brief A button to switch between light and dark themes.
 */
class ThemeButton : public HeaderButton {
    Q_OBJECT

public:
    /**
     * @brief Constructor for ThemeButton.
     * @param parent Parent widget.
     */
    explicit ThemeButton(QWidget *parent = nullptr);

    protected slots:
        /**
         * @brief Slot to change the theme when the button is clicked.
         */
        void changeTheme();

private:
    bool isDarkTheme; ///< Indicates whether the current theme is dark.
    QPixmap buttonImage; ///< Image for the button.
};

#endif // THEMEBUTTON_H