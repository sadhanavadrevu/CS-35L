#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void sig_handler() {
  fprintf(stderr, "Segmentation fault\n");
  exit(4); //4 is error code for segfault
}

void seg_fault() {
  char* ptr = NULL;
  *ptr = 'a';
}

int main(int argc, char *argv[]) {
  
  int stdin = 0; // 0 if read from stdin, 1 if read from file
  int stdout = 0; // 0 if write to stdout, 1 if write to file
  char* uInput = "";
  char* uOutputFile = "";
  int segfault = 0; // 0 if off, 1 if on
  int catch = 0; // 0 if off, 1 if on

  int opt;
  static struct option long_options[] = //options for getopt
    {
     {"input", 1, 0, 'i'},
     {"output", 1, 0, 'o'},
     {"segfault", 0, 0, 's'},
     {"catch", 0, 0, 'c'}
    };

  int opt_index = 0;

  opt = getopt_long(argc, argv, "i:o:sc", long_options, &opt_index);
  opterr = 0;
  while(opt != -1) {

    switch (opt)
      {
      case 'i': 
	stdin = 1;
	uInput = optarg;
	break;
	
      case 'o':
	stdout = 1;
	uOutputFile = optarg;
	break;

      case 's':
	segfault = 1;
	break;

      case 'c':
	catch = 1;
	break;

      case '?':
	fprintf(stderr, "Invalid option: %s.\n Valid options are:\n\t--input=[filename]\n\t--output=[filename]\n\t--segfault\n\t--catch\n", argv[opt_index+1]);
	exit(1);
	break;
	
      default:
	break;
      }

    opt = getopt_long(argc, argv, "i:o:sc", long_options, &opt_index);

  }

  if (stdin == 1) { //if read from file
    int ifd = open(uInput, O_RDONLY);
    if (ifd >= 0) { //make input file stdin
      close(0);
      dup(ifd);
      close(ifd);
    }
    else {
      fprintf(stderr, "Error: --input option failed because of requested file: %s.\n%s\n", uInput, strerror(errno));
      exit(2);
    }
  }
  if (stdout == 1) { //if write to file
    int ofd = creat(uOutputFile, 0666);
    if (ofd >= 0) { //make output file stdout
      close(1);
      dup(ofd);
      close(ofd);
    }
    else {
      fprintf(stderr, "Error: --output option could not access requested file '%s'.\n%s\n", uOutputFile, strerror(errno));
      exit(3);
    }
  }

  if (catch == 1) {
    signal(SIGSEGV, sig_handler);
  }
  
  if (segfault == 1) {
    seg_fault();
  }

  int bytes_read;
  do {
    char buffer[10];
    bytes_read = read(0, buffer, 10);
    write(1, buffer, bytes_read);
  } while (bytes_read == 10);

  exit(0);
}
