#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : OpenGLWidgetBase(parent)
{

}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glViewport(0, 0, this->width(), this->height());
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable (GL_LINE_SMOOTH);
    glHint (GL_LINE_SMOOTH, GL_NICEST);
    glEnable (GL_POLYGON_SMOOTH );
    glHint (GL_POLYGON_SMOOTH , GL_NICEST);


    shaderProgram = loadShaders("model_loading.vs", "model_loading.fs");
    view = View(glm::vec3(0.0f, 0.0f, 20.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));
    handle_obj = select_model = -1;
    move_rotate = 0;
    showAxis = true;

    dirLightDirection = glm::vec3(0.2f, -1.0f, -0.3f);
    dirLightAmbient = glm::vec3(0.05f, 0.05f, 0.05f);
    dirLightDiffuse = glm::vec3(0.4f, 0.4f, 0.4f);
    dirLightSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
    pointLightPos = glm::vec3(6.0f, 6.0f, 6.0f);
    pointLightAmbient = glm::vec3(0.4f, 0.4f, 0.4f);
    pointLightDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    pointLightSpecular = glm::vec3(1.0f, 0.5f, 0.5f);
    pointLightAttenuation = glm::vec3(1.0f, 0.045f, 0.0075f);
    spotLightPos = glm::vec3(0.0f, 6.0f, 0.0f);
    spotLightDirection = glm::vec3(0.0f, -1.0f, 0.0f);
    spotLightAmbient = glm::vec3(0.0f, 0.0f, 0.0f);
    spotLightDiffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    spotLightSpecular = glm::vec3(1.0f, 1.0f, 1.0f);
    spotLightAttenuation = glm::vec3(1.0f, 0.09f, 0.032f);
    spotLightCutoff = 12.5f;
    spotLightOuterCutoff = 25.0f;

    glUniform1i(glGetUniformLocation(shaderProgram, "material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "material.specular"), 1);

    float axisVertex[] = {
        0.0f, 0.0f, 0.0f, 50.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 50.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 50.0f,
        0.0f, 0.0f, 0.0f, -50.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, -50.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -50.0f
    };
    GLuint axisVBO;
    glGenVertexArrays(1, &axisVAO);
    glGenBuffers(1, &axisVBO);
    glBindVertexArray(axisVAO);
    glBindBuffer(GL_ARRAY_BUFFER, axisVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertex), axisVertex, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void MyOpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);
    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(view.zoom), float(this->width())/this->height(), 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
    glm::mat4 m_view = view.getViewMatrix();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &m_view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &glm::mat4()[0][0]);

    if (showAxis)
    {
        glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.ambient"), 0, 0, 0);
        glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.diffuse"), 0, 0, 0);
        glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.specular"), 0, 0, 0);
        glUniform3f(glGetUniformLocation(shaderProgram, "pointLight.ambient"), 0, 0, 0);
        glUniform3f(glGetUniformLocation(shaderProgram, "pointLight.diffuse"), 0, 0, 0);
        glUniform3f(glGetUniformLocation(shaderProgram, "pointLight.specular"), 0, 0, 0);
        glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.ambient"), 0, 0, 0);
        glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.diffuse"), 0, 0, 0);
        glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.specular"), 0, 0, 0);
        glBindVertexArray(axisVAO);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x0001);
        glUniform3f(glGetUniformLocation(shaderProgram, "fragcolor"), 1.0f, 0.0f, 0.0f);
        glDrawArrays(GL_LINES, 0, 2);
        glUniform3f(glGetUniformLocation(shaderProgram, "fragcolor"), 0.0f, 1.0f, 0.0f);
        glDrawArrays(GL_LINES, 2, 2);
        glUniform3f(glGetUniformLocation(shaderProgram, "fragcolor"), 0.0f, 0.8f, 1.0f);
        glDrawArrays(GL_LINES, 4, 2);
        glUniform3f(glGetUniformLocation(shaderProgram, "fragcolor"), 0.4f, 0.4f, 0.4f);
        glDrawArrays(GL_LINES, 6, 6);
        glDisable(GL_LINE_STIPPLE);
    }

    glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, &view.eye[0]);
    glUniform1f(glGetUniformLocation(shaderProgram, "material.shininess"), 64.0f);

    glUniform3fv(glGetUniformLocation(shaderProgram, "dirLight.direction"), 1, &dirLightDirection[0]);
    glUniform3fv(glGetUniformLocation(shaderProgram, "dirLight.ambient"), 1, &dirLightAmbient[0]);
    glUniform3fv(glGetUniformLocation(shaderProgram, "dirLight.diffuse"), 1, &dirLightDiffuse[0]);
    glUniform3fv(glGetUniformLocation(shaderProgram, "dirLight.specular"), 1, &dirLightSpecular[0]);

    glUniform3fv(glGetUniformLocation(shaderProgram, "pointLight.position"), 1, &pointLightPos[0]);
    glUniform3fv(glGetUniformLocation(shaderProgram, "pointLight.ambient"), 1, &pointLightAmbient[0]);
    glUniform3fv(glGetUniformLocation(shaderProgram, "pointLight.diffuse"), 1, &pointLightDiffuse[0]);
    glUniform3fv(glGetUniformLocation(shaderProgram, "pointLight.specular"), 1, &pointLightSpecular[0]);
    glUniform3fv(glGetUniformLocation(shaderProgram, "pointLight.attenuation"), 1, &pointLightAttenuation[0]);

    glUniform3fv(glGetUniformLocation(shaderProgram, "spotLight.position"), 1, &spotLightPos[0]);
    glUniform3fv(glGetUniformLocation(shaderProgram, "spotLight.direction"), 1, &spotLightDirection[0]);
    glUniform3fv(glGetUniformLocation(shaderProgram, "spotLight.ambient"), 1, &spotLightAmbient[0]);
    glUniform3fv(glGetUniformLocation(shaderProgram, "spotLight.diffuse"), 1, &spotLightDiffuse[0]);
    glUniform3fv(glGetUniformLocation(shaderProgram, "spotLight.specular"), 1, &spotLightSpecular[0]);
    glUniform3fv(glGetUniformLocation(shaderProgram, "spotLight.attenuation"), 1, &spotLightAttenuation[0]);
    glUniform1f(glGetUniformLocation(shaderProgram, "spotLight.cutOff"), glm::cos(glm::radians(spotLightCutoff)));
    glUniform1f(glGetUniformLocation(shaderProgram, "spotLight.outerCutOff"), glm::cos(glm::radians(spotLightOuterCutoff)));

    for (int i = 0; i < models.size(); i++)
    {
        if (models[i].model.outer == nullptr)
        {
            models[i].model = Model(this, models[i].model.path);
            float maxcoord = 0.00001;
            for (auto mesh : models[i].model.meshes)
                for (auto vertex : mesh.vertices)
                {
                    if (vertex.Position.x > maxcoord) maxcoord = vertex.Position.x;
                    if (vertex.Position.y > maxcoord) maxcoord = vertex.Position.y;
                    if (vertex.Position.z > maxcoord) maxcoord = vertex.Position.z;
                }
            float scaleratio = 4.0 / maxcoord;
            models[i].m_model = glm::scale(models[i].m_model, glm::vec3(scaleratio, scaleratio, scaleratio));
        }

        // render the loaded model
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1,
                           GL_FALSE, &(models[i].m_model * models[i].m_initmodel)[0][0]);

        glm::mat3 normalModel = glm::mat3(glm::transpose(glm::inverse(models[i].m_model)));
        glUniformMatrix3fv(glGetUniformLocation(shaderProgram, "normalModel"), 1, GL_FALSE, &normalModel[0][0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, "fragcolor"), 1, &models[i].color[0]);

        glPolygonMode(GL_FRONT_AND_BACK, models[i].draw_mode);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, models[i].texture);

        models[i].model.draw(shaderProgram);
    }
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *e)
{
    preCusorPos = e->pos();
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    float xoffset = e->x() - preCusorPos.x();
    float yoffset = e->y() - preCusorPos.y();

    if (move_rotate == 0)
    {
        if (e->buttons() & Qt::LeftButton)
        {
            if (handle_obj == -1)
            {
                view.moveOnLeftRight(xoffset);
                view.moveOnUpDown(yoffset);
            } else {
                models[handle_obj].m_model = glm::translate(models[handle_obj].m_model, glm::vec3(xoffset, -yoffset, 0));
            }
        } else if (e->buttons() & Qt::RightButton) {
            if (handle_obj == -1)
            {
                view.moveOnLeftRight(xoffset);
                view.moveOnFrontBack(yoffset);
            } else {
                models[handle_obj].m_model = glm::translate(models[handle_obj].m_model, glm::vec3(xoffset, 0, -yoffset));
            }
        }
    } else if (move_rotate == 1) {
        if (e->buttons() & Qt::LeftButton)
        {
            if (handle_obj == -1)
            {
                view.rotateAroundUp(xoffset);
                view.rotateAroundRight(yoffset);
            } else {
                models[handle_obj].m_model = glm::rotate(models[handle_obj].m_model, glm::radians(xoffset), glm::vec3(0, 1, 0));
                models[handle_obj].m_model = glm::rotate(models[handle_obj].m_model, glm::radians(yoffset), glm::vec3(1, 0, 0));
            }
        } else if (e->buttons() & Qt::RightButton) {
            if (handle_obj == -1)
            {
                view.rotateAroundEye(xoffset);
                view.rotateAroundRight(yoffset);
            } else {
                models[handle_obj].m_model = glm::rotate(models[handle_obj].m_model, glm::radians(xoffset), glm::vec3(0, 0, 1));
                models[handle_obj].m_model = glm::rotate(models[handle_obj].m_model, glm::radians(yoffset), glm::vec3(1, 0, 0));
            }
        }
    }
    preCusorPos = e->pos();
    update();
}

