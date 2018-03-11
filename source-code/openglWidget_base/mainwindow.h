#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColor>
#include <QPushButton>
#include <QColorDialog>
#include <QListWidgetItem>
#include <QMainWindow>
#include <string>
using std::string;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void modelDeleted(int index);
    void modelColorChanged(QColor c);
    void localMoveChanged(float x, float y, float z);
    void dirLightDirChanged(float x, float y, float z);
    void dirAmbientChanged(QColor c);
    void dirDiffuseChanged(QColor c);
    void dirSpecularChanged(QColor c);
    void pointLightPosChanged(float x, float y, float z);
    void pointLightAttenuationChanged(float constant, float linear, float quadratic);
    void pointAmbientChanged(QColor c);
    void pointDiffuseChanged(QColor c);
    void pointSpecularChanged(QColor c);
    void spotLightPosChanged(float x, float y, float z);
    void spotLightDirChanged(float x, float y, float z);
    void spotLightCutOffChanged(float cutoff, float outerCutoff);
    void spotLightAttenuationChanged(float constant, float linear, float quadratic);
    void spotAmbientChanged(QColor c);
    void spotDiffuseChanged(QColor c);
    void spotSpecularChanged(QColor c);

private slots:
    void modelLoaded(string modelName);
    void drawModeChanged(int index);
    void setModelColor(QColor c);
    void deleteModelSlot();
    void clearModelSlot();
    void selectedModelChanged();
    void on_modelList_customContextMenuRequested(const QPoint &pos);

    void on_localMoveConfirm_clicked();    
    void dirLightDirConfirmed();
    void pointLightPosConfirmed();
    void pointLightAttenuationConfirmed();
    void spotLightPosConfirmed();
    void spotLightDirConfirmed();
    void spotLightCutOffConfirmed();
    void spotLightAttenuationConfirmed();
    void lightColorBtnClicked();

    void on_modelColorBtn_clicked(bool checked);

    void on_handleModelBtn_clicked(bool checked);

    void on_modelList_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
