#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QDebug>
#include <QStackedLayout>
#include <QFile>
#include <QApplication>

#include "CustomButton.h"
#include "ThemeButton.h"
#include "TemperatureWidget.h"
#include "HeaderWidget.h"
#include "TapButton.h"
#include "StatusBlockGraphics.h"
#include "InterfaceManager.h"
#include "SettingsDialog.h"

/**
 * @class MainWindow
 * @brief The main application window.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructor for MainWindow.
     * @param parent Parent widget.
     */
    explicit MainWindow(QWidget *parent = nullptr);

private:
    /**
     * @brief Sets up the UI components.
     */
    void setupUi();

    /**
     * @brief Creates the header widget.
     * @param parent Parent widget.
     * @return Pointer to the created HeaderWidget.
     */
    HeaderWidget* createHeaderWidget(QWidget *parent);

    /**
     * @brief Creates the main widget.
     * @param parent Parent widget.
     * @return Pointer to the created main widget.
     */
    QWidget* createMainWidget(QWidget *parent);

    /**
     * @brief Creates the left widget.
     * @param parent Parent widget.
     * @return Pointer to the created left widget.
     */
    QWidget* createLeftWidget(QWidget *parent);

    /**
     * @brief Creates the right widget.
     * @param parent Parent widget.
     * @return Pointer to the created right widget.
     */
    QWidget* createRightWidget(QWidget *parent);

    /**
     * @brief Creates the temperature control layout.
     * @param parent Parent widget.
     * @return Pointer to the created QHBoxLayout.
     */
    QHBoxLayout* createTemperatureControlLayout(QWidget *parent);

    /**
     * @brief Creates the blow direction layout.
     * @param parent Parent widget.
     * @return Pointer to the created QHBoxLayout.
     */
    QHBoxLayout* createBlowDirectionLayout(QWidget *parent);

    /**
     * @brief Creates a custom button.
     * @param iconPath Path to the icon.
     * @param activeIconPath Path to the active icon.
     * @param parent Parent widget.
     * @return Pointer to the created CustomButton.
     */
    CustomButton* createCustomButton(const QString &iconPath, const QString& activeIconPath, QWidget *parent);

    /**
     * @brief Creates a tap button.
     * @param iconPath Path to the icon.
     * @param parent Parent widget.
     * @return Pointer to the created TapButton.
     */
    TapButton* createTapButton(const QString &iconPath, QWidget *parent);

    QLabel *temperatureLabel; ///< Label for temperature.
    QLabel *humidityLabel; ///< Label for humidity.
    QLabel *pressureLabel; ///< Label for pressure.

    QPushButton *powerButton; ///< Button to toggle power.
    QPushButton *increaseTempButton; ///< Button to increase temperature.
    QPushButton *decreaseTempButton; ///< Button to decrease temperature.

    QComboBox *temperatureUnitComboBox; ///< Combo box for temperature units.
    QGraphicsScene *scene; ///< Graphics scene.
    QGraphicsView *view; ///< Graphics view.

    HeaderWidget *headerWidget; ///< Header widget.
    QWidget *leftWidget; ///< Left widget.
    QWidget *rightWidget; ///< Right widget.

    TapButton *tempMinusButton; ///< Button to decrease temperature.
    TapButton *tempPlusButton; ///< Button to increase temperature.

    SettingsDialog *settingsDialog; ///< Settings dialog.

    bool isDarkTheme = false; ///< Flag for dark theme.

public:
    /**
     * @brief Sets the theme file.
     * @param themeName Name of the theme.
     */
    static void setThemeFile(const QString &themeName);

protected:
    /**
     * @brief Handles the resize event.
     * @param event Resize event.
     */
    void resizeEvent(QResizeEvent *event) override;

protected slots:
    /**
     * @brief Slot to handle theme changes.
     * @param themeName Name of the new theme.
     */
    void themeChanged(const QString& themeName);
};

#endif // MAINWINDOW_H