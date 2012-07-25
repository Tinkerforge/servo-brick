program ExampleCallback;

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
    procedure ReachedCB(const servoNum: byte; const position: smallint);
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = '9eitci17HNS';

var
  e: TExample;

{ Use position reached callback to swing back and forth }
procedure TExample.ReachedCB(const servoNum: byte; const position: smallint);
begin
  if (position = 9000) then begin
    WriteLn('Position: 90°, going to -90°');
    servo.SetPosition(servoNum, -9000);
  end
  else if (position = -9000) then begin
    WriteLn('Position: -90°, going to 90°');
    servo.SetPosition(servoNum, 9000);
  end
  else begin
    WriteLn('Error'); { Can only happen if another program sets position }
  end;
end;

procedure TExample.Execute;
begin
  { Create IP connection to brickd }
  ipcon := TIPConnection.Create(HOST, PORT);

  { Create device object }
  servo := TBrickServo.Create(UID);

  { Add device to IP connection }
  ipcon.AddDevice(servo);
  { Don't use device before it is added to a connection }

  { Register "position reached callback" to procedure ReachedCB.
    ReachedCB will be called every time a position set with
    SetPosition is reached }
  servo.OnPositionReached := {$ifdef FPC}@{$endif}ReachedCB;

  { Set velocity to 100°/s. This has to be smaller or equal to
    maximum velocity of the servo, otherwise cb_reached will be
    called to early. }
  servo.SetVelocity(0, 10000);
  servo.SetPosition(0, 9000);
  servo.Enable(0);

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy;
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
