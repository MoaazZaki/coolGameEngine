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

void famm::Store::loadAssets()
{
    /// Shaders Creating & loading
    std::vector<std::pair<std::string, std::string>> namesOfShadersProgram = { std::make_pair("light_transform.vert","light_array.frag"),std::make_pair("transform.vert","texture.frag") };
    char* shaderName[4] = { "lightSupport","textureProgram" };
    for (int i = 0; i < namesOfShadersProgram.size(); i++)
    {
        tableOfShaderPrograms[shaderName[i]] = new ShaderProgram;
        tableOfShaderPrograms[shaderName[i]]->create();
        tableOfShaderPrograms[shaderName[i]]->attach("assets/shaders/" + namesOfShadersProgram[i].first, GL_VERTEX_SHADER);
        tableOfShaderPrograms[shaderName[i]]->attach("assets/shaders/" + namesOfShadersProgram[i].second, GL_FRAGMENT_SHADER);
        tableOfShaderPrograms[shaderName[i]]->link();
    }

    /// Meshes Creating/Loading
    char* MeshName[5] = { "Suzanne","cube","land", "sphere", "EiffelTower"};

    //Wolf Mesh
    tableOfMeshes[MeshName[0]] = new Mesh;
    famm::mesh_utils::loadOBJ(*tableOfMeshes[MeshName[0]], "assets/models/Suzanne/Suzanne.obj");
    

    ////Cube Mesh
    tableOfMeshes[MeshName[1]] = new Mesh;
    famm::mesh_utils::Cuboid(*(tableOfMeshes[MeshName[1]]));

    //Land Mesh
    tableOfMeshes[MeshName[2]] = new Mesh;
    famm::mesh_utils::Plane(*tableOfMeshes[MeshName[2]], { 1, 1 }, false, { 0, 0, 0 }, { 1, 1 }, { 0, 0 }, { 100, 100 });

    ////Sphere Mesh
    tableOfMeshes[MeshName[3]] = new Mesh;
    famm::mesh_utils::Sphere(*(tableOfMeshes[MeshName[3]]));

    //////food Mesh
    //tableOfMeshes[MeshName[4]] = new Mesh;
    //famm::mesh_utils::loadOBJ(*tableOfMeshes[MeshName[4]], "assets/models/Food/Food.obj");

    ////Eiffel Tower Mesh
    tableOfMeshes[MeshName[4]] = new Mesh;
    famm::mesh_utils::loadOBJ(*tableOfMeshes[MeshName[4]], "assets/models/EiffelTower/EiffelTower.obj");


    /// Textures Loading
    //White
    Texture2D* whiteTexture = new Texture2D;
    whiteTexture->create();
    whiteTexture->loadTexture({ 255, 255, 255, 255 });
    tableOfTextures["white"] = whiteTexture;

    //Black
    Texture2D* blackTexture = new Texture2D;
    blackTexture->create();
    blackTexture->loadTexture({ 0, 0, 0, 255 });
    tableOfTextures["black"] = blackTexture;

    //checkerboard_albedo
    Texture2D* cbAlbedoTexture = new Texture2D;
    cbAlbedoTexture->create();
    cbAlbedoTexture->loadTexture({ 256,256 }, { 128,128 }, { 255, 255, 255, 255 }, { 16, 16, 16, 255 });
    tableOfTextures["checkerboard_albedo"] = cbAlbedoTexture;
    //checkerboard_specular
    Texture2D* cbSpeculatTexture = new Texture2D;
    cbSpeculatTexture->create();
    cbSpeculatTexture->loadTexture({ 256,256 }, { 128,128 }, { 0, 0, 0, 255 }, { 255, 255, 255, 255 });
    tableOfTextures["checkerboard_specular"] = cbSpeculatTexture;
    //checkerboard_roughness
    Texture2D* cbRoughnessTexture = new Texture2D;
    cbRoughnessTexture->create();
    cbRoughnessTexture->loadTexture({ 256,256 }, { 128,128 }, { 255, 255, 255, 255 }, { 64, 64, 64, 255 });
    tableOfTextures["checkerboard_roughness"] = cbRoughnessTexture;

    //asphalt_albedo
    Texture2D* asphaltAlbedo = new Texture2D;
    asphaltAlbedo->create();
    asphaltAlbedo->loadTexture("assets/images/common/materials/asphalt/albedo.jpg");
    tableOfTextures["asphalt_albedo"] = asphaltAlbedo;

    //asphalt_specular
    Texture2D* asphaltSpecular = new Texture2D;
    asphaltSpecular->create();
    asphaltSpecular->loadTexture("assets/images/common/materials/asphalt/specular.jpg");
    tableOfTextures["asphalt_specular"] = asphaltSpecular;

    //asphalt_roughness
    Texture2D* asphaltRoughness = new Texture2D;
    asphaltRoughness->create();
    asphaltRoughness->loadTexture("assets/images/common/materials/asphalt/roughness.jpg", true, false); // greyscale
    tableOfTextures["asphalt_roughness"] = asphaltRoughness;

    //asphalt_emissive
    Texture2D* asphaltEmissive = new Texture2D;
    asphaltEmissive->create();
    asphaltEmissive->loadTexture("assets/images/common/materials/asphalt/emissive.jpg");
    tableOfTextures["asphalt_emissive"] = asphaltEmissive;

    //discoball_roughness
    Texture2D* ballRoughness = new Texture2D;
    ballRoughness->create();
    ballRoughness->loadTexture("assets/images/common/materials/discoball/roughness.png", true, false);
    tableOfTextures["ball_roughness"] = ballRoughness;

    //discoball_normal
    Texture2D* ballNormal = new Texture2D;
    ballNormal->create();
    ballNormal->loadTexture("assets/images/common/materials/discoball/normal.png");
    tableOfTextures["ball_normal"] = ballNormal;

    //discoball_emissive
    Texture2D* ballEmissive = new Texture2D;
    ballEmissive->create();
    ballEmissive->loadTexture("assets/images/common/materials/discoball/emissive.png"); // greyscale
    tableOfTextures["discoball_emissive"] = ballEmissive;

    //discoball_metalness
    Texture2D* ballMetalness = new Texture2D;
    ballMetalness->create();
    ballMetalness->loadTexture("assets/images/common/materials/discoball/metalness.png");
    tableOfTextures["discoball_metalness"] = ballMetalness;

    //discoball_color
    Texture2D* ballDisplacement = new Texture2D;
    ballDisplacement->create();
    ballDisplacement->loadTexture("assets/images/common/materials/discoball/displacement.png");
    tableOfTextures["discoball_displacement"] = ballDisplacement;

    //discoball_color
    Texture2D* ballColor = new Texture2D;
    ballColor->create();
    ballColor->loadTexture("assets/images/common/materials/discoball/color.png");
    tableOfTextures["discoball_color"] = ballColor;

    //glass
    Texture2D* glass = new Texture2D;
    glass->create();
    glass->loadTexture("assets/images/common/glass-panels.png");
    tableOfTextures["glass"] = glass;

    //glitter
    Texture2D* glitter = new Texture2D;
    glitter->create();
    glitter->loadTexture("assets/images/common/glitter.jpg");
    tableOfTextures["glitter"] = glitter;

    //sprinkles
    Texture2D* sprinkles = new Texture2D;
    sprinkles->create();
    sprinkles->loadTexture("assets/images/common/sprinkles.jpg");
    tableOfTextures["sprinkles"] = sprinkles;


    /// Sampler creating
    Sampler* mySampler = new Sampler;
    mySampler->create();
    mySampler->setSamplerParameters();
    tableOfSampelers["default"] = mySampler;

    /// Material Creating
    
    // Land
    Material* landMaterial = new Material(getShaderPointer("lightSupport"));

    landMaterial->addProperty("material.albedo_tint", { 1,1,1 });
    landMaterial->addProperty("material.specular_tint", { 1,1,1 });
    landMaterial->addProperty("material.roughness_range", { 0.0,1.0 });
    landMaterial->addProperty("material.emissive_tint", { 1,1,1 });

    landMaterial->addTextureSampler(cbAlbedoTexture, mySampler);
    landMaterial->addTextureSampler(whiteTexture, mySampler);
    landMaterial->addTextureSampler(whiteTexture, mySampler);
    landMaterial->addTextureSampler(cbRoughnessTexture, mySampler);
    landMaterial->addTextureSampler(asphaltSpecular, mySampler);
    tableOfMaterials["land"] = landMaterial;


    // Suzanne
    Material* Suzanne = new Material(getShaderPointer("lightSupport"));

    Suzanne->addProperty("material.albedo_tint", { 1,1,1 });
    Suzanne->addProperty("material.specular_tint", { 1,1,1 });
    Suzanne->addProperty("material.roughness_range", { 0.0,1.0 });
    Suzanne->addProperty("material.emissive_tint", { 1,1,1 });

    Suzanne->addTextureSampler(asphaltAlbedo, mySampler);
    Suzanne->addTextureSampler(asphaltSpecular, mySampler);
    Suzanne->addTextureSampler(whiteTexture, mySampler);
    Suzanne->addTextureSampler(asphaltRoughness, mySampler);
    Suzanne->addTextureSampler(asphaltEmissive, mySampler);
    tableOfMaterials["Suzanne"] = Suzanne;


    // EiffelTower
    Material* EiffelTower = new Material(getShaderPointer("lightSupport"));

    EiffelTower->addProperty("material.albedo_tint", { 1,1,1 });
    EiffelTower->addProperty("material.specular_tint", { 1,1,1 });
    EiffelTower->addProperty("material.roughness_range", { 0.0,1.0 });
    EiffelTower->addProperty("material.emissive_tint", { 1,1,1 });

    EiffelTower->addTextureSampler(whiteTexture, mySampler);
    EiffelTower->addTextureSampler(whiteTexture, mySampler);
    EiffelTower->addTextureSampler(whiteTexture, mySampler);
    EiffelTower->addTextureSampler(whiteTexture, mySampler);
    EiffelTower->addTextureSampler(whiteTexture, mySampler);
    tableOfMaterials["EiffelTower"] = EiffelTower;



    // Sphere
    Material* sphere = new Material(getShaderPointer("textureProgram"));

    sphere->addProperty("material.albedo_tint", {1,1,1});
    sphere->addProperty("material.specular_tint", { 1,1,1 });
    sphere->addProperty("material.roughness_range", { 0.0,1.0});
    sphere->addProperty("material.emissive_tint", { 1,1,1 });

    sphere->addTextureSampler(glass, mySampler);
    tableOfMaterials["Sphere"] = sphere;

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