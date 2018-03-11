#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->modelList->setStyleSheet("QListWidget{background-color:transparent;border:transparent;}QScrollBar{width:0;height:0}");

    connect(ui->loadModelBtn, SIGNAL(clicked(bool)), ui->myGLWidget, SLOT(loadModelBtnClicked()), Qt::AutoConnection);
    connect(ui->loadTextureBtn, SIGNAL(clicked(bool)), ui->myGLWidget, SLOT(loadTextureBtnClicked()), Qt::AutoConnection);
    connect(ui->faceBtn, SIGNAL(clicked(bool)), ui->myGLWidget, SLOT(faceBtnClicked()), Qt::AutoConnection);
    connect(ui->lineBtn, SIGNAL(clicked(bool)), ui->myGLWidget, SLOT(lineBtnClicked()), Qt::AutoConnection);
    connect(ui->axisBtn, SIGNAL(clicked(bool)), ui->myGLWidget, SLOT(axisBtnClicked(bool)), Qt::AutoConnection);
    connect(ui->pointBtn, SIGNAL(clicked(bool)), ui->myGLWidget, SLOT(pointBtnClicked()), Qt::AutoConnection);
    connect(ui->moveBtn, SIGNAL(clicked(bool)), ui->myGLWidget, SLOT(moveBtnClicked()), Qt::AutoConnection);
    connect(ui->rotateBtn, SIGNAL(clicked(bool)), ui->myGLWidget, SLOT(rotateBtnClicked()), Qt::AutoConnection);
    connect(ui->handleModelBtn, SIGNAL(clicked(bool)), ui->myGLWidget, SLOT(handleModelBtnClicked()), Qt::AutoConnection);
    connect(ui->handleViewBtn, SIGNAL(clicked(bool)), ui->myGLWidget, SLOT(handleViewBtnClicked()), Qt::AutoConnection);

    connect(ui->myGLWidget, SIGNAL(modelLoaded(string)), this, SLOT(modelLoaded(string)), Qt::AutoConnection);
    connect(ui->myGLWidget, SIGNAL(changeDrawMode(int)), this, SLOT(drawModeChanged(int)), Qt::AutoConnection);
    connect(this, SIGNAL(modelDeleted(int)), ui->myGLWidget, SLOT(modelDeleted(int)), Qt::AutoConnection);

    connect(ui->modelList, SIGNAL(currentRowChanged(int)), ui->myGLWidget, SLOT(changeSelectedModel(int)), Qt::AutoConnection);
    connect(ui->modelList, SIGNAL(currentRowChanged(int)), this, SLOT(selectedModelChanged()), Qt::AutoConnection);

    connect(this, SIGNAL(modelColorChanged(QColor)), ui->myGLWidget, SLOT(modelColorChanged(QColor)), Qt::AutoConnection);
    connect(ui->myGLWidget, SIGNAL(changeModelColor(QColor)), this, SLOT(setModelColor(QColor)), Qt::AutoConnection);

    connect(this, SIGNAL(localMoveChanged(float,float,float)), ui->myGLWidget, SLOT(changeLocalMove(float,float,float)), Qt::AutoConnection);

    connect(ui->dirX, SIGNAL(editingFinished()), this, SLOT(dirLightDirConfirmed()), Qt::AutoConnection);
    connect(ui->dirY, SIGNAL(editingFinished()), this, SLOT(dirLightDirConfirmed()), Qt::AutoConnection);
    connect(ui->dirZ, SIGNAL(editingFinished()), this, SLOT(dirLightDirConfirmed()), Qt::AutoConnection);
    connect(this, SIGNAL(dirLightDirChanged(float,float,float)), ui->myGLWidget, SLOT(dirLightDirChanged(float,float,float)), Qt::AutoConnection);

    connect(ui->pointX, SIGNAL(editingFinished()), this, SLOT(pointLightPosConfirmed()), Qt::AutoConnection);
    connect(ui->pointY, SIGNAL(editingFinished()), this, SLOT(pointLightPosConfirmed()), Qt::AutoConnection);
    connect(ui->pointZ, SIGNAL(editingFinished()), this, SLOT(pointLightPosConfirmed()), Qt::AutoConnection);
    connect(this, SIGNAL(pointLightPosChanged(float,float,float)), ui->myGLWidget, SLOT(pointLightPosChanged(float,float,float)), Qt::AutoConnection);

    connect(ui->pointConstant, SIGNAL(editingFinished()), this, SLOT(pointLightAttenuationConfirmed()), Qt::AutoConnection);
    connect(ui->pointLinear, SIGNAL(editingFinished()), this, SLOT(pointLightAttenuationConfirmed()), Qt::AutoConnection);
    connect(ui->pointQuadratic, SIGNAL(editingFinished()), this, SLOT(pointLightAttenuationConfirmed()), Qt::AutoConnection);
    connect(this, SIGNAL(pointLightAttenuationChanged(float,float,float)), ui->myGLWidget, SLOT(pointLightAttenuationChanged(float,float,float)), Qt::AutoConnection);

    connect(ui->spotX, SIGNAL(editingFinished()), this, SLOT(spotLightPosConfirmed()), Qt::AutoConnection);
    connect(ui->spotY, SIGNAL(editingFinished()), this, SLOT(spotLightPosConfirmed()), Qt::AutoConnection);
    connect(ui->spotZ, SIGNAL(editingFinished()), this, SLOT(spotLightPosConfirmed()), Qt::AutoConnection);
    connect(this, SIGNAL(spotLightPosChanged(float,float,float)), ui->myGLWidget, SLOT(spotLightPosChanged(float,float,float)), Qt::AutoConnection);

    connect(ui->spotDirX, SIGNAL(editingFinished()), this, SLOT(spotLightDirConfirmed()), Qt::AutoConnection);
    connect(ui->spotDirY, SIGNAL(editingFinished()), this, SLOT(spotLightDirConfirmed()), Qt::AutoConnection);
    connect(ui->spotDirZ, SIGNAL(editingFinished()), this, SLOT(spotLightDirConfirmed()), Qt::AutoConnection);
    connect(this, SIGNAL(spotLightDirChanged(float,float,float)), ui->myGLWidget, SLOT(spotLightDirChanged(float,float,float)), Qt::AutoConnection);

    connect(ui->spotCutoff, SIGNAL(editingFinished()), this, SLOT(spotLightCutOffConfirmed()), Qt::AutoConnection);
    connect(ui->spotOuterCutoff, SIGNAL(editingFinished()), this, SLOT(spotLightCutOffConfirmed()), Qt::AutoConnection);
    connect(this, SIGNAL(spotLightCutOffChanged(float,float)), ui->myGLWidget, SLOT(spotLightCutOffChanged(float,float)), Qt::AutoConnection);

    connect(ui->spotConstant, SIGNAL(editingFinished()), this, SLOT(spotLightAttenuationConfirmed()), Qt::AutoConnection);
    connect(ui->spotLinear, SIGNAL(editingFinished()), this, SLOT(spotLightAttenuationConfirmed()), Qt::AutoConnection);
    connect(ui->spotQuadratic, SIGNAL(editingFinished()), this, SLOT(spotLightAttenuationConfirmed()), Qt::AutoConnection);
    connect(this, SIGNAL(spotLightAttenuationChanged(float,float,float)), ui->myGLWidget, SLOT(spotLightAttenuationChanged(float,float,float)), Qt::AutoConnection);

    connect(ui->dirAmbientBtn, SIGNAL(clicked(bool)), this, SLOT(lightColorBtnClicked()), Qt::AutoConnection);
    connect(this, SIGNAL(dirAmbientChanged(QColor)), ui->myGLWidget, SLOT(dirAmbientChanged(QColor)), Qt::AutoConnection);
    connect(ui->dirDiffuseBtn, SIGNAL(clicked(bool)), this, SLOT(lightColorBtnClicked()), Qt::AutoConnection);
    connect(this, SIGNAL(dirDiffuseChanged(QColor)), ui->myGLWidget, SLOT(dirDiffuseChanged(QColor)), Qt::AutoConnection);
    connect(ui->dirSpecularBtn, SIGNAL(clicked(bool)), this, SLOT(lightColorBtnClicked()), Qt::AutoConnection);
    connect(this, SIGNAL(dirSpecularChanged(QColor)), ui->myGLWidget, SLOT(dirSpecularChanged(QColor)), Qt::AutoConnection);
    connect(ui->pointAmbientBtn, SIGNAL(clicked(bool)), this, SLOT(lightColorBtnClicked()), Qt::AutoConnection);
    connect(this, SIGNAL(pointAmbientChanged(QColor)), ui->myGLWidget, SLOT(pointAmbientChanged(QColor)), Qt::AutoConnection);
    connect(ui->pointDiffuseBtn, SIGNAL(clicked(bool)), this, SLOT(lightColorBtnClicked()), Qt::AutoConnection);
    connect(this, SIGNAL(pointDiffuseChanged(QColor)), ui->myGLWidget, SLOT(pointDiffuseChanged(QColor)), Qt::AutoConnection);
    connect(ui->pointSpecularBtn, SIGNAL(clicked(bool)), this, SLOT(lightColorBtnClicked()), Qt::AutoConnection);
    connect(this, SIGNAL(pointSpecularChanged(QColor)), ui->myGLWidget, SLOT(pointSpecularChanged(QColor)), Qt::AutoConnection);
    connect(ui->spotAmbientBtn, SIGNAL(clicked(bool)), this, SLOT(lightColorBtnClicked()), Qt::AutoConnection);
    connect(this, SIGNAL(spotAmbientChanged(QColor)), ui->myGLWidget, SLOT(spotAmbientChanged(QColor)), Qt::AutoConnection);
    connect(ui->spotDiffuseBtn, SIGNAL(clicked(bool)), this, SLOT(lightColorBtnClicked()), Qt::AutoConnection);
    connect(this, SIGNAL(spotDiffuseChanged(QColor)), ui->myGLWidget, SLOT(spotDiffuseChanged(QColor)), Qt::AutoConnection);
    connect(ui->spotSpecularBtn, SIGNAL(clicked(bool)), this, SLOT(lightColorBtnClicked()), Qt::AutoConnection);
    connect(this, SIGNAL(spotSpecularChanged(QColor)), ui->myGLWidget, SLOT(spotSpecularChanged(QColor)), Qt::AutoConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::modelLoaded(string modelName)
{
    ui->modelList->addItem(QString::fromStdString(modelName));
    ui->modelList->setCurrentRow(ui->modelList->count() - 1);
}

void MainWindow::drawModeChanged(int index)
{
    if (index == 0)
        ui->faceBtn->setChecked(true);
    else if (index == 1)
        ui->lineBtn->setChecked(true);
    else ui->pointBtn->setChecked(true);
}

void MainWindow::on_modelList_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem* curItem = ui->modelList->itemAt(pos);
    if( curItem == NULL ) return;
    QMenu *rightMenu = new QMenu(this);
    QAction *deleteModel = new QAction(tr("删除"), this);
    QAction *clearModel = new QAction(tr("清空"), this);
    rightMenu->addAction(deleteModel);
    rightMenu->addAction(clearModel);
    connect(deleteModel, SIGNAL(triggered(bool)), this, SLOT(deleteModelSlot()));
    connect(clearModel, SIGNAL(triggered(bool)), this, SLOT(clearModelSlot()));
    rightMenu->exec(QCursor::pos());
    delete rightMenu;
    delete deleteModel;
    delete clearModel;
}

