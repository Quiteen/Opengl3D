#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <string>

#include <QPoint>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>

#include <openglwidgetbase.h>
#include <camera.h>
#define VIEW_STATIC
#include <view.h>

class MyOpenGLWidget : public OpenGLWidgetBase
{
    Q_OBJECT

public:
    MyOpenGLWidget(QWidget *parent = 0);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;

signals:
    void modelLoaded(string modelName);
    void changeModelColor(QColor c);
    void changeDrawMode(int index);

private slots:
    void loadModelBtnClicked();
    void modelDeleted(int index);
    void modelColorChanged(QColor c);
    void loadTextureBtnClicked();
    void faceBtnClicked();
    void lineBtnClicked();
    void axisBtnClicked(bool checked);
    void pointBtnClicked();
    void moveBtnClicked();
    void rotateBtnClicked();
    void handleModelBtnClicked();
    void handleViewBtnClicked();
    void changeSelectedModel(int index);
    void changeLocalMove(float x, float y, float z);
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

public:
    class LoadedModel {
    public:
       GLuint draw_mode, texture;
       glm::mat4 m_initmodel, m_model;
       glm::vec3 color;
       Model model;
       LoadedModel() : draw_mode(GL_FILL) {}
       LoadedModel(const string &path) : draw_mode(GL_FILL), model(path) {}
    };

private:
    QPoint preCusorPos;

    unsigned int shaderProgram, axisVAO;
    vector<LoadedModel> models;

    int handle_obj, select_model, move_rotate;
    bool showAxis;
    View view;
    glm::vec3 dirLightDirection, dirLightAmbient, dirLightDiffuse, dirLightSpecular;
    glm::vec3 pointLightPos, pointLightAmbient, pointLightDiffuse, pointLightSpecular, pointLightAttenuation;
    glm::vec3 spotLightPos, spotLightDirection, spotLightAmbient, spotLightDiffuse, spotLightSpecular, spotLightAttenuation;
    float spotLightCutoff, spotLightOuterCutoff;
};

#endif // MYOPENGLWIDGET_H
