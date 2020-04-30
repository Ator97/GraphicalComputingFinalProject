// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "stb_image.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );

// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
float rot = 180.0f;
float rot2 = 180.0f;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Proyecto Final", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
	printf("%f", glfwGetTime());

    // GLFW Options
    glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Setup and compile our shaders
	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
    Shader shader( "Shaders/modelLoading.vs", "Shaders/modelLoading.frag" );
	Shader shader2("Shaders/modelLoading.vs", "Shaders/modelLoading.frag");

    // Load models 
    //Model ourModel( (char *)"Models/Tienda/tienda.obj");
	//Model model2((char *)"Models/Gabinete1/gabinete1.obj");
	//Model gabinete2((char *)"Models/Gabinete2/gabinete2.obj");
	Model sofa((char *)"Models/Sofa/sofa.obj");
	//Model calentador((char *)"Models/Calentador/calentador.obj");
	//Model mesa((char *)"Models/Mesa/mesa.obj");
	//Model espejo((char *)"Models/Espejo/espejo.obj");
	//Model puertaVidrio((char *)"Models/PuertaVidrio/puertaVidrio.obj");
	//Model puertaMadera((char *)"Models/PuertaMadera/puertaMadera.obj");

    // Draw in wireframe
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );


	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	//SkyBox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);

	// Load textures
	vector<const GLchar*> faces;
	faces.push_back("SkyBox/right.tga");
	faces.push_back("SkyBox/left.tga");
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/bottom.tga");
	faces.push_back("SkyBox/back.tga");
	faces.push_back("SkyBox/front.tga");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
    // Game loop
    while( !glfwWindowShouldClose( window ) )
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime( )/4;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // Check and call events
        glfwPollEvents( );
        DoMovement( );
        
        // Clear the colorbuffer
        glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        shader.Use( );
        
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv( glGetUniformLocation( shader.Program, "projection" ), 1, GL_FALSE, glm::value_ptr( projection ) );
        glUniformMatrix4fv( glGetUniformLocation( shader.Program, "view" ), 1, GL_FALSE, glm::value_ptr( view ) );
        
		//--Model section --//
        //Casa
		//glm::mat4 model(1);
		//model = glm::translate( model, glm::vec3( -0.0f, -1.75f, 0.0f ) ); // Translate it down a bit so it's at the center of the scene
		//model = glm::scale( model, glm::vec3( 0.02f, 0.02f, 0.02f ) );	// It's a bit too big for our scene, so scale it down
		////model = glm::rotate(model, (float)glfwGetTime(75.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv( glGetUniformLocation( shader.Program, "model" ), 1, GL_FALSE, glm::value_ptr( model ) );
		//ourModel.Draw( shader );

		////Gavinete1
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(0.37f, -1.33f, 0.17f)); // Translate it down a bit so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004));	// It's a bit too big for our scene, so scale it down
		//model = glm::rotate(model, glm::radians(92.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//model2.Draw(shader);

		////Gavinete2
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-0.155f, -1.33f, 0.4f)); // Translate it down a bit so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004));	// It's a bit too big for our scene, so scale it down
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//gabinete2.Draw(shader);

		//model = glm::mat4(1.0f);
		glm::mat4 model(1);
		model = glm::translate(model, glm::vec3(0.16f, -1.33f, 0.42f)); // Translate it down a bit so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.002f, 0.002f, 0.002));	// It's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		sofa.Draw(shader);


		//model = glm::mat4(1.0f);
		////glm::mat4 model(1);
		//model = glm::translate(model, glm::vec3(-0.025f, -1.27f, 0.40f)); // Translate it down a bit so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.0015f, 0.0015f, 0.0015f));	// It's a bit too big for our scene, so scale it down
		//model = glm::rotate(model, glm::radians(00.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//calentador.Draw(shader);


		//model = glm::mat4(1.0f);
		////glm::mat4 model(1);
		//model = glm::translate(model, glm::vec3(0.16f, -1.33f, 0.1f)); // Translate it down a bit so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.0002f, 0.0002f, 0.0002f));	// It's a bit too big for our scene, so scale it down
		//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//mesa.Draw(shader);


		//model = glm::mat4(1.0f);
		////glm::mat4 model(1);
		//model = glm::translate(model, glm::vec3(0.37f, -1.33f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// It's a bit too big for our scene, so scale it down
		//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//espejo.Draw(shader);

		//--Animation section--//

		//model = glm::mat4(1.0f);
		////glm::mat4 model(1);
		//model = glm::translate(model, glm::vec3(-0.20f, -1.74f, 0.45f)); // Translate it down a bit so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.0190f, 0.019f, 0.0125f));	// It's a bit too big for our scene, so scale it down
		//model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//puertaVidrio.Draw(shader);

		//model = glm::mat4(1.0f);
		////glm::mat4 model(1);
		//model = glm::translate(model, glm::vec3(-0.3f, -1.0f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.0190f, 0.019f, 0.0125f));	// It's a bit too big for our scene, so scale it down
		//model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//puertaMadera.Draw(shader);

		//--Skybox section--//

		// Draw skybox as last
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
		SkyBoxshader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		//// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Set depth function back to default

        // Swap the buffers
        glfwSwapBuffers( window );
    }
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);
    glfwTerminate( );
    return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }
	if (keys[GLFW_KEY_O] )
	{
		if (rot <=260)
			rot = rot + 0.1;
	}
	if (keys[GLFW_KEY_P])
	{
		if (rot >= 180)
			rot = rot - 0.1;
	}

	if (keys[GLFW_KEY_K])
	{
		if (rot2 <= 260)
			rot2 = rot2 + 0.1;
	}
	if (keys[GLFW_KEY_L])
	{
		if (rot2 >= 180)
			rot2 = rot2 - 0.1;
	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