void MyOpenGLWidget::wheelEvent(QWheelEvent *e)
{
    float yoffset = e->angleDelta().y();
    if (yoffset > 110 || yoffset < -110)
        yoffset /= 60;

    if (handle_obj == -1)
    {
        view.changeZoom(yoffset);
    } else {
        yoffset = atan(yoffset) / (2*3.1415926535898) + 1;
        models[handle_obj].m_model = glm::scale(models[handle_obj].m_model, glm::vec3(yoffset, yoffset, yoffset));
    }

    update();
}

void MyOpenGLWidget::loadModelBtnClicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("选择模型"), ".", tr("模型文件(*.obj)"));
    if (path.length() == 0)
        QMessageBox::information(NULL, tr("文件"), tr("你没有选择任何文件"));
    else
    {
        string modelPath = path.toLocal8Bit();
        models.push_back(LoadedModel(modelPath));
        update();
        string modelName = modelPath.substr(modelPath.find_last_of('/')+1);
        emit modelLoaded(modelName);
    }
}

void MyOpenGLWidget::modelDeleted(int index)
{
    models[index].model.clear(); // 可能会内存泄露, 经测试VAO缓冲泄漏，但是VBOEBO缓冲却不会泄漏
    glDeleteTextures(1, &models[index].texture); // 纹理不知是否有问题
    models.erase(models.begin()+index);
    update();
}

