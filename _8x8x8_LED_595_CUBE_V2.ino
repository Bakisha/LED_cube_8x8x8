#include<SPI.h>
#include<LedCube.h>


//  HARDWARE
//  595         =  Arduino
//-----------------------------
const byte Latch       = 9;
const byte OE_pin      = 10;
const byte DataIN      = 11;// (MOSI)
const byte SRCLK       = 13;// (SCK)
//  OE can be tied to ground (and dissconnected from pin D10)
//minimum Refresh frequency =  BAM (4bit - 16, 3bit - 8, 2bit - 4, 1bit - 2) * LayerNumber (4-8) *  FPS (25-100) *  double buffer - sync (2)   // recomended = Layer * 1000
//Cube size = CUBE_SIZE_8x8x8
LedCube cube(OE_pin, Latch, CUBE_SIZE_8x8x8, 7680 );


int fps =    20;
float animtime = 90000; // duration of animations
#ifndef PI
#define PI 3.14159265358979323846
#endif


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



/* starfield parameters
  - time:                 Define the length of time that the animation should be executed.
  - cubeRef:            Define the instance of the 'LedCube' class that you made in your main program.
  - numberOfVoxels:  Define the number of voxels that should be drawn each frame.
  - shiftDelay (optional):    Define the delay (in ms) . Normally a value of
                  50 - 100 ms will suffice.
*/

void starfield(float time, LedCube & cubeRef, uint8_t stars,  uint16_t shiftDelay)
{
  // Declare and initialize other variables needed for the animation

  int cubesize = cubeRef.getCubeSize();
  float star_x [stars];
  float star_y [stars];
  float star_z [stars];
  float star_speed[stars];

  int i;
  byte trail;
  // Other variables
  for (i = 0; i < stars ; i++) {
    star_x [i] = random(cubesize);
    star_y [i] = cubesize + random(cubesize); // field move along Y axis
    star_z [i] = random(cubesize);
    star_speed[i] = 0.3 + (random(150) / 150); // speed of individual stars
  }


  float  startTime = millis();
  while (millis() - startTime < time)
  {

    //    cubeRef.voxel(z, y, x, 1, bightness);
    ///////////////////

    // display stars:
    for (i = 0 ; i < stars; i++)
    {
      for ( trail = 0 ; trail <= 4; trail++)
      {

        if (star_y[i] + trail < cubesize)
        {
          cubeRef.voxel(star_z[i], star_y[i] + trail, star_x[i], 1, 8 - ( trail * 2));
        }
      }// trail
    }// i

    delay(shiftDelay);
    cubeRef.drawVoxels();

    // star calculations:

    for (i = 0; i < stars; i++) {

      star_y[i] = star_y[i] - star_speed[i];

      if (star_y[i] <= -4)
      { // star has "passed", calculate new star position

        star_x [i] = random(cubesize);
        star_y [i] = cubesize + random(cubesize); // field move along Y axis
        star_z [i] = random(cubesize);
        star_speed[i] = 0.2 + (random(200) / 200); // speed of individual stars
      }



    } // i stars













    //    delay(shiftDelay);
    ///////////////////////
  } // while


  cubeRef.clearAllVoxels();
}




//
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



/* folder parameters   ***   ***
  - time:                 Define the length of time that the animation should be executed.
  - cubeRef:            Define the instance of the 'LedCube' class that you made in your main program.
  - shiftDelay :        Define the delay (in ms) . Normally a value of
                50 - 100 ms will suffice.

*/

