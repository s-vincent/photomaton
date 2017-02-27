/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "camera.h"
#include "ui_camera.h"
#include "imagesettings.h"

#include <QMediaService>
#include <QMediaRecorder>
#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QMediaMetaData>

#include <QMessageBox>
#include <QPalette>

#include <QtWidgets>

Q_DECLARE_METATYPE(QCameraInfo)

const QString DUMMY_FILEPATH = QDir::currentPath() + "/images/dummy.dmy";

Camera::Camera(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Camera),
    camera(0),
    imageCapture(0),
    isCapturingImage(false),
    applicationExiting(false)
{
    ui->setupUi(this);
    this->showMaximized();
    //this->showFullScreen();

    this->ui->statusbar->setVisible(false);
    this->ui->menubar->setVisible(false);

#ifdef Q_OS_UNIX
    /* there are some problems with overlay in video widget on Unix platforms */
    this->ui->lbl->setParent(NULL);
    //this->ui->lbl->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->ui->lbl->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);
    this->ui->lbl->setAttribute(Qt::WA_TranslucentBackground);
    this->ui->lbl->setAttribute(Qt::WA_ShowWithoutActivating);
#endif

    int idx = 0;
    this->cameraIdx = 0;

    //Camera devices
    QActionGroup *videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
    foreach (const QCameraInfo &cameraInfo, QCameraInfo::availableCameras()) {
        QAction *videoDeviceAction = new QAction(cameraInfo.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant::fromValue(cameraInfo));
        if (cameraInfo == QCameraInfo::defaultCamera())
        {
            videoDeviceAction->setChecked(true);
            cameraIdx = idx;
        }
        idx++;
        ui->menuDevices->addAction(videoDeviceAction);
    }

    connect(videoDevicesGroup, SIGNAL(triggered(QAction*)), SLOT(updateCameraDevice(QAction*)));

    setCamera(QCameraInfo::defaultCamera());
    timer = new QTimer(this);
    timerPrint = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(displayCountdown()));
    connect(timerPrint, SIGNAL(timeout()), this, SLOT(displayPrint()));
}

Camera::~Camera()
{
    delete imageCapture;
    delete camera;
}

void Camera::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

#ifdef Q_OS_UNIX
    /* there are some problems with overlay in video widget on Unix platforms */
    int w = ui->viewfinder->size().width();
    int h = ui->viewfinder->size().height();

    ui->lbl->setGeometry(ui->viewfinder->pos().x(), ui->viewfinder->pos().y(), w, h);
#else
    int w = ui->lbl->parentWidget()->size().width();
    int h = ui->lbl->parentWidget()->size().height();
    ui->lbl->setGeometry(0, 0, w, h);
#endif
}

void Camera::setCamera(const QCameraInfo &cameraInfo)
{
    delete imageCapture;
    delete camera;

    camera = new QCamera(cameraInfo);

    connect(camera, SIGNAL(stateChanged(QCamera::State)), this, SLOT(updateCameraState(QCamera::State)));
    connect(camera, SIGNAL(error(QCamera::Error)), this, SLOT(displayCameraError()));

    imageCapture = new QCameraImageCapture(camera);
    QImageEncoderSettings settings = imageCapture->encodingSettings();
    settings.setQuality(QMultimedia::EncodingQuality(QMultimedia::VeryHighQuality));
    settings.setResolution(1920, 1080);

    camera->setViewfinder(ui->viewfinder);

    updateCameraState(camera->state());
    updateLockStatus(camera->lockStatus(), QCamera::UserRequest);

    connect(imageCapture, SIGNAL(readyForCaptureChanged(bool)), this, SLOT(readyForCapture(bool)));
    connect(imageCapture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(processCapturedImage(int,QImage)));
    connect(imageCapture, SIGNAL(imageSaved(int,QString)), this, SLOT(imageSaved(int,QString)));
    connect(imageCapture, SIGNAL(error(int,QCameraImageCapture::Error,QString)), this,
            SLOT(displayCaptureError(int,QCameraImageCapture::Error,QString)));

    connect(camera, SIGNAL(lockStatusChanged(QCamera::LockStatus,QCamera::LockChangeReason)),
            this, SLOT(updateLockStatus(QCamera::LockStatus,QCamera::LockChangeReason)));

    updateCaptureMode();
    camera->start();

    cpt = 0;
    nbPhoto = 0;
    this->ui->lbl->setVisible(false);
    this->ui->lbl->setStyleSheet("border: 0px;");
}

