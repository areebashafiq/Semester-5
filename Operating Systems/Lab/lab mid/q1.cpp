// Abdul Saboor
// 20L-1113
// BDS-5A1
// Question 1

// Note: You cannot use ifstream or ofstream library in this question in any way.
// Write a main program which creates four children. The following steps occur in the program:
// 1. The parent process first creates a file and writes data in it using the write system call and writes the
// data to a pipe. The input file can have any number of integers and special characters.
// The data is as follows: 11!17!21$6$89!43$67
// 2. Child 1 will then read the data from the file, remove special characters, and write the modified data to
// the same file again.
// 3. Child 2 will read the modified data from the file again using the read system call and arrange the
// integers in the ascending order. It will then write the modified arranged data to the same file again.
// 4 Child 3 will print the number of characters left after reading the data from the file and print them and
// write the data to another file named ‘final.txt’
// 5. After Child 3 has done its job, the parent will print “Task Completed” on the terminal.

