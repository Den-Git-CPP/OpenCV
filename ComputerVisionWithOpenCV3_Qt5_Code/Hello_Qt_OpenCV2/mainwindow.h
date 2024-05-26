#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QCloseEvent>
#include <QMessageBox>
#include <QSettings>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow (QWidget* parent = 0);
    ~MainWindow ();

  protected:
    void closeEvent (QCloseEvent* event);

  private slots:
    void on_inputPushButton_pressed ();

    void on_outputPushButton_pressed ();

  private:
    Ui::MainWindow* ui;

    void loadSettings ();
    void saveSettings ();
};