void Camera::keyPressEvent(QKeyEvent * event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_CameraFocus:
        displayViewfinder();
        camera->searchAndLock();
        event->accept();
        break;
    case Qt::Key_Camera:
        if (camera->captureMode() == QCamera::CaptureStillImage) {
            takeImage();
        }
        event->accept();
        break;
    default:
        if(cheatCode == "" && event->key() == 'A')
        {
            cheatCode.append("A");
        }
        else if(cheatCode == "A" && event->key() == 'K')
        {
            cheatCode.append("K");
        }
        else if(cheatCode == "AK" && event->key() == '8')
        {
            cheatCode.append("8");
        }
        else if(cheatCode == "AK8" && event->key() == '4')
        {
            timer->stop();
            QMessageBox box(this);
            box.setText("Exit mode");
            box.exec();

            // exit code
            QFile::remove(DUMMY_FILEPATH);
            cheatCode.clear();
            exit(1);
            break;
        }
        else if(cheatCode == "AK8" && event->key() == '5')
        {
            timer->stop();
            timerPrint->stop();
            this->ui->lbl->setVisible(false);

            QMessageBox box(this);
            box.setText("Reset mode");
            box.exec();

            // reset code
            cpt = 0;
            nbPhoto = 0;
            QFile::remove(DUMMY_FILEPATH);
            cheatCode.clear();
            break;
        }
        else if(cheatCode == "AK8" && event->key() == '6')
        {
            timer->stop();
            timerPrint->stop();
            cpt = 0;
            this->ui->lbl->setVisible(false);

            QMessageBox box(this);

            QList<QCameraInfo> cams = QCameraInfo::availableCameras();

            // only one camera so quit
            if(cams.size() == 1)
            {
                return;
            }

            cameraIdx++;
            if(cameraIdx >= cams.size())
            {
                cameraIdx = 0;
            }

            box.setText("Change webcam " + QString::number(cameraIdx));
            box.exec();

            setCamera(cams.at(cameraIdx));
            cheatCode.clear();
            break;
        }
        else if(cheatCode == "AK8" && event->key() == '7')
        {
            timer->stop();
            timerPrint->stop();
            cpt = 0;
            this->ui->lbl->setVisible(false);

            QMessageBox box(this);
            box.setText("Go in fullscreen mode");
            box.exec();

            this->showFullScreen();
            cheatCode.clear();
            break;
        }
        else if(cheatCode == "AK8" && event->key() == '8')
        {
            timer->stop();
            timerPrint->stop();
            cpt = 0;
            this->ui->lbl->setVisible(false);

            if(!this->isFullScreen())
            {
                break;
            }

            QMessageBox box(this);
            box.setText("Exit fullscreen mode");
            box.exec();

            this->showMaximized();
            cheatCode.clear();
            break;
        }
        else
        {
            cheatCode.clear();
        }

        //QMainWindow::keyPressEvent(event);
        if(cpt == 0 && nbPhoto == 0)
        {
            if(QFile::exists(DUMMY_FILEPATH))
            {
                // dummy file still present, printing in progress
                return;
            }
            countdown();
        }
        break;
    }
}

void Camera::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_CameraFocus:
        camera->unlock();
        break;
    default:
        //QMainWindow::keyReleaseEvent(event);
        break;
    }
}

void Camera::moveEvent(QMoveEvent *event)
{
    QWidget::moveEvent(event);

#ifdef Q_OS_UNIX
    /* there are some problems with overlay in video widget on Unix platforms */
    int w = ui->viewfinder->size().width();
    int h = ui->viewfinder->size().height();

    ui->lbl->setGeometry(ui->viewfinder->pos().x(), ui->viewfinder->pos().y(), w, h);
#endif
}

void Camera::processCapturedImage(int requestId, const QImage& img)
{
    Q_UNUSED(requestId);
    QImage scaledImage = img.scaled(ui->viewfinder->size(),
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);

    ui->lastImagePreviewLabel->setPixmap(QPixmap::fromImage(scaledImage));

    // Display captured image for 4 seconds.
    displayCapturedImage();
    QTimer::singleShot(4000, this, SLOT(displayViewfinder()));
}

void Camera::configureCaptureSettings()
{
    switch (camera->captureMode()) {
    case QCamera::CaptureStillImage:
        configureImageSettings();
        break;
    default:
        break;
    }
}

void Camera::configureImageSettings()
{
    ImageSettings settingsDialog(imageCapture);

    settingsDialog.setImageSettings(imageSettings);

    if (settingsDialog.exec()) {
        imageSettings = settingsDialog.imageSettings();
        imageCapture->setEncodingSettings(imageSettings);
    }
}

