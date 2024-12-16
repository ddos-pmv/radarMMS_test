#include "../include/TemperatureWidget.h"

namespace InitConstants {
    const int CircleRadius = 100;
    const int CirclePadding = 160;
    const QFont TempFont = QFont("Arial", 26, QFont::Bold); ///< Font for temperature text

    const int HaloRadius = CircleRadius + 10;
    const QColor HaloColor = QColor(153, 222, 249, 100);
    const int HaloPlus = 5;
    const int HaloBlurRadius = 18;
    const int AnimDuration = 2000;
    const int HaloAnimWidth = 20;

    const QColor HaloRadColor = QColor(250,0,0,100); ///< Halo color when turned off
}

TemperatureWidget::TemperatureWidget(QWidget *parent) : QGraphicsView(parent) {
    setFrameShape(NoFrame);
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setRenderHint(QPainter::Antialiasing);
    setScene(scene);
    setStyleSheet("background: transparent");

    circle = new QGraphicsEllipseItem(0, 0, InitConstants::CircleRadius, InitConstants::CircleRadius);
    circle->setBrush(QBrush(Qt::white));
    circle->setPen(Qt::NoPen);

    halo = new AnimatedEllipse(0, 0, InitConstants::HaloRadius, InitConstants::HaloRadius);
    halo->setBrush(QBrush(InitConstants::HaloColor));
    halo->setPen(Qt::NoPen);

    haloAnimation = new QPropertyAnimation(halo, "rect");
    haloAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    haloAnimation->setLoopCount(-1);
    haloAnimation->setDuration(InitConstants::AnimDuration);
    haloAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    blurEffect = new QGraphicsBlurEffect(halo);
    blurEffect->setBlurRadius(InitConstants::HaloBlurRadius);
    halo->setGraphicsEffect(blurEffect);

    InterfaceManager* managerInstance = InterfaceManager::instance();

    Temperature curTemp = managerInstance->curTemperature();
    Temperature targetTemp = managerInstance->targetTemperature();
    TemperatureScale curTempScale = managerInstance->temperatureScale();
    temperatureText = new QGraphicsTextItem();
    temperatureText->setDefaultTextColor(Qt::black);
    setMainText(curTemp, curTempScale);

    Pressure curPressure = managerInstance->curPressure();
    PressureUnit curPressureUnit = managerInstance->pressureUnit();
    int humidity = managerInstance->curHumidity();
    descriptionText = new QGraphicsTextItem();
    descriptionText->setDefaultTextColor(Qt::gray);
    setDescriptionText(curPressure, humidity, curPressureUnit);

    scene->addItem(halo);
    scene->addItem(circle);
    scene->addItem(temperatureText);
    scene->addItem(descriptionText);

    if (managerInstance->isOn()) turnOn();
    else turnOff();

    themeChanged(managerInstance->currentTheme());

    connect(InterfaceManager::instance(), &InterfaceManager::themeChanged, this, &TemperatureWidget::themeChanged);
    connect(InterfaceManager::instance(), &InterfaceManager::somePropertyUpdated, this, &TemperatureWidget::somePropertyChanged);
    connect(InterfaceManager::instance(), &InterfaceManager::powerOn, this, &TemperatureWidget::turnOn);
    connect(InterfaceManager::instance(), &InterfaceManager::powerOff, this, &TemperatureWidget::turnOff);
}

void TemperatureWidget::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    updateWidget();
}

void TemperatureWidget::updateWidget() {
    const int size = qMin(width(), height()) - InitConstants::CirclePadding;
    scene->setSceneRect(QRectF(0, 0, size, size));
    circle->setRect(0, 0, size, size);
    halo->setRect(QRectF(
        circle->rect().x() - InitConstants::HaloPlus,
        circle->rect().y() - InitConstants::HaloPlus,
        circle->rect().width() + 2 * InitConstants::HaloPlus,
        circle->rect().height() + 2 * InitConstants::HaloPlus));
    updateHaloAnimation();

    Temperature curTemp = InterfaceManager::instance()->curTemperature();
    Temperature targetTemp = InterfaceManager::instance()->targetTemperature();
    updateTargetCircle(curTemp, targetTemp);

    updateTextPosition();
    scene->update();
}

void TemperatureWidget::updateHaloAnimation() {
    QRectF newHaloRect = halo->rect();
    haloAnimation->setStartValue(newHaloRect);
    haloAnimation->setKeyValueAt(0.5, QRectF(
        newHaloRect.x() - InitConstants::HaloAnimWidth,
        newHaloRect.y() - InitConstants::HaloAnimWidth,
        newHaloRect.width() + InitConstants::HaloAnimWidth * 2,
        newHaloRect.height() + InitConstants::HaloAnimWidth * 2
    ));
    haloAnimation->setEndValue(newHaloRect);
}