void MyOpenGLWidget::modelColorChanged(QColor c)
{
    if (select_model == -1) return;
    models[select_model].color = glm::vec3(c.redF(), c.greenF(), c.blueF());
}

void MyOpenGLWidget::loadTextureBtnClicked()
{
    //glDeleteTextures(1, &texture);
    QString path = QFileDialog::getOpenFileName(this, tr("选择纹理"), ".", tr("图像文件(*.bmp *.jpg *.png)"));
    if (path.length() == 0)
        QMessageBox::information(NULL, tr("纹理"), tr("你没有选择任何文件"));
    else
    {
        GLuint preTexture = models[select_model].texture;
        models[select_model].texture = TextureFromFile(path.toLocal8Bit());
        glDeleteTextures(1, &preTexture);  //可能会内存泄漏
        update();
    }
}

void MyOpenGLWidget::faceBtnClicked()
{
    if (select_model == -1) return;
    models[select_model].draw_mode = GL_FILL;
    update();
}
void MyOpenGLWidget::lineBtnClicked()
{
    if (select_model == -1) return;
    models[select_model].draw_mode = GL_LINE;
    update();
}
void MyOpenGLWidget::pointBtnClicked()
{
    if (select_model == -1) return;
    models[select_model].draw_mode = GL_POINT;
    update();
}
void MyOpenGLWidget::axisBtnClicked(bool checked) { showAxis = checked; update(); }

