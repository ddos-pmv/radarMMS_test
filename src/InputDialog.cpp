// InputDialog.cpp
#include "../include/InputDialog.h"

#include <QIntValidator>

/**
 * @brief Constructor for InputDialog.
 * @param parent Parent widget.
 */
InputDialog::InputDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Ввод данных");

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Temperature input
    layout->addWidget(new QLabel("Температура (Цельсий):"));
    temperatureInput = new QLineEdit(this);
    temperatureInput->setValidator(new QIntValidator(-273, 1000, this)); // Limit to integer values
    layout->addWidget(temperatureInput);

    // Pressure input
    layout->addWidget(new QLabel("Давление (мм рт. ст.):"));
    pressureInput = new QLineEdit(this);
    pressureInput->setValidator(new QIntValidator(0, 10000, this)); // Limit to integer values
    layout->addWidget(pressureInput);

    // Humidity input
    layout->addWidget(new QLabel("Влажность (%):"));
    humidityInput = new QLineEdit(this);
    humidityInput->setValidator(new QIntValidator(0, 100, this)); // Limit to integer values
    layout->addWidget(humidityInput);

    // Submit button
    QPushButton *okButton = new QPushButton("Отправить", this);
    connect(okButton, &QPushButton::clicked, this, &InputDialog::onAccept);
    layout->addWidget(okButton);
}

/**
 * @brief Slot to handle the accept action.
 */
void InputDialog::onAccept() {
    // Convert values and send through InterfaceManager
    int tempCelsius = temperatureInput->text().toInt();
    int pressureMmHg = pressureInput->text().toInt();
    int humidityPercent = humidityInput->text().toInt();

    InterfaceManager::instance()->updateTemperature(tempCelsius);
    InterfaceManager::instance()->updatePressure(pressureMmHg);
    InterfaceManager::instance()->updateHumidity(humidityPercent);

    emit dataEntered(temperatureInput->text(), pressureInput->text(), humidityInput->text());
}