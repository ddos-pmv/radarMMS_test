// InputDialog.h
#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "InterfaceManager.h"

/**
 * @class InputDialog
 * @brief A dialog for inputting temperature, pressure, and humidity data.
 */
class InputDialog : public QDialog {
    Q_OBJECT
public:
    /**
     * @brief Constructor for InputDialog.
     * @param parent Parent widget.
     */
    explicit InputDialog(QWidget *parent = nullptr);

    signals:
        /**
         * @brief Signal emitted when data is entered.
         * @param temperature Entered temperature.
         * @param pressure Entered pressure.
         * @param humidity Entered humidity.
         */
        void dataEntered(const QString &temperature, const QString &pressure, const QString &humidity);

    private slots:
        /**
         * @brief Slot to handle the accept action.
         */
        void onAccept();

private:
    QLineEdit *temperatureInput; ///< Input field for temperature.
    QLineEdit *pressureInput; ///< Input field for pressure.
    QLineEdit *humidityInput; ///< Input field for humidity.
};

#endif // INPUTDIALOG_H