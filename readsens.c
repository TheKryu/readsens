// --------------------------------------------------------
// read data from arduino sensors via usb, v0.01 16.10.2017
// --------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
//#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>

extern int errno;

int main(int argc, char *argv[])
{
  char buf[200];
  int file;
  int fr = 0;
  short qt = 0;

  if ( argc < 2 )
  {
    puts("usage: readusb DEVICE delay1 delay1 v(erbose)");
    exit(1);
  }

  if (argv[4][0] == 'v') qt = 1;

  if (qt)
  {
    puts("Read DATA from myArdSensors, V0.01");
    puts("----------------------------------");
    printf("trying to open %s\n", argv[1]);
  }

  file = open(argv[1], O_RDWR | O_NOCTTY | O_SYNC);

  if (!file)
  {
    printf("Error open file: %s\n", argv[1]);
    fprintf(stderr, "%s\n", strerror(errno));
    perror("cant open device");
    exit(1);
  }

  if (qt) puts("ok");

  for(int i = 0; i < 200; i++) buf[i] = 0x00;

  if (qt) printf("wait %s sec...\n", argv[2]);

  sleep(atoi(argv[2]));

  strcpy(buf, "get");

  if (qt) printf("write cmd %s\n", buf);

  write(file, buf, 3);

  if (errno)
  {
    printf("Error write to file: %s\n", argv[1]);
    fprintf(stderr, "%s\n", strerror(errno));
    perror("unable to write");
    close(file);
    exit(1);
  }

  sleep(atoi(argv[3]));

  fr = read(file, buf, 100);

  close(file);

  if (qt) printf("read %d bytes:\n%s\n", fr, buf);
  else printf("%s", buf);
}

