Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "6wywsn" ' Change to your UID

    ' Callback function for distance callback (parameter has unit mm)
    Sub ReachedCB(ByVal sender As BrickServo, ByVal servoNum As Byte, ByVal position As Short)
        If position = 9000 Then
            System.Console.WriteLine("Position: 90°, going to -90°")
            sender.SetPosition(servoNum, -9000)
        Else If position = -9000 Then
            System.Console.WriteLine("Position: -90°, going to 90°")
            sender.SetPosition(servoNum, 9000)
        Else
            ' Can only happen if another program sets position
            System.Console.WriteLine("Error")
        End If
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim servo As New BrickServo(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Register "position reached callback" to ReachedCB
        ' ReachedCB will be called every time a position set with
        ' SetPosition is reached
        AddHandler servo.PositionReached, AddressOf ReachedCB

        servo.EnablePositionReachedCallback()

        ' Set velocity to 100°/s. This has to be smaller or equal to
        ' maximum velocity of the servo, otherwise ReachedCB will be
        ' called too early
        servo.SetVelocity(0, 10000)
        servo.SetPosition(0, 9000)
        servo.Enable(0)

        System.Console.WriteLine("Press key to exit")
        System.Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
