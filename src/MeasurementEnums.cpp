#include "../include/MeasurementEnums.h"

int Temperature::operator[](TemperatureScale scale) const {
    switch (scale) {
        case TemperatureScale::Celsius:
            return valueCelsius;
        case TemperatureScale::Fahrenheit:
            return valueFahrenheit;
        case TemperatureScale::Kelvin:
            return valueKelvin;
        default:
            return 0; // Invalid scale
    }
}

void Temperature::set(int value, TemperatureScale scale) {
    switch (scale) {
        case TemperatureScale::Celsius:
            valueCelsius = value;
            valueFahrenheit = static_cast<int>(value * 9.0 / 5.0 + 32.0);
            valueKelvin = value + 273;
            break;
        case TemperatureScale::Fahrenheit:
            valueCelsius = static_cast<int>((value - 32.0) * 5.0 / 9.0);
            valueFahrenheit = value;
            valueKelvin = valueCelsius + 273;
            break;
        case TemperatureScale::Kelvin:
            valueCelsius = value - 273;
            valueFahrenheit = static_cast<int>(valueCelsius * 9.0 / 5.0 + 32.0);
            valueKelvin = value;
            break;
        default:
            break;
    }
}

QString Temperature::toString(TemperatureScale scale) const {
    switch (scale) {
        case TemperatureScale::Celsius:
            return QString::number(valueCelsius) + "°C";
        case TemperatureScale::Fahrenheit:
            return QString::number(valueFahrenheit) + "°F";
        case TemperatureScale::Kelvin:
            return QString::number(valueKelvin) + "K";
        default:
            return "Unknown value";
    }
}

int Pressure::operator[](PressureUnit unit) const {
    switch (unit) {
        case PressureUnit::Pascal:
            return valuePascal;
        case PressureUnit::MmHg:
            return valueMmHg;
        default:
            return 0; // Invalid unit
    }
}

void Pressure::set(int value, PressureUnit unit) {
    switch (unit) {
        case PressureUnit::Pascal:
            valuePascal = value;
            valueMmHg = static_cast<int>(value * 0.0075);
            break;
        case PressureUnit::MmHg:
            valuePascal = static_cast<int>(value / 0.0075);
            valueMmHg = value;
            break;
        default:
            break;
    }
}

QString Pressure::toString(PressureUnit unit) const {
    switch (unit) {
        case PressureUnit::Pascal:
            return QString::number(valuePascal) + "Pa";
        case PressureUnit::MmHg:
            return QString::number(valueMmHg) + "mmHg";
        default:
            return "Unknown value";
    }
}

QString temperatureScaleToString(TemperatureScale scale) {
    switch (scale) {
        case TemperatureScale::Celsius:
            return "Celsius";
        case TemperatureScale::Fahrenheit:
            return "Fahrenheit";
        case TemperatureScale::Kelvin:
            return "Kelvin";
        default:
            return "Unknown scale";
    }
}

QString pressureUnitToString(PressureUnit unit) {
    switch (unit) {
        case PressureUnit::Pascal:
            return "Pascal";
        case PressureUnit::MmHg:
            return "Millimeters of Mercury";
        default:
            return "Unknown unit";
    }
}