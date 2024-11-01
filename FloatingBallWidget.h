#ifndef FLOATINGBALLWIDGET_H
#define FLOATINGBALLWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
class FloatingBallWidget : public QWidget
{
    Q_OBJECT

public:
    FloatingBallWidget(QWidget *parent = nullptr);
    ~FloatingBallWidget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void updateInfo();
    void onNetworkReply();
    void onCpuUsageReply();

private:
    QTimer *timer;
    double cpuUsage;
    double downloadSpeed;

    bool dragging; // 是否正在拖动
    QPoint dragPosition; // 拖动时的初始位置
};

#endif // FLOATINGBALLWIDGET_H

