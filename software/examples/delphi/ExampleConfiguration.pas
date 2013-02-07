program ExampleConfiguration;

{$ifdef MSWINDOWS}{$apptype CONSOLE}{$endif}
{$ifdef FPC}{$mode OBJFPC}{$H+}{$endif}

uses
  SysUtils, IPConnection, BrickServo;

type
  TExample = class
  private
    ipcon: TIPConnection;
    servo: TBrickServo;
  public
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = '9eitci17HNS'; { Change to your UID }

var
  e: TExample;

procedure TExample.Execute;
begin
  { Create IP connection }
  ipcon := TIPConnection.Create;

  { Create device object }
  servo := TBrickServo.Create(UID, ipcon);

  { Connect to brickd }
  ipcon.Connect(HOST, PORT);
  { Don't use device before ipcon is connected }

  { Configure two servos with voltage 5.5V
    Servo 1: Connected to port 0, period of 19.5ms, pulse width of 1 to 2ms
             and operating angle -100 to 100°

    Servo 2: Connected to port 5, period of 20ms, pulse width of 0.95
             to 1.95ms and operating angle -90 to 90° }
  servo.SetOutputVoltage(5500);

  servo.SetDegree(0, -10000, 10000);
  servo.SetPulseWidth(0, 1000, 2000);
  servo.SetPeriod(0, 19500);
  servo.SetAcceleration(0, 1000); { Slow acceleration }
  servo.SetVelocity(0, $FFFF); { Full speed }

  servo.SetDegree(5, -9000, 9000);
  servo.SetPulseWidth(5, 950, 1950);
  servo.SetPeriod(5, 20000);
  servo.SetAcceleration(5, $FFFF); { Full acceleration }
  servo.SetVelocity(5, $FFFF); { Full speed }

  servo.SetPosition(0, 10000); { Set to most right position }
  servo.Enable(0);

  servo.SetPosition(5, -9000); { Set to most left position }
  servo.Enable(5);

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy; { Calls ipcon.Disconnect internally }
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
