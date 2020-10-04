#include <syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

long long int buffer_size= 1000000;

int main(int argc, char *argv[])
{	
	if (argc != 3)
	{
		write(2,"Enter 2 arguements",17);
		return 0 ;
	}

	int md = mkdir ("Assignment", S_IRWXU) ; 
	int fo = open(argv[1], O_RDONLY) ;
	int fw = open(argv[2], O_WRONLY|O_CREAT, 0670);	
	
	char c[100], b[] = "Assignment/" ;
	int i, j ;
	for( i = 0 ; b[i] != '\0' ; i++ ) 
	{
		c[i] = b[i];
	}

	for( j = 0 ; argv[2][j] != '\0' ; j++)
	{
		c[i] = argv[2][j] ;
		i++;
	}
 
	char arr1[buffer_size];
	char arr2[buffer_size]; 
	
	long long int ret = lseek(fo,0,SEEK_END) ;

	long long int z = (long long int) ret ; 

	int q;

	while(ret>buffer_size)
	{	
		ret=lseek(fo, -buffer_size, SEEK_CUR);

		read(fo, arr1, buffer_size);

		for ( i=0 ; i<buffer_size; ++i)
		{
			arr2[buffer_size-1-i] = arr1[i];
		}

		for ( i=0 ; i < buffer_size ; i++)
		{
			if (arr2[i]>='A' && arr2[i]<='Z')
				arr2[i]+=32;
			else if(arr2[i]>='a' && arr2[i] <='z')
				arr2[i]-=32;
		}

		write(fw,arr2,buffer_size);

		ret=lseek(fo, -buffer_size, SEEK_CUR);

		if(ret < buffer_size)
		{
			break;
		}
	}

	long long int k = z % buffer_size ;

	lseek(fo, 0, SEEK_SET);
	read(fo,arr1,k);

	for ( i=0 ; i<k; ++i)
	{
		arr2[k-1-i] = arr1[i];
	}

	for ( i=0 ; i < k ; ++i)
	{
		if (arr2[i]>='A' && arr2[i]<='Z')
			arr2[i]+=32;
		else if(arr2[i]>='a' && arr2[i] <='z')
			arr2[i]-=32;
	}

	
	write(fw,arr2,k);

	close(fo);
	close(fw);

	return 0;
}