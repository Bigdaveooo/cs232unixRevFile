//dab37 David Barry
//1/23/23
//Prof. Norman


#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int check_num_args(int argc, char *argv[]) {
	//checks if there aren't 3 arguments
	if (argc != 3) {
		perror("not corect amount of arguments\n");
		return(-1);
	}
	return(0);
}

int check_src_file_is_regular(char *argv) {
	//checks if the src file is a regular file
	struct stat path_stat;
	stat(argv, &path_stat);
	if (!S_ISREG(path_stat.st_mode)) {
		perror("src file is not a regular file\n");
		return(-1);
	}
	return(0);
}

int copy_src_to_dest(char *argv, char *argv1) {
	//checks if src file is copyable
	char c;
	FILE *srcF = fopen(argv, "r");
	FILE *destF = fopen(argv1, "w");
	//sets start point at end of src file
	fseek(srcF, -2, SEEK_END);
	int srcFLen = ftell(srcF);
	for (int filePos = srcFLen; filePos >= 0; filePos--) {
		fseek(srcF, filePos, SEEK_SET);
		fputc(fgetc(srcF), destF);
	}
	fclose(srcF);
	fclose(destF);
	return(0);
}

int main(int argc, char *argv[]) {
	/* These functions exit(-1) if there is a problem. */
	check_num_args(argc, argv);
	check_src_file_is_regular(argv[1]);
	copy_src_to_dest(argv[1], argv[2]);
	return 0;   /* no error */
}