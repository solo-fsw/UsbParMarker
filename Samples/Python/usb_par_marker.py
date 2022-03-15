
def send_command(ser_device, command):

    if ser_device.port == 'FAKECOM':
        decoded_data = 'ERROR: no data, FAKECOM used.'

    else:
        if type(command) == str:
            ser_device.write(command.encode()) 
            data = ser_device.readline()
            decoded_data = data.decode('utf-8')
        elif type(command) == int:
            ser_device.write(bytearray([command]))

    return decoded_data


# # Test code:
# import init_and_close_serial_device
# import time
#
# # Get device name:
# usb_par_mar = init_and_close_serial_device.init_serial_device('COM5', 4800)
# data = send_command(usb_par_mar, 'P')
# print('data' + data)
# init_and_close_serial_device.close_serial_device(usb_par_mar)
#
# # Send pulse:
# usb_par_mar = init_and_close_serial_device.init_serial_device('COM5', 115200)
# data = send_command(usb_par_mar, 255)
# time.sleep(2)
# data = send_command(usb_par_mar, 0)
# print('data' + data)
# init_and_close_serial_device.close_serial_device(usb_par_mar)


