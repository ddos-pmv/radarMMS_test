// src/SettingsDialog.cpp
#include "../include/SettingsDialog.h"
#include "../include/InterfaceManager.h"
#include "../include/MeasurementEnums.h"

/**
 * @brief Constructor for SettingsDialog.
 * @param parent Parent widget.
 */
SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Настройки данных");

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Temperature
    layout->addWidget(new QLabel("Температура:"));

    scaleComboBox = new QComboBox;
    scaleComboBox->addItems({
        temperatureScaleToString(TemperatureScale::Celsius),
        temperatureScaleToString(TemperatureScale::Fahrenheit),
        temperatureScaleToString(TemperatureScale::Kelvin)
    });
    scaleComboBox->setMinimumHeight(40); // Increase height for touchscreen
    layout->addWidget(scaleComboBox);

    // Pressure
    layout->addWidget(new QLabel("Давление:"));
    pressureComboBox = new QComboBox;
    pressureComboBox->addItems({
        pressureUnitToString(PressureUnit::Pascal),
        pressureUnitToString(PressureUnit::MmHg)
    });
    pressureComboBox->setMinimumHeight(40); // Increase height for touchscreen
    layout->addWidget(pressureComboBox);

    // Buttons
    QPushButton *okButton = new QPushButton("Ok");
    QPushButton *cancelButton = new QPushButton("Cancel");
    okButton->setMinimumHeight(40); // Increase height for touchscreen
    cancelButton->setMinimumHeight(40); // Increase height for touchscreen
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &SettingsDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &SettingsDialog::reject);
    connect(InterfaceManager::instance(), &InterfaceManager::openSettingsDialog, this, &SettingsDialog::open);
}

/**
 * @brief Sets the current settings in the dialog.
 * @param tempScale The current temperature scale.
 * @param pressureUnit The current pressure unit.
 */
void SettingsDialog::setCurrentSettings(TemperatureScale tempScale, PressureUnit pressureUnit) {
    scaleComboBox->setCurrentIndex(static_cast<int>(tempScale));
    pressureComboBox->setCurrentIndex(static_cast<int>(pressureUnit));
}

/**
 * @brief Gets the selected temperature scale.
 * @return The selected temperature scale.
 */
TemperatureScale SettingsDialog::getSelectedTemperatureScale() const {
    return static_cast<TemperatureScale>(scaleComboBox->currentIndex());
}

/**
 * @brief Gets the selected pressure unit.
 * @return The selected pressure unit.
 */
PressureUnit SettingsDialog::getSelectedPressureUnit() const {
    return static_cast<PressureUnit>(pressureComboBox->currentIndex());
}

/**
 * @brief Accepts the dialog and updates the settings.
 */
void SettingsDialog::accept() {
    InterfaceManager::instance()->updateMeasurementScale(getSelectedTemperatureScale(), getSelectedPressureUnit());
    close();
}

/**
 * @brief Opens the dialog and sets the current settings.
 */
void SettingsDialog::open() {
    setCurrentSettings(InterfaceManager::instance()->temperatureScale(), InterfaceManager::instance()->pressureUnit());
    QDialog::open();
}