/**
 ******************************************************************************
 * @file    main.cpp
 * @author  Davide Aliprandi, STMicroelectronics
 * @version V1.0.0
 * @date    November 4th, 2015
 * @brief   mbed test application for the STMicroelectronics X-NUCLEO-IHM02A1
 *          Motor Control Expansion Board: control of 2 motors.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */


/* Includes ------------------------------------------------------------------*/

/* mbed specific header files. */
#include "mbed.h"

/* Helper header files. */
#include "DevSPI.h"

/* Expansion Board specific header files. */
#include "x_nucleo_ihm02a1_class.h"


/* Definitions ---------------------------------------------------------------*/

/* Number of movements per revolution. */
#define MPR_1 4

/* Number of steps. */
#define STEPS_1 (400 * 128)   /* 1 revolution given a 400 steps motor configured at 1/128 microstep mode. */
#define STEPS_2 (STEPS_1 * 2)

/* Delay in milliseconds. */
#define DELAY_1 1000
#define DELAY_2 2000
#define DELAY_3 5000


/* Variables -----------------------------------------------------------------*/

/* Motor Control Expansion Board. */
X_NUCLEO_IHM02A1 *x_nucleo_ihm02a1;

/* Initialization parameters of the motors connected to the expansion board. */
L6470_Init_t init[L6470DAISYCHAINSIZE] =
{
    /* First Motor. */
    {
        9.0,                           /* Motor supply voltage in V. */
        400,                           /* Min number of steps per revolution for the motor. */
        1.7,                           /* Max motor phase voltage in A. */
        3.06,                          /* Max motor phase voltage in V. */
        300.0,                         /* Motor initial speed [step/s]. */
        500.0,                         /* Motor acceleration [step/s^2] (comment for infinite acceleration mode). */
        500.0,                         /* Motor deceleration [step/s^2] (comment for infinite deceleration mode). */
        992.0,                         /* Motor maximum speed [step/s]. */
        0.0,                           /* Motor minimum speed [step/s]. */
        602.7,                         /* Motor full-step speed threshold [step/s]. */
        3.06,                          /* Holding kval [V]. */
        3.06,                          /* Constant speed kval [V]. */
        3.06,                          /* Acceleration starting kval [V]. */
        3.06,                          /* Deceleration starting kval [V]. */
        61.52,                         /* Intersect speed for bemf compensation curve slope changing [step/s]. */
        392.1569e-6,                   /* Start slope [s/step]. */
        643.1372e-6,                   /* Acceleration final slope [s/step]. */
        643.1372e-6,                   /* Deceleration final slope [s/step]. */
        0,                             /* Thermal compensation factor (range [0, 15]). */
        3.06 * 1000 * 1.10,            /* Ocd threshold [ma] (range [375 ma, 6000 ma]). */
        3.06 * 1000 * 1.00,            /* Stall threshold [ma] (range [31.25 ma, 4000 ma]). */
        StepperMotor::STEP_MODE_1_128, /* Step mode selection. */
        0xFF,                          /* Alarm conditions enable. */
        0x2E88                         /* Ic configuration. */
    },

    /* Second Motor. */
    {
        9.0,                           /* Motor supply voltage in V. */
        400,                           /* Min number of steps per revolution for the motor. */
        1.7,                           /* Max motor phase voltage in A. */
        3.06,                          /* Max motor phase voltage in V. */
        300.0,                         /* Motor initial speed [step/s]. */
        500.0,                         /* Motor acceleration [step/s^2] (comment for infinite acceleration mode). */
        500.0,                         /* Motor deceleration [step/s^2] (comment for infinite deceleration mode). */
        992.0,                         /* Motor maximum speed [step/s]. */
        0.0,                           /* Motor minimum speed [step/s]. */
        602.7,                         /* Motor full-step speed threshold [step/s]. */
        3.06,                          /* Holding kval [V]. */
        3.06,                          /* Constant speed kval [V]. */
        3.06,                          /* Acceleration starting kval [V]. */
        3.06,                          /* Deceleration starting kval [V]. */
        61.52,                         /* Intersect speed for bemf compensation curve slope changing [step/s]. */
        392.1569e-6,                   /* Start slope [s/step]. */
        643.1372e-6,                   /* Acceleration final slope [s/step]. */
        643.1372e-6,                   /* Deceleration final slope [s/step]. */
        0,                             /* Thermal compensation factor (range [0, 15]). */
        3.06 * 1000 * 1.10,            /* Ocd threshold [ma] (range [375 ma, 6000 ma]). */
        3.06 * 1000 * 1.00,            /* Stall threshold [ma] (range [31.25 ma, 4000 ma]). */
        StepperMotor::STEP_MODE_1_128, /* Step mode selection. */
        0xFF,                          /* Alarm conditions enable. */
        0x2E88                         /* Ic configuration. */
    }
};


