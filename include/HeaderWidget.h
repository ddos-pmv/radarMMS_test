// include/HeaderWidget.h
#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QIcon>
#include <set>

#include "HeaderButton.h"
#include "ThemeButton.h"
#include "InterfaceManager.h"
#include "SettingsButton.h"

/**
 * @class HeaderWidget
 * @brief A widget for the header containing power, theme, and settings buttons.
 */
class HeaderWidget : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Constructor for HeaderWidget.
     * @param parent Parent widget.
     */
    explicit HeaderWidget(QWidget *parent = nullptr);

protected:
    /**
     * @brief Handles the resize event.
     * @param event Resize event.
     */
    void resizeEvent(QResizeEvent *event) override;

private:
    HeaderButton *powerBtn; ///< Button to toggle power.
    SettingsButton *settingsBtn; ///< Button to open settings.
    ThemeButton *themeBtn; ///< Button to toggle theme.
};

#endif // HEADERWIDGET_H