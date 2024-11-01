#include "FloatingBallWidget.h"
#include <QProcess>
#include <QMouseEvent>
#include <QNetworkRequest>
#include <QGuiApplication>
#include <QScreen>
FloatingBallWidget::FloatingBallWidget(QWidget *parent)
    : QWidget(parent), cpuUsage(0.0), downloadSpeed(0.0), dragging(false)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    resize(200, 100);

    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->geometry();
        int x = screenGeometry.width() - 3*width();  // 右侧位置
        int y = screenGeometry.height() -3* height(); // 底部位置
        move(x, y);  // 设置初始位置为右下角
    }
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FloatingBallWidget::updateInfo);
    timer->start(1000);

}

FloatingBallWidget::~FloatingBallWidget()
{
}

void FloatingBallWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::white);
    painter.drawEllipse(0, 0, width(), height());

    painter.setPen(Qt::black);
    painter.drawText(rect(), Qt::AlignCenter, 
    QString("CPU: %1%\nDownload: %2 MB/s").arg(cpuUsage).arg(downloadSpeed));
}

void FloatingBallWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = true; // 开始拖动
        dragPosition = event->globalPos() - frameGeometry().topLeft(); // 记录拖动的起始位置
        setCursor(Qt::ClosedHandCursor); // 更改鼠标指针
    }
}

void FloatingBallWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging) {
        move(event->globalPos() - dragPosition); // 更新位置
    }
}

void FloatingBallWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = false; // 结束拖动
        unsetCursor(); // 恢复鼠标指针
    }
}

void FloatingBallWidget::updateInfo()
{
    onNetworkReply();
    onCpuUsageReply();
    // 更新界面
    update();
}

void FloatingBallWidget::onCpuUsageReply()
{
    // 获取 CPU 占用率
    QProcess process;
    process.start("./getCpu.sh");
    process.waitForFinished();
    QString output(process.readAllStandardOutput());
    cpuUsage = output.remove('%').toDouble();
}

void FloatingBallWidget::onNetworkReply()
{
    QProcess process;
    process.start("./getDownloadSpeed.sh");
    process.waitForFinished();
    QString output(process.readAllStandardOutput());
    downloadSpeed =  output.toDouble();
}