void MainWindow::deleteModelSlot()
{
    int question = QMessageBox::warning(NULL, "注意",
        tr("确定要删除这个模型吗?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (question != QMessageBox::Yes) return ;

    QListWidgetItem *item = ui->modelList->currentItem();
    if (item == NULL) return ;

    int index = ui->modelList->row(item);
    ui->modelList->takeItem(index);
    delete item;
    emit modelDeleted(index);
}

void MainWindow::clearModelSlot()
{
    int question = QMessageBox::warning(NULL, "注意",
        tr("确定要清空所有模型吗?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (question != QMessageBox::Yes) return ;

    for (int i = ui->modelList->count()-1; i > -1; i--)
        emit modelDeleted(i);
    ui->modelList->clear();
}

void MainWindow::on_modelList_itemClicked(QListWidgetItem *item)
{ ui->handleModelBtn->click(); }

void MainWindow::selectedModelChanged()
{
    //if (ui->handleModelBtn->isChecked())
        ui->handleModelBtn->setChecked(true);
}

void MainWindow::setModelColor(QColor c)
{
    ui->modelColorBtn->setStyleSheet(QString("background-color:rgb(%1,%2,%3);").arg(c.red()).arg(c.green()).arg(c.blue()));
}

void MainWindow::on_handleModelBtn_clicked(bool checked)
{
    if (ui->modelList->currentRow() == -1)
        ui->handleViewBtn->click();
}

void MainWindow::on_localMoveConfirm_clicked()
{
    bool okx, oky, okz;
    okx = oky = okz = false;
    float x = ui->localXtoMove->text().toFloat(&okx);
    float y = ui->localYtoMove->text().toFloat(&oky);
    float z = ui->localZtoMove->text().toFloat(&okz);
    if (!okx || !oky || !okz)
    {
        QMessageBox::critical(NULL, "错误", tr("输入不全是浮点数"));
    }
    else emit localMoveChanged(x, y, z);
}

void MainWindow::dirLightDirConfirmed()
{
    bool okx, oky, okz;
    okx = oky = okz = false;
    float dirx = ui->dirX->text().toFloat(&okx);
    float diry = ui->dirY->text().toFloat(&oky);
    float dirz = ui->dirZ->text().toFloat(&okz);
    if (!okx || !oky || !okz)
    {
        QMessageBox::critical(NULL, "错误", tr("输入不全是浮点数"));
    }
    else emit dirLightDirChanged(dirx, diry, dirz);
}

void MainWindow::pointLightPosConfirmed()
{
    bool okx, oky, okz;
    okx = oky = okz = false;
    float pointx = ui->pointX->text().toFloat(&okx);
    float pointy = ui->pointY->text().toFloat(&oky);
    float pointz = ui->pointZ->text().toFloat(&okz);
    if (!okx || !oky || !okz)
    {
        QMessageBox::critical(NULL, "错误", tr("输入不全是浮点数"));
    }
    else emit pointLightPosChanged(pointx, pointy, pointz);
}

void MainWindow::pointLightAttenuationConfirmed()
{
    bool okc, okl, okq;
    okc = okl = okq = false;
    float constant = ui->pointConstant->text().toFloat(&okc);
    float linear = ui->pointLinear->text().toFloat(&okl);
    float quadratic = ui->pointQuadratic->text().toFloat(&okq);
    if (!okc || !okl || !okq)
    {
        QMessageBox::critical(NULL, "错误", tr("输入不全是浮点数"));
    }
    else emit pointLightAttenuationChanged(constant, linear, quadratic);
}

void MainWindow::spotLightPosConfirmed()
{
    bool okx, oky, okz;
    okx = oky = okz = false;
    float spotx = ui->spotX->text().toFloat(&okx);
    float spoty = ui->spotY->text().toFloat(&oky);
    float spotz = ui->spotZ->text().toFloat(&okz);
    if (!okx || !oky || !okz)
    {
        QMessageBox::critical(NULL, "错误", tr("输入不全是浮点数"));
    }
    else emit spotLightPosChanged(spotx, spoty, spotz);
}

void MainWindow::spotLightDirConfirmed()
{
    bool okx, oky, okz;
    okx = oky = okz = false;
    float x = ui->spotDirX->text().toFloat(&okx);
    float y = ui->spotDirY->text().toFloat(&oky);
    float z = ui->spotDirZ->text().toFloat(&okz);
    if (!okx || !oky || !okz)
    {
        QMessageBox::critical(NULL, "错误", tr("输入不全是浮点数"));
    }
    else emit spotLightDirChanged(x, y, z);
}

void MainWindow::spotLightCutOffConfirmed()
{
    bool okc, oko;
    okc = oko = false;
    float cutoff = ui->spotCutoff->text().toFloat(&okc);
    float outerCutoff = ui->spotOuterCutoff->text().toFloat(&oko);
    if (!okc || !oko)
    {
        QMessageBox::critical(NULL, "错误", tr("输入不全是浮点数"));
    }
    else emit spotLightCutOffChanged(cutoff, outerCutoff);
}

void MainWindow::spotLightAttenuationConfirmed()
{
    bool okc, okl, okq;
    okc = okl = okq = false;
    float constant = ui->spotConstant->text().toFloat(&okc);
    float linear = ui->spotLinear->text().toFloat(&okl);
    float quadratic = ui->spotQuadratic->text().toFloat(&okq);
    if (!okc || !okl || !okq)
    {
        QMessageBox::critical(NULL, "错误", tr("输入不全是浮点数"));
    }
    else emit spotLightAttenuationChanged(constant, linear, quadratic);
}

void MainWindow::lightColorBtnClicked()
{
    QPushButton* btn = dynamic_cast<QPushButton*>(sender());
    QColor color = QColorDialog::getColor();
    if (color == QColor::Invalid)
    {
        QMessageBox::information(NULL, "提示", tr("你没有选择任何颜色"));
        return;
    }
    btn->setStyleSheet(QString("background-color:rgb(%1,%2,%3);").arg(color.red()).arg(color.green()).arg(color.blue()));
    if (btn == ui->dirAmbientBtn)
        emit dirAmbientChanged(color);
    else if (btn == ui->dirDiffuseBtn)
        emit dirDiffuseChanged(color);
    else if (btn == ui->dirSpecularBtn)
        emit dirSpecularChanged(color);
    else if (btn == ui->pointAmbientBtn)
        emit pointAmbientChanged(color);
    else if (btn == ui->pointDiffuseBtn)
        emit pointDiffuseChanged(color);
    else if (btn == ui->pointSpecularBtn)
        emit pointSpecularChanged(color);
    else if (btn == ui->spotAmbientBtn)
        emit spotAmbientChanged(color);
    else if (btn == ui->spotDiffuseBtn)
        emit spotDiffuseChanged(color);
    else if (btn == ui->spotSpecularBtn)
        emit spotSpecularChanged(color);
}

void MainWindow::on_modelColorBtn_clicked(bool checked)
{
    QColor color = QColorDialog::getColor();
    if (color == QColor::Invalid)
    {
        QMessageBox::information(NULL, "提示", tr("你没有选择任何颜色"));
        return;
    }
    setModelColor(color);
    emit modelColorChanged(color);
}
