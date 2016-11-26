
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


const GLuint WIDTH = 800, HEIGHT = 600;


glm::vec3 lightPos(0.0f, 0.0f, 1.0f);


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // MAC
	
	
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	
	glfwSetKeyCallback(window, key_callback);
	
	glewExperimental = GL_TRUE;
	glewInit();
	

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	
	glEnable(GL_DEPTH_TEST);  // 开启深度测试
	
	
	// 光源
    Shader lightShader("/Users/apple/Documents/Xcode/GLDemo/light.vert", "/Users/apple/Documents/Xcode/GLDemo/light.frag");
    // 物体
    Shader objectShader("/Users/apple/Documents/Xcode/GLDemo/object.vert", "/Users/apple/Documents/Xcode/GLDemo/object.frag");
	
    
    GLfloat vertices[] =
    {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
	
    glm::vec3 cubePositions[] =
    {
        glm::vec3(  0.0f,  0.0f,  0.0f),
        glm::vec3(  2.0f,  5.0f, -15.0f),
        glm::vec3( -1.5f, -2.2f, -2.5f),
        glm::vec3( -3.8f, -2.0f, -12.3f),
        glm::vec3(  2.4f, -0.4f, -3.5f),
        glm::vec3( -1.7f,  3.0f, -7.5f),
        glm::vec3(  1.3f, -2.0f, -2.5f),
        glm::vec3(  2.0f,  2.0f, -2.5f),
        glm::vec3(  1.5f,  0.2f, -1.5f),
        glm::vec3( -1.3f,  1.0f, -1.5f)
    };
    
    glm::vec3 pointLigPos[] =
    {
        glm::vec3(  0.7f,  0.2f,  1.5f),
        glm::vec3(  2.3f, -3.0f, -3.0f),
        glm::vec3( -4.0f,  3.0f, -3.0f),
        glm::vec3( -3.0f,  0.0f, -2.0f)
    };
    
    
    GLuint objectVAO;  // 物体
    GLuint VBO;
	glGenVertexArrays(1, &objectVAO);
	glGenBuffers(1, &VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
    glBindVertexArray(objectVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    
    
    GLuint lightVAO;  // 光源
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	
	while (!glfwWindowShouldClose(window))
	{
		  glfwPollEvents();
		
		  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
      lightPos.x = sin(glfwGetTime());
        

        // 物体着色器
        objectShader.Use();
        
        // 观察者坐标
        GLint viewPosLoc = glGetUniformLocation(objectShader.Program, "viewPos");
        glUniform3f(viewPosLoc, 0.0f, 0.0f, 5.0f);
        
        // 物体材质
        GLint matAmbientLoc = glGetUniformLocation(objectShader.Program, "material.ambient");
        GLint matDiffuseLoc = glGetUniformLocation(objectShader.Program, "material.diffuse");
        GLint matSpecularLoc = glGetUniformLocation(objectShader.Program, "material.specular");
        GLint matShineLoc = glGetUniformLocation(objectShader.Program, "material.shininess");
        glUniform3f(matAmbientLoc, 1.0f, 1.0f, 1.0f);
        glUniform3f(matDiffuseLoc, 1.0f, 0.0f, 0.16f);
        glUniform3f(matSpecularLoc, 0.5f, 0.6f, 0.7f);
        glUniform1f(matShineLoc, 32.0f);
        
        // 平行光照
        glUniform3f(glGetUniformLocation(objectShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
        
        // 点光源 1
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[0].position"), pointLigPos[0].x, pointLigPos[0].y, pointLigPos[0].z);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[0].diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[0].linear"), 0.09);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[0].quadratic"), 0.032);
        
        // 点光源 2
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[1].position"), pointLigPos[1].x, pointLigPos[1].y, pointLigPos[1].z);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[1].diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[1].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[1].linear"), 0.09);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[1].quadratic"), 0.032);
        
        // 点光源 3
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[2].position"), pointLigPos[2].x, pointLigPos[2].y, pointLigPos[2].z);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[2].diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[2].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[2].linear"), 0.09);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[2].quadratic"), 0.032);
        
        // 点光源 4
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[3].position"), pointLigPos[3].x, pointLigPos[3].y, pointLigPos[3].z);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[3].diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[3].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[3].linear"), 0.09);
        glUniform1f(glGetUniformLocation(objectShader.Program, "pointLights[3].quadratic"), 0.032);
        
        // 聚光灯
        glUniform3f(glGetUniformLocation(objectShader.Program, "spotLight.position"), lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(glGetUniformLocation(objectShader.Program, "spotLight.direction"), 0.0f, 0.0f, -1.0f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "spotLight.diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(objectShader.Program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(objectShader.Program, "spotLight.linear"), 0.09);
        glUniform1f(glGetUniformLocation(objectShader.Program, "spotLight.quadratic"), 0.032);
        glUniform1f(glGetUniformLocation(objectShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
        glUniform1f(glGetUniformLocation(objectShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(17.0f)));
        
        
        // 物体顶点位置
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
        
        //LookUp矩阵: view = glm::lookAt(glm::vec3(0.0, 0.0, 5), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		    projection = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
		
        GLint modelLoc = glGetUniformLocation(objectShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(objectShader.Program, "view");
        GLint projectionLoc = glGetUniformLocation(objectShader.Program, "projection");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        
        
        glBindVertexArray(objectVAO);
        
        for (GLuint i = 1; i <= 10; ++i)
        {
            model = glm::mat4();
            model = glm::translate(model, cubePositions[i]);
            GLfloat angle = i * (GLfloat)glfwGetTime() / 5;
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            model = glm::scale(model, glm::vec3(0.8f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(0);
        
        
        // 光源着色器
        lightShader.Use();
        
        glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
        glBindVertexArray(lightVAO);
        
        for (GLuint i = 0; i < 4; ++i)
        {
            model = glm::mat4();
            model = glm::translate(model, pointLigPos[i]);
            model = glm::scale(model, glm::vec3(0.1f));
            glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        model = glm::mat4();
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.02f));
        glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        
        
        glfwSwapBuffers(window);
	}
	
	  glDeleteVertexArrays(1, &objectVAO);
    glDeleteVertexArrays(1, &lightVAO);
	  glDeleteBuffers(1, &VBO);
	
	  glfwTerminate();
	  return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q)&& action == GLFW_PRESS)
	  {
		    glfwSetWindowShouldClose(window, GL_TRUE);
	  }
}
