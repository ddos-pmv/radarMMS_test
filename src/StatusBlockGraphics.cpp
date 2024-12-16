#include "../include/StatusBlockGraphics.h"
#include "../include/InterfaceManager.h"

namespace {
    constexpr qreal FanSizeFactor = 0.6;         ///< Размер изображения относительно высоты блока
    constexpr qreal FanMarginFactor = 0.05;      ///< Отступ изображения от левого края
    constexpr qreal TextMargin = 20;             ///< Расстояние между изображением и текстом
    constexpr qreal TextTopMarginFactor = 0.1;   ///< Отступ верхнего текста от верхнего края
    constexpr qreal HeaderFontFactor = 0.2;      ///< Размер шрифта заголовка
    constexpr qreal InfoFontFactor = 0.1;        ///< Размер шрифта для статуса и информации
    constexpr qreal LineSpacing = 5;            ///< Расстояние между строками
}

StatusBlockGraphics::StatusBlockGraphics(const QString &header, bool powerIsOn, const QString &info, const QString &imgSrc, QWidget *parent)
    : QGraphicsView(parent) {
    setFrameShape(NoFrame);
    setRenderHint(QPainter::Antialiasing);
    setStyleSheet("background: transparent");
    setContentsMargins(0, 0, 0, 0);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Создание сцены
    scene = new QGraphicsScene(this);
    this->setScene(scene);

    // Фон блока
    background = createRectItem(QColor(240, 240, 240));
    scene->addItem(background);

    // Картинка вентилятора
    fanPixmapItem = createPixmapItem(imgSrc);
    scene->addItem(fanPixmapItem);

    // Надпись header
    cpuText = createTextItem(Qt::black);
    cpuText->setPlainText(header);
    scene->addItem(cpuText);

    // Текст статуса
    statusText = createTextItem(Qt::gray);
    scene->addItem(statusText);

    // Дополнительная информация
    infoText = createTextItem(Qt::gray);
    scene->addItem(infoText);

    updatePower(powerIsOn);
    updateInfoText(info);

    // Подключение сигналов для обновления состояния питания
    connect(InterfaceManager::instance(), &InterfaceManager::powerOff, [&]() {
        updatePower(false);
    });
    connect(InterfaceManager::instance(), &InterfaceManager::powerOn, [&]() {
        updatePower(true);
    });
}

void StatusBlockGraphics::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    resizeElements();
}

void StatusBlockGraphics::resizeElements() {
    const qreal viewWidth = this->width() - contentsMargins().left() - contentsMargins().right();
    const qreal viewHeight = this->height() - contentsMargins().top() - contentsMargins().bottom();
    scene->setSceneRect(0, 0, viewWidth, viewHeight);

    // Обновление фона
    background->setRect(0, 0, viewWidth, viewHeight);

    // Размер и позиция вентилятора
    const qreal fanSize = viewHeight * FanSizeFactor;
    fanPixmapItem->setPixmap(fanPixmapItem->pixmap().scaled(fanSize, fanSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    fanPixmapItem->setPos(viewWidth * FanMarginFactor, (viewHeight - fanSize) / 2);

    // Расчёт позиций текста
    QRectF pixmapBounds = fanPixmapItem->sceneBoundingRect();
    qreal textStartX = pixmapBounds.right() + TextMargin;
    qreal textStartY = viewHeight * TextTopMarginFactor;

    // Обновляем шрифты и позиции текста
    updateText(cpuText, HeaderFontFactor, textStartX, textStartY);
    updateText(statusText, InfoFontFactor, textStartX, cpuText->sceneBoundingRect().bottom() + LineSpacing);
    updateText(infoText, InfoFontFactor, textStartX, statusText->sceneBoundingRect().bottom() + LineSpacing);
}

void StatusBlockGraphics::updatePower(bool isPowerOn) {
    if (isPowerOn) {
        statusText->setPlainText("Power: On");
    } else {
        statusText->setPlainText("Power: Off");
    }
}

void StatusBlockGraphics::updateInfoText(const QString &info) {
    infoText->setPlainText(info);
}

QGraphicsRectItem* StatusBlockGraphics::createRectItem(const QColor &color) {
    auto *rect = new QGraphicsRectItem();
    rect->setBrush(color);
    rect->setPen(Qt::NoPen);
    return rect;
}

QGraphicsPixmapItem* StatusBlockGraphics::createPixmapItem(const QString &imgSrc) {
    QPixmap pixmap(imgSrc);
    auto *item = new QGraphicsPixmapItem();
    item->setTransformationMode(Qt::SmoothTransformation);
    item->setPixmap(pixmap);
    return item;
}

QGraphicsTextItem* StatusBlockGraphics::createTextItem(const QColor &color) {
    auto *textItem = new QGraphicsTextItem();
    textItem->setDefaultTextColor(color);
    return textItem;
}

void StatusBlockGraphics::updateText(QGraphicsTextItem *textItem, qreal fontFactor, qreal x, qreal y) {
    QFont font("Arial", scene->height() * fontFactor);
    textItem->setFont(font);
    textItem->setPos(x, y);
}