/* nasty.c - flips right and left on the
 * VGA console --- "Arabic" display */
# include <stdio.h>
# include <string.h>
# include <sys/mman.h>
int main (int argc, char **argv) {
    FILE    *fh;
    short*  vid_addr, temp;
    int     x, y, ofs;
    fh = fopen ("/dev/mem", "r+");
    vid_addr = (short*) mmap (
        /* where to map to: don't mind */
        NULL,
        /* how many bytes ? */
        0x4000,
        /* want to read and write */
        PROT_READ | PROT_WRITE,
        /* no copy on write */
        MAP_SHARED,
        /* handle to /dev/mem */
        fileno (fh),
        /* hopefully the Text-buffer :-)*/
        0xB8000);
    if (vid_addr)
        for (y = 0; y < 100; y++)
            for (x = 0; x < 40; x++) {
                ofs = y*80;
                temp = vid_addr [ofs+x];
                vid_addr [ofs+x] =
                  vid_addr [ofs+79-x];
                vid_addr [ofs+79-x] = temp;
            }
    munmap (/*(caddr_t)*/ vid_addr, 0x4000);
    fclose (fh);
    return 0;
}
