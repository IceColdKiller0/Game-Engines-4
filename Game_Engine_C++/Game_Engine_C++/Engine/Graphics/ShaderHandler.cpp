#include "ShaderHandler.h"

using namespace std;

unique_ptr<ShaderHandler> ShaderHandler::shaderInstance = nullptr;
unordered_map<string, GLuint> ShaderHandler::programs = unordered_map<string, GLuint>();

ShaderHandler* ShaderHandler::GetInstance()
{
    if (shaderInstance.get() == nullptr)
    {
        shaderInstance.reset(new ShaderHandler);
    }
    return shaderInstance.get();
}

void ShaderHandler::CreateProgram(const std::string& shaderName_, const std::string& vertexShaderFileName_, const std::string& fragmentShaderFileName_)
{
    string vertexShaderCode = ReadShader(vertexShaderFileName_);
    string fragmentShaderCode = ReadShader(fragmentShaderFileName_);

    if (vertexShaderCode == "" || fragmentShaderCode == "")
    {
        return;
    }

    GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, shaderName_);
    GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, shaderName_);

    if (vertexShader == 0 || fragmentShader == 0)
    {
        return;
    }

    GLint linkResult = 0;
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

    if (!linkResult)
    {
        GLint infoLogLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        vector<char> programLog(infoLogLength);
        glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
        string programString(programLog.begin(), programLog.end());
        Debugger::Error("Failed to link shader " + shaderName_ + ". Error: " + programString,
            "ShaderHandler.cpp", __LINE__);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(program);
        return;
    }

    programs[shaderName_] = program;
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint ShaderHandler::GetShader(const std::string& shaderName_)
{
    if (programs.find(shaderName_) != programs.end())
    {
        return programs[shaderName_];
    }
    return 0;
}

void ShaderHandler::OnDestroy()
{
    if (programs.size() > 0)
    {
        for (auto p : programs)
        {
            glDeleteProgram(p.second);
        }
        programs.clear();
    }
}

ShaderHandler::ShaderHandler()
{
    
}

ShaderHandler::~ShaderHandler()
{
    OnDestroy();
}

std::string ShaderHandler::ReadShader(const std::string& filePath_)
{
    string shaderCode = "";
    ifstream file;

    file.exceptions(ifstream::badbit);
    try 
    {
        file.open(filePath_);
        stringstream tmpStream;
        tmpStream << file.rdbuf();
        file.close();
        shaderCode = tmpStream.str();

    }
    catch (std::ifstream::failure error_)
    {
        Debugger::Error("Could not read the shader: " + filePath_, "ShaderHandle.cpp", __LINE__);
        return "";
    }

    return shaderCode;
}

GLuint ShaderHandler::CreateShader(GLenum shaderType_, const std::string& source_, const std::string& shaderName_)
{
    GLint compileResult = 0;
    GLuint shader = glCreateShader(shaderType_);
    const char* shaderCodePtr = source_.c_str();
    const int shaderCodeSize = source_.size();

    glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

    if (!compileResult)
    {
        GLint infoLogLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        vector<char> shaderLog(infoLogLength);
        glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
        string shaderString(shaderLog.begin(), shaderLog.end());
        Debugger::Error("Error compiling shader " + shaderName_ + ". Error: \n" + shaderString, 
            "ShaderHandler.cpp", __LINE__);

        return 0;
    }

    return shader;
}