void Camera::toggleLock()
{
    switch (camera->lockStatus()) {
    case QCamera::Searching:
    case QCamera::Locked:
        camera->unlock();
        break;
    case QCamera::Unlocked:
        camera->searchAndLock();
    }
}

void Camera::updateLockStatus(QCamera::LockStatus status, QCamera::LockChangeReason reason)
{
    QColor indicationColor = Qt::black;

    switch (status) {
    case QCamera::Searching:
        indicationColor = Qt::yellow;
        ui->statusbar->showMessage(tr("Focusing..."));
        break;
    case QCamera::Locked:
        indicationColor = Qt::darkGreen;
        ui->statusbar->showMessage(tr("Focused"), 2000);
        break;
    case QCamera::Unlocked:
        indicationColor = reason == QCamera::LockFailed ? Qt::red : Qt::black;
        if (reason == QCamera::LockFailed)
            ui->statusbar->showMessage(tr("Focus Failed"), 2000);
    }
}

void Camera::countdown()
{
    cpt = 5;
    this->ui->lbl->setVisible(true);
    this->ui->lbl->setText(QString::number(cpt));

    QFont f( "Arial", 200, QFont::Normal);
    this->ui->lbl->setFont(f);

    timer->start(1000);
}

void Camera::displayCountdown()
{
    cpt--;

    if(cpt == 0)
    {
        timer->stop();
        this->ui->lbl->setVisible(false);
        takeImage();
    }
    else
    {
        this->ui->lbl->setText(QString::number(cpt));
        this->ui->lbl->setVisible(true);
    }
}

void Camera::displayPrint()
{
    if(!QFile::exists(DUMMY_FILEPATH))
    {
        timerPrint->stop();
        this->ui->lbl->setVisible(false);
    }
    else
    {
        QFont f( "Arial", 100, QFont::Normal);
        this->ui->lbl->setFont(f);
        this->ui->lbl->setText("Printing in progress");
        if(this->ui->lbl->isVisible())
        {
            this->ui->lbl->setVisible(false);
        }
        else
        {
            this->ui->lbl->setVisible(true);
        }
    }
}

void Camera::takeImage()
{
    isCapturingImage = true;

    // saving image to file
    QString path = QDir::currentPath() + "/images/party-";
    path += QString::number(QDateTime::currentMSecsSinceEpoch());
    path += ".jpg";

    imageCapture->capture(path);
}

void Camera::displayCaptureError(int id, const QCameraImageCapture::Error error, const QString &errorString)
{
    Q_UNUSED(id);
    Q_UNUSED(error);
    QMessageBox::warning(this, tr("Image Capture Error"), errorString);
    isCapturingImage = false;
}

void Camera::startCamera()
{
    camera->start();
}

void Camera::stopCamera()
{
    camera->stop();
}

void Camera::updateCaptureMode()
{

}

void Camera::updateCameraState(QCamera::State state)
{
    switch (state) {
    case QCamera::ActiveState:
        ui->actionStartCamera->setEnabled(false);
        ui->actionStopCamera->setEnabled(true);
        ui->actionSettings->setEnabled(true);
        break;
    case QCamera::UnloadedState:
    case QCamera::LoadedState:
        ui->actionStartCamera->setEnabled(true);
        ui->actionStopCamera->setEnabled(false);
        ui->actionSettings->setEnabled(false);
    }
}

void Camera::setExposureCompensation(int index)
{
    camera->exposure()->setExposureCompensation(index*0.5);
}

void Camera::displayCameraError()
{
    QMessageBox::warning(this, tr("Camera error"), camera->errorString());
}

void Camera::updateCameraDevice(QAction *action)
{
    setCamera(qvariant_cast<QCameraInfo>(action->data()));
}

void Camera::displayViewfinder()
{
    ui->stackedWidget->setCurrentIndex(0);
    this->ui->lbl->setVisible(false);

    nbPhoto++;
    if(nbPhoto < 3)
    {
        countdown();
    }
    else
    {
        nbPhoto = 0;
        cpt = 0;
        QFile dummy(DUMMY_FILEPATH);
        dummy.open(QIODevice::ReadWrite);
        dummy.write("0", 1);
        dummy.close();
        timerPrint->start(1000);
    }
}

void Camera::displayCapturedImage()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Camera::imageSaved(int id, const QString &fileName)
{
    Q_UNUSED(id);
    Q_UNUSED(fileName);

    isCapturingImage = false;
    if (applicationExiting)
        close();
}

void Camera::closeEvent(QCloseEvent *event)
{
    if (isCapturingImage) {
        setEnabled(false);
        applicationExiting = true;
        event->ignore();
    } else {
        //event->accept();
        event->ignore();
    }
}
