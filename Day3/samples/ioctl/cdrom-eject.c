/* (cdrom-eject.c) Eject a CD-ROM
   How to Run: ./cdrom-eject /dev/hdc
 */

#include <fcntl.h>
#include <linux/cdrom.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  /* open a file descriptor to the device specified on the command line */
  int fd = open(argv[1], O_RDONLY);
  /* eject the CD-ROM */
  ioctl(fd, CDROMEJECT);
  /* close the file descriptor */
  close(fd);

  return 0;
}
