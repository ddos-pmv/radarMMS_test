#ifndef MEASUREMENTENUMS_H
#define MEASUREMENTENUMS_H

#include <QString>

/**
 * @enum TemperatureScale
 * @brief Enumeration for temperature scales.
 */
enum class TemperatureScale {
    Celsius,    ///< Celsius scale
    Fahrenheit, ///< Fahrenheit scale
    Kelvin      ///< Kelvin scale
};

/**
 * @enum PressureUnit
 * @brief Enumeration for pressure units.
 */
enum class PressureUnit {
    Pascal, ///< Pascal unit
    MmHg    ///< Millimeters of mercury unit
};

/**
 * @struct Temperature
 * @brief Structure to hold temperature values in different scales.
 */
struct Temperature {
    int valueCelsius;    ///< Temperature in Celsius
    int valueFahrenheit; ///< Temperature in Fahrenheit
    int valueKelvin;     ///< Temperature in Kelvin

    /**
     * @brief Get the temperature value in the specified scale.
     * @param scale The temperature scale.
     * @return The temperature value in the specified scale.
     */
    int operator[](TemperatureScale scale) const;

    /**
     * @brief Set the temperature value in the specified scale.
     * @param value The temperature value.
     * @param scale The temperature scale.
     */
    void set(int value, TemperatureScale scale);

    /**
     * @brief Convert the temperature value to a string representation.
     * @param scale The temperature scale.
     * @return The string representation of the temperature value.
     */
    QString toString(TemperatureScale scale) const;
};

/**
 * @struct Pressure
 * @brief Structure to hold pressure values in different units.
 */
struct Pressure {
    int valuePascal; ///< Pressure in Pascals
    int valueMmHg;   ///< Pressure in millimeters of mercury

    /**
     * @brief Get the pressure value in the specified unit.
     * @param unit The pressure unit.
     * @return The pressure value in the specified unit.
     */
    int operator[](PressureUnit unit) const;

    /**
     * @brief Set the pressure value in the specified unit.
     * @param value The pressure value.
     * @param unit The pressure unit.
     */
    void set(int value, PressureUnit unit);

    /**
     * @brief Convert the pressure value to a string representation.
     * @param unit The pressure unit.
     * @return The string representation of the pressure value.
     */
    QString toString(PressureUnit unit) const;
};

/**
 * @brief Convert a TemperatureScale enum to a string.
 * @param scale The temperature scale.
 * @return The string representation of the temperature scale.
 */
QString temperatureScaleToString(TemperatureScale scale);

/**
 * @brief Convert a PressureUnit enum to a string.
 * @param unit The pressure unit.
 * @return The string representation of the pressure unit.
 */
QString pressureUnitToString(PressureUnit unit);

#endif // MEASUREMENTENUMS_H