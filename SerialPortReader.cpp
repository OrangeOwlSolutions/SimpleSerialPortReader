#include <stdio.h>      
#include <unistd.h>     
#include <fcntl.h>      
#include <errno.h>      
#include <termios.h>    
#include <iostream>

using namespace std;

int main()
{
	int  serial_port = open( "/dev/ttyACM0", O_RDWR| O_NOCTTY );
	fcntl(serial_port, F_SETFL, 0);

	/*Define the POSIX structure*/
	struct termios _serial_options;

	/*Read the attribute structure*/
	tcgetattr(serial_port, &serial_options);

	/*Set the baud rate of the port  to 9600*/
	cfsetispeed(&serial_options, B9600);
	cfsetospeed(&serial_options, B9600);
        	serial_options.c_cflag |= (CLOCAL | CREAD);

	/*Define other parameters in order to  realize the 8N1 standard*/
	serial_options.c_cflag &= ~PARENB;
	serial_options.c_cflag &= ~CSTOPB;
	serial_options.c_cflag &= ~CSIZE;
	serial_options.c_cflag |= CS8;
	
	/*Apply the new attributes */
	tcsetattr(serial_port, TCSANOW, &serial_options);


	/*Now, we read the first 100 line from the data stream, then we close the port */

	char buf[1000];

	for(int i=0; i<100;i++) {
		read( serial_port, &buf , VEOL);
		std::cout << "Read: " << buf << endl;
	}

	close(serial_port);
	return 0;

}
