#include "stdlib.h"
#include "fileutil.h"

// PURPOSE:
// Universal file loader: alloc space in uncached memory and load file
// Allocates 1 extra byte and terminates loaded data with a 0 if 'add0' == 1
// RETURN:
//  pointer to loaded file (0 if fail)
//      stat() size stored in st_size (-1 if no file)
//		read() size stored in rv_size (-1 if no file)
//          
//-------------------------------------------------------------------
static char* _load_file(const char* name, int* rv_size, int* st_size, int add0)
{
	int fd;
	int ssize = -1;     // stat() size
    int rsize = -1;     // # of bytes actually read
	char* buf = 0;      // memory buffer to return

    if (add0 != 0) add0 = 1; // Sanity check

	// get file stats
	struct stat st;
    if (stat(name,&st) == 0)
    {
        // get file size & check size is valid
		ssize = st.st_size;
	    if (ssize > 0)
        {
            // open file & check file is valid
	        fd = open( name, O_RDONLY, 0777 );
	        if (fd >= 0)
            {
                // allocate uncached buffer to read into & check valid
                char *ubuf = umalloc(512);
	            if (ubuf != 0)
                {
                    // allocate output buffer and check valid
                    // add 1 to file size if terminating 0 is required
    	            buf = malloc(ssize+add0);
                    if (buf != 0)
                    {
                        // loop over file reading in 512 bytes chunks
                        int lsize = 0;
                        rsize = 0;
                        while (lsize < ssize)
                        {
                            int len = ssize - lsize;
                            if (len > 512) len = 512;
                            rsize += read(fd, ubuf, len);
                            memcpy(buf+lsize,ubuf,len);
                            lsize += len;
                        }
                        if (add0) buf[ssize] = 0;
                    }
                    ufree(ubuf);
	            }
	            close(fd);
            }
        }
    }

    // save stat() size and read() size
    if (rv_size) *rv_size = rsize;
    if (st_size) *st_size = ssize;

	return buf;
}

// Use _load_file to read a file into memory
// Returns:
//      read() size in *rv_size
//      memory buffer allocated (caller must free buffer)
//-------------------------------------------------------------------
char* load_file(const char* name, int* rv_size, int add0)
{
	int rsize, ssize;

	char* buf = _load_file(name, &rsize, &ssize, add0);

    if (rv_size) *rv_size = rsize;

	if (rsize != ssize)
    {
        if (buf) free(buf);
        buf = 0;
        if (rv_size) *rv_size = -1;
    }

	return buf;
}

// PURPOSE:
// Universal file processor
// Load file, process by callback, unalloc/close file
// RETURN:
//	 Transfer return value from callback
// NOTE:
//	 Call callback even if fail to load/malloc (size=-1 if no file, size=0 if empty) 
//-------------------------------------------------------------------
int process_file(const char *filename, callback_process_file callback, int add0)
{
    int size;

    char *buf = load_file(filename, &size, add0);

	size = callback(buf, size);

	if (buf)
		free(buf);

	return size;
}

//-------------------------------------------------------------------

// PURPOSE: Load content to *value_p if file exist and contain number
// RETURN: 0-file_not_exist_or_failed (value is not changed), 1-ok

int load_int_value_file( const char* filename, int* value_p )
{
	char *buf;

	buf = load_file(filename, 0, 1);
	if (!buf)
	   return 0;
	
	if (value_p)	
		*value_p = strtol(buf, NULL, 10 /*dec*/);
	free(buf);

	return 1;
}

// PURPOSE: Save integer "value" to text file with name "filename"

void save_int_value_file( const char* filename, int value )
{
	char* buf = umalloc(20);
	if ( !buf )
		return;

	sprintf(buf,"%d", value);

	int fd = open( filename, O_WRONLY|O_CREAT|O_TRUNC, 0777);
	if (fd>=0) 
	{
		write(fd, buf, strlen(buf)+1);
		close(fd);
	} 
	ufree(buf);
}

//-------------------------------------------------------------------
