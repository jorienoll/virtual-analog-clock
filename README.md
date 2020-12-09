# virtual-analog-clock
This program taught me the basics of OpenGL programming, including drawing primitives and geometric transformations.

First, I set up OpenGL and GLUT. In MacOS, I used XCode and created a command line tool in C++. Next, I added the OpenGL and GLUT frameworks to the project's frameworks and libraries.

I created a virtual analog clock in OpenGL.

To draw the clock's face, I rendered a circle using a GL_TRIANGLE_FAN. I used
a for loop to create 360 vertices, so that the circle would be smooth.
I used basic trigonometry multiplying by sin and cos to calculate the coordinates
of each unique vertex.

To render the second, minute, and hour hands I used GL_LINES, GL_TRIANGLES,
and GL_TRIANGLE_STRIP respectively. For each hand I declared the color using
glColor3f(x,y,z). Then I declared the vertices on each hand, which were provided in 
the assignment prompt. To rotate the hands dynamically, I utilized the provided TimeEvent
function to grab the current time to calculate the rotation angle. Then I rotated the hands using a translate, a rotate, followed by another translate.

 This program resulted in a 2D analog clock that moves synchronously,
 generated from the command line. It renders a face and rotating second, minute,
 and hour hands.
