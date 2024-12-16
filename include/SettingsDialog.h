 // include/SettingsDialog.h
#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "MeasurementEnums.h"

/**
 * @class SettingsDialog
 * @brief A dialog for setting temperature and pressure units.
 */
class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructor for SettingsDialog.
     * @param parent Parent widget.
     */
    explicit SettingsDialog(QWidget *parent = nullptr);

    /**
     * @brief Sets the current settings in the dialog.
     * @param tempScale The current temperature scale.
     * @param pressureUnit The current pressure unit.
     */
    void setCurrentSettings(TemperatureScale tempScale, PressureUnit pressureUnit);

    /**
     * @brief Gets the selected temperature scale.
     * @return The selected temperature scale.
     */
    TemperatureScale getSelectedTemperatureScale() const;

    /**
     * @brief Gets the selected pressure unit.
     * @return The selected pressure unit.
     */
    PressureUnit getSelectedPressureUnit() const;

    /**
     * @brief Accepts the dialog and updates the settings.
     */
    void accept() override;

    /**
     * @brief Opens the dialog and sets the current settings.
     */
    void open() override;

private:
    QComboBox *scaleComboBox; ///< Combo box for selecting temperature scale.
    QComboBox *pressureComboBox; ///< Combo box for selecting pressure unit.
};

#endif // SETTINGSDIALOG_H