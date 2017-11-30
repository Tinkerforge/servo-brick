Imports System
Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XXYYZZ" ' Change XXYYZZ to the UID of your Servo Brick

    ' Use position reached callback to swing back and forth
    Sub PositionReachedCB(ByVal sender As BrickServo, ByVal servoNum As Byte, _
                          ByVal position As Short)
        If position = 9000 Then
            Console.WriteLine("Position: 90°, going to -90°")
            sender.SetPosition(servoNum, -9000)
        Else If position = -9000 Then
            Console.WriteLine("Position: -90°, going to 90°")
            sender.SetPosition(servoNum, 9000)
        Else
            ' Can only happen if another program sets position
            Console.WriteLine("Error")
        End If
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim servo As New BrickServo(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Register position reached callback to subroutine PositionReachedCB
        AddHandler servo.PositionReachedCallback, AddressOf PositionReachedCB

        ' Enable position reached callback
        servo.EnablePositionReachedCallback()

        ' Set velocity to 100°/s. This has to be smaller or equal to the
        ' maximum velocity of the servo you are using, otherwise the position
        ' reached callback will be called too early
        servo.SetVelocity(0, 10000)
        servo.SetPosition(0, 9000)
        servo.Enable(0)

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        servo.Disable(0)
        ipcon.Disconnect()
    End Sub
End Module