void MyOpenGLWidget::moveBtnClicked() { move_rotate = 0; }
void MyOpenGLWidget::rotateBtnClicked() { move_rotate = 1; }
void MyOpenGLWidget::handleModelBtnClicked() { handle_obj = select_model; }
void MyOpenGLWidget::handleViewBtnClicked() { handle_obj = -1; }

void MyOpenGLWidget::changeSelectedModel(int index)
{
    handle_obj = select_model = index;
    if (select_model == -1) return;
    glm::vec3 modelColor = 255.0f * models[select_model].color;
    emit changeModelColor(QColor(modelColor.r, modelColor.g, modelColor.b));
    if (models[select_model].draw_mode == GL_FILL)
        emit changeDrawMode(0);
    else if(models[select_model].draw_mode == GL_LINE)
        emit changeDrawMode(1);
    else emit changeDrawMode(2);
}
void MyOpenGLWidget::changeLocalMove(float x, float y, float z)
{
    if (select_model == -1) return;
    models[select_model].m_initmodel = glm::translate(glm::mat4(), glm::vec3(x,y,z));
    update();
}

void MyOpenGLWidget::dirLightDirChanged(float x, float y, float z)
{ dirLightDirection = glm::vec3(x, y, z); update(); }

void MyOpenGLWidget::dirAmbientChanged(QColor c)
{ dirLightAmbient = glm::vec3(c.redF(), c.greenF(), c.blueF()); }

void MyOpenGLWidget::dirDiffuseChanged(QColor c)
{ dirLightDiffuse = glm::vec3(c.redF(), c.greenF(), c.blueF()); }

void MyOpenGLWidget::dirSpecularChanged(QColor c)
{ dirLightSpecular = glm::vec3(c.redF(), c.greenF(), c.blueF()); }

void MyOpenGLWidget::pointLightPosChanged(float x, float y, float z)
{ pointLightPos = glm::vec3(x, y, z); update(); }

void MyOpenGLWidget::pointAmbientChanged(QColor c)
{ pointLightAmbient = glm::vec3(c.redF(), c.greenF(), c.blueF()); }

void MyOpenGLWidget::pointDiffuseChanged(QColor c)
{ pointLightDiffuse = glm::vec3(c.redF(), c.greenF(), c.blueF()); }

void MyOpenGLWidget::pointSpecularChanged(QColor c)
{ pointLightSpecular = glm::vec3(c.redF(), c.greenF(), c.blueF()); }

void MyOpenGLWidget::pointLightAttenuationChanged(float constant, float linear, float quadratic)
{ pointLightAttenuation = glm::vec3(constant, linear, quadratic); }

void MyOpenGLWidget::spotLightPosChanged(float x, float y, float z)
{ spotLightPos = glm::vec3(x, y, z); update(); }

void MyOpenGLWidget::spotLightDirChanged(float x, float y, float z)
{ spotLightDirection = glm::vec3(x, y, z); update(); }

void MyOpenGLWidget::spotLightCutOffChanged(float cutoff, float outerCutoff)
{
    spotLightCutoff = cutoff;
    spotLightOuterCutoff = outerCutoff;
}

void MyOpenGLWidget::spotAmbientChanged(QColor c)
{ spotLightAmbient = glm::vec3(c.redF(), c.greenF(), c.blueF()); }

void MyOpenGLWidget::spotDiffuseChanged(QColor c)
{ spotLightDiffuse = glm::vec3(c.redF(), c.greenF(), c.blueF()); }

void MyOpenGLWidget::spotSpecularChanged(QColor c)
{ spotLightSpecular = glm::vec3(c.redF(), c.greenF(), c.blueF()); }

void MyOpenGLWidget::spotLightAttenuationChanged(float constant, float linear, float quadratic)
{ spotLightAttenuation = glm::vec3(constant, linear, quadratic); }
