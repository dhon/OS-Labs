The goal of this lab is to write a simple UNIX-like file system based on the topics
covered in class. Although you will implement a toy file system, you will learn about
many concepts used in real file systems. The file system you will write makes the
following simplifying assumptions:

The file system resides on a disk that is 128KB in size.
There is only one root directory. No subdirectories are allowed.
The file system supports a maximum of 16 files.
The maximum size of a file is 8 blocks; each block is 1KB in size.
Each file has a unique name, the file name can be no longer than 8 characters.
The layout of your 128 KB disk is as follows

The first 1KB block is called the super block.
It stores the free block list and index nodes (inode) for each file.
The remaining 127 1KB blocks store data blocks of the files on your file system.
The exact structure of the super block is as follows.
The first 128 bytes stores the free block list. Each entry in this list indicates
whether the corresponding block is free or in use (if the i-th byte is 0, it indicates
that the block is free, else it is in use). Intially all blocks except the super block are free.

Immediately following the free block list are the 16 index nodes, one for each file that is
allowed in the file system. Initially, all inode are free. Each inode stores the following information:
char name[8]; //file name
int size;     // file size (in number of blocks)
int blockPointers[8]; // direct block pointers
int used;             // 0 => inode is free; 1 => in use
Note that each inode is 48 bytes in size, since a char has size 1 and an int has size 4.
Together, all 16 inodes take up 768 bytes. Combining this with the free block list gives
us a total size of 896 bytes for the super block. The super block may not fill the 1 KB,
but start writing file blocks after 1KB into the disk.

You need to implement the following operations for your file system:

create(char name[8], int size): create a new file with this name and with these many blocks.
(For simplicity, we shall assume that the file size is specified at file creation time and the
file does not grow or shrink from this point on)

delete(char name[8]): delete the file with this name

read(char name[8], int blockNum, char buf[1024]): read the specified block from this file
into the specified buffer; blockNum can range from 0 to 7.

write(char name[8], int blockNum, char buf[1024]): write the data in the buffer to the
specified block in this file.

ls(void): list the names of all files in the file system and their sizes.