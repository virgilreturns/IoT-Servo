#include <Arduino.h>

/*

        Blackbox Design

            PID controller (in-house)
                100 Hz      targetVelocity  = runPID(PID_t* PositionController, int targetPosition)
                1 kHz       targetVoltage   = runPID(PID_t* VelocityController, int targetVelocity)
                Read/Write
                    string  getPIDParameters()

            Motor Driver (in-house)
                Motor.driveMotor(targetVoltage)
                    Direction Control
                    Active Braking
            Encoder (outsourced)
                Encoder.velocityRead()
                Encoder.positionRead()
            Commands
                Serial
                TTP
                Read/Write
                    Target Velocity
                    Target Position
                    Actual Velocity
                    Actual Position

            
    Task Design

        Task1
            MAX CLK     velocityRead()
                        positionRead()

            100 Hz      runPID(PID_t* PositionController ...)
            1   kHz     runPID(PID_t* VelocityController ...)

        Task2
            if (Serial.available() < 3) {
                vbTaskDelay(1000);
            }
            if (Serial.available() < 3) {
                msgbuf[0]   = Serial.read();
                msgbuf[1]   = Serial.read();
                msgbuf[2]   = Serial.read();

                msg.header  = msgbuf[0];
                msg.value   = msgbuf[1] | msgbuf[2] << 8;
            }
            
            if !(msg.header == 0 && msg.value == 0) {
                Command myCommand = cmds[msg.header];   // call command
                if(myCommand(msg.value) == SUCCESS) {
                msg.header  = 0;
                msg.value   = 0;
                };
            }

    Data Design

        struct  PID_t
                int   k_p
                int   k_i
                int   k_d
        struct  msg_t
                uint8_t header
                int value
        
        typedef int (*Command)(uint16_t value) // 
        
        static int cmds[256] = {
            [0x01] = SetTargetVelocity,
            [0x02] = SetTargetPosition,
            [0x03] = ...
        }

        static int targetVelocity //global params 
        static int targetPosition
        static bool SerialEncoderReadingEnabled
        #define SUCCESS 1


    Function Design
        
        // user cmds
        int SetTargetVelocity(uint16_t value) {
            targetVelocity = value; return SUCCESS}
        int SetTargetPosition() {
            targetPosition = value; return SUCCESS}
        int ToggleSerialEncoderReading() {
            SerialEncoderReadingEnabled = !SerialEncoderReadingEnabled; return SUCCESS}
        
        //abstracting functions
        Motor.driveMotor() {
            S
        }
        
*/

