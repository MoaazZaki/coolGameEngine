#include "Store.hpp"

// Include the Dear ImGui implementation headers
#define IMGUI_IMPL_OPENGL_LOADER_GLAD2
#include <imgui_impl/imgui_impl_glfw.h>
#include <imgui_impl/imgui_impl_opengl3.h>
#include <mesh/mesh-utils.hpp>

#if !defined(NDEBUG)
// If NDEBUG (no debug) is not defined, enable OpenGL debug messages
#define ENABLE_OPENGL_DEBUG_MESSAGES
#endif

// This function will be used to log errors thrown by GLFW
void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error: " << error << ": " << description << std::endl;
}

// This function will be used to log OpenGL debug messages
void GLAPIENTRY opengl_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    std::string _source;
    std::string _type;
    std::string _severity;

    // What is the source of the message
    switch (source) {
    case GL_DEBUG_SOURCE_API:
        _source = "API"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        _source = "WINDOW SYSTEM"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        _source = "SHADER COMPILER"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        _source = "THIRD PARTY"; break;
    case GL_DEBUG_SOURCE_APPLICATION:
        _source = "APPLICATION"; break;
    case GL_DEBUG_SOURCE_OTHER: default:
        _source = "UNKNOWN"; break;
    }

    // What is the type of the message (error, warning, etc).
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        _type = "ERROR"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        _type = "DEPRECATED BEHAVIOR"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        _type = "UDEFINED BEHAVIOR"; break;
    case GL_DEBUG_TYPE_PORTABILITY:
        _type = "PORTABILITY"; break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        _type = "PERFORMANCE"; break;
    case GL_DEBUG_TYPE_OTHER:
        _type = "OTHER"; break;
    case GL_DEBUG_TYPE_MARKER:
        _type = "MARKER"; break;
    default:
        _type = "UNKNOWN"; break;
    }

    // How severe is the message
    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        _severity = "HIGH"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        _severity = "MEDIUM"; break;
    case GL_DEBUG_SEVERITY_LOW:
        _severity = "LOW"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        _severity = "NOTIFICATION"; break;
    default:
        _severity = "UNKNOWN"; break;
    }

    std::cout << "OpenGL Debug Message " << id << " (type: " << _type << ") of " << _severity
        << " raised from " << _source << ": " << message << std::endl;
}

void famm::Store::configureOpenGL() {
    // Request that OpenGL is 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Only enable core functionalities (disable features from older OpenGL versions that were removed in 3.3)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Enable forward compatibility with newer OpenGL versions by removing deprecated functionalities
    // This is necessary for some platforms
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //Make window size fixed (User can't resize it)
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    //Set Number of sample used in MSAA (0 = Disabled)
    glfwWindowHint(GLFW_SAMPLES, 0);

    //Enable Double Buffering
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    //Set the bit-depths of the frame buffer
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);

    //Set Bits for Depth Buffer
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    //Set Bits for Stencil Buffer
    glfwWindowHint(GLFW_STENCIL_BITS, 8);

    //Set the refresh rate of the window (GLFW_DONT_CARE = Run as fast as possible)
    glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
}


