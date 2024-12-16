//
// Created by Сергей Перлин on 12.12.2024.
//

#include "../include/InterfaceManager.h"

#include <QApplication>

InterfaceManager* InterfaceManager::m_instance = nullptr;


InterfaceManager* InterfaceManager::instance() {
    if (!m_instance) {
        m_instance = new InterfaceManager();
    }
    return m_instance;
}

InterfaceManager::InterfaceManager(QObject *parent) : QObject(parent) {
    QString resourcePath = ":/settings/settings.xml";
    m_currentTheme = "light";
    xmlFilePath = QApplication::applicationDirPath() + "/settings.xml";
    loadSettingFromXml();
}

void InterfaceManager::loadSettingFromXml() {
    QFile file(xmlFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Не удалось открыть файл для чтения:" << xmlFilePath;
        return;
    }

    QXmlStreamReader xmlReader(&file);

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();

        if (xmlReader.isStartElement()) {
            QString name = xmlReader.name().toString();
            if (name == "TemperatureScale") {
                m_temperatureScale = static_cast<TemperatureScale>(xmlReader.readElementText().toInt());
            } else if (name == "PressureUnit") {
                m_pressureUnit = static_cast<PressureUnit>(xmlReader.readElementText().toInt());
            } else if (name == "LastTemperatureCelsius") {
                lastTemperature.set(xmlReader.readElementText().toInt(), TemperatureScale::Celsius);
            } else if (name == "LastPressureMmHg") {
                lastPressure.set(xmlReader.readElementText().toInt(), PressureUnit::MmHg);
            } else if (name == "LastHumidity") {
                lastHumidity = xmlReader.readElementText().toInt();
            } else if (name == "TargetTemperatureCelsius") {
                lastTargetTemperature.set(xmlReader.readElementText().toInt(), TemperatureScale::Celsius);
            } else if (name == "Theme") {
                m_currentTheme = xmlReader.readElementText();
            }
        }
    }

    if (xmlReader.hasError()) {
        qWarning() << "Ошибка чтения XML:" << xmlReader.errorString();
    }

    file.close();
}


void InterfaceManager::saveSettingToXml() {
    QFile file(xmlFilePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Не удалось открыть файл для записи:" << xmlFilePath;
        return;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("Settings");

    // Сохраняем настройки температуры
    xmlWriter.writeTextElement("TemperatureScale", QString::number(static_cast<int>(m_temperatureScale)));

    // Сохраняем настройки давления
    xmlWriter.writeTextElement("PressureUnit", QString::number(static_cast<int>(m_pressureUnit)));

    // Сохраняем текущие значения
    xmlWriter.writeTextElement("LastTemperatureCelsius", QString::number(lastTemperature[TemperatureScale::Celsius]));
    xmlWriter.writeTextElement("LastPressureMmHg", QString::number(lastPressure[PressureUnit::MmHg]));
    xmlWriter.writeTextElement("LastHumidity", QString::number(lastHumidity));

    // Сохраняем целевую температуру
    xmlWriter.writeTextElement("TargetTemperatureCelsius", QString::number(lastTargetTemperature[TemperatureScale::Celsius]));

    // Сохраняем текущую тему
    xmlWriter.writeTextElement("Theme", m_currentTheme);

    xmlWriter.writeEndElement(); // Закрываем элемент "Settings"
    xmlWriter.writeEndDocument();

    file.close();
}

void InterfaceManager::setTheme(const QString &themeName) {
    m_currentTheme = themeName;
    emit themeChanged(themeName);
    saveSettingToXml();
}

QString InterfaceManager::currentTheme() const {
    return m_currentTheme;
}

void InterfaceManager::updateTemperature(int newCelsius) {
    lastTemperature.set(newCelsius, TemperatureScale::Celsius);
    emit somePropertyUpdated();
    emit temperatureUpdated(lastTemperature);
}

void InterfaceManager::updatePressure(int newMmHg) {
    lastPressure.set(newMmHg, PressureUnit::MmHg);
    emit somePropertyUpdated();
    emit pressureUpdated(lastPressure);
}

void InterfaceManager::updateHumidity(int newHumidity) {
    lastHumidity = newHumidity;
    emit somePropertyUpdated();
    emit humidityUpdated(newHumidity);
}

TemperatureScale InterfaceManager::temperatureScale() { return m_temperatureScale; }
PressureUnit InterfaceManager::pressureUnit() { return m_pressureUnit; }
Temperature InterfaceManager::targetTemperature() const {return lastTargetTemperature;}
Temperature InterfaceManager::curTemperature() const { return lastTemperature;}
Pressure InterfaceManager::curPressure() const { return lastPressure;}
int InterfaceManager::curHumidity() const { return lastHumidity;}
bool InterfaceManager::isOn() const { return isPowerOn;}

void InterfaceManager::updateMeasurementScale(TemperatureScale newTempScale, PressureUnit newPressureUnit) {
    m_temperatureScale = newTempScale;
    m_pressureUnit = newPressureUnit;
    emit somePropertyUpdated();
    emit measurementScaleUpdated(m_temperatureScale, m_pressureUnit);
    saveSettingToXml();
}

void InterfaceManager::togglePower() {
    if(isPowerOn) {
        isPowerOn = false;
        emit powerOff();
    }
    else {
        isPowerOn = true;
        emit powerOn();
    }

    saveSettingToXml();

}

void InterfaceManager::incrementTargetTemperature(int delta, TemperatureScale scale) {
    lastTargetTemperature.set(lastTargetTemperature[scale] + delta, scale);

    emit somePropertyUpdated();
    emit targetTemperatureUpdated(lastTargetTemperature);

    saveSettingToXml();
}


void InterfaceManager::settingsBtnClicked() {
    emit openSettingsDialog();
}



