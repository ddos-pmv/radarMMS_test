//
// Created by Сергей Перлин on 12.12.2024.
//

#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QXmlStreamReader>
#include <QStandardPaths>
#include <QDir>

#include "MeasurementEnums.h"

/**
 * @class InterfaceManager
 * @brief Manages the interface settings and state.
 */
class InterfaceManager : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Returns the singleton instance of InterfaceManager.
     * @return Pointer to the singleton instance.
     */
    static InterfaceManager* instance();

    /**
     * @brief Sets the current theme.
     * @param themeName Name of the theme to set.
     */
    void setTheme(const QString& themeName);

    /**
     * @brief Gets the current theme.
     * @return Name of the current theme.
     */
    QString currentTheme() const;

    /**
     * @brief Updates the current temperature.
     * @param newTemp New temperature value in Celsius.
     */
    void updateTemperature(int newTemp);

    /**
     * @brief Updates the current pressure.
     * @param newMmHg New pressure value in mmHg.
     */
    void updatePressure(int newMmHg);

    /**
     * @brief Updates the current humidity.
     * @param newHumidity New humidity value in percentage.
     */
    void updateHumidity(int newHumidity);

    /**
     * @brief Updates the measurement scales for temperature and pressure.
     * @param newTempScale New temperature scale.
     * @param newPressureUnit New pressure unit.
     */
    void updateMeasurementScale(TemperatureScale newTempScale, PressureUnit newPressureUnit);

    /**
     * @brief Toggles the power state.
     */
    void togglePower();

    /**
     * @brief Increments the target temperature.
     * @param delta Increment delta to increase or decrease.
     * @param scale Temperature scale.
     */
    void incrementTargetTemperature(int delta, TemperatureScale scale);

    /**
     * @brief Gets the current temperature scale.
     * @return Current temperature scale.
     */
    TemperatureScale temperatureScale();

    /**
     * @brief Gets the current pressure unit.
     * @return Current pressure unit.
     */
    PressureUnit pressureUnit();

    /**
     * @brief Gets the target temperature.
     * @return Target temperature.
     */
    Temperature targetTemperature() const;

    /**
     * @brief Gets the current temperature.
     * @return Current temperature.
     */
    Temperature curTemperature() const;

    /**
     * @brief Gets the current pressure.
     * @return Current pressure.
     */
    Pressure curPressure() const;

    /**
     * @brief Gets the current humidity.
     * @return Current humidity.
     */
    int curHumidity() const;

    /**
     * @brief Checks if the power is on.
     * @return True if power is on, false otherwise.
     */
    bool isOn() const;

public slots:
    /**
     * @brief Slot to handle settings button click.
     */
    void settingsBtnClicked();

signals:
    /**
     * @brief Signal emitted when the theme is changed.
     * @param themeName Name of the new theme.
     */
    void themeChanged(const QString& themeName);

    /**
     * @brief Signal emitted to open the settings dialog.
     */
    void openSettingsDialog();

    /**
     * @brief Signal emitted when the measurement scale is updated.
     * @param newTempScale New temperature scale.
     * @param newPressureUnit New pressure unit.
     */
    void measurementScaleUpdated(TemperatureScale newTempScale, PressureUnit newPressureUnit);

    /**
     * @brief Signal emitted when the target temperature is updated.
     * @param newTargetTemperature New target temperature.
     */
    void targetTemperatureUpdated(Temperature newTargetTemperature);

    /**
     * @brief Signal emitted when the temperature is updated.
     * @param newTemperature New temperature.
     */
    void temperatureUpdated(Temperature newTemperature);

    /**
     * @brief Signal emitted when the pressure is updated.
     * @param newPressure New pressure.
     */
    void pressureUpdated(Pressure newPressure);

    /**
     * @brief Signal emitted when the humidity is updated.
     * @param newPercent New humidity percentage.
     */
    void humidityUpdated(int newPercent);

    /**
     * @brief Signal emitted when some property is updated.
     */
    void somePropertyUpdated();

    /**
     * @brief Signal emitted when the power is turned on.
     */
    void powerOn();

    /**
     * @brief Signal emitted when the power is turned off.
     */
    void powerOff();

private:
    /**
     * @brief Private constructor for singleton pattern.
     * @param parent Parent QObject.
     */
    explicit InterfaceManager(QObject* parent = nullptr);

    /**
     * @brief Loads settings from an XML file.
     */
    void loadSettingFromXml();

    /**
     * @brief Saves settings to an XML file.
     */
    void saveSettingToXml();

    static InterfaceManager *m_instance; ///< Singleton instance.
    QString m_currentTheme; ///< Current theme.

    Temperature lastTemperature; ///< Last recorded temperature.
    Pressure lastPressure; ///< Last recorded pressure.
    int lastHumidity; ///< Last recorded humidity.
    Temperature lastTargetTemperature; ///< Last target temperature.

    bool isPowerOn; ///< Power state.

    QString xmlFilePath; ///< Path to the XML settings file.

    TemperatureScale m_temperatureScale; ///< Current temperature scale.
    PressureUnit m_pressureUnit; ///< Current pressure unit.
};

#endif //THEMEMANAGER_H