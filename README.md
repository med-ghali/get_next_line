# get_next_line
A function that reads from an fd line by line.


char *get_next_line(int fd) :
 takes a file descriptor, and returns an allocated string representing the next line of the file pointed by the fd . in case of no line left it returns NULL ;
