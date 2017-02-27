/********************************************************************************
** Form generated from reading UI file 'videosettings.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOSETTINGS_H
#define UI_VIDEOSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoSettingsUi
{
public:
    QGridLayout *gridLayout_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QComboBox *audioCodecBox;
    QLabel *label_5;
    QComboBox *audioSampleRateBox;
    QLabel *label_3;
    QSlider *audioQualitySlider;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_8;
    QComboBox *videoResolutionBox;
    QLabel *label_9;
    QComboBox *videoFramerateBox;
    QLabel *label_6;
    QComboBox *videoCodecBox;
    QLabel *label_7;
    QSlider *videoQualitySlider;
    QLabel *label_4;
    QComboBox *containerFormatBox;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *VideoSettingsUi)
    {
        if (VideoSettingsUi->objectName().isEmpty())
            VideoSettingsUi->setObjectName(QStringLiteral("VideoSettingsUi"));
        VideoSettingsUi->resize(561, 369);
        gridLayout_4 = new QGridLayout(VideoSettingsUi);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        scrollArea = new QScrollArea(VideoSettingsUi);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 543, 250));
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 2);

        audioCodecBox = new QComboBox(groupBox);
        audioCodecBox->setObjectName(QStringLiteral("audioCodecBox"));

        gridLayout->addWidget(audioCodecBox, 1, 0, 1, 2);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 2);

        audioSampleRateBox = new QComboBox(groupBox);
        audioSampleRateBox->setObjectName(QStringLiteral("audioSampleRateBox"));

        gridLayout->addWidget(audioSampleRateBox, 3, 0, 1, 2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        audioQualitySlider = new QSlider(groupBox);
        audioQualitySlider->setObjectName(QStringLiteral("audioQualitySlider"));
        audioQualitySlider->setMaximum(4);
        audioQualitySlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(audioQualitySlider, 4, 1, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 0, 0, 1, 2);

        videoResolutionBox = new QComboBox(groupBox_2);
        videoResolutionBox->setObjectName(QStringLiteral("videoResolutionBox"));

        gridLayout_2->addWidget(videoResolutionBox, 1, 0, 1, 2);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 2, 0, 1, 2);

        videoFramerateBox = new QComboBox(groupBox_2);
        videoFramerateBox->setObjectName(QStringLiteral("videoFramerateBox"));

        gridLayout_2->addWidget(videoFramerateBox, 3, 0, 1, 2);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 4, 0, 1, 2);

        videoCodecBox = new QComboBox(groupBox_2);
        videoCodecBox->setObjectName(QStringLiteral("videoCodecBox"));

        gridLayout_2->addWidget(videoCodecBox, 5, 0, 1, 2);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 6, 0, 1, 1);

        videoQualitySlider = new QSlider(groupBox_2);
        videoQualitySlider->setObjectName(QStringLiteral("videoQualitySlider"));
        videoQualitySlider->setMaximum(4);
        videoQualitySlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(videoQualitySlider, 6, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 0, 1, 3, 1);

        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_3->addWidget(label_4, 1, 0, 1, 1);

        containerFormatBox = new QComboBox(scrollAreaWidgetContents);
        containerFormatBox->setObjectName(QStringLiteral("containerFormatBox"));

        gridLayout_3->addWidget(containerFormatBox, 2, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_4->addWidget(scrollArea, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(VideoSettingsUi);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_4->addWidget(buttonBox, 2, 0, 1, 1);


        retranslateUi(VideoSettingsUi);
        QObject::connect(buttonBox, SIGNAL(accepted()), VideoSettingsUi, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), VideoSettingsUi, SLOT(reject()));

        QMetaObject::connectSlotsByName(VideoSettingsUi);
    } // setupUi

    void retranslateUi(QDialog *VideoSettingsUi)
    {
        VideoSettingsUi->setWindowTitle(QApplication::translate("VideoSettingsUi", "Dialog", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("VideoSettingsUi", "Audio", Q_NULLPTR));
        label_2->setText(QApplication::translate("VideoSettingsUi", "Audio Codec:", Q_NULLPTR));
        label_5->setText(QApplication::translate("VideoSettingsUi", "Sample Rate:", Q_NULLPTR));
        label_3->setText(QApplication::translate("VideoSettingsUi", "Quality:", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("VideoSettingsUi", "Video", Q_NULLPTR));
        label_8->setText(QApplication::translate("VideoSettingsUi", "Resolution:", Q_NULLPTR));
        label_9->setText(QApplication::translate("VideoSettingsUi", "Framerate:", Q_NULLPTR));
        label_6->setText(QApplication::translate("VideoSettingsUi", "Video Codec:", Q_NULLPTR));
        label_7->setText(QApplication::translate("VideoSettingsUi", "Quality:", Q_NULLPTR));
        label_4->setText(QApplication::translate("VideoSettingsUi", "Container Format:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VideoSettingsUi: public Ui_VideoSettingsUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOSETTINGS_H
