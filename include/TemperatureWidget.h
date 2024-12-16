#ifndef TEMPERATUREWIDGET_H
#define TEMPERATUREWIDGET_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QFont>
#include <QEasingCurve>
#include <QGraphicsBlurEffect>

#include "AnimatedEllipse.h"
#include "InterfaceManager.h"
#include "MeasurementEnums.h"

/**
 * @class TemperatureWidget
 * @brief A widget to display temperature and related information.
 */
class TemperatureWidget : public QGraphicsView {
    Q_OBJECT
public:
    /**
     * @brief Constructor for TemperatureWidget.
     * @param parent Parent widget.
     */
    TemperatureWidget(QWidget *parent = nullptr);

protected:
    /**
     * @brief Handles the resize event.
     * @param event Resize event.
     */
    void resizeEvent(QResizeEvent *event) override;

protected slots:
    /**
     * @brief Slot to handle theme changes.
     * @param theme Name of the new theme.
     */
    void themeChanged(const QString& theme);

    /**
     * @brief Slot to handle property changes.
     */
    void somePropertyChanged();

    /**
     * @brief Slot to turn on the widget.
     */
    void turnOn();

    /**
     * @brief Slot to turn off the widget.
     */
    void turnOff();

private:
    QGraphicsScene *scene; ///< The graphics scene.
    QGraphicsEllipseItem *circle; ///< The main circle item.
    AnimatedEllipse *halo; ///< The halo animation item.
    QGraphicsTextItem *temperatureText; ///< The temperature text item.
    QGraphicsTextItem *descriptionText; ///< The description text item.
    QPropertyAnimation *haloAnimation; ///< The halo animation.
    QGraphicsBlurEffect *blurEffect; ///< The blur effect.

    /**
     * @brief Updates the text size based on the widget size.
     */
    void updateTextSize();

    /**
     * @brief Updates the text position based on the widget size.
     */
    void updateTextPosition();

    /**
     * @brief Updates the halo animation.
     */
    void updateHaloAnimation();

    /**
     * @brief Updates the target circle based on the current and target temperatures.
     * @param curTemp Current temperature.
     * @param targetTemp Target temperature.
     */
    void updateTargetCircle(Temperature &curTemp, Temperature &targetTemp);

    /**
     * @brief Sets the main text to display the current temperature.
     * @param curTemp Current temperature.
     * @param curTempScale Current temperature scale.
     */
    void setMainText(Temperature &curTemp, TemperatureScale &curTempScale);

    /**
     * @brief Sets the description text to display the current pressure and humidity.
     * @param curPressure Current pressure.
     * @param curHumidity Current humidity.
     * @param curPressureUnit Current pressure unit.
     */
    void setDescriptionText(Pressure &curPressure, int &curHumidity, PressureUnit &curPressureUnit);

    /**
     * @brief Updates the widget elements.
     */
    void updateWidget();
};

#endif // TEMPERATUREWIDGET_H