//
// Created by Сергей Перлин on 11.12.2024.
//

#ifndef HEADERBUTTON_H
#define HEADERBUTTON_H

#include <QPushButton>
#include <QIcon>
#include <QWidget>
#include "InterfaceManager.h"

class HeaderButton : public QPushButton {
    Q_OBJECT
public:
    explicit HeaderButton(QWidget* parent = nullptr);

    void setImage(const QString& lightThemePath, const QString& darkThemePath);
    void setPadding(int padding);

    void resizeEvent(QResizeEvent *event) override;

protected slots:
    void themeChanged(const QString& themeName);

protected:
    int m_padding = 15;
    QString lightThemeImagePath;
    QString darkThemeImagePath;

    QPixmap currImage;
};

#endif //HEADERBUTTON_H
