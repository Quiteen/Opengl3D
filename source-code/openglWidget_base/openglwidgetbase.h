#ifndef OPENGLWIDGETBASE_H
#define OPENGLWIDGETBASE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Compatibility>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma comment(lib, "assimp.lib")

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using std::vector;
using std::string;
using std::cout;
using std::endl;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};
struct Texture {
    unsigned int id;
    string type;
    aiString path;
};

class OpenGLWidgetBase : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Compatibility
{
    Q_OBJECT
public:
    class Mesh {
    public:
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;
        unsigned int VAO, VBO, EBO;

        Mesh(OpenGLWidgetBase *p, vector<Vertex> vs, vector<GLuint> is, vector<Texture> ts);
        void setupMesh();
        void draw(GLuint shader);
        void clear();
    private:
        OpenGLWidgetBase *outer;
    };
    class Model {
    public:
        // stores all the textures loaded so far,
        // to make sure textures aren't loaded more than once.
        vector<Texture> textures_loaded;
        vector<Mesh> meshes;
        string path;
        bool gammaCorrection;
        OpenGLWidgetBase *outer;

        Model() : outer(nullptr) {}
        Model(const string &path) : outer(nullptr) { this->path = path; }
        Model(OpenGLWidgetBase *p, string const &path, bool gamma = false);

        void loadModel(const string &path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
        void draw(GLuint shader);
        void clear();
    };

private:
    void checkShaderCompileErrors(GLuint shader, std::string type);

public:
    OpenGLWidgetBase(QWidget *parent = 0);


protected:
    void initializeGL() override;
    GLuint loadShaders(const char* vertexPath, const char* fragmentPath,
                       const char* geometryPath = nullptr);    
    GLuint TextureFromFile(const char *path);

signals:

public slots:

};

#endif // OPENGLWIDGETBASE_H
