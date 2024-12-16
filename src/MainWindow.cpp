// src/MainWindow.cpp
#include "../include/MainWindow.h"

namespace ResourcePaths {
    const QString MinusBtn = ":/resources/images/btns/minusBtnBlack.png";
    const QString PlusBtn = ":/resources/images/btns/plusBtnBlack.png";
    const QString WindRight = ":/resources/images/wind/windBlackRight.png";
    const QString WindLeft = ":/resources/images/wind/windBlackLeft.png";
    const QString WindUp = ":/resources/images/wind/windBlackUp.png";
    const QString WindDown = ":/resources/images/wind/windBlackDown.png";
    const QString WindRightActive = ":/resources/images/wind/windWhiteRight.png";
    const QString WindLeftActive = ":/resources/images/wind/windWhiteLeft.png";
    const QString WindUpActive = ":/resources/images/wind/windWhiteUp.png";
    const QString WindDownActive = ":/resources/images/wind/windWhiteDown.png";
    const QString FanIcon = ":/resources/images/blocks/fan.png";
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi();
    connect(InterfaceManager::instance(), &InterfaceManager::themeChanged, this, &MainWindow::themeChanged);
    setThemeFile(InterfaceManager::instance()->currentTheme());
}

void MainWindow::setupUi() {
    QWidget *centralWidget = new QWidget(this);
    QStackedLayout *centralLayout = new QStackedLayout(centralWidget);

    settingsDialog = new SettingsDialog(this);
    headerWidget = createHeaderWidget(centralWidget);

    QWidget *mainWidget = createMainWidget(centralWidget);

    centralLayout->addWidget(headerWidget);
    centralLayout->addWidget(mainWidget);
    centralLayout->setStackingMode(QStackedLayout::StackAll);

    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);
}

HeaderWidget* MainWindow::createHeaderWidget(QWidget *parent) {
    auto *widget = new HeaderWidget(parent);
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widget->setContentsMargins(0, 2, 0, 0);
    return widget;
}

QWidget* MainWindow::createMainWidget(QWidget *parent) {
    QWidget *mainWidget = new QWidget(parent);
    QHBoxLayout *mainLayout = new QHBoxLayout(mainWidget);

    leftWidget = createLeftWidget(mainWidget);
    rightWidget = createRightWidget(mainWidget);

    mainLayout->addWidget(leftWidget, 5);
    mainLayout->addWidget(rightWidget, 4);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    mainWidget->setLayout(mainLayout);

    return mainWidget;
}

QWidget* MainWindow::createLeftWidget(QWidget *parent) {
    QWidget *widget = new QWidget(parent);
    widget->setAttribute(Qt::WA_StyledBackground, true);
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widget->setObjectName("LeftWidget");

    QVBoxLayout *layout = new QVBoxLayout(widget);

    layout->addWidget(new TemperatureWidget(widget), 5);
    layout->addLayout(createTemperatureControlLayout(widget), 1);
    layout->addLayout(createBlowDirectionLayout(widget), 1);
    layout->setSpacing(10);

    widget->setLayout(layout);

    return widget;
}

QWidget* MainWindow::createRightWidget(QWidget *parent) {
    InterfaceManager* managerInstance = InterfaceManager::instance();

    QWidget *widget = new QWidget(parent);
    widget->setObjectName("RightWidget");
    widget->setAttribute(Qt::WA_StyledBackground, true);
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout *layout = new QVBoxLayout(widget);

    StatusBlockGraphics *firstBlock = new StatusBlockGraphics("Fan1", managerInstance->isOn(), "No issues", ResourcePaths::FanIcon, this);
    StatusBlockGraphics *secondBlock = new StatusBlockGraphics("Fan2", managerInstance->isOn(), "No issues", ResourcePaths::FanIcon, this);
    StatusBlockGraphics *thirdBlock = new StatusBlockGraphics("Fan3", managerInstance->isOn(), "No issues", ResourcePaths::FanIcon, this);

    firstBlock->setMaximumHeight(height() / 4);
    secondBlock->setMaximumHeight(height() / 4);
    thirdBlock->setMaximumHeight(height() / 4);

    layout->setContentsMargins(20, 20, 20, 20);
    layout->addWidget(firstBlock);
    layout->addWidget(secondBlock);
    layout->addWidget(thirdBlock);
    layout->addStretch();

    widget->setLayout(layout);
    return widget;
}

QHBoxLayout* MainWindow::createTemperatureControlLayout(QWidget *parent) {
    QHBoxLayout *layout = new QHBoxLayout();

    tempMinusButton = createTapButton(ResourcePaths::MinusBtn, parent);
    tempPlusButton = createTapButton(ResourcePaths::PlusBtn, parent);

    connect(tempMinusButton, &TapButton::clicked, []() {
        InterfaceManager::instance()->incrementTargetTemperature(-1, InterfaceManager::instance()->temperatureScale());
    });

    connect(tempPlusButton, &TapButton::clicked, []() {
        InterfaceManager::instance()->incrementTargetTemperature(1, InterfaceManager::instance()->temperatureScale());
    });

    QLabel *temperatureLabel = new QLabel("Temperature", parent);
    temperatureLabel->setAlignment(Qt::AlignCenter);
    temperatureLabel->setObjectName("temperatureLabel");
    temperatureLabel->setAttribute(Qt::WA_StyledBackground, true);
    temperatureLabel->setMargin(0);
    temperatureLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(tempMinusButton, 1);
    layout->addWidget(temperatureLabel, 2);
    layout->addWidget(tempPlusButton, 1);
    layout->setSpacing(5);
    layout->setContentsMargins(0,0,0,0);

    return layout;
}

QHBoxLayout* MainWindow::createBlowDirectionLayout(QWidget *parent) {
    QHBoxLayout *layout = new QHBoxLayout();

    auto *blowDown = createCustomButton(ResourcePaths::WindDown, ResourcePaths::WindDownActive, parent);
    auto *blowLeft = createCustomButton(ResourcePaths::WindLeft, ResourcePaths::WindLeftActive, parent);
    auto *blowRight = createCustomButton(ResourcePaths::WindRight, ResourcePaths::WindRightActive, parent);
    auto *blowUp = createCustomButton(ResourcePaths::WindUp, ResourcePaths::WindUpActive, parent);

    layout->addWidget(blowLeft);
    layout->addWidget(blowUp);
    layout->addWidget(blowRight);
    layout->addWidget(blowDown);

    layout->setSpacing(5);
    layout->setContentsMargins(0, 0,0,0);

    return layout;
}

CustomButton* MainWindow::createCustomButton(const QString &iconPath, const QString &activeIconPath, QWidget *parent) {
    CustomButton *button = new CustomButton(parent);
    button->setImage(iconPath, activeIconPath);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setObjectName("customButton");
    button->setAttribute(Qt::WA_StyledBackground, true);
    return button;
}

TapButton* MainWindow::createTapButton(const QString &iconPath, QWidget *parent) {
    auto *button = new TapButton(parent);
    button->setImage(iconPath);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setObjectName("temperatureButton");
    setAttribute(Qt::WA_StyledBackground, true);
    return button;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    int windowHeight = height();
    headerWidget->setMaximumHeight(windowHeight / 15);
    rightWidget->setContentsMargins(0, headerWidget->height(), 0, 0);
}

void MainWindow::themeChanged(const QString &themeName) {
    setThemeFile(themeName);
}

void MainWindow::setThemeFile(const QString &themeName) {
    QFile file(":/resources/styles/" + themeName + ".qss");
    if (file.open(QIODevice::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
    } else {
        qDebug() << "error file opening to set theme";
    }
}