#include "inc/Shader.h"
#include "inc/camera.h"
#include "inc/Transform.h"
#include <string>
using namespace std;

unsigned int Shader::program;

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
    string vertexCode;
    string fragmentCode;

    ifstream vShaderFile(vertexPath, ios::in);

    ifstream fShaderFile(fragmentPath, ios::in);

    stringstream vShaderStream, fShaderStream;


    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();


    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex_shader, fragment_shader;


    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vShaderCode, NULL);
    glCompileShader(vertex_shader);
    checkCompileErrors(vertex_shader, "VERTEX");

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fShaderCode, NULL);
    glCompileShader(fragment_shader);
    checkCompileErrors(fragment_shader, "FRAGMENT");


    realProgram = glCreateProgram();
    program = realProgram;
    glAttachShader(realProgram, vertex_shader);
    glAttachShader(realProgram, fragment_shader);
    glLinkProgram(realProgram);
    checkCompileErrors(vertex_shader, "PROGRAM");

    GLint index = Shader::get_shader_index("textCoord");
    glBindAttribLocation(realProgram, index, "textCoord");

    GLint indexUV = Shader::get_shader_index("vNorm");
    glBindAttribLocation(realProgram, indexUV, "vNorm");


    m_uniforms[0] = glGetUniformLocation(realProgram, "transform");

};


void Shader::use()
{
    if(program != realProgram)
    {
        program = realProgram;
    }
    glUseProgram(this->realProgram);
}

void Shader::update(Transform transform, Camera camera)
{
    if(program != realProgram)
    {
        program = realProgram;
    }
    //mat4 model = ;
    GLint mvp_location = glGetUniformLocation(realProgram, "MVP");
    mat4 *cameraRes = camera.GetViewProjection();
    mat4 *res = transform.getModel();
    mat4 rr;
    glm_mat4_identity(rr);
    glm_mat4_mul(*cameraRes, *res, rr);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE,  rr[0]);
}

void Shader::setBool(const std::string &name, bool value) const
{
    unsigned int pp = program;
    glUniform1i(glGetUniformLocation(realProgram, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(realProgram, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(realProgram, name.c_str()), value);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (success != GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

