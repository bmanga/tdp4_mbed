#include "mbed.h"

DigitalOut trigger(p6);
DigitalOut myled(LED1); //monitor trigger
DigitalOut myled2(LED2); //monitor echo
DigitalIn  echo(p7);
Serial pc(USBTX, USBRX, 115200);
int distance = 0;
int correction = 0;
Timer sonar;
Timer global_timer;
InterruptIn warn (p15);

#if 0
int main()
{
    sonar.reset();
// measure actual software polling timer delays
// delay used later in time correction
// start timer
    sonar.start();
// min software polling delay to read echo pin
    while (echo==2) {};
    myled2 = 0;
// stop timer
    sonar.stop();
// read timer
    correction = sonar.read_us();
    pc.printf("Approximate software overhead timer delay is %d uS\n\r",correction);
 
//Loop to read Sonar distance values, scale, and print
    while(1) {
    	global_timer.start();
// trigger sonar to send a ping
        trigger = 1;
        myled = 1;
        myled2 = 0;
        sonar.reset();
        wait_us(10.0);
        trigger = 0;
        myled = 0;
//wait for echo high
        while (echo==0) {};
        myled2=echo;
//echo high, so start timer
        sonar.start();
//wait for echo low
        while (echo==1) {};
//stop timer and read value
        sonar.stop();
        global_timer.stop();
        pc.printf("time taken is %d\n", global_timer.read_us());
        global_timer.reset();
//subtract software overhead timer delay and scale to cm
        distance = (sonar.read_us()-correction)/58.0;
        myled2 = 0;
        pc.printf(" %d cm \n\r", distance);
//wait so that any echo(s) return before sending another ping
        wait(0.2);
    }
}

#else
void warn_collision()
{
	pc.printf("Warning: obstable at less than 10cm!\n");
}
Serial aux (p9,p10, 115200);
int main()
{
	warn.rise(&warn_collision);
	pc.printf("Hello world");
	while(true) {
		pc.putc(aux.getc());
	}
}
#endif