void TemperatureWidget::updateTextSize() {
    QRectF circleBounds = circle->rect();
    int circleWidth = circleBounds.width();

    QString text = temperatureText->toPlainText();
    int textLength = text.length();
    int fontSize = circleWidth / textLength;

    QFont tempFont = temperatureText->font();
    fontSize = qMax(fontSize, 12);
    tempFont.setPointSize(fontSize);
    temperatureText->setFont(tempFont);

    QString description = descriptionText->toPlainText();
    int descriptionLength = description.length();
    int descFontSize = circleWidth / descriptionLength;
    descFontSize = qMax(descFontSize, 10);
    QFont descFont = descriptionText->font();
    descFont.setPointSize(descFontSize);
    descriptionText->setFont(descFont);
}

void TemperatureWidget::updateTextPosition() {
    updateTextSize();
    int space = 20;
    QRectF circleBounds = circle->rect();
    QRectF tempBounds = temperatureText->boundingRect();
    QRectF modeBounds = descriptionText->boundingRect();

    temperatureText->setPos(
        circleBounds.center().x() - tempBounds.width() / 2,
        circleBounds.center().y() - tempBounds.height() / 2 - space
    );

    QRectF newTempTextBounds = temperatureText->boundingRect();
    descriptionText->setPos(
        circleBounds.center().x() - modeBounds.width() / 2,
        circleBounds.center().y() - tempBounds.height() / 2 + newTempTextBounds.height() / 2 + modeBounds.height() / 2
    );

    scene->update();
    update();
}

void TemperatureWidget::themeChanged(const QString& theme) {
    if (theme == "dark") {
        circle->setBrush(Qt::black);
        temperatureText->setDefaultTextColor(Qt::white);
        descriptionText->setDefaultTextColor(Qt::lightGray);
    } else {
        circle->setBrush(Qt::white);
        temperatureText->setDefaultTextColor(Qt::black);
        descriptionText->setDefaultTextColor(Qt::gray);
    }
    update();
}

void TemperatureWidget::somePropertyChanged() {
    InterfaceManager* managerInstance = InterfaceManager::instance();
    Temperature curTemp = managerInstance->curTemperature();
    Pressure curPressure = managerInstance->curPressure();
    int curHumidity = managerInstance->curHumidity();

    Temperature curTargetTemp = managerInstance->targetTemperature();

    PressureUnit curPressureUnit = managerInstance->pressureUnit();
    TemperatureScale curTempScale = managerInstance->temperatureScale();

    setMainText(curTemp, curTempScale);
    setDescriptionText(curPressure, curHumidity, curPressureUnit);

    updateTextPosition();
    updateTargetCircle(curTemp, curTargetTemp);
}

void TemperatureWidget::turnOn() {
    haloAnimation->start();
    halo->setBrush(InitConstants::HaloColor);
}

void TemperatureWidget::turnOff() {
    haloAnimation->setCurrentTime(0);
    haloAnimation->stop();
    halo->setBrush(InitConstants::HaloRadColor);
}

void TemperatureWidget::setMainText(Temperature &curTemp, TemperatureScale &curTempScale) {
    temperatureText->setPlainText(curTemp.toString(curTempScale));
    scene->update();
    update();
}

void TemperatureWidget::setDescriptionText(Pressure &curPressure, int &curHumidity, PressureUnit &curPressureUnit) {
    descriptionText->setPlainText(curPressure.toString(curPressureUnit) + "  " + QString::number(curHumidity) + "%");
}

void TemperatureWidget::updateTargetCircle(Temperature &curTemp, Temperature &targetTemp) {
    static QGraphicsEllipseItem *targetCircle = nullptr;
    static QGraphicsTextItem *targetTempText = nullptr;

    if (curTemp[InterfaceManager::instance()->temperatureScale()] != targetTemp[InterfaceManager::instance()->temperatureScale()]) {
        if (!targetCircle) {
            targetCircle = new QGraphicsEllipseItem();
            targetCircle->setBrush(QColor(100, 100, 100, 150));
            targetCircle->setPen(QPen(Qt::lightGray, 1));
            scene->addItem(targetCircle);
        }
        if (!targetTempText) {
            targetTempText = new QGraphicsTextItem();
            targetTempText->setDefaultTextColor(Qt::white);
            scene->addItem(targetTempText);
        }

        QRectF circleBounds = circle->rect();
        qreal smallCircleSize = circleBounds.width() * 0.3;
        qreal offsetX = circleBounds.right();
        qreal offsetY = circleBounds.top();

        targetCircle->setRect(offsetX, offsetY, smallCircleSize, smallCircleSize);

        QFont font("Arial", 12, QFont::Bold);
        qreal fontSize = smallCircleSize * 0.3;
        font.setPointSizeF(qMax(fontSize, 6.0));
        targetTempText->setFont(font);

        targetTempText->setPlainText(targetTemp.toString(InterfaceManager::instance()->temperatureScale()));
        QRectF textBounds = targetTempText->boundingRect();
        targetTempText->setPos(
            targetCircle->rect().center().x() - textBounds.width() / 2,
            targetCircle->rect().center().y() - textBounds.height() / 2
        );

        scene->update();
        update();
    } else {
        if (targetCircle) {
            scene->removeItem(targetCircle);
            delete targetCircle;
            targetCircle = nullptr;
        }
        if (targetTempText) {
            scene->removeItem(targetTempText);
            delete targetTempText;
            targetTempText = nullptr;
        }
    }
}