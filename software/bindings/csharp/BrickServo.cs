/*************************************************************
 * This file was automatically generated on 2011-09-20.      *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

namespace Tinkerforge
{
	public class BrickServo : Device 
	{
		private static byte TYPE_ENABLE = 1;
		private static byte TYPE_DISABLE = 2;
		private static byte TYPE_IS_ENABLED = 3;
		private static byte TYPE_SET_POSITION = 4;
		private static byte TYPE_GET_POSITION = 5;
		private static byte TYPE_GET_CURRENT_POSITION = 6;
		private static byte TYPE_SET_VELOCITY = 7;
		private static byte TYPE_GET_VELOCITY = 8;
		private static byte TYPE_GET_CURRENT_VELOCITY = 9;
		private static byte TYPE_SET_ACCELERATION = 10;
		private static byte TYPE_GET_ACCELERATION = 11;
		private static byte TYPE_SET_OUTPUT_VOLTAGE = 12;
		private static byte TYPE_GET_OUTPUT_VOLTAGE = 13;
		private static byte TYPE_SET_PULSE_WIDTH = 14;
		private static byte TYPE_GET_PULSE_WIDTH = 15;
		private static byte TYPE_SET_DEGREE = 16;
		private static byte TYPE_GET_DEGREE = 17;
		private static byte TYPE_SET_PERIOD = 18;
		private static byte TYPE_GET_PERIOD = 19;
		private static byte TYPE_GET_SERVO_CURRENT = 20;
		private static byte TYPE_GET_OVERALL_CURRENT = 21;
		private static byte TYPE_GET_STACK_INPUT_VOLTAGE = 22;
		private static byte TYPE_GET_EXTERNAL_INPUT_VOLTAGE = 23;
		private static byte TYPE_SET_MINIMUM_VOLTAGE = 24;
		private static byte TYPE_GET_MINIMUM_VOLTAGE = 25;
		private static byte TYPE_UNDER_VOLTAGE = 26;
		private static byte TYPE_POSITION_REACHED = 27;
		private static byte TYPE_VELOCITY_REACHED = 28;

		public delegate void UnderVoltage(ushort voltage);
		public delegate void PositionReached(byte servoNum, short position);
		public delegate void VelocityReached(byte servoNum, short velocity);

		public BrickServo(string uid) : base(uid) 
		{
			messageCallbacks[TYPE_UNDER_VOLTAGE] = new MessageCallback(CallbackUnderVoltage);
			messageCallbacks[TYPE_POSITION_REACHED] = new MessageCallback(CallbackPositionReached);
			messageCallbacks[TYPE_VELOCITY_REACHED] = new MessageCallback(CallbackVelocityReached);
		}

		public void Enable(byte servoNum)
		{
			byte[] data = new byte[5];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_ENABLE, 1, data);
			LEConverter.To((ushort)5, 2, data);
			LEConverter.To(servoNum, 4, data);

			ipcon.Write(this, data, TYPE_ENABLE, false);
		}

		public void Disable(byte servoNum)
		{
			byte[] data = new byte[5];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_DISABLE, 1, data);
			LEConverter.To((ushort)5, 2, data);
			LEConverter.To(servoNum, 4, data);

			ipcon.Write(this, data, TYPE_DISABLE, false);
		}

		public void IsEnabled(byte servoNum, out bool enabled)
		{
			byte[] data = new byte[5];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_IS_ENABLED, 1, data);
			LEConverter.To((ushort)5, 2, data);
			LEConverter.To(servoNum, 4, data);

			ipcon.Write(this, data, TYPE_IS_ENABLED, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for IsEnabled in time");
			}

			enabled = LEConverter.BoolFrom(4, answer);

			writeEvent.Set();
		}

		public void SetPosition(byte servoNum, short position)
		{
			byte[] data = new byte[7];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_POSITION, 1, data);
			LEConverter.To((ushort)7, 2, data);
			LEConverter.To(servoNum, 4, data);
			LEConverter.To(position, 5, data);

			ipcon.Write(this, data, TYPE_SET_POSITION, false);
		}

		public void GetPosition(byte servoNum, out short position)
		{
			byte[] data = new byte[5];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_POSITION, 1, data);
			LEConverter.To((ushort)5, 2, data);
			LEConverter.To(servoNum, 4, data);

			ipcon.Write(this, data, TYPE_GET_POSITION, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetPosition in time");
			}

			position = LEConverter.ShortFrom(4, answer);

			writeEvent.Set();
		}

		public void GetCurrentPosition(byte servoNum, out short position)
		{
			byte[] data = new byte[5];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_CURRENT_POSITION, 1, data);
			LEConverter.To((ushort)5, 2, data);
			LEConverter.To(servoNum, 4, data);

			ipcon.Write(this, data, TYPE_GET_CURRENT_POSITION, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetCurrentPosition in time");
			}

			position = LEConverter.ShortFrom(4, answer);

			writeEvent.Set();
		}

		public void SetVelocity(byte servoNum, ushort velocity)
		{
			byte[] data = new byte[7];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_VELOCITY, 1, data);
			LEConverter.To((ushort)7, 2, data);
			LEConverter.To(servoNum, 4, data);
			LEConverter.To(velocity, 5, data);

			ipcon.Write(this, data, TYPE_SET_VELOCITY, false);
		}

		public void GetVelocity(byte servoNum, out ushort velocity)
		{
			byte[] data = new byte[5];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_VELOCITY, 1, data);
			LEConverter.To((ushort)5, 2, data);
			LEConverter.To(servoNum, 4, data);

			ipcon.Write(this, data, TYPE_GET_VELOCITY, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetVelocity in time");
			}

			velocity = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void GetCurrentVelocity(byte servoNum, out ushort velocity)
		{
			byte[] data = new byte[5];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_CURRENT_VELOCITY, 1, data);
			LEConverter.To((ushort)5, 2, data);
			LEConverter.To(servoNum, 4, data);

			ipcon.Write(this, data, TYPE_GET_CURRENT_VELOCITY, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetCurrentVelocity in time");
			}

			velocity = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void SetAcceleration(byte servoNum, ushort acceleration)
		{
			byte[] data = new byte[7];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_ACCELERATION, 1, data);
			LEConverter.To((ushort)7, 2, data);
			LEConverter.To(servoNum, 4, data);
			LEConverter.To(acceleration, 5, data);

			ipcon.Write(this, data, TYPE_SET_ACCELERATION, false);
		}

		public void GetAcceleration(byte servoNum, out ushort acceleration)
		{
			byte[] data = new byte[5];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_ACCELERATION, 1, data);
			LEConverter.To((ushort)5, 2, data);
			LEConverter.To(servoNum, 4, data);

			ipcon.Write(this, data, TYPE_GET_ACCELERATION, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetAcceleration in time");
			}

			acceleration = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void SetOutputVoltage(ushort voltage)
		{
			byte[] data = new byte[6];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_OUTPUT_VOLTAGE, 1, data);
			LEConverter.To((ushort)6, 2, data);
			LEConverter.To(voltage, 4, data);

			ipcon.Write(this, data, TYPE_SET_OUTPUT_VOLTAGE, false);
		}

		public void GetOutputVoltage(out ushort voltage)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_OUTPUT_VOLTAGE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_OUTPUT_VOLTAGE, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetOutputVoltage in time");
			}

			voltage = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void SetPulseWidth(byte servoNum, ushort min, ushort max)
		{
			byte[] data = new byte[9];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_PULSE_WIDTH, 1, data);
			LEConverter.To((ushort)9, 2, data);
			LEConverter.To(servoNum, 4, data);
			LEConverter.To(min, 5, data);
			LEConverter.To(max, 7, data);

			ipcon.Write(this, data, TYPE_SET_PULSE_WIDTH, false);
		}

		public void GetPulseWidth(byte servoNum, out ushort min, out ushort max)
		{
			byte[] data = new byte[5];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_PULSE_WIDTH, 1, data);
			LEConverter.To((ushort)5, 2, data);
			LEConverter.To(servoNum, 4, data);

			ipcon.Write(this, data, TYPE_GET_PULSE_WIDTH, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetPulseWidth in time");
			}

			min = LEConverter.UShortFrom(4, answer);
			max = LEConverter.UShortFrom(6, answer);

			writeEvent.Set();
		}

		public void SetDegree(byte servoNum, short min, short max)
		{
			byte[] data = new byte[9];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_DEGREE, 1, data);
			LEConverter.To((ushort)9, 2, data);
			LEConverter.To(servoNum, 4, data);
			LEConverter.To(min, 5, data);
			LEConverter.To(max, 7, data);

			ipcon.Write(this, data, TYPE_SET_DEGREE, false);
		}

		public void GetDegree(byte servoNum, out short min, out short max)
		{
			byte[] data = new byte[5];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_DEGREE, 1, data);
			LEConverter.To((ushort)5, 2, data);
			LEConverter.To(servoNum, 4, data);

			ipcon.Write(this, data, TYPE_GET_DEGREE, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetDegree in time");
			}

			min = LEConverter.ShortFrom(4, answer);
			max = LEConverter.ShortFrom(6, answer);

			writeEvent.Set();
		}

		public void SetPeriod(byte servoNum, ushort period)
		{
			byte[] data = new byte[7];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_PERIOD, 1, data);
			LEConverter.To((ushort)7, 2, data);
			LEConverter.To(servoNum, 4, data);
			LEConverter.To(period, 5, data);

			ipcon.Write(this, data, TYPE_SET_PERIOD, false);
		}

		public void GetPeriod(byte servoNum, out ushort period)
		{
			byte[] data = new byte[5];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_PERIOD, 1, data);
			LEConverter.To((ushort)5, 2, data);
			LEConverter.To(servoNum, 4, data);

			ipcon.Write(this, data, TYPE_GET_PERIOD, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetPeriod in time");
			}

			period = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void GetServoCurrent(byte servoNum, out ushort current)
		{
			byte[] data = new byte[5];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_SERVO_CURRENT, 1, data);
			LEConverter.To((ushort)5, 2, data);
			LEConverter.To(servoNum, 4, data);

			ipcon.Write(this, data, TYPE_GET_SERVO_CURRENT, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetServoCurrent in time");
			}

			current = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void GetOverallCurrent(out ushort current)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_OVERALL_CURRENT, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_OVERALL_CURRENT, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetOverallCurrent in time");
			}

			current = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void GetStackInputVoltage(out ushort voltage)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_STACK_INPUT_VOLTAGE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_STACK_INPUT_VOLTAGE, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetStackInputVoltage in time");
			}

			voltage = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void GetExternalInputVoltage(out ushort voltage)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_EXTERNAL_INPUT_VOLTAGE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_EXTERNAL_INPUT_VOLTAGE, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetExternalInputVoltage in time");
			}

			voltage = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void SetMinimumVoltage(ushort voltage)
		{
			byte[] data = new byte[6];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_MINIMUM_VOLTAGE, 1, data);
			LEConverter.To((ushort)6, 2, data);
			LEConverter.To(voltage, 4, data);

			ipcon.Write(this, data, TYPE_SET_MINIMUM_VOLTAGE, false);
		}

		public void GetMinimumVoltage(out ushort voltage)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_MINIMUM_VOLTAGE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_MINIMUM_VOLTAGE, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetMinimumVoltage in time");
			}

			voltage = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public int CallbackUnderVoltage(byte[] data)
		{
			ushort voltage = LEConverter.UShortFrom(4, data);

			((UnderVoltage)callbacks[TYPE_UNDER_VOLTAGE])(voltage);
			return 6;
		}

		public int CallbackPositionReached(byte[] data)
		{
			byte servoNum = LEConverter.ByteFrom(4, data);
			short position = LEConverter.ShortFrom(5, data);

			((PositionReached)callbacks[TYPE_POSITION_REACHED])(servoNum, position);
			return 7;
		}

		public int CallbackVelocityReached(byte[] data)
		{
			byte servoNum = LEConverter.ByteFrom(4, data);
			short velocity = LEConverter.ShortFrom(5, data);

			((VelocityReached)callbacks[TYPE_VELOCITY_REACHED])(servoNum, velocity);
			return 7;
		}

		public void RegisterCallback(System.Delegate d)
		{
			if(d.GetType() == typeof(UnderVoltage))
			{
				callbacks[TYPE_UNDER_VOLTAGE] = d;
			}
			else if(d.GetType() == typeof(PositionReached))
			{
				callbacks[TYPE_POSITION_REACHED] = d;
			}
			else if(d.GetType() == typeof(VelocityReached))
			{
				callbacks[TYPE_VELOCITY_REACHED] = d;
			}
		}
	}
}
