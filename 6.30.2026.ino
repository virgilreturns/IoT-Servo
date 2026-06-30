#include <Arduino.h>

/*


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

            
    Task Structure

        Task1
            MAX CLK     velocityRead()
                        positionRead()

            100 Hz      runPID(PID_t* PositionController ...)
            1   kHz     runPID(PID_t* VelocityController ...)

        Task2
            readSerial(command_t* CommandBuffer)
            




*/

