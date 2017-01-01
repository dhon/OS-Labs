#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

// block size = 1KB
#define block_size 1024

// global vars for fast create+delete
int files;
int space;

struct idxNode{ // structure for the inode
	char name[8]; // file name
	int size;    // file size (in number of blocks)
	int blockPointers[8]; // direct block pointers
	int used;            // 0 => inode is free; 1 => in use
};

class myFileSystem{
private:
	fstream disk;
public:

	myFileSystem(char diskName[16]){
	// open the file with the above name
	// this file will act as the "disk" for your file system
		disk.open(diskName); // open disk
		space = 127; // available space
		files = 0; // number of stored files
	}

	int create_file(char name[8], int size){ 
	// create a file with this name and this size
	// high level pseudo code for creating a new file

	// Step 1: check to see if we have sufficient free space on disk by
	// reading in the free block list. To do this:
	// move the file pointer to the start of the disk file.
	// Read the first 128 bytes (the free/in-use block information)
	// Scan the list to make sure you have sufficient free blocks to
	// allocate a new file of this size

		if(size < 1 || size > 8) // input size error
			return -1;
		if(files == 16) // already max files
			return -1;
		if(size > space) // not enough space
			return -1;

		files++; // new file, add 1
		space -= size; // used space, minus by size

		char blocks[128]; // block information
		char fblocks[size]; // free block information
		disk.seekg(0, ios::beg); // pointer to start
		disk.read(blocks, 128); // read first 128 bytes

		int x = 0; // fblocks index counter
		for(int i = 0; i < 128; i++){ // loop over blocks
			if(blocks[i] == 0){ // if free block
				fblocks[x] = i; // add index location to fblocks
				x++; // used index, add 1
				if(x == size) // found enough fblocks
					break; // exit for
			}
		}

	// Step 2: we look	for a free inode om disk
	// Read in a inode
	// check the "used" field to see if it is free
	// If not, repeat the above two steps until you find a free inode
	// Set the "used" field to 1
	// Copy the filename to the "name" field
	// Copy the file size (in units of blocks) to the "size" field

		idxNode node; // node
		char buf[48]; // buffer
		int n; // index location
		for(int i = 0; i < 16; i++){ // loop over idxNodes
			disk.seekg(128 + i*48, ios::beg); // pointer to idxNode
			disk.read(buf, 48); // read idxNode to buffer
			memcpy(&node, &buf, sizeof(node)); // copy buffer to node
			if(node.used == 0){ // if unused node
				node.used = 1; // set used
				node.size = size; // set size
				strncpy(node.name, name, 8); // set name
				n = i; // store index
				break; // exit for
			}
		}

	// Step 3: Allocate data blocks to the file
	// for(i=0;i<size;i++)
	  // Scan the block list that you read in Step 1 for a free block
	  // Once you find a free block, mark it as in-use (Set it to 1)
	  // Set the blockPointer[i] field in the inode to this block number.
	  // 
	// end for

		for(int i = 0; i < size; i++){ // update loop
			blocks[fblocks[i]] = 1; // set newly used blocks as used
			node.blockPointers[i] = fblocks[i]; // set blockpointers
		}

	// Step 4: Write out the inode and free block list to disk
	// Move the file pointer to the start of the file 
	// Write out the 128 byte free block list
	// Move the file pointer to the position on disk where this inode was stored
	// Write out the inode

		disk.seekg(0, ios::beg); // pointer to start
		disk.write(blocks, 128); // write updated blocks
		memcpy(&buf, &node, sizeof(node)); // copy node to buffer
		disk.seekg(128 + n*48, ios::beg); // pointer to newly used idxNode
		disk.write(buf, 48); // write updated node
		return 1;

	} // End Create


	int delete_file(char name[8]){
	// Delete the file with this name

	// Step 1: Locate the inode for this file
	// Move the file pointer to the 1st inode (129th byte)
	// Read in an inode
	// If the inode is free, repeat above step.
	// If the inode is in use, check if the "name" field in the
	//   inode matches the file we want to delete. If not, read the next
	//   inode and repeat

		// if(files == 0) // no files to delete
		//	return -1;
		// if(space == 127) // already at max free space
		//	return -1;

		idxNode node; // node
		char buf[48]; // buffer
		char blocks[128]; // block information
		bool exists = false; // remove variable
		int n; // index location
		for(int i = 0; i < 16; i++){ // loop over idxNodes
			disk.seekg(128 + i*48, ios::beg); // pointer to idxNode
			disk.read(buf, 48); // read idxNode to buffer
			memcpy(&node, &buf, sizeof(node)); // copy buffer to node
			if(strcmp(name, node.name) == 0 && node.used == 1){ // if found node
				exists = true; // it exists, set true
				n = i; // store index
				break; // exit for
			}
		}

	// Step 2: free blocks of the file being deleted
	// Read in the 128 byte free block list (move file pointer to start
	//	 of the disk and read in 128 bytes)
	// Free each block listed in the blockPointer fields as follows:
	// for(i=0;i< inode.size; i++) 
		// freeblockList[ inode.blockPointer[i] ] = 0;

		// Done in Step 4

	// Step 3: mark inode as free
	// Set the "used" field to 0.
	  // if(exists == false)
	  //  return -1;

		if(exists == false) // if not exists cannot delete
			return -1;

	// Step 4: Write out the inode and free block list to disk
	// Move the file pointer to the start of the file 
	// Write out the 128 byte free block list
	// Move the file pointer to the position on disk where this inode was stored
	// Write out the inode

		files--; // deleted file, minus 1
		space += node.size; // freed space, add by size
		node.used = 0; // set unused
		disk.seekg(0, ios::beg); // pointer to start
		disk.read(blocks,128); // read first 128 bytes
		for(int i = 0; i < node.size; i++) // update loop
			blocks[node.blockPointers[i]] = 0; // set blocks unused
		disk.seekg(0, ios::beg); // pointer to start
		disk.write(blocks, 128); // write updated blocks
		memcpy(&buf, &node, sizeof(node)); // copy node to buffer
		disk.seekg(128 + n*48, ios::beg); // pointer to newly freed idxNode
		disk.write(buf, 48); // write updated node
		return 1;

	} // End Delete