/* Main ----------------------------------------------------------------------*/

int main()
{
    /*----- Initialization. -----*/

    /* Initializing SPI bus. */
    DevSPI dev_spi(D11, D12, D3);

    /* Initializing Motor Control Expansion Board. */
    x_nucleo_ihm02a1 = new X_NUCLEO_IHM02A1(&init[0], &init[1], A4, A5, D4, A2, &dev_spi);

    /* Building a list of motor control components. */
    L6470 **motors = x_nucleo_ihm02a1->GetComponents();

    /* Printing to the console. */
    printf("Motor Control Application Example for 2 Motors\r\n\n");


    /*----- Setting home and marke positions, getting positions, and going to positions. -----*/

    /* Printing to the console. */
    printf("--> Setting home position.\r\n");

    /* Setting the home position. */
    motors[0]->SetHome();

    /* Waiting. */
    wait_ms(DELAY_1);

    /* Getting the current position. */
    int position = motors[0]->GetPosition();

    /* Printing to the console. */
    printf("--> Getting the current position: %d\r\n", position);

    /* Waiting. */
    wait_ms(DELAY_1);

    /* Printing to the console. */
    printf("--> Moving forward %d steps.\r\n", STEPS_1);

    /* Moving. */
    motors[0]->Move(StepperMotor::FWD, STEPS_1);

    /* Waiting while active. */
    motors[0]->WaitWhileActive();

    /* Getting the current position. */
    position = motors[0]->GetPosition();
    
    /* Printing to the console. */
    printf("--> Getting the current position: %d\r\n", position);

    /* Printing to the console. */
    printf("--> Marking the current position.\r\n");

    /* Marking the current position. */
    motors[0]->SetMark();

    /* Waiting. */
    wait_ms(DELAY_1);

    /* Printing to the console. */
    printf("--> Moving backward %d steps.\r\n", STEPS_2);

    /* Moving. */
    motors[0]->Move(StepperMotor::BWD, STEPS_2);

    /* Waiting while active. */
    motors[0]->WaitWhileActive();

    /* Waiting. */
    wait_ms(DELAY_1);

    /* Getting the current position. */
    position = motors[0]->GetPosition();
    
    /* Printing to the console. */
    printf("--> Getting the current position: %d\r\n", position);

    /* Waiting. */
    wait_ms(DELAY_1);

    /* Printing to the console. */
    printf("--> Going to marked position.\r\n");

    /* Going to marked position. */
    motors[0]->GoMark();
    
    /* Waiting while active. */
    motors[0]->WaitWhileActive();

    /* Waiting. */
    wait_ms(DELAY_1);

    /* Getting the current position. */
    position = motors[0]->GetPosition();
    
    /* Printing to the console. */
    printf("--> Getting the current position: %d\r\n", position);

    /* Waiting. */
    wait_ms(DELAY_1);

    /* Printing to the console. */
    printf("--> Going to home position.\r\n");

    /* Going to home position. */
    motors[0]->GoHome();
    
    /* Waiting while active. */
    motors[0]->WaitWhileActive();

    /* Waiting. */
    wait_ms(DELAY_1);

    /* Getting the current position. */
    position = motors[0]->GetPosition();
    
    /* Printing to the console. */
    printf("--> Getting the current position: %d\r\n", position);

    /* Waiting. */
    wait_ms(DELAY_1);

    /* Printing to the console. */
    printf("--> Halving the microsteps.\r\n");

    /* Halving the microsteps. */
    init[0].step_sel = (init[0].step_sel > 0 ? init[0].step_sel -  1 : init[0].step_sel);
    if (!motors[0]->SetStepMode((StepperMotor::step_mode_t) init[0].step_sel))
        printf("    Step Mode not allowed.\r\n");

    /* Waiting. */
    wait_ms(DELAY_1);

    /* Printing to the console. */
    printf("--> Setting home position.\r\n");

    /* Setting the home position. */
    motors[0]->SetHome();

    /* Waiting. */
    wait_ms(DELAY_1);

    /* Getting the current position. */
    position = motors[0]->GetPosition();
    
    /* Printing to the console. */
    printf("--> Getting the current position: %d\r\n", position);

    /* Waiting. */
    wait_ms(DELAY_1);

    /* Printing to the console. */
    printf("--> Moving forward %d steps.\r\n", STEPS_1);

    /* Moving. */
    motors[0]->Move(StepperMotor::FWD, STEPS_1);

    /* Waiting while active. */
    motors[0]->WaitWhileActive();

    /* Getting the current position. */
    position = motors[0]->GetPosition();
    
    /* Printing to the console. */
    printf("--> Getting the current position: %d\r\n", position);

    /* Printing to the console. */
    printf("--> Marking the current position.\r\n");

    /* Marking the current position. */
    motors[0]->SetMark();

    /* Waiting. */
    wait_ms(DELAY_2);


    /*----- Running together for a certain amount of time. -----*/

    /* Printing to the console. */
    printf("--> Running together for %d seconds.\r\n", DELAY_3 / 1000);

    /* Preparing each motor to perform a run at a specified speed. */
    for (int m = 0; m < L6470DAISYCHAINSIZE; m++)
        motors[m]->PrepareRun(StepperMotor::BWD, 400);

    /* Performing the action on each motor at the same time. */
    x_nucleo_ihm02a1->PerformPreparedActions();

    /* Waiting. */
    wait_ms(DELAY_3);


    /*----- Increasing the speed while running. -----*/

    /* Preparing each motor to perform a run at a specified speed. */
    for (int m = 0; m < L6470DAISYCHAINSIZE; m++)
        motors[m]->PrepareGetSpeed();

    /* Performing the action on each motor at the same time. */
    uint32_t* results = x_nucleo_ihm02a1->PerformPreparedActions();

    /* Printing to the console. */
    printf("    Speed: M1 %d, M2 %d.\r\n", results[0], results[1]);

    /* Printing to the console. */
    printf("--> Doublig the speed while running again for %d seconds.\r\n", DELAY_3 / 1000);

    /* Preparing each motor to perform a run at a specified speed. */
    for (int m = 0; m < L6470DAISYCHAINSIZE; m++)
        motors[m]->PrepareRun(StepperMotor::BWD, results[m] << 1);

    /* Performing the action on each motor at the same time. */
    results = x_nucleo_ihm02a1->PerformPreparedActions();

    /* Waiting. */
    wait_ms(DELAY_3);

    /* Preparing each motor to perform a run at a specified speed. */
    for (int m = 0; m < L6470DAISYCHAINSIZE; m++)
        motors[m]->PrepareGetSpeed();

    /* Performing the action on each motor at the same time. */
    results = x_nucleo_ihm02a1->PerformPreparedActions();

    /* Printing to the console. */
    printf("    Speed: M1 %d, M2 %d.\r\n", results[0], results[1]);

    /* Waiting. */
    wait_ms(DELAY_1);


    /*----- Hard Stop. -----*/

    /* Printing to the console. */
    printf("--> Hard Stop.\r\n");

    /* Preparing each motor to perform a hard stop. */
    for (int m = 0; m < L6470DAISYCHAINSIZE; m++)
        motors[m]->PrepareHardStop();

    /* Performing the action on each motor at the same time. */
    x_nucleo_ihm02a1->PerformPreparedActions();

    /* Waiting. */
    wait_ms(DELAY_2);


    /*----- Doing a full revolution on each motor, one after the other. -----*/

    /* Printing to the console. */
    printf("--> Doing a full revolution on each motor, one after the other.\r\n");

    /* Doing a full revolution on each motor, one after the other. */
    for (int m = 0; m < L6470DAISYCHAINSIZE; m++)
        for (int i = 0; i < MPR_1; i++)
        {
            /* Computing the number of steps. */
            int steps = (int) (((int) init[m].fullstepsperrevolution * pow(2.0f, init[m].step_sel)) / MPR_1);

            /* Moving. */
            motors[m]->Move(StepperMotor::FWD, steps);
            
            /* Waiting while active. */
            motors[m]->WaitWhileActive();

            /* Waiting. */
            wait_ms(DELAY_1);
        }

    /* Waiting. */
    wait_ms(DELAY_2);


    /*----- High Impedance State. -----*/

    /* Printing to the console. */
    printf("--> High Impedance State.\r\n");

    /* Preparing each motor to set High Impedance State. */
    for (int m = 0; m < L6470DAISYCHAINSIZE; m++)
        motors[m]->PrepareHardHiZ();

    /* Performing the action on each motor at the same time. */
    x_nucleo_ihm02a1->PerformPreparedActions();

    /* Waiting. */
    wait_ms(DELAY_2);
}