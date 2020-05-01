// Std. Includes
#include <string>
#include <iostream>
#include <cmath>

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
Camera camera( glm::vec3( 0.0f, 0.0f, 0.0f ) );
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
float rot = 180.0f;
float rotY = -0.6f;
float rotX = 0.0f;
float limN = -0.037;
float limP = 0.037;

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
    Model ourModel( (char *)"Models/Tienda/tienda.obj");
	Model model2((char *)"Models/Gabinete1/gabinete1.obj");
	Model gabinete2((char *)"Models/Gabinete2/gabinete2.obj");
	Model sofa((char *)"Models/Sofa/sofa.obj");
	Model calentador((char *)"Models/Calentador/calentador.obj");
	Model mesa((char *)"Models/Mesa/mesa.obj");
	Model espejo((char *)"Models/Espejo/espejo.obj");
	Model limpieza((char *)"Models/Limpieza/Limpieza.obj");
	Model cocina((char *)"Models/Cocina/cocina.obj");
	Model mesa_restaurant((char *)"Models/mesa_restaurant/mesa_restaurant.obj");
	Model arcade((char *)"Models/arcade/arcade.obj");
	Model silla((char *)"Models/Silla/silla.obj");
	Model puertaVidrio((char *)"Models/PuertaVidrio/puertaVidrio.obj");


	////Model puertaVidrio((char *)"Models/PuertaVidrio/puertaVidrio.obj");

    // Draw in wireframe
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );


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
        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        shader.Use( );
        
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv( glGetUniformLocation( shader.Program, "projection" ), 1, GL_FALSE, glm::value_ptr( projection ) );
        glUniformMatrix4fv( glGetUniformLocation( shader.Program, "view" ), 1, GL_FALSE, glm::value_ptr( view ) );
        


		//--Model section --//

		//Casa
			glm::mat4 model(1);
			model = glm::translate( model, glm::vec3( -0.0f, -1.75f, 0.0f ) ); // Translate it down a bit so it's at the center of the scene
			model = glm::scale( model, glm::vec3( 0.02f, 0.02f, 0.02f ) );	// It's a bit too big for our scene, so scale it down
			glUniformMatrix4fv( glGetUniformLocation( shader.Program, "model" ), 1, GL_FALSE, glm::value_ptr( model ) );
			ourModel.Draw( shader );

		//Gavinete1
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.37f, -1.33f, 0.17f)); // Translate it down a bit so it's at the center of the scene
			model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004));	// It's a bit too big for our scene, so scale it down
			model = glm::rotate(model, glm::radians(92.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			model2.Draw(shader);

		//Gavinete2
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(-0.155f, -1.33f, 0.4f)); // Translate it down a bit so it's at the center of the scene
			model = glm::scale(model, glm::vec3(0.004f, 0.004f, 0.004));	// It's a bit too big for our scene, so scale it down
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			gabinete2.Draw(shader);

		////Sofa
			model = glm::mat4(1.0f);
			//glm::mat4 model(1);
			model = glm::translate(model, glm::vec3(0.16f, -1.33f, 0.42f)); // Translate it down a bit so it's at the center of the scene
			model = glm::scale(model, glm::vec3(0.002f, 0.002f, 0.002));	// It's a bit too big for our scene, so scale it down
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			sofa.Draw(shader);

		//Calentador
			model = glm::mat4(1.0f);
			//glm::mat4 model(1);
			model = glm::translate(model, glm::vec3(-0.025f, -1.27f, 0.40f)); // Translate it down a bit so it's at the center of the scene
			model = glm::scale(model, glm::vec3(0.0015f, 0.0015f, 0.0015f));	// It's a bit too big for our scene, so scale it down
			model = glm::rotate(model, glm::radians(00.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			calentador.Draw(shader);

		//Mesa
			model = glm::mat4(1.0f);
			//glm::mat4 model(1);
			model = glm::translate(model, glm::vec3(0.16f, -1.33f, 0.1f)); // Translate it down a bit so it's at the center of the scene
			model = glm::scale(model, glm::vec3(0.0002f, 0.0002f, 0.0002f));	// It's a bit too big for our scene, so scale it down
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			mesa.Draw(shader);

		//Espejo
			model = glm::mat4(1.0f);
			//glm::mat4 model(1);
			model = glm::translate(model, glm::vec3(0.37f, -1.33f, 0.0f)); // Translate it down a bit so it's at the center of the scene
			model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// It's a bit too big for our scene, so scale it down
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			espejo.Draw(shader);

		//Limpieza
			model = glm::mat4(1.0f);
			//glm::mat4 model(1);
			model = glm::translate(model, glm::vec3(0.35f, -1.33f, -0.15f)); // Translate it down a bit so it's at the center of the scene
			model = glm::scale(model, glm::vec3(0.025f, 0.025f, 0.025f));	// It's a bit too big for our scene, so scale it down
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			limpieza.Draw(shader);

		//Cocina
			model = glm::mat4(1.0f);
			//glm::mat4 model(1);
			model = glm::translate(model, glm::vec3(-0.12f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
			model = glm::scale(model, glm::vec3(0.025f, 0.025f, 0.020));	// It's a bit too big for our scene, so scale it down
			model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			cocina.Draw(shader);

		//Mesa Restaurant
			model = glm::mat4(1.0f);
			//glm::mat4 model(1);
			model = glm::translate(model, glm::vec3(0.0f, -1.75f, -0.1f)); // Translate it down a bit so it's at the center of the scene
			model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.015));	// It's a bit too big for our scene, so scale it down
			model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			mesa_restaurant.Draw(shader);

		////Arcade
			model = glm::mat4(1.0f);
			//glm::mat4 model(1);
			model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.1f)); // Translate it down a bit so it's at the center of the scene
			model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.015));	// It's a bit too big for our scene, so scale it down
			model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			arcade.Draw(shader);

		//--Animation section--//
			model = glm::mat4(1.0f);
			//glm::mat4 model(1);
			model = glm::translate(model, glm::vec3(rotX, -1.75f, rotY)); // Translate it down a bit so it's at the center of the scene
			model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.015));	// It's a bit too big for our scene, so scale it down
			model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			silla.Draw(shader);

			model = glm::mat4(1.0f);
			//glm::mat4 model(1);
			model = glm::translate(model, glm::vec3(-0.20f, -1.74f, 0.45f)); // Translate it down a bit so it's at the center of the scene
			model = glm::scale(model, glm::vec3(0.0190f, 0.019f, 0.0125f));	// It's a bit too big for our scene, so scale it down
			model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			puertaVidrio.Draw(shader);




        // Swap the buffers
        glfwSwapBuffers( window );
    }

    glfwTerminate( );
    return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if (  keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if (  keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }
	if (keys[GLFW_KEY_Q] )
	{
		if (rot <=260)
			rot = rot + 0.1;
	}
	if (keys[GLFW_KEY_W])
	{
		if (rot >= 180)
			rot = rot - 0.1;
	}

	if (keys[GLFW_KEY_A])
	{
		printf("Para A, rotX vale: %d",rotX);
		if (rotX > limN)
			rotX = rotX - 0.01;
	}
	if (keys[GLFW_KEY_S])
	{
		printf("Para S, rotX vale: %d", rotX);
		if (rotX < limP)
			rotX = rotX + 0.01;
	}
	if (keys[GLFW_KEY_D]){
		printf("Para D, rotX vale: %d", rotY);
		if (rotY < -0.5 ) {
			rotY = rotY + 0.01;
			limP = limP + 0.001; //Abrimos abanico de X
			limN = limN - 0.001;
		}
	}
	if (keys[GLFW_KEY_F]){
		printf("Para F, rotX vale: %d", rotY);
		if (rotY > -0.7) {
			rotY = rotY - 0.01;
			limP = limP - 0.001; //Cerramos abanico de X
			limN = limN + 0.001;
		}
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