	int ls(void){ 
	// List names of all files on disk

	// Step 1: read in each inode and print!
	// Move file pointer to the position of the 1st inode (129th byte)
	// for(i=0;i<16;i++)
	  // REad in a inode
	  // If the inode is in-use
	    // print to list.txt the "name" and "size" fields from the inode
	// end for

		idxNode node; // node
		char buf[48]; // buffer
		ofstream myfile; // file
		myfile.open("list.txt"); // open file
		for(int i = 0; i < 16; i++){ // loop over idxNodes
			disk.seekg(128 + i*48, ios::beg); // pointer to idxNode
			disk.read(buf, 48); // read idxNode to buffer
			memcpy(&node, &buf, sizeof(node)); // copy buffer to node
			if(node.used == 1) // if node is used
				myfile << node.name << " " << node.size << "\n"; // output
		}
		myfile.close(); // close file
		return 1;

	} // End ls

	int read(char name[8], int blockNum, char buff[1024]){
	// read this block from this file

	// Step 1: locate the inode for this file
	// Move file pointer to the position of the 1st inode (129th byte)
	// Read in an inode
	// If the inode is in use, compare the "name" field with the above file
	// If the file names don't match, repeat

	// Step 2: Read in the specified block
	// Check that blockNum < inode.size, else flag an error
	// Get the disk address of the specified block
	// That is, addr = inode.blockPointer[blockNum]
	// Move the file pointer to the block location (i.e., to byte #
	//   addr*1024 in the file)

	// Read in the block => Read in 1024 bytes from this location
	//   into the buffer "buff"

		idxNode node; // node
		char buf[48]; // buffer
		for(int i = 0; i < 16; i++){ // loop over idxNodes
			disk.seekg(128 + i*48, ios::beg); // pointer to idxNode
			disk.read(buf, 48); // read idxNode to buffer
			memcpy(&node, &buf, sizeof(node)); // copy buffer to node
			if(strcmp(name, node.name) == 0 && node.used == 1){ // if found node
				if(blockNum < node.size){ // check for error
					int addr = node.blockPointers[blockNum]; // get disk address
					disk.seekg(addr*1024, ios::beg); // pointer to block location
					disk.read(buff, 1024); // read location into buffer
					return 1;
				}else // error found
					return -1;
			}
		}
		return -1;

	} // End read


	int write(char name[8], int blockNum, char buff[1024]){
	// write this block to this file

	// Step 1: locate the inode for this file
	// Move file pointer to the position of the 1st inode (129th byte)
	// Read in a inode
	// If the inode is in use, compare the "name" field with the above file
	// If the file names don't match, repeat

	// Step 2: Write to the specified block
	// Check that blockNum < inode.size, else flag an error
	// Get the disk address of the specified block
	// That is, addr = inode.blockPointer[blockNum]
	// Move the file pointer to the block location (i.e., byte # addr*1024)

	// Write the block! => Write 1024 bytes from the buffer "buff" to 
	//   this location

		// Same as read
		idxNode node; // node
		char buf[48]; // buffer
		for(int i = 0; i < 16; i++){ // loop over idxNodes
			disk.seekg(128 + i*48, ios::beg); // pointer to idxNode
			disk.read(buf, 48); // read idxNode to buffer
			memcpy(&node, &buf, sizeof(node)); // copy buffer to node
			if(strcmp(name, node.name) == 0 && node.used == 1){ // if found node
				if(blockNum < node.size){ // check for error
					int addr = node.blockPointers[blockNum]; // get disk address
					disk.seekg(addr*1024, ios::beg); // pointer to block location
					disk.write(buff, 1024); // write buffer into location
					return 1;
				}else // error found
					return -1;
			}
		}
		return -1;

	} // end write

	int close_disk(){
	// close the file(disk) opened in the constructor
	// this is to check the persistency of file system
		disk.close(); // close disk
		return 1;
	}

};