void folder(float time, LedCube & cubeRef, uint16_t shiftDelay)
{
  // Declare and initialize other variables needed for the animation

  byte cubesize = cubeRef.getCubeSize();

  // Other variables



  float  startTime = millis();
  while (millis() - startTime < time)
  {

    //    cubeRef.voxel(z, y, x, 1, bightness);
    ///////////////////





    //////////////////////////////////////////// FrontZ to FrontX
    for (byte a = 0; a < cubesize - 1; a++)
    {
      for (byte z = 0; z < cubesize; z++)
      {
        cubeRef.voxelLine(0, 0, z,  a, cubesize - 1, z );

      }
      delay(shiftDelay);
      cubeRef.drawVoxels();
    }
    for (byte a = 0; a < cubesize; a++)
    {
      for (byte z = 0; z < cubesize; z++)
      {
        cubeRef.voxelLine(0, 0, z,  cubesize - 1, cubesize - 1 - a, z);
      }
      delay(shiftDelay);
      cubeRef.drawVoxels();
    }
    ///////////////////////////////////////////



    //////////////////////////////////////////// FrontX to BackZ
    for (byte a = 0; a < cubesize - 1; a++)
    {
      for (byte z = 0; z < cubesize; z++)
      {
        cubeRef.voxelLine(  cubesize - 1 , 0, z , 0, a , z);

      }
      delay(shiftDelay);
      cubeRef.drawVoxels();
    }
    for (byte a = 0; a < cubesize; a++)
    {
      for (byte z = 0; z < cubesize; z++)
      {
        cubeRef.voxelLine((cubesize - 1), 0, z,  a, cubesize - 1 , z);
      }
      delay(shiftDelay);
      cubeRef.drawVoxels();
    }
    ///////////////////////////////////////////


    //////////////////////////////////////////// BackZ to BackY
    for (byte a = 0; a < cubesize - 1; a++)
    {
      for (byte z = 0; z < cubesize; z++)
      {
        cubeRef.voxelLine(cubesize - 1, z, cubesize - 1, cubesize - 1 - a, z , 0);

      }
      delay(shiftDelay);
      cubeRef.drawVoxels();
    }
    for (byte a = 0; a < cubesize; a++)
    {
      for (byte z = 0; z < cubesize; z++)
      {
        cubeRef.voxelLine(cubesize - 1, z, cubesize - 1, 0, z , a);
      }
      delay(shiftDelay);
      cubeRef.drawVoxels();
    }
    ///////////////////////////////////////////


    //////////////////////////////////////////// BackY to BackX
    for (byte a = 0; a < cubesize - 1; a++)
    {
      for (byte z = 0; z < cubesize; z++)
      {
        cubeRef.voxelLine(z, cubesize - 1, cubesize - 1, z, 0 , cubesize - 1 - a);

      }
      delay(shiftDelay);
      cubeRef.drawVoxels();
    }
    for (byte a = 0; a < cubesize; a++)
    {
      for (byte z = 0; z < cubesize; z++)
      {
        cubeRef.voxelLine(z, cubesize - 1, cubesize - 1, z, a , 0);
      }
      delay(shiftDelay);
      cubeRef.drawVoxels();
    }
    ///////////////////////////////////////////

    //////////////////////////////////////////// BackX to FrontY
    for (byte a = 0; a < cubesize - 1; a++)
    {
      for (byte z = 0; z < cubesize; z++)
      {
        cubeRef.voxelLine(z, cubesize - 1, 0, z, cubesize - 1 - a , cubesize - 1);

      }
      delay(shiftDelay);
      cubeRef.drawVoxels();
    }
    for (byte a = 0; a < cubesize; a++)
    {
      for (byte z = 0; z < cubesize; z++)
      {
        cubeRef.voxelLine(z, cubesize - 1, 0, z, 0 , cubesize - 1 - a);
      }
      delay(shiftDelay);
      cubeRef.drawVoxels();
    }
    ///////////////////////////////////////////


    //////////////////////////////////////////// FrontWallY to FrontWallX
    for (byte a = 0; a < cubesize - 1; a++)
    {
      for (byte z = 0; z < cubesize; z++)
      {
        cubeRef.voxelLine(z, 0, 0,  z, cubesize - 1, a);
      }
      delay(shiftDelay);
      cubeRef.drawVoxels();
    }
    for (byte a = 0; a < cubesize; a++)
    {
      for (byte z = 0; z < cubesize; z++)
      {
        cubeRef.voxelLine(z, 0, 0,  z, cubesize - 1 - a, cubesize - 1);
      }
      delay(shiftDelay);
      cubeRef.drawVoxels();
    }
    ///////////////////////////////////////////

    //////////////////////////////////////////// FrontX to FrontZ
    for (byte a = 0; a < cubesize - 1; a++)
    {
      for (byte z = 0; z < cubesize; z++)
      {
        cubeRef.voxelLine(0, 0, z,  cubesize - 1, a, z );

      }
      delay(shiftDelay);
      cubeRef.drawVoxels();
    }
    for (byte a = 0; a < cubesize; a++)
    {
      for (byte z = 0; z < cubesize; z++)
      {
        cubeRef.voxelLine(0, 0, z,  cubesize - 1 - a, cubesize - 1 , z);
      }
      delay(shiftDelay);
      cubeRef.drawVoxels();
    }
    ///////////////////////////////////////////



    //    delay(shiftDelay);
    ///////////////////////
  } // while


  cubeRef.clearAllVoxels();
}


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/* plasma1 parameters   ***   ***
  - time:                 Define the length of time that the animation should be executed.
  - cubeRef:            Define the instance of the 'LedCube' class that you made in your main program.
  -*note :              There is no delay() function, it is already very slow
*/
void plasma1(float time, LedCube & cubeRef)
{
  // Declare and initialize other variables needed for the animation
  //  float omega = (2.0 * PI) / (2 * cubeRef.getCubeSize()); // Calculate the radial frequency omega
  byte cubesize = cubeRef.getCubeSize();

  // Other variables

  float xoffset = PI / 24;//19
  float yoffset = PI / 37;//37
  float zoffset = PI / 19;//24

  float xx;
  float yy;
  float zz;


  float plasma;

  float xmap[cubesize];
  //  float ymap[cubesize];
  //  float zmap[cubesize];
  for ( byte cc = 0 ; cc < cubesize; cc++)
  {
    xmap[cc] = map(cc, 0, cubesize - 1, 0, 2 * PI);
    //    ymap[cc] = map(cc, 0, cubesize - 1, 0, 2 * PI);
    //    zmap[cc] = map(cc, 0, cubesize - 1, 0, 2 * PI);
  }

  float fx;
  float fy;
  float fz;







  float  startTime = millis();
  while (millis() - startTime < time)
  {
    ///////////////////

    for ( byte x = 0; x < cubesize ; x++)
    {

      //     xmap = map(x, 0, cubesize - 1, 0, 2 * PI);
      //     fx = sin(xx + xmap) ;
      fx = sin(xx + xmap[x]) ;
      for ( byte z = 0; z < cubesize; z++)
      {

        //         zmap = map(z, 0, cubesize - 1, 0, 2 * PI);
        //         fz = cos(zz + zmap) ;
        fz = cos(zz + xmap[z]) ;



        //          if (plasma < 4) {
        //            plasma = 0;

        //          }

        for ( byte y = 0 ; y < cubesize ; y++ )
        {

          //          ymap = map(y, 0, cubesize - 1, 0, 2 * PI);
          //fy = sin(yy + map(y, 0, cubesize - 1, 0, 2 * PI)) ;
          fy = sin(yy + xmap[y]) ;
          plasma =   fy + fz + fx ; // - 3 , 3  // (0-6) * 2.5 = (0 - 15)

          if (plasma > 0) {
            cubeRef.voxel(z, x, y, 1, plasma * 3);
          }


        }//  z
      }  //  x
    }    //  y


    xx = xx + xoffset;
    zz = zz + zoffset;
    yy = yy + yoffset;

    cube.drawVoxels(false); // Draw the frame to the cube explicitly not using vsync
    //    cubeRef.drawVoxels();
    //    delay(shiftDelay);
    ///////////////////////
  } // while


  cubeRef.clearAllVoxels();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/* explodingsphere parameters   ***   ***
  - time:                 Define the length of time that the animation should be executed.
  - cubeRef:            Define the instance of the 'LedCube' class that you made in your main program.
  - shiftDelay :        Define the delay (in ms) . Normally a value of
                  50 - 100 ms will suffice.
*/
void explodingsphere(float time, LedCube & cubeRef, uint16_t shiftDelay /* = 75 */)
{
  // Declare and initialize other variables needed for the animation
  // float omega = (2.0 * PI) / (2 * cubeRef.getCubeSize()); // Calculate the radial frequency omega
  byte cubesize = cubeRef.getCubeSize();
  float radspeed = 1;
  float radius = cubesize / 2;
  float radius2;
  float distance;

  int center_x = (cubesize / 2) - 1;
  int center_y = (cubesize / 2) - 1;
  int center_z = (cubesize / 2) - 1;

  //float x, y, z;
  float x1, y1, z1;
  float x2, y2, z2;
  // Other variables
  int br;
  int M = 8;
  int N = 8;
  int n, m;
  int x, y, z;


  long  startTime = millis();
  while (millis() - startTime < time)
  {
    ///////////////////
    center_x = (cubesize / 4) + random(cubesize / 2);
    center_y = (cubesize / 4) + random(cubesize / 2);
    center_z = (cubesize / 4) + random(cubesize / 2);



    for (  radius = 0; radius <  cubesize   ; radius = radius + radspeed)
    {

      for (  m = 1; m < M ; m++)
      {

        for (  n = 1; n < N ; n++)
        {

          x = radius * (sin(PI * m / M) * cos(2 * PI * n / N));

          y = radius * (sin(PI * m / M) * sin(2 * PI * n / N));

          z = radius * cos(PI * m / M);

          //     (x, y, z) = (sin(Pi * m / M) cos(2Pi * n / N), sin(Pi * m / M) sin(2Pi * n / N), cos(Pi * m / M));

          cubeRef.voxel(center_z + z, center_y + y, center_z + x , 1);





        }
      }
      cubeRef.drawVoxels();
      delay(shiftDelay);

    }
    //    cubeRef.drawVoxels();
    //   delay(shiftDelay);





    ///////////////////////
  } // while
  cubeRef.clearAllVoxels();
}


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/* explodingimplodingsphere parameters   ***   ***
  - time:                 Define the length of time that the animation should be executed.
  - cubeRef:            Define the instance of the 'LedCube' class that you made in your main program.
  - shiftDelay :        Define the delay (in ms) . Normally a value of
                  50 - 100 ms will suffice.
*/
void explodingimplodingsphere(float time, LedCube & cubeRef, uint16_t shiftDelay /* = 75 */)
{
  // Declare and initialize other variables needed for the animation
  // float omega = (2.0 * PI) / (2 * cubeRef.getCubeSize()); // Calculate the radial frequency omega
  float cubesize = cubeRef.getCubeSize();
  float radspeed = 0.50;

  float radius = cubesize / 2;
  float radius2;
  float distance;

  float center_x = (cubesize / 2) - 1;
  float center_y = (cubesize / 2) - 1;
  float center_z = (cubesize / 2) - 1;

  float x1, y1, z1;
  float czzp, cyyp, cxxp, czzn, cyyn, cxxn;
  // Other variables
  float br;


  long  startTime = millis();
  while (millis() - startTime < time)
  {

    ///////////////////
    center_x = (cubesize / 4) + random(cubesize / 2);
    center_y = (cubesize / 4) + random(cubesize / 2);
    center_z = (cubesize / 4) + random(cubesize / 2);



    for (  radius = 0; radius <=  cubesize - 1  ; radius = radius + radspeed)
    {
      radius2 = radius * radius;
      for ( float x = 0; x < cubesize ; x++)
      {
        x1 = x * x;
        for ( float y = 0; y < cubesize ; y++)
        {
          y1 = x1 + (y * y);
          for ( float z = 0; z < cubesize ; z++)
          {

            distance =  y1 + (z * z)  ;
            if (distance < radius2 )
            {
              br = 15 - radius * 2;


              czzp = center_z + z;
              cyyp = center_y + y;
              cxxp = center_x + x;
              czzn = center_z - z;
              cyyn = center_y - y;
              cxxn = center_x - x;
              /*
                            if (czzn < 0) {
                              czzn = 0;
                            }
                            if (cyyn < 0) {
                              cyyn = 0;
                            }
                            if (cxxn < 0) {
                              cxxn = 0;
                            }

                            if (czzp > cubesize - 1) {
                              czzp = cubesize - 1;
                            }
                            if (cyyp > cubesize - 1) {
                              cyyp = cubesize - 1;
                            }
                            if (cxxp > cubesize - 1) {
                              cxxp = cubesize - 1;
                            }
              */

              cubeRef.voxel(czzp, cyyp, cxxp , 1, br);
              cubeRef.voxel(czzp, cyyp, cxxn , 1, br);
              cubeRef.voxel(czzp, cyyn, cxxp, 1, br);
              cubeRef.voxel(czzp, cyyn, cxxn , 1, br);
              cubeRef.voxel(czzn, cyyp, cxxp , 1, br);
              cubeRef.voxel(czzn, cyyp, cxxn , 1, br);
              cubeRef.voxel(czzn, cyyn, cxxp , 1, br);
              cubeRef.voxel(czzn, cyyn, cxxn , 1, br);


            }


          }
        }
      }
      cubeRef.drawVoxels();
      delay(shiftDelay);
    }



    for (  radius = cubesize - 1; radius >=  0  ; radius = radius - radspeed )
    {
      radius2 = radius * radius;
      for ( float x = 0; x < cubesize ; x++)
      {
        x1 = x * x;
        for ( float y = 0; y < cubesize ; y++)
        {
          y1 = x1 + (y * y);
          for ( float z = 0; z < cubesize ; z++)
          {

            distance =  y1 + (z * z)  ;
            if (distance < radius2 )
            {
              br = 15 - radius * 2;
              czzp = center_z + z;
              cyyp = center_y + y;
              cxxp = center_x + x;
              czzn = center_z - z;
              cyyn = center_y - y;
              cxxn = center_x - x;

              /*
                            if (czzn < 0) {
                              czzn = 0;
                            }
                            if (cyyn < 0) {
                              cyyn = 0;
                            }
                            if (cxxn < 0) {
                              cxxn = 0;
                            }

                            if (czzp > cubesize - 1) {
                              czzp = cubesize - 1;
                            }
                            if (cyyp > cubesize - 1) {
                              cyyp = cubesize - 1;
                            }
                            if (cxxp > cubesize - 1) {
                              cxxp = cubesize - 1;
                            }
              */
              cubeRef.voxel(czzp, cyyp, cxxp , 1, br);
              cubeRef.voxel(czzp, cyyp, cxxn , 1, br);
              cubeRef.voxel(czzp, cyyn, cxxp, 1, br);
              cubeRef.voxel(czzp, cyyn, cxxn , 1, br);
              cubeRef.voxel(czzn, cyyp, cxxp , 1, br);
              cubeRef.voxel(czzn, cyyp, cxxn , 1, br);
              cubeRef.voxel(czzn, cyyn, cxxp , 1, br);
              cubeRef.voxel(czzn, cyyn, cxxn , 1, br);

            }


          }
        }
      }
      cubeRef.drawVoxels();
      delay(shiftDelay);
    }



    ///////////////////////
  } // while
  cubeRef.clearAllVoxels();
}
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/* sinmess parameters   ***   ***
  - time:                 Define the length of time that the animation should be executed.
  - cubeRef:            Define the instance of the 'LedCube' class that you made in your main program.
  - shiftDelay :        Define the delay (in ms) . Normally a value of
                  50 - 100 ms will suffice.
*/
void sinmess(float time, LedCube & cubeRef, uint16_t shiftDelay /* = 75 */)
{
  // Declare and initialize other variables needed for the animation
  //  float omega = (2.0 * PI) / (2 * cubeRef.getCubeSize()); // Calculate the radial frequency omega
  byte cubesize = cubeRef.getCubeSize();

  // Other variables


  long  startTime = millis();
  while (millis() - startTime < time)
  {
    ///////////////////


    for ( float offset = 0; offset < 4 * PI ; offset = offset +  (PI / (cubesize * 2)) ) {
      for ( byte x = 0; x < cubesize ; x++) {
        for ( byte z = 0; z < cubesize ; z++)
        {
          float      ipsilon = 10000 *  sin(offset + ((map(x, 0, cubesize - 1, -PI, PI))));
          float     y   = map(ipsilon, -10000, 10000, 0, cubesize );
          float      ipsilon1 = 10000 *  sin(offset / 2 + ((map(x, 0, cubesize - 1, -PI, PI))));
          float     y1   = map(ipsilon1, -10000, 10000, 0, cubesize );

          cubeRef.voxel(x, y, z, 1);
          cubeRef.voxel(z, y1, x, 1);
        }
      }
      cubeRef.drawVoxels();
      delay(shiftDelay);

    }

    ///////////////////////
  }
  cubeRef.clearAllVoxels();
}


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/* sinpluscos parameters   ***   ***
  - time:                 Define the length of time that the animation should be executed.
  - cubeRef:            Define the instance of the 'LedCube' class that you made in your main program.
  - shiftDelay :        Define the delay (in ms) . Normally a value of
                  50 - 100 ms will suffice.
*/
void sinpluscos(float time, LedCube & cubeRef, uint16_t shiftDelay /* = 75 */)
{
  // Declare and initialize other variables needed for the animation
  //  float omega = (2.0 * PI) / (2 * cubeRef.getCubeSize()); // Calculate the radial frequency omega
  byte cubesize = cubeRef.getCubeSize();

  // Other variables


  long  startTime = millis();
  while (millis() - startTime < time)
  {
    ///////////////////


    for ( float offset = 0; offset < 4 * PI ; offset = offset +  (PI / (cubesize * 2)) ) {
      for ( byte x = 0; x < cubesize ; x++) {
        for ( byte z = 0; z < cubesize ; z++)
        {
          float      ipsilon = 10000 *  sin(offset + ((map(x, 0, cubesize - 1, -PI, PI) + (map(z, 0, cubesize - 1, -PI, PI)))));
          // y=sin(z * omega + offset ) * cos( x * omega + offset  );
          float     y   = map(ipsilon, -10000, 10000, 0, cubesize - 1);


          cubeRef.voxel(y, x, z, 1);
        }
      }
      cubeRef.drawVoxels();
      delay(shiftDelay);

    }

    ///////////////////////
  }
  cubeRef.clearAllVoxels();
}



// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/* sinx2y2nobr parameters   ***   ***
  - time:                 Define the length of time that the animation should be executed.
  - cubeRef:            Define the instance of the 'LedCube' class that you made in your main program.
  - shiftDelay :        Define the delay (in ms) . Normally a value of
                  50 - 100 ms will suffice.
*/
void sinx2y2nobr(float time, LedCube & cubeRef, uint16_t shiftDelay /* = 75 */)
{
  // Declare and initialize other variables needed for the animation
  // float omega = (2.0 * PI) / (2 * cubeRef.getCubeSize()); // Calculate the radial frequency omega
  byte cubesize = cubeRef.getCubeSize();

  // Other variables


  long  startTime = millis();
  while (millis() - startTime < time)
  {
    ///////////////////


    for ( float offset = 0; offset < 4 * PI ; offset = offset +  (PI / (cubesize * 2)) ) {
      for ( byte x = 0; x < cubesize ; x++) {
        for ( byte z = 0; z < cubesize ; z++)
        {
          float      ipsilon = 10000 *  sin(offset + sqrt(pow(map(x, 0, cubesize - 1, -PI, PI), 2) + pow(map(z, 0, cubesize - 1, -PI, PI), 2)));
          // y=sin(z * omega + offset ) * cos( x * omega + offset  );
          float     y   = map(ipsilon, -10000, 10000, 0, cubesize);


          cubeRef.voxel(x, y, z, 1);
        }
      }
      cubeRef.drawVoxels();
      delay(shiftDelay);

    }

    ///////////////////////
  }
  cubeRef.clearAllVoxels();
}



// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/*
  color_wheelTWO cube parameters
  - time:                 Define the length of time that the animation should be executed.
  - cubeRef:            Define the instance of the 'LedCube' class that you made in your main program.
  - shiftDelay (optional):    Define the delay (in ms) . Normally a value of
                  50 - 100 ms will suffice.
*/


void color_wheelTWO(float time, LedCube & cubeRef, uint16_t shiftDelay /* = 75 */)
{
  //*****colorWheelTwo*****colorWheelTwo*****colorWheelTwo*****colorWheelTwo*****colorWheelTwo
  byte cubesize = cubeRef.getCubeSize();
  int xx, yy, zz, ww, rr = 1, gg = 1, bb = 1, ranx, rany , ranz, select, swiper, br;


  long  startTime = millis();
  while (millis() - startTime < time)
  {

    swiper = random(6);
    select = random(3);
    br = random(16);
    if (select == 0) {
      ranx = 1;
      rany = random(16);
      ranz = random(16);
    }
    if (select == 1) {
      ranx = random(16);
      rany = 1;
      ranz = random(16);
    }
    if (select == 2) {
      ranx = random(16);
      rany = random(16);
      ranz = 1;
    }


    if (swiper == 0) {
      for (yy = 0; yy < cubesize; yy++) { //left to right
        for (xx = 0; xx < cubesize; xx++) {
          for (zz = 0; zz < cubesize; zz++) {
            cubeRef.voxel(zz, yy, xx, 1, br);
            // LED(xx, yy, zz,  ranx, ranz, rany);
          }
        }
        cubeRef.drawVoxels();
        delay(shiftDelay);
      }
    }
    if (swiper == 1) { //bot to top
      for (xx = 0; xx < cubesize; xx++) {
        for (yy = 0; yy < cubesize; yy++) {
          for (zz = 0; zz < cubesize; zz++) {
            cubeRef.voxel(zz, yy, xx, 1, br);
            //  LED(xx, yy, zz,  ranx, ranz, rany);
          }
        }
        cubeRef.drawVoxels();
        delay(shiftDelay);
      }
    }
    if (swiper == 2) { //back to front
      for (zz = 0; zz < cubesize; zz++) {
        for (xx = 0; xx < cubesize; xx++) {
          for (yy = 0; yy < cubesize; yy++) {
            cubeRef.voxel(zz, yy, xx, 1, br);
            // LED(xx, yy, zz,  ranx, ranz, rany);
          }
        }
        cubeRef.drawVoxels();
        delay(shiftDelay);
      }
    }
    if (swiper == 3) {
      for (yy = cubesize - 1; yy >= 0; yy--) { //right to left
        for (xx = 0; xx < cubesize; xx++) {
          for (zz = 0; zz < cubesize; zz++) {
            cubeRef.voxel(zz, yy, xx, 1, br);
            // LED(xx, yy, zz,  ranx, ranz, rany);
          }
        }
        cubeRef.drawVoxels();
        delay(shiftDelay);
      }
    }
    if (swiper == 4) { //top to bot
      for (xx = cubesize - 1; xx >= 0; xx--) {
        for (yy = 0; yy < cubesize; yy++) {
          for (zz = 0; zz < cubesize; zz++) {
            cubeRef.voxel(zz, yy, xx, 1, br);
            //  LED(xx, yy, zz,  ranx, ranz, rany);
          }
        }
        cubeRef.drawVoxels();
        delay(shiftDelay);
      }
    }
    if (swiper == 5) { //front to back
      for (zz = cubesize - 1; zz >= 0; zz--) {
        for (xx = 0; xx < cubesize; xx++) {
          for (yy = 0; yy < cubesize; yy++) {
            cubeRef.voxel(zz, yy, xx, 1, br);
            //LED(xx, yy, zz,  ranx, ranz, rany);
          }
        }
        cubeRef.drawVoxels();
        delay(shiftDelay);
      }
    }




  }//while

}//color wheel

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*   snake animation ****NOTE ****

  - time:               Define the length of time that the animation should be executed.
  - cubeRef:            Define the instance of the 'LedCube' class that you made in your main program.
  - shiftDelay :        Define the delay (in ms) . Normally a value of 50 - 100 ms will suffice.
  - iterations:         Define the number of iterations
  - mode :              Define mode (1 - enable ; 0 - disable): bit1 - crash action  ; bit2 - avoid corners
  - drawmode :          Define drawmode : 0 - pixel snake ; 1 - draw snake
*/


void snake(float time, LedCube & cubeRef, int shiftDelay, uint16_t iterations,  unsigned char mode)
{
  //  fill(0x00);   // Blank the cube
  byte cubesize = cubeRef.getCubeSize();
  int x, y, z;    // Current coordinates for the point
  int dx, dy, dz; // Direction of movement
  int lol, i;   // lol?
  unsigned char crash_x, crash_y, crash_z;

  y = random(cubesize) % (cubesize - 1);
  x = random(cubesize) % (cubesize - 1);
  z = random(cubesize) % (cubesize - 1);

  // Coordinate array for the snake.
  int snake[iterations][3];
  for (i = 0; i < iterations; ++i)
  {
    snake[i][0] = x;
    snake[i][1] = y;
    snake[i][2] = z;
  }


  dx = 1;
  dy = 1;
  dz = 1;




  long  startTime = millis();
  while (millis() - startTime < time)
  {
    ///////////////////




    crash_x = 0;
    crash_y = 0;
    crash_z = 0;


    // Let's mix things up a little:
    if (random(cubesize) % 3 == 0)
    {
      // Pick a random axis, and set the speed to a random number.
      lol = random(cubesize) % 3;
      if (lol == 0)
        dx = random(cubesize) % 3 - 1;

      if (lol == 1)
        dy = random(cubesize) % 3 - 1;

      if (lol == 2)
        dz = random(cubesize) % 3 - 1;
    }

    // The point has reached 0 on the x-axis and is trying to go to -1
    // aka a crash
    if (dx == -1 && x == 0)
    {
      crash_x = 0x01;
      if (random(cubesize) % 3 == 1)
      {
        dx = 1;
      } else
      {
        dx = 0;
      }
    }

    // y axis 0 crash
    if (dy == -1 && y == 0)
    {
      crash_y = 0x01;
      if (random(cubesize) % 3 == 1)
      {
        dy = 1;
      } else
      {
        dy = 0;
      }
    }

    // z axis 0 crash
    if (dz == -1 && z == 0)
    {
      crash_z = 0x01;
      if (random(cubesize) % 3 == 1)
      {
        dz = 1;
      } else
      {
        dz = 0;
      }
    }

    // x axis 7 crash
    if (dx == 1 && x == (cubesize - 1))
    {
      crash_x = 0x01;
      if (random(cubesize) % 3 == 1)
      {
        dx = -1;
      } else
      {
        dx = 0;
      }
    }

    // y axis 7 crash
    if (dy == 1 && y == (cubesize - 1))
    {
      crash_y = 0x01;
      if (random(cubesize) % 3 == 1)
      {
        dy = -1;
      } else
      {
        dy = 0;
      }
    }

    // z azis 7 crash
    if (dz == 1 && z == (cubesize - 1))
    {
      crash_z = 0x01;
      if (random(cubesize) % 3 == 1)
      {
        dz = -1;
      } else
      {
        dz = 0;
      }
    }

    // mode bit 0 sets crash action enable
    if (mode | 0x01)
    {
      if (crash_x)
      {
        if (dy == 0)
        {
          if (y == (cubesize - 1))
          {
            dy = -1;
          } else if (y == 0)
          {
            dy = +1;
          } else
          {
            if (random(cubesize) % 2 == 0)
            {
              dy = -1;
            } else
            {
              dy = 1;
            }
          }
        }
        if (dz == 0)
        {
          if (z == (cubesize - 1))
          {
            dz = -1;
          } else if (z == 0)
          {
            dz = 1;
          } else
          {
            if (random(cubesize) % 2 == 0)
            {
              dz = -1;
            } else
            {
              dz = 1;
            }
          }
        }
      }

      if (crash_y)
      {
        if (dx == 0)
        {
          if (x == (cubesize - 1))
          {
            dx = -1;
          } else if (x == 0)
          {
            dx = 1;
          } else
          {
            if (random(cubesize) % 2 == 0)
            {
              dx = -1;
            } else
            {
              dx = 1;
            }
          }
        }
        if (dz == 0)
        {
          if (z == 3)
          {
            dz = -1;
          } else if (z == 0)
          {
            dz = 1;
          } else
          {
            if (random(cubesize) % 2 == 0)
            {
              dz = -1;
            } else
            {
              dz = 1;
            }
          }
        }
      }

      if (crash_z)
      {
        if (dy == 0)
        {
          if (y == (cubesize - 1))
          {
            dy = -1;
          } else if (y == 0)
          {
            dy = 1;
          } else
          {
            if (random(cubesize) % 2 == 0)
            {
              dy = -1;
            } else
            {
              dy = 1;
            }
          }
        }
        if (dx == 0)
        {
          if (x == (cubesize - 1))
          {
            dx = -1;
          } else if (x == 0)
          {
            dx = 1;
          } else
          {
            if (random(cubesize) % 2 == 0)
            {
              dx = -1;
            } else
            {
              dx = 1;
            }
          }
        }
      }
    }

    // mode bit 1 sets corner avoid enable
    if (mode | 0x02)
    {
      if (  // We are in one of 8 corner positions
        (x == 0 && y == 0 && z == 0) ||
        (x == 0 && y == 0 && z == (cubesize - 1)) ||
        (x == 0 && y == (cubesize - 1) && z == 0) ||
        (x == 0 && y == (cubesize - 1) && z == (cubesize - 1)) ||
        (x == (cubesize - 1) && y == 0 && z == 0) ||
        (x == (cubesize - 1) && y == 0 && z == (cubesize - 1)) ||
        (x == (cubesize - 1) && y == (cubesize - 1) && z == 0) ||
        (x == (cubesize - 1) && y == (cubesize - 1) && z == (cubesize - 1))
      )
      {
        // At this point, the voxel would bounce
        // back and forth between this corner,
        // and the exact opposite corner
        // We don't want that!

        // So we alter the trajectory a bit,
        // to avoid corner stickyness
        lol = random(cubesize) % 3;
        if (lol == 0)
          dx = 0;

        if (lol == 1)
          dy = 0;

        if (lol == 2)
          dz = 0;
      }
    }

    // one last sanity check
    if (x == 0 && dx == -1)
      dx = 1;

    if (y == 0 && dy == -1)
      dy = 1;

    if (z == 0 && dz == -1)
      dz = 1;

    if (x == (cubesize - 1) && dx == 1)
      dx = -1;

    if (y == (cubesize - 1) && dy == 1)
      dy = -1;

    if (z == (cubesize - 1) && dz == 1)
      dz = -1;


    // Finally, move the voxel.
    x = x + dx;
    y = y + dy;
    z = z + dz;


    for (i = iterations - 1; i >= 0; --i)
    {
      snake[i][0] = snake[i - 1][0];
      snake[i][1] = snake[i - 1][1];
      snake[i][2] = snake[i - 1][2];
    }
    snake[0][0] = x;
    snake[0][1] = y;
    snake[0][2] = z;

    for (i = 0; i < iterations; ++i)
    {
      cubeRef.voxel(snake[i][2],  snake[i][1], snake[i][0],  1); //(snake[i][0], snake[i][1], snake[i][2]);
    }
    cubeRef.drawVoxels();
    delay(shiftDelay);







  }//while
  cubeRef.clearAllVoxels();
} // void



// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*   fireworks animation ****NOTE ****

  - time:               Define the length of time that the animation should be executed.
  - cubeRef:            Define the instance of the 'LedCube' class that you made in your main program.
  - iterations:         Define the number of iterations
  - shiftDelay :        Define the delay (in ms) . Normally a value of 50 - 100 ms will suffice.
*/

void fireworks(float time, LedCube & cubeRef, int iterations, int n, int shiftDelay)
{
  byte cubesize = cubeRef.getCubeSize();

  int i, f, e;

  float origin_x = 3;
  float origin_y = 3;
  float origin_z = 3;

  int rand_y, rand_x, rand_z;

  float slowrate, gravity;

  // Particles and their position, x,y,z and their movement, dx, dy, dz
  float particles[n][6];

  long  startTime = millis();
  while (millis() - startTime < time)
  {
    ///////////////////




    for (i = 0; i < iterations; ++i)
    {

      origin_x = random(cubesize) % 4;
      origin_y = random(cubesize) % 4;
      origin_z = random(cubesize) % 2;
      origin_z += ((cubesize / 2) + 1);
      origin_x += (cubesize / 4);
      origin_y += (cubesize / 4);

      // shoot a particle up in the air
      for (e = 0; e < origin_z; ++e)
      {
        cubeRef.voxel( (cubesize - 1) - e, origin_x, origin_y, 1);
        //      setvoxel(origin_x,origin_y,e);

        cubeRef.drawVoxels();
        delay(shiftDelay);

      }

      // Fill particle array
      for (f = 0; f < n; ++f)
      {
        // Position
        particles[f][0] = origin_x;
        particles[f][1] = origin_y;
        particles[f][2] = origin_z;

        rand_x = random(256) % 200;
        rand_y = random(256) % 200;
        rand_z = random(256) % 200;

        // Movement
        particles[f][3] = 1 - (float)rand_x / 100; // dx
        particles[f][4] = 1 - (float)rand_y / 100; // dy
        particles[f][5] = 1 - (float)rand_z / 100; // dz
      }

      // explode
      for (e = 0; e < 25; ++e)
      {
        slowrate = 1 + tan((e + 0.1) / 20) * 10;

        gravity = tan((e + 0.1) / 20) / 2;

        for (f = 0; f < n; ++f)
        {
          particles[f][0] += particles[f][3] / slowrate;
          particles[f][1] += particles[f][4] / slowrate;
          particles[f][2] += particles[f][5] / slowrate;
          particles[f][2] -= gravity;



          cubeRef.voxel((cubesize - 1) - particles[f][2], particles[f][0], particles[f][1],  1);
        }

        cubeRef.drawVoxels();
        delay(shiftDelay);

      }

    }
    cubeRef.clearAllVoxels();
  }



}



// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/* sphere cube parameters
  - time:                 Define the length of time that the animation should be executed.
  - cubeRef:            Define the instance of the 'LedCube' class that you made in your main program.
  - sphere_center_x       Define x coordinate of center of cube
  - sphere_center_y       Define y coordinate of center of cube
  - sphere_center_z       Define z coordinate of center of cube
  - sphereSize:          Radium of sphere
  - brightness:          sphere brightness
  - shiftDelay (optional):    Define the delay (in ms) . Normally a value of
                  50 - 100 ms will suffice.
*/
void sphere(float time, LedCube & cubeRef, uint16_t sphere_center_x, uint16_t sphere_center_y, uint16_t sphere_center_z, uint16_t sphereSize, uint16_t brightness, uint16_t shiftDelay /* = 75 */)
{
  // Declare and initialize other variables needed for the animation
  //  float omega = (2.0 * PI) / (2 * cubeRef.getCubeSize()); // Calculate the radial frequency omega
  byte cubesize = cubeRef.getCubeSize();
  byte cubecenter = cubesize / 2;
  int pp = 100 ;
  // Voxel coordinates
  uint8_t z;
  uint8_t x;
  uint8_t y;

  // For loop iterators
  float x0, x1, x2;
  float y0, y1, y2;
  float z0, z1, z2;


  // Other variables
  float currentRadius;



  long  startTime = millis();
  while (millis() - startTime < time)
  {
    ///////////////////





    for ( float zed = -PI; zed < PI ; zed = zed +  (PI / (2 * cubesize) ) )
    {
      z0 = cos(zed);
      z1 = 1000 * z0;
      z = map(z1, -1000, 1000, -sphereSize, sphereSize);



      for ( float offset = 0; offset < 2 * PI ; offset = offset +  (PI / (8 * cubesize) ) )
      {
        x0 = sin(offset);
        x1 =  1000 * x0;
        x = map(x1, -1000,  1000, -(sphereSize * z), sphereSize * z);


        y0 = cos(offset);
        y1 =  1000 * y0;
        y = map(y1, - 1000, 1000, -(sphereSize * z), sphereSize * z);


        //       float      br = 1000 * sin( omega + offset / 0.55  );
        //      br = map(br, -1000, 1000, 3, 15);
        cubeRef.voxel(z + sphere_center_z, y + sphere_center_y, x + sphere_center_x, 1, brightness);
        //        cubeRef.drawVoxels();
        //       delay(shiftDelay);
      }

    }
    cubeRef.drawVoxels();
    delay(shiftDelay);


  } // while



  cubeRef.clearAllVoxels();
} // void

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------




/* luckyanim cube parameters
  - time:                 Define the length of time that the animation should be executed.
  - cubeRef:            Define the instance of the 'LedCube' class that you made in your main program.
  - sphereSize:          Radium of sphere
  - shiftDelay (optional):    Define the delay (in ms) . Normally a value of
                  50 - 100 ms will suffice.
*/
void luckyanim(float time, LedCube & cubeRef, uint16_t shiftDelay /* = 75 */)
{
  // Declare and initialize other variables needed for the animation
  float omega = (2.0 * PI) / (2 * cubeRef.getCubeSize()); // Calculate the radial frequency omega
  byte cubesize = cubeRef.getCubeSize();
  int pp = 100 ;
  // Voxel coordinates
  uint8_t z;
  uint8_t x;
  uint8_t y;

  // For loop iterators
  float x1, x2;
  float y1, y2;
  float z1, z2;
  // Other variables

  long  startTime = millis();
  while (millis() - startTime < time)
  {
    ///////////////////

    for ( float offset = 0; offset < 4 * PI ; offset = offset +  0.18 ) {
      for ( byte x = 0; x < cubesize; x++) {
        for ( byte z = 0; z < cubesize; z++)
        {
          float      ipsilon = 10000 *  sin(offset + ((map(x, 0, cubesize - 1, -PI, PI)) * (map(z, 0, cubesize - 1, -PI, PI))));
          // y=sin(z * omega + offset ) * cos( x * omega + offset  );
          float     y   = map(ipsilon, -10000, 10000, 0, cubesize);



          float      br = 10000 * sin(x * omega + offset / 0.55  );
          br = map(br, -10000, 10000, 1, 15);
          cubeRef.voxel(y, x, z, 1, br);


        }
      }
      cubeRef.drawVoxels();
      delay(shiftDelay);

    }






    cubeRef.clearAllVoxels();
  }

}
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/* wipeout parameters
  - time:                     Define the length of time that the animation should be executed.
  - cubeRef:                Define the instance of the 'LedCube' class that you made in your main program.
  - timeDelay (optional):     Define the delay (in ms) between each iteration of the rain drops falling down. Normally a value of
                    50 - 100 ms will suffice.
*/



void    wipeout(float time, LedCube & cubeRef, unsigned int drawDelay)
{



  int cubesize = cube.getCubeSize();
  int xxx = 0, yyy = 0, zzz = 0;
  int fx = random(cubesize), fy = random(cubesize), fz = random(cubesize), direct, fxm = 1, fym = 1, fzm = 1, fxo = 0, fyo = 0, fzo = 0;
  int  ftx = random(cubesize), fty = random(cubesize), ftz = random(cubesize), ftxm = 1, ftym = 1, ftzm = 1, ftxo = 0, ftyo = 0, ftzo = 0;
  int select, rr, gg, bb, rrt, ggt, bbt;

  rr = random(0, 15);
  gg = random(0, 15);






  long  startTime = millis();
  while (millis() - startTime < time)
  {
    ///////////////////

    //fx=random(8); fy=random(8); fz=random(8);
    // cube.voxel(z, x, y, 1, br);
    cube.voxel(fxo, fyo, fzo, 0);
    cube.voxel(fxo, fyo, fzo + 1, 0);
    cube.voxel(fxo, fyo, fzo - 1, 0);
    cube.voxel(fxo + 1, fyo, fzo, 0);
    cube.voxel(fxo - 1, fyo, fzo, 0);
    cube.voxel(fxo, fyo + 1, fzo, 0);
    cube.voxel(fxo, fyo - 1, fzo, 0);

    cube.voxel(ftxo, ftyo, ftzo, 0);
    cube.voxel(ftxo, ftyo, ftzo + 1, 0);
    cube.voxel(ftxo, ftyo, ftzo - 1, 0);
    cube.voxel(ftxo + 1, ftyo, ftzo, 0);
    cube.voxel(ftxo - 1, ftyo, ftzo, 0);
    cube.voxel(ftxo, ftyo + 1, ftzo, 0);
    cube.voxel(ftxo, ftyo - 1, ftzo, 0);

    cube.voxel(ftx, fty, ftz, 1, rr);
    cube.voxel(ftx, fty, ftz + 1, rr);
    cube.voxel(ftx, fty, ftz - 1,  rr);
    cube.voxel(ftx + 1, fty, ftz, rr);
    cube.voxel(ftx - 1, fty, ftz, rr);
    cube.voxel(ftx, fty + 1, ftz, rr);
    cube.voxel(ftx, fty - 1, ftz, rr);

    cube.voxel(fx, fy, fz, 1, gg);
    cube.voxel(fx, fy, fz + 1, 1, gg);
    cube.voxel(fx, fy, fz - 1, 1, gg);
    cube.voxel(fx + 1, fy, fz, 1, gg);
    cube.voxel(fx - 1, fy, fz, 1, gg);
    cube.voxel(fx, fy + 1, fz, 1, gg);
    cube.voxel(fx, fy - 1, fz, 1, gg);


    cube.drawVoxels(true); // Draw the frame to the cube explicitly using vsync
    delay(drawDelay);

    fxo = fx;
    fyo = fy;
    fzo = fz;

    ftxo = ftx;
    ftyo = fty;
    ftzo = ftz;

    direct = random(3);
    if (direct == 0)
      fx = fx + fxm;
    if (direct == 1)
      fy = fy + fym;
    if (direct == 2)
      fz = fz + fzm;
    if (fx < 0) {
      fx = 0; fxm = 1;
    }
    if (fx > cubesize - 1) {
      fx = cubesize - 1; fxm = -1;
    }
    if (fy < 0) {
      fy = 0; fym = 1;
    }
    if (fy > cubesize - 1) {
      fy = cubesize - 1; fym = -1;
    }
    if (fz < 0) {
      fz = 0; fzm = 1;
    }
    if (fz > cubesize - 1) {
      fz = cubesize - 1; fzm = -1;
    }

    direct = random(3);
    if (direct == 0)
      ftx = ftx + ftxm;
    if (direct == 1)
      fty = fty + ftym;
    if (direct == 2)
      ftz = ftz + ftzm;
    if (ftx < 0) {
      ftx = 0; ftxm = 1;
    }
    if (ftx > cubesize - 1) {
      ftx = cubesize - 1; ftxm = -1;
    }
    if (fty < 0) {
      fty = 0; ftym = 1;
    }
    if (fty > cubesize - 1) {
      fty = cubesize - 1; ftym = -1;
    }
    if (ftz < 0) {
      ftz = 0; ftzm = 1;
    }
    if (ftz > cubesize - 1) {
      ftz = cubesize - 1; ftzm = -1;
    }
  }//while

  cube.clearAllVoxels();
}//wipeout







// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/* brightsincos parameters
  - time:                     Define the length of time that the animation should be executed.
  - cubeRef:                Define the instance of the 'LedCube' class that you made in your main program.
  - timeDelay (optional):     Define the delay (in ms) between each iteration of the rain drops falling down. Normally a value of
                    50 - 100 ms will suffice.
*/



void    brightsincos(float time, LedCube & cubeRef, unsigned int drawDelay)
{



  //  brightsincosVariables

  unsigned char z;
  unsigned char x;
  unsigned char y;
  const float period = 2 * cube.getCubeSize(); // Use the getter to retrieve the chosen cube size (1D) from the instance
  const float omega = (2.0 * PI) / period; // Calculate the radial frequency omega
  int cubesize = cube.getCubeSize();
  float offset = 0;

  //  brightsincosVariables

  // Timing variables
  unsigned long timestamp;


  long  startTime = millis();
  while (millis() - startTime < time)
  {
    ///////////////////


    for (  offset = 0; offset < 4 * PI; offset = offset +  0.08) {



      for ( byte x = 0; x < cubesize; x++) {
        for ( byte z = 0; z < cubesize; z++)
        {
          float      ipsilon = 100 * sin(z * omega + offset );   // * sin( x * omega + offset  );

          float     y   = map(ipsilon, -100, 100, 0, cubesize);

          float      br = 100 * sin( 2 * (z * omega + offset)  );
          br = map(br, -100, 100, 0, 15);
          cube.voxel(z, x, y, 1, br);
        }
      }
      cube.drawVoxels(true); // Draw the frame to the cube explicitly using vsync
      delay(drawDelay);
    }
    // Important! Update timestamp of last drawn frame

  }


  cube.clearAllVoxels();



}


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/* Rain parameters
  - time:                     Define the length of time that the animation should be executed.
  - cubeRef:                Define the instance of the 'LedCube' class that you made in your main program.
  - rainVoxels:               Define the number of voxels that should be drawn onto the top layer each iteration (rain density).
  - floorVoxels (optional):       With this value you can define how long a voxels should be remembered when hitting the last layer of
                    the cube. For example: make this value '5', whenever a voxel hits the last layer it will then stay lit
                    for another five iterations. Make this value '0' to turn this option off.
  - rainDelay (optional):     Define the delay (in ms) between each iteration of the rain drops falling down. Normally a value of
                    50 - 100 ms will suffice.
  - invertDirection (optional): With this value you can invert the direction which way the rain drops 'fall'.
*/




void rain(float time, LedCube & cubeRef, uint8_t rainVoxels /* = 2 */, uint8_t floorVoxels /* =4  */, uint16_t rainDelay /* = 75 */, bool invertDirection /* = false */)
{
  // Voxel arrays
  int8_t xVoxel[cubeRef.getCubeSize()][rainVoxels];
  int8_t yVoxel[cubeRef.getCubeSize()][rainVoxels];
  int8_t xVoxelFloor[floorVoxels][rainVoxels];
  int8_t yVoxelFloor[floorVoxels][rainVoxels];

  // Voxel coordinates
  uint8_t z;
  int8_t x;
  int8_t y;

  // For loop iterators
  uint8_t i;
  uint8_t j;

  // Other variables
  uint8_t maxVoxelValue = cubeRef.getCubeSize() - 1;

  // Initialize arrays with '-1' values to define a off state
  for (i = 0; i < cubeRef.getCubeSize(); i++)
  {
    for (j = 0; j < rainVoxels; j++)
    {
      xVoxel[i][j] = -1;
      yVoxel[i][j] = -1;
    }
  }
  for (i = 0; i < floorVoxels; i++)
  {
    for (j = 0; j < rainVoxels; j++)
    {
      xVoxelFloor[i][j] = -1;
      yVoxelFloor[i][j] = -1;
    }
  }

  long  startTime = millis();
  while (millis() - startTime < time)
  {
    // Shift floor array values to next item
    for (i = floorVoxels; i-- > 1;)
    {
      for (j = 0; j < rainVoxels; j++)
      {
        xVoxelFloor[i][j] = xVoxelFloor[i - 1][j];
        yVoxelFloor[i][j] = yVoxelFloor[i - 1][j];
      }
    }
    for (i = 0; i < rainVoxels; i++)
    {
      xVoxelFloor[0][i] = xVoxel[maxVoxelValue][i];
      yVoxelFloor[0][i] = yVoxel[maxVoxelValue][i];
    }

    // Shift rain array values to next item
    for (i = cubeRef.getCubeSize(); i-- > 1;)
    {
      for (j = 0; j < rainVoxels; j++)
      {
        xVoxel[i][j] = xVoxel[i - 1][j];
        yVoxel[i][j] = yVoxel[i - 1][j];
      }
    }

    // Calculate new voxels at first layer
    for (i = 0; i < rainVoxels; i++)
    {
      xVoxel[0][i] = random(cubeRef.getCubeSize());
      yVoxel[0][i] = random(cubeRef.getCubeSize());
    }

    // Display new rain voxel data
    for (i = 0; i < cubeRef.getCubeSize(); i++)
    {
      for (j = 0; j < rainVoxels; j++)
      {
        if (invertDirection)
          z = i;
        else
          z = maxVoxelValue - i;
        x = xVoxel[i][j];
        y = yVoxel[i][j];
        if (x != -1 && y != -1)
          cubeRef.voxel(z, x, y, 1);
      }
    }

    // Set z position outside loop so it's only calculated once
    if (invertDirection)
      z = maxVoxelValue;
    else
      z = 0;

    // Display new floor voxel data
    for (i = 0; i < floorVoxels; i++)
    {
      for (j = 0; j < rainVoxels; j++)
      {
        x = xVoxelFloor[i][j];
        y = yVoxelFloor[i][j];
        if (x != -1 && y != -1)
          cubeRef.voxel(z, x, y, 1);
      }
    }
    cubeRef.drawVoxels();
    delay(rainDelay);
  }
  cubeRef.clearAllVoxels();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/* Slanting lines parameters
  - time:                 Define the length of time that the animation should be executed.
  - cubeRef:                Define the instance of the 'LedCube' class that you made in your main program.
  - shiftDelay (optional):        Define the delay (in ms) between each iteration of shifting the lines to a new position. Normally a value of
                    50 - 100 ms will suffice.
  - invertDirection (optional): With this value you can invert the direction which way the slanting lines are rotating.
*/
void slantingLines(float time, LedCube & cubeRef, uint16_t shiftDelay /* = 75 */, bool invertDirection /* = false */)
{

  // Voxel arrays
  uint8_t xVoxel[cubeRef.getCubeSize()];
  uint8_t yVoxel[cubeRef.getCubeSize()];

  // Voxel coordinates
  uint8_t z;
  uint8_t x;
  uint8_t y;

  // For loop iterators
  uint8_t i;

  // Other variables
  uint8_t maxVoxelValue = cubeRef.getCubeSize() - 1;

  // Initialize arrays
  for (i = 0; i < cubeRef.getCubeSize(); i++)
  {
    xVoxel[i] = i;
    yVoxel[i] = 0;
  }

  long  startTime = millis();
  while (millis() - startTime < time)
  {
    // Display voxel data
    for (i = 0; i < cubeRef.getCubeSize(); i++)
    {
      // Normal line
      z = i;
      x = xVoxel[i];
      y = yVoxel[i];
      if (invertDirection)
        cubeRef.voxel(z, y, x, 1);
      else
        cubeRef.voxel(z, x, y, 1);

      // Opposite line
      z = maxVoxelValue - i;
      x = maxVoxelValue - xVoxel[maxVoxelValue - i];
      y = maxVoxelValue - yVoxel[maxVoxelValue - i];
      if (invertDirection)
        cubeRef.voxel(z, y, x, 1);
      else
        cubeRef.voxel(z, x, y, 1);
    }
    cubeRef.drawVoxels();

    // Calculate new voxels
    for (i = 0; i < cubeRef.getCubeSize(); i++)
    {
      if (xVoxel[i] < maxVoxelValue && yVoxel[i] == maxVoxelValue)
        xVoxel[i] += 1;
      else if (xVoxel[i] == maxVoxelValue && yVoxel[i] > 0)
        yVoxel[i] -= 1;
      else if (xVoxel[i] > 0 && yVoxel[i] == 0)
        xVoxel[i] -= 1;
      else if (xVoxel[i] == 0 && yVoxel[i] < maxVoxelValue)
        yVoxel[i] += 1;
    }
    delay(shiftDelay);
  }
  cubeRef.clearAllVoxels();
}


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* Corner cube parameters
  - time:                       Define the length of time that the animation should be executed.
  - cubeRef:                    Define the instance of the 'LedCube' class that you made in your main program.
  - resizeDelay (optional):       Define the delay (in ms) between each iteration of changing the cubes to a new size. Normally a value of
                        50 - 100 ms will suffice.
  - minimumCubeSize (optional):   Define the minimum size the cube will shrink to. Values smaller than '0' or bigger than the maximum cube size will be omitted.
*/
void cornerCube(float time, LedCube & cubeRef, uint16_t resizeDelay /* =75 */, uint8_t minimumCubeSize /* = 2 */)
{
  // Voxel offset
  uint8_t zOffset;
  uint8_t xOffset;
  uint8_t yOffset;

  // For loop iterators
  uint8_t i;
  uint8_t j;

  // Other variables
  uint8_t maxVoxelValue = cubeRef.getCubeSize() - 1;
  uint8_t cubeSize = cubeRef.getCubeSize() - 1;
  uint8_t cornerSelectBits;
  int8_t increment;
  uint8_t resizeCount;

  // Restrict input values
  if (minimumCubeSize == 0)
    resizeCount = (cubeRef.getCubeSize() - 2) * 2;
  else if (minimumCubeSize < cubeRef.getCubeSize())
    resizeCount = (cubeRef.getCubeSize() - minimumCubeSize) * 2;
  else
    resizeCount = (cubeRef.getCubeSize() - maxVoxelValue) * 2;

  long  startTime = millis();
  while (millis() - startTime < time)
  {
    increment = -1; // Shrink the cube
    uint8_t selectBits = random(8);
    while (selectBits == cornerSelectBits) {
      selectBits = random(8);
    }; // Ensure the new select bits do not equal the previous corner select bits.
    cornerSelectBits = selectBits;
    zOffset = 0;
    xOffset = 0;
    yOffset = 0;
    for (i = 0; i < resizeCount; i++)
    {
      for (j = 0; j <= cubeSize; j++)
      {
        // Lower layer
        cubeRef.voxel(0 + zOffset, 0 + xOffset, j + yOffset, 1);
        cubeRef.voxel(0 + zOffset, j + xOffset, 0 + yOffset, 1);
        cubeRef.voxel(0 + zOffset, cubeSize + xOffset, j + yOffset, 1);
        cubeRef.voxel(0 + zOffset, j + xOffset, cubeSize + yOffset, 1);

        // Upper layer
        cubeRef.voxel(cubeSize + zOffset, 0 + xOffset, j + yOffset, 1);
        cubeRef.voxel(cubeSize + zOffset, j + xOffset, 0 + yOffset, 1);
        cubeRef.voxel(cubeSize + zOffset, cubeSize + xOffset, j + yOffset, 1);
        cubeRef.voxel(cubeSize + zOffset, j + xOffset, cubeSize + yOffset, 1);

        // Inner layers
        cubeRef.voxel(j + zOffset, 0 + xOffset, 0 + yOffset, 1);
        cubeRef.voxel(j + zOffset, 0 + xOffset, cubeSize + yOffset, 1);
        cubeRef.voxel(j + zOffset, cubeSize + xOffset, 0 + yOffset, 1);
        cubeRef.voxel(j + zOffset, cubeSize + xOffset, cubeSize + yOffset, 1);
      }
      cubeRef.drawVoxels();
      delay(resizeDelay);

      // Make increment positive when cube is at its minimum selected size
      if (i == (resizeCount / 2))
        increment = 1;
      cubeSize += increment;

      // Calculate needed offset according to the corner select bits (LSB numbering)
      // bit 0: offset for z position
      // bit 1: offset for x position
      // bit 2: offset for y position
      // bit 3...7: not used
      zOffset = (maxVoxelValue - cubeSize) * (cornerSelectBits & 1); // Right shift not needed
      xOffset = (maxVoxelValue - cubeSize) * ((cornerSelectBits & 2) >> 1); // Right shift bit to use it as '1' or '0' multiplier
      yOffset = (maxVoxelValue - cubeSize) * ((cornerSelectBits & 4 ) >> 2);  // Right shift bit to use it as '1' or '0' multiplier
    }
  }
  cubeRef.clearAllVoxels();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/* Sine wave parameters
  - time:                 Define the length of time that the animation should be executed.
  - cubeRef:            Define the instance of the 'LedCube' class that you made in your main program.
  - shiftDelay (optional):    Define the delay (in ms) between each iteration of shifting the sine wave to a new position. Normally a value of
                  50 - 100 ms will suffice.
  - period (optional):    Period time of the sine wave. Normally a value of 2 times the cube size will suffice.
*/
void sineWave(float time, LedCube & cubeRef, uint16_t shiftDelay /* = 75 */, uint8_t period /* = 16 */)
{
  // Voxel coordinates
  uint8_t z;
  uint8_t x;
  uint8_t y;

  // For loop iterators
  uint16_t i;
  uint8_t j;

  // Other variables
  uint8_t timeCount = 0;
  float sineOffset = (cube.getCubeSize() - 1) / 2.0;
  float omega = (2.0 * PI) / (float)period;

  long  startTime = millis();
  while (millis() - startTime < time)
  {
    for (i = timeCount; i < (timeCount + cube.getCubeSize()); i++)
    {
      z = round(sineOffset * sin(i * omega) + sineOffset); // Calculate z position
      x = i - timeCount;
      for (j = 0; j < cube.getCubeSize(); j++)
      {
        y = j;
        cubeRef.voxel(z, x, y, 1);
      }
    }
    cubeRef.drawVoxels();
    delay(shiftDelay);
    timeCount++;
    if (timeCount >= period)
      timeCount = 0;
  }
  cubeRef.clearAllVoxels();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/* Sine wave two parameters
  - time:                 Define the length of time that the animation should be executed.
  - cubeRef:            Define the instance of the 'LedCube' class that you made in your main program.
  - shiftDelay (optional):    Define the delay (in ms) between each iteration of shifting the sine wave to a new position. Normally a value of
                  50 - 100 ms will suffice.
  - periodX (optional):     Period time of the x-axis sine wave . Normally a value of 2 times the cube size will suffice.
  - periodY (optional):     Period time of the y-axis sine wave . Normally a value of 2 times the cube size will suffice.
*/
void sineWaveTwo(float time, LedCube & cubeRef, uint16_t shiftDelay /* = 75 */, uint8_t periodX /* = 16 */,  uint8_t periodY /* = 16 */)
{
  // Voxel coordinates
  uint8_t z;
  uint8_t x;
  uint8_t y;

  // For loop iterators
  uint16_t i;
  uint16_t j;

  // Other variables
  uint8_t timeCountX = 0;
  uint8_t timeCountY = 0;
  float sineOffset = (cubeRef.getCubeSize() - 1) / 4.0;
  float omegaX = (2.0 * PI) / (float)periodX;
  float omegaY = (2.0 * PI) / (float)periodY;

  long  startTime = millis();
  while (millis() - startTime < time)
  {
    for (i = timeCountX; i < (timeCountX + cubeRef.getCubeSize()); i++)
    {
      x = i - timeCountX;
      for (j = timeCountY; j < (timeCountY + cubeRef.getCubeSize()); j++)
      {
        y = j - timeCountY;
        z = round(sineOffset * (sin(i * omegaX)  - sin(j * omegaY + PI)) + 2 * sineOffset); // Calculate z position
        cubeRef.voxel(z, x, y, 1);
      }
    }
    cubeRef.drawVoxels();
    delay(shiftDelay);
    timeCountX++;
    timeCountY++;
    if (timeCountX >= periodX)
      timeCountX = 0;
    if (timeCountY >= periodY)
      timeCountY = 0;
  }
  cubeRef.clearAllVoxels();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/* Sine wave three parameters
  - time:                           Define the length of time that the animation should be executed.
  - cubeRef:                      Define the instance of the 'LedCube' class that you made in your main program.
  - shiftDelay (optional):              Define the delay (in ms) between each iteration of shifting the sine wave to a new position. Normally a value of
                            50 - 100 ms will suffice.
  - period (optional):              Period time of the main sine wave . Normally a value of 2 times the cube size will suffice.
  - baseWavePeriodicFactor (optional):  A factor that represents how many times larger the period of the base (carrying wave) has to be compared to the main wave its period.
*/
void sineWaveThree(float time, LedCube & cubeRef, uint16_t shiftDelay /* = 75 */, uint8_t period /* = 16 */,  uint8_t baseWavePeriodicFactor /* = 4 */)
{
  // Voxel coordinates
  uint8_t z;
  uint8_t x;
  uint8_t y;

  // For loop iterators
  uint16_t i;
  uint8_t j;

  // Other variables
  float timeCount = 0;
  float sineOffset = (cubeRef.getCubeSize() - 1) / 4.0;
  float omegaAlpha = (2.0 * PI) / (float)period;
  float omegaBeta = (2.0 * PI) / ((float)period * baseWavePeriodicFactor);

  long  startTime = millis();
  while (millis() - startTime < time)
  {
    for (i = timeCount; i < (timeCount + cubeRef.getCubeSize()); i++)
    {
      x = i - timeCount;
      z = round(sineOffset * (sin(i * omegaAlpha) - sin(i * omegaBeta + PI)) + 2 * sineOffset); // Calculate z position
      for (j = 0; j < cubeRef.getCubeSize(); j++)
      {
        y = j;
        cubeRef.voxel(z, x, y, 1);
      }
    }
    cubeRef.drawVoxels();
    delay(shiftDelay);
    timeCount++;
    if (timeCount >= period * baseWavePeriodicFactor)
      timeCount = 0;
  }
  cubeRef.clearAllVoxels();
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/* sinx2y2 cube parameters
  - time:                 Define the length of time that the animation should be executed.
  - cubeRef:            Define the instance of the 'LedCube' class that you made in your main program.
  - shiftDelay (optional):    Define the delay (in ms) . Normally a value of
                  50 - 100 ms will suffice.
*/
void sinx2y2(float time, LedCube & cubeRef, uint16_t shiftDelay /* = 75 */)
{
  // Declare and initialize other variables needed for the animation
  float omega = (2.0 * PI) / (2 * cubeRef.getCubeSize()); // Calculate the radial frequency omega
  byte cubesize = cubeRef.getCubeSize();

  // Other variables


  long  startTime = millis();
  while (millis() - startTime < time)
  {
    ///////////////////


    for ( float offset = 0; offset < 4 * PI ; offset = offset +  0.18 ) {
      for ( byte x = 0; x < cubesize; x++) {
        for ( byte z = 0; z < cubesize; z++)
        {
          float      ipsilon = 10000 *  sin(offset + sqrt(pow(map(x, 0, cubesize - 1, -PI, PI), 2) + pow(map(z, 0, cubesize - 1, -PI, PI), 2)));
          // y=sin(z * omega + offset ) * cos( x * omega + offset  );
          float     y   = map(ipsilon, -10000, 10000, 0, cubesize);

          float      br = 10000 * sin(x * omega + offset / 0.55  );
          br = map(br, -10000, 10000, 1, 15);
          cubeRef.voxel(y, x, z, 1, br);
        }
      }
      cubeRef.drawVoxels();
      delay(shiftDelay);

    }

    ///////////////////////
  }
  cubeRef.clearAllVoxels();
}


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



/* RandomLedAnimator parameters
  - time:                 Define the length of time that the animation should be executed.
  - cubeRef:            Define the instance of the 'LedCube' class that you made in your main program.
  - numberOfVoxels:  Define the number of voxels that should be drawn each frame.
  - shiftDelay (optional):    Define the delay (in ms) . Normally a value of
                  50 - 100 ms will suffice.
*/

void RandomLedAnimator(float time, LedCube & cubeRef, unsigned char numberOfVoxels, unsigned int drawDelay)
{

  // Declare and initialize other variables needed for the animation
  // Voxel coordinates
  uint8_t z;
  uint8_t x;
  uint8_t y;
  uint8_t br;

  // Always set the timestamp to 0
  long  timestamp = 0;


  long startTime = millis();
  while (millis() - startTime < time)
  {
    ///////////////////


    if (millis() - timestamp > drawDelay) // Only draw the frame when the delay is elapsed, same as the Blink Without Delay example
    {
      for (unsigned char i = 0; i < numberOfVoxels; i++)
      {
        // Use the getter to retrieve the chosen cube size (1D) from the LedCube instance
        // Choose a random number (between 0 and maximum voxel value) for the z, x, y coordinates
        z = random(cubeRef.getCubeSize());
        x = random(cubeRef.getCubeSize());
        y = random(cubeRef.getCubeSize());
        br = random(15);
        cubeRef.voxel(z, x, y, 1, br); // Set a voxel brightness in the current frame with the random generated z, x, y coordinates
      }
      cubeRef.drawVoxels(true); // Draw the frame to the cube explicitly using vsync
      delay(drawDelay);
      // Important! Update timestamp of last drawn frame
      timestamp = millis();
    }

  }
  cubeRef.clearAllVoxels();
}
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------





void setup()
{
  //Start the cube
  cube.begin();
  randomSeed(analogRead(0));
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{

  starfield(animtime, cube, cube.getCubeSize() * 4, fps / 2 ); // animation time lenght, cube,number of stars, delay time
  plasma1(animtime * 2, cube); // animation time lenght, cube
  folder(animtime, cube, fps * 1 ); // animation time lenght, cube, delay time
  rain(animtime, cube , 4 , 3 , fps * 3 , true ); // animation time lenght, cube, rainVoxels; floorVoxels; rainDelay; invertDirection = false/true
  fireworks(animtime , cube, 1, 32, fps * 2); // animation time lenght, cube, delay time, iterations ???, number of particles, delay time **** 8x8x8 *** specific
  rain(animtime, cube , 2 , 4 , fps * 4 , true ); // animation time lenght, cube, rainVoxels; floorVoxels; rainDelay; invertDirection = false/true
  explodingsphere(animtime, cube, fps * 3); // animation time lenght, cube, delay time
  wipeout(animtime, cube, fps * 2); // animation time lenght, cube, delay time
  sinmess(animtime, cube, fps); // animation time lenght, cube, delay time
  sinpluscos(animtime, cube, fps * 2); // animation time lenght, cube, delay time
  sinx2y2nobr(animtime, cube, fps); // animation time lenght, cube, delay time
  sineWaveTwo(animtime, cube, fps * 2, 8, 2); // animation time lenght, cube, delay time,  periodX ; periodY
  sinx2y2(animtime, cube, fps); // animation time lenght, cube, delay time
  color_wheelTWO(animtime, cube, fps * 6); // animation time lenght, cube, delay time
  snake(animtime, cube, fps * 4, 16, 0); //animation time lenght, cube, delay time,snake lenght , collision modde **** 8x8x8 *** specific
  fireworks(animtime , cube, 1, 32, fps * 4); //animation time lenght, cube, delay time, iterations ???, number of particles, delay time **** 8x8x8 *** specific
  sineWaveTwo(animtime, cube, fps, 16, 16); // animation time lenght, cube, delay time,  periodX ; periodY
  luckyanim(animtime * 2, cube, fps ); // animation time lenght, cube, delay time
  sineWave(animtime, cube, fps, 4 * cube.getCubeSize()); // shiftDelay ; period = *4
  brightsincos(animtime, cube, fps * 4); // animation time lenght, cube, delay time
  sineWaveThree(animtime, cube, fps * 2, 16, 4); // animation time lenght, cube, delay time, period ; baseWavePeriodicFactor
  RandomLedAnimator(animtime, cube,  7,  fps * 4); // animation time lenght, cube, number of leds, delay time
  sineWaveTwo(animtime, cube, fps * 4, 16, 8); // animation time lenght, cube, delay time,  periodX ; periodY
  sineWaveThree(animtime, cube, fps * 2, 8, 2); // animation time lenght, cube, delay time, period ; baseWavePeriodicFactor
  cornerCube(animtime, cube, fps * 4, 1); // animation time lenght, cube, resizeDelay ; minimumCubeSize
  sineWave(animtime, cube, fps * 2, cube.getCubeSize() * 8 ); //cube, shiftDelay ; period = 8
  slantingLines(animtime, cube, fps * 4, true); // animation time lenght, cube, delay time, invertDirection = false/true
  sineWaveTwo(animtime, cube, fps * 2, 16, 16); // animation time lenght, cube, delay time,  periodX ; periodY
  sineWave(animtime, cube, fps * 2, 2 * cube.getCubeSize()); // shiftDelay ; period = 1
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