void famm::Store::startInit()
{
    // Set the function to call when an error occurs.
    glfwSetErrorCallback(glfw_error_callback);

    // Initialize GLFW and exit if it failed
    if (!glfwInit()) {
        std::cerr << "Failed to Initialize GLFW" << std::endl;
        //return 1;
    }

    configureOpenGL();                                      // This function sets OpenGL window hints.

    /////////////
    static bool firstTime = true;
    if (firstTime)
    {
        if (deviceManager->createNewWindow()) //return 1; //creating Window
        firstTime = false;
    }
    ////////////////

    gladLoadGL(glfwGetProcAddress);         // Load the OpenGL functions from the driver

    // Print information about the OpenGL context
    std::cout << "VENDOR          : " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "RENDERER        : " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "VERSION         : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL VERSION    : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

#if defined(ENABLE_OPENGL_DEBUG_MESSAGES)
    // if we have OpenGL debug messages enabled, set the message callback
    glDebugMessageCallback(opengl_callback, nullptr);
    // Then enable debug output
    glEnable(GL_DEBUG_OUTPUT);
    // Then make the output synchronized to the OpenGL commands.
    // This will make sure that OpenGL and the main thread are synchronized such that message callback is called as soon
    // as the command causing it is called. This is useful for debugging but slows down the code execution.
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif

    //setupCallbacks(deviceManager->getWindow());
    deviceManager->attachWindow();

    // Start the ImGui context and set dark style (just my preference :D)
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    //ImFont* font1 = io.Fonts->AddFontFromFileTTF("./assets/Fonts/Roboto-Black.ttf", 22);

    // Initialize ImGui for GLFW and OpenGL
    ImGui_ImplGlfw_InitForOpenGL(deviceManager->getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");


    loadAssets();

}

////////////// JSON UTILS ///////////////////
// JSON Types
enum magSampler { MAG_NEAREST, MAG_LINEAR };
int mapMagSampler(magSampler m)
{
    switch (m)
    {
    case magSampler::MAG_NEAREST:
        return GL_NEAREST;
        break;
    case magSampler::MAG_LINEAR:
        return GL_LINEAR;
        break;

    }
}
enum minSampler { MIN_NEAREST, MIN_LINEAR, MIN_NEAREST_MIPMAP_NEAREST, MIN_LINEAR_MIPMAP_NEAREST, MIN_NEAREST_MIPMAP_LINEAR, MIN_LINEAR_MIPMAP_LINEAR };
int mapMinSampler(minSampler m) {
    switch (m)
    {
    case minSampler::MIN_NEAREST:
        return GL_NEAREST;
        break;
    case minSampler::MIN_LINEAR:
        return GL_LINEAR;
        break;
    case minSampler::MIN_NEAREST_MIPMAP_NEAREST:
        return GL_NEAREST_MIPMAP_NEAREST;
        break;
    case minSampler::MIN_LINEAR_MIPMAP_NEAREST:
        return GL_LINEAR_MIPMAP_NEAREST;
        break;
    case minSampler::MIN_NEAREST_MIPMAP_LINEAR:
        return GL_NEAREST_MIPMAP_LINEAR;
        break;
    case minSampler::MIN_LINEAR_MIPMAP_LINEAR:
        return GL_LINEAR_MIPMAP_LINEAR;
        break;
    }
}
enum wrapSampler { WRAP_CLAMP_TO_EDGE, WRAP_CLAMP_TO_BORDER, WRAP_REPEAT, WRAP_MIRRORED_REPEAT, WRAP_MIRROR_CLAMP_TO_EDGE };
int mapWrapSampler(wrapSampler m)
{
    switch (m)
    {
    case wrapSampler::WRAP_CLAMP_TO_EDGE:
        return GL_CLAMP_TO_EDGE;
        break;
    case wrapSampler::WRAP_CLAMP_TO_BORDER:
        return GL_CLAMP_TO_BORDER;
        break;
    case wrapSampler::WRAP_REPEAT:
        return GL_REPEAT;
        break;
    case wrapSampler::WRAP_MIRRORED_REPEAT:
        return GL_MIRRORED_REPEAT;
        break;
    case wrapSampler::WRAP_MIRROR_CLAMP_TO_EDGE:
        return GL_MIRROR_CLAMP_TO_EDGE;
        break;
    }
}


struct shaderJSON {
    std::string name;
    std::string vertex;
    std::string fragment;
};
struct meshJSON {
    std::string type;
    std::string name;
    std::string path;
};
struct textureData {
    glm::vec2 x;
    glm::vec2 y;
    glm::vec4 z;
    glm::vec4 w;
};
struct textureJSON {
    std::string type;
    std::string name;
    bool colored;
    std::string path;
    textureData data;
};
struct samplerJSON {
    std::string name;
    magSampler mag;
    minSampler min;
    wrapSampler wrap_t;
    wrapSampler wrap_s;
    glm::vec4 border;
    float anisotropy;
};
struct materialproperty {
    std::string name;
    std::string type;
    float scalar;
    glm::vec2 v2;
    glm::vec3 v3;
    glm::vec4 v4;
};
struct textureSampler {
    std::string sampler;
    std::string texture;
};
struct materialJSON
{
    std::string type;
    std::string name;
    std::string shader;
    std::vector<materialproperty> properties;
    std::vector<textureSampler> textureSampler;
};

template<typename T>
std::vector<T> extractJSON(const nlohmann::json& j, std::string parent) {
    return j.at(parent).get<std::vector<T>>();
}

void from_json(const nlohmann::json& j, shaderJSON& s)
{
    j.at("name").get_to(s.name);
    j.at("vertex").get_to(s.vertex);
    j.at("fragment").get_to(s.fragment);
}


void from_json(const nlohmann::json& j, meshJSON& m)
{
    j.at("type").get_to(m.type);
    j.at("name").get_to(m.name);
    m.path = j.value<std::string>("path", "");
}

void from_json(const nlohmann::json& j, textureData& d)
{
    d.x = j.value<glm::vec2>("x", {0.0f,0.0f});
    d.y = j.value<glm::vec2>("y", {0.0f,0.0f});
    d.z = j.value<glm::vec4>("z", {0.0f,0.0f,0.0f,0.0f});
    d.w = j.value<glm::vec4>("w", {0.0f,0.0f,0.0f,0.0f});
}

void from_json(const nlohmann::json& j, textureJSON& t)
{
    j.at("type").get_to(t.type);
    j.at("name").get_to(t.name);
    t.colored = (bool)j.value<int>("colored", 1);
    t.path = j.value<std::string>("path", "");
    
    textureData data = j.value<textureData>("data", textureData());
    t.data.x = data.x;
    t.data.y = data.y;
    t.data.z = data.z;
    t.data.w = data.w;
}

void from_json(const nlohmann::json& j, samplerJSON &s)
{
    j.at("name").get_to(s.name);
    s.mag = (magSampler)j.value<int>("mag", 1);
    s.min = (minSampler)j.value<int>("min", 5);
    s.wrap_s = (wrapSampler)j.value<int>("wrap_s", 2);
    s.wrap_t = (wrapSampler)j.value<int>("wrap_t", 2);
    s.border = j.value<glm::vec4>("border", {1.0f,1.0f ,1.0f ,1.0f });
    s.anisotropy = j.value<float>("anisotropy", 1.0);
}

void from_json(const nlohmann::json& j, materialproperty& p)
{
    p.name = j.value<std::string>("name","");
    p.type = j.value<std::string>("type","");
    p.scalar = j.value<float>("scalar",0.0f);
    p.v2 = j.value<glm::vec2>("scalar", {0.0f,0.0f});
    p.v3 = j.value<glm::vec3>("vec3", {0.0f,0.0f,0.0f });
    p.v4 = j.value<glm::vec4>("vec4", {0.0f,0.0f,0.0f ,0.0f });
}

void from_json(const nlohmann::json& j, textureSampler& ts)
{
    j.at("sampler").get_to(ts.sampler);
    j.at("texture").get_to(ts.texture);
}

void from_json(const nlohmann::json& j, materialJSON& m)
{
    j.at("type").get_to(m.type);
    j.at("name").get_to(m.name);
    j.at("shader").get_to(m.shader);
    m.properties = extractJSON<materialproperty>(j, "properties");
    m.textureSampler = extractJSON<textureSampler>(j, "textureSampler");
}


///////////////////////////////////////////////////
void famm::Store::loadAssets()
{
    std::ifstream file_in("assets/data/resources.json");
    nlohmann::json resources;
    file_in >> resources;
    file_in.close();
    
    std::vector<shaderJSON> desShader;
    desShader = extractJSON<shaderJSON>(resources,"shaders");


    for (auto& [name,vertex,fragment]: desShader)
    {
        tableOfShaderPrograms[name] = new ShaderProgram;
        tableOfShaderPrograms[name]->create();
        tableOfShaderPrograms[name]->attach(vertex, GL_VERTEX_SHADER);
        tableOfShaderPrograms[name]->attach(fragment, GL_FRAGMENT_SHADER);
        tableOfShaderPrograms[name]->link();
    }
//  desShader.clear();

    /// Meshes Creating/Loading
    std::vector<meshJSON> desMesh;
    desMesh = extractJSON<meshJSON>(resources, "meshes");
    for (auto& [type, name, path]: desMesh)
    {
        tableOfMeshes[name] = new Mesh;
        if (type == "utils")
        {
            if(name == "cuboid") famm::mesh_utils::Cuboid(*(tableOfMeshes[name]));
            else if(name == "sphere") famm::mesh_utils::Sphere(*(tableOfMeshes[name]));
            else if(name == "plane") famm::mesh_utils::Plane(*tableOfMeshes[name]);
        }
        else
        {
            famm::mesh_utils::loadOBJ(*tableOfMeshes[name], path.c_str());
        }
    }
    desMesh.clear();

    /// Textures Loading
    std::vector<textureJSON> desTexture;
    desTexture = extractJSON<textureJSON>(resources, "textures");
    for (auto& [type,name,colored,path,data]: desTexture)
    {
        tableOfTextures[name] = new Texture2D;
        tableOfTextures[name]->create();
        if (type == "file")
        {
            tableOfTextures[name]->loadTexture(path.c_str(), true, colored);
        }
        else
        {
            if(type == "checkboard")
                tableOfTextures[name]->loadTexture(data.x, data.y,data.z,data.w);
            else
                tableOfTextures[name]->loadTexture(data.z);
        }
    }
    desTexture.clear();

    /// Sampler creating
    //default sampler
    std::vector<samplerJSON> desSampler;
    desSampler = extractJSON<samplerJSON>(resources, "samplers");
    for (auto& [name,mag,min,wrap_s,wrap_t,border,anisotropy]: desSampler)
    {
        tableOfSampelers[name] = new Sampler(mapMagSampler(mag),mapMinSampler(min),mapWrapSampler(wrap_s),mapWrapSampler(wrap_t),border,anisotropy);
        tableOfSampelers[name]->create();
        tableOfSampelers[name]->setSamplerParameters();
        
    }
    desSampler.clear();

    /// Material Creating
    std::vector<materialJSON> desMaterial;
    desMaterial = extractJSON<materialJSON>(resources, "materials");
    for (auto&[type,name,shader, properties, textureSampler] : desMaterial)
    {
        tableOfMaterials[name] = new Material(getShaderPointer(shader));
        for (auto& [propName, propType, scalar, v2, v3, v4] : properties)
        {
            if (propType == "scalar") tableOfMaterials[name]->addProperty("material."+propName, scalar);
            else if(propType == "vec2") tableOfMaterials[name]->addProperty("material."+propName, v2);
            else if(propType == "vec3") tableOfMaterials[name]->addProperty("material."+propName, v3);
            else if(propType == "vec4") tableOfMaterials[name]->addProperty("material."+propName, v4);
        }
        for (auto& [sampler,texture]: textureSampler)
        {
            tableOfMaterials[name]->addTextureSampler(getTexturePointer(texture),getSamplerPointer(sampler));
        }
    }
    desMaterial.clear();

}

void famm::Store::startCleaning()
{
    for (auto& it : tableOfShaderPrograms)
    {
        it.second->destroy();
        delete it.second;
    }
    for (auto& it : tableOfMeshes)
    {
        it.second->destroy();
        delete it.second;
    }
    for (auto& it : tableOfMaterials)
    {
        it.second->destroy();
        delete it.second;
    }
    for (auto& it : tableOfTextures)
    {
        it.second->destroy();
    }
    for (auto& it : tableOfSampelers)
    {
        it.second->destroy();
    }
    // Shutdown ImGui & destroy the context
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();


   
}