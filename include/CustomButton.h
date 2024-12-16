// include/CustomButton.h
#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QPixmap>
#include <QVariant>
#include <QDebug>
#include <QResizeEvent>
#include <QStyle>

#include "TapButton.h"

/**
 * @class CustomButton
 * @brief A custom button that changes its image and color when selected.
 */
class CustomButton : public QPushButton {
    Q_OBJECT

public:
    /**
     * @brief Constructor for CustomButton.
     * @param parent Parent widget.
     */
    explicit CustomButton(QWidget *parent = nullptr);

    /**
     * @brief Sets the images for the unselected and selected states.
     * @param unselected Path to the image for the unselected state.
     * @param selected Path to the image for the selected state.
     */
    void setImage(const QString &unselected, const QString &selected);

protected:
    /**
     * @brief Handles the resize event.
     * @param event Resize event.
     */
    void resizeEvent(QResizeEvent *event) override;

    protected slots:
        /**
         * @brief Slot to change the color and image of the button when clicked.
         */
        void changeColor();

private:
    QPixmap unselectedImage; ///< Image for the unselected state.
    QPixmap selectedImage; ///< Image for the selected state.
    bool isSelected; ///< Indicates whether the button is selected.
    QSize fixedIconSize = QSize(30, 30); ///< Fixed size for the icon.
    int padding = 40; ///< Padding for the button.

    /**
     * @brief Updates the button content based on the selected state.
     */
    void updateButtonContent();
};

#endif // CUSTOMBUTTON_H