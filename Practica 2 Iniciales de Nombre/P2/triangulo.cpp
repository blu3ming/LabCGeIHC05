#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>
//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;
//VAO: Se le puden asignar posiciones y colores, (coordenadas y colores de los vertices) Recibe estos datos (datos espaciales)
//Muchas veces solo se delcaran coordenadas del vertice.
//VBO: Los procesa y los almacena en el buffer. Debemos decirle cómo va a recibir esos datos, se le dice que son datos de vertices y/o de colores
//Entero de OpenGL
GLuint VAO, VBO, shader;

//Arreglo de indices: indice a un vértice. Estos son (X0,Y0,Z0)

//Vertex Shader. Recibe posicion y en opengl lo interpreta en posiciones x y y z
//vshader shader de vertices recibe posiciones y colores dentro de los datos del arreglo de vertices.
//Rango de shaders
//optimización, prácticas de buen uso. Que mande a la posicion 0 en una pila de arreglos que se va a procesar.
//in indica que va a recibir datos
//recibe un v4, posicion en x,y,z y la ultima bandera siempre va ne 1. En OpenGL todas las matrices son de 4x4, solo es por concordancia ese 1.
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
layout (location = 1) in vec3 col;					\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 		\n\
	color = vec4(col.x,col.y,col.z,1.0f);			\n\
}";

//Fragment Shader. Salida un vector de 4 posiciones en color

static const char* fShader = "						\n\
#version 330										\n\
in vec4 color;										\n\
out vec4 color2;									\n\
void main()											\n\
{													\n\
	color2 = color;	 								\n\
}";


//Declaramos nuestros vertices que enviamos a los shaders
void CrearTriangulo()
{
	//Flotante de OpenGL, arreglo dinamico
	GLfloat vertices[] = {//Datos de posiciones, se le pueden añadir tambien el color que entraria como in a fragment shader, se agregan en sentido antihorario
		//L
		-0.5f,-0.4f,0.0f,
		-0.5f,-0.3f,0.0f,
		-0.8f,-0.4f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,

		-0.8f,-0.4f,0.0f,
		-0.5f,-0.3f,0.0f,
		-0.8f,-0.3f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,

		-0.8f,-0.4f,0.0f,
		-0.8f,0.5f,0.0f,
		-0.9f,0.5f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,

		-0.8f,-0.4f,0.0f,
		-0.9f,0.5f,0.0f,
		-0.9f,-0.4f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,

		//J
		-0.3f,-0.4f,0.0,//inf izq
		-0.3f,-0.2f, 0.0f,//inf derecha
		-0.4f,-0.2f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,

		-0.3f,-0.4f,0.0f,
		-0.4f,-0.2f,0.0f,
		-0.4f,-0.4f,0.0f,//Son los 3 vertices del triangulo: superior
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,

		-0.2f,-0.4f,0.0,//inf izq
		-0.2f,-0.3f, 0.0f,//inf derecha
		-0.3f,-0.3f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,

		-0.2f,-0.4f,0.0,//inf izq
		-0.3f,-0.3f, 0.0f,//inf derecha
		-0.3f,-0.4f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,

		-0.1f,-0.4f,0.0f,//inf izq
		-0.1f,0.4f, 0.0f,//inf derecha
		-0.2f,0.4f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,

		-0.1f,-0.4f,0.0,//inf izq
		-0.2f,0.4f, 0.0f,//inf derecha
		-0.2f,-0.4f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,

		0.0f,0.4f,0.0,//inf izq
		0.0f,0.5f, 0.0f,//inf derecha
		-0.3f,0.4f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,

		0.0f,0.5f,0.0,//inf izq
		-0.3f,0.5f, 0.0f,//inf derecha
		-0.3f,0.4f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,

		//C
		0.4f,-0.4f,0.0,//inf izq
		0.4f,-0.3f, 0.0f,//inf derecha
		0.2f,-0.4f,0.0f,
		0.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,

		0.2f,-0.4f,0.0,//inf izq
		0.4f,-0.3f, 0.0f,//inf derecha
		0.2f,-0.3f,0.0f,
		0.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,

		0.4f,0.4f,0.0,//inf izq
		0.4f,0.5f, 0.0f,//inf derecha
		0.2f,0.4f,0.0f,
		0.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,

		0.2f,0.4f,0.0,//inf izq
		0.4f,0.5f, 0.0f,//inf derecha
		0.2f,0.5f,0.0f,
		0.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,

		0.2f,-0.4f,0.0,//inf izq
		0.2f,0.5f, 0.0f,//inf derecha
		0.1f,0.5f,0.0f,
		0.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,

		0.1f,-0.4f,0.0,//inf izq
		0.2f,-0.4f, 0.0f,//inf derecha
		0.1f,0.5f,0.0f,
		0.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,

		//M
		0.5f,-0.4f,0.0,//inf izq
		0.6f,-0.4f, 0.0f,//inf derecha
		0.5f,0.5f,0.0f,
		1.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,

		0.6f,-0.4f,0.0,//inf izq
		0.6f,0.5f, 0.0f,//inf derecha
		0.5f,0.5f,0.0f,
		1.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,

		0.8f,-0.4f,0.0,//inf izq
		0.9f,-0.4f, 0.0f,//inf derecha
		0.8f,0.5f,0.0f,
		1.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,

		0.9f,-0.4f,0.0,//inf izq
		0.9f,0.5f, 0.0f,//inf derecha
		0.8f,0.5f,0.0f,
		1.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,

		0.7f,0.0f,0.0,//inf izq
		0.8f,0.2f, 0.0f,//inf derecha
		0.6f,0.2f,0.0f,
		1.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,

		0.7f,0.2f,0.0,//inf izq
		0.8f,0.2f, 0.0f,//inf derecha
		0.8f,0.5f,0.0f,
		1.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,

		0.7f,0.2f,0.0,//inf izq
		0.6f,0.5f, 0.0f,//inf derecha
		0.6f,0.2f,0.0f,
		1.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f

	};//la interpolacion da toda la gradiente para pasar de un color a otro.
	glGenVertexArrays(1, &VAO); //generar 1 VAO. todos esos ertices se los asignamos a vao, solo uno, por eso el 1. Genera
	glBindVertexArray(VAO);//asignar VAO. cuando se genera, se liga. lo manda a la tarjeta grafica. Manda a tarjeta

	glGenBuffers(1, &VBO);//
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//se dice que es un bufer de arreglo, le pasamos al vbo los datos que 
	//queremos almacenar en el bufer de memoria que estamos declarando
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, 
		//los datos y en este caso es estático pues no se modificarán los valores (GL_STATIC_DRAW), sería false si es que se emovieran.
		//No hábrá un evento que lo modifique.
		//Desde qué localidad empieza, tamaño de la regla de datos, tipo de datos, falso o verdadero si hay color, si es verdadero cual es el offset
		//cuantos datos debe omitir si hay datos de color.
		//De los datos del array creado, como los va a tomar.
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)36);
		glEnableVertexAttribArray(0);//inicia
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);//ya terminamos de utilizar el vertex array y bindbuffer, por lo tanto se resetean
		glBindVertexArray(0);//se resetea

}
//se recibe el shader, se procesa, verifica que sea correcta, si esta bien, lo compila. Agregr a la tarjeta grafica la info del shader y lo renderiza
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) //Función para agregar los shaders a la tarjeta gráfica
//the Program recibe los datos de theShader


{
	GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
	const GLchar* theCode[1];
	theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);//longitud del texto
	glShaderSource(theShader,1, theCode, codeLength);//Se le asigna al shader el código (source, 1, codigo, tamaño codigo)
	glCompileShader(theShader);//Se comila el shader
	GLint result = 0;
	GLchar eLog[1024] = { 0 };//trycatch
	//verificaciones y prevención de errores
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n",shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el código a la tarjeta gráfica
}

void CompileShaders() {
	shader= glCreateProgram(); //se crea un programa de shader
	if (!shader)//si falla
	{
		printf("Error creando el shader");
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);//Agregar vertex shader, se le agrega un shader de vertices,
	//vshader serán datos de un archivo externo, es toda la cadena del shader
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);//Agregar fragment shader
	//Para terminar de linkear el programa y ver que no tengamos errores
	GLint result = 0;//shader, el programa
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);//se linkean los shaders a la tarjeta gráfica
	 //verificaciones y prevención de errores
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al linkear es: %s \n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al validar es: %s \n", eLog);
		return;
	}



}
int main()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Primer ventana", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);

 //Crear tríangulo
	CrearTriangulo();
	CompileShaders();


	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Recibir eventos del usuario; desde tres eventos, teclado, mouse, y joystick, si se presiona una tecla, si se
		//libera, si se mueve el mouse, si se presiona un boton, si se mueve el joystick, etc.
		glfwPollEvents();

		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//se le dice a la ventana que use el shader y se muestre
		glUseProgram(shader);

		glBindVertexArray(VAO);//se va a utilizar el vao (vertices)
		glDrawArrays(GL_TRIANGLES,0,150);//este comando es el que dibujará el triangulo en la ventana, desde la localidad 0 y cada 3 son los vertices
		glBindVertexArray(0);//se libera

		glUseProgram(0);//limpia memoria

		//Si vamos a manejar eventos, hay que declarar un buffer doble y este se encarga de intercambiarlos
		//Todos los eventos que se reciban por medio de pollevents no se veran en pantalla, se quedara estatico en la primer
		//imagen que renderice.
		glfwSwapBuffers(mainWindow);

	}


	return 0;
}