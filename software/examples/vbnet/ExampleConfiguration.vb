Imports Tinkerforge

Module ExampleConfiguration
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "6wywsn" ' Change to your UID

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim servo As New BrickServo(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Configure two servos with voltage 5.5V
        ' Servo 1: Connected to port 0, period of 19.5ms, pulse width of 1 to 2ms
        '          and operating angle -100 to 100°
        '
        ' Servo 2: Connected to port 5, period of 20ms, pulse width of 0.95
        '          to 1.95ms and operating angle -90 to 90°
        servo.SetOutputVoltage(5500)

        servo.SetDegree(0, -10000, 10000)
        servo.SetPulseWidth(0, 1000, 2000)
        servo.SetPeriod(0, 19500)
        servo.SetAcceleration(0, 1000) ' Slow acceleration
        servo.SetVelocity(0, &HFFFF) ' Full speed

        servo.SetDegree(5, -9000, 9000)
        servo.SetPulseWidth(5, 950, 1950)
        servo.SetPeriod(5, 20000)
        servo.SetAcceleration(5, &HFFFF) ' Full acceleration
        servo.SetVelocity(5, &HFFFF) ' Full speed

        servo.SetPosition(0, 10000) ' Set to most right position
        servo.Enable(0)

        servo.SetPosition(5, -9000) ' Set to most left position
        servo.Enable(5)

        System.Console.WriteLine("Press key to exit")
        System.Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
