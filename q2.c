#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

long long int buffer_size =1000000;

int main(int argc, char *argv[])
{
	char c[100], b[] = "Assignment/" ;
	int i, j ;
	for( i = 0 ; b[i] != '\0' ; i++ ) 
	{
		c[i] = b[i];
	}

	for( j = 0 ; argv[1][j] != '\0' ; j++)
	{
		c[i] = argv[1][j] ;
		i++;
	}
	//
	printf("%s\n",c );
	symlink(c,"CreatedSymlink");

	struct stat checkSyslink ; 
	struct stat checkFolder ;
	struct stat checkFile ;

	int cS,cL,cF ;
	//
	char msg1[] = "Checking whether directory has been created :";
	write(2, msg1, sizeof(msg1)-1);
	cL = lstat("Assignment", &checkFolder)  ; 
	if (cL != 0)
		write(STDOUT_FILENO, "No", sizeof("No")-1);
	else
		write(STDOUT_FILENO, "Yes", sizeof("Yes")-1);
	//
	char msg2[] = "Checking whether file has been created :";
	write(2, msg2, sizeof(msg2)-1);
	int f1 = open(c, O_RDONLY), f2 ;
	if(f1 < 0)
	{
		printf("No\n");
	}
	else 
	 printf("Yes\n");
	//
	char msg3[] = "Checking whether symlink has been created :";
	write(2, msg3, sizeof(msg3)-1);
	cS = lstat("CreatedSymlink" , &checkSyslink) ; 
	if (cS != 0) 
		perror("No\n");
	else
		printf("Yes\n");
	//
	int flag = 0;
	char msg4[] = "Checking whether file contents have been created :";
	write(2, msg4, sizeof(msg4)-1);

	f2 = open(argv[2] , O_RDONLY) ; 

	long long int ret = lseek(f1,0,SEEK_END) ;

	long long int z =  ret ; 

	char file1[buffer_size] , file2[buffer_size], rev[buffer_size] ;

	while(ret>buffer_size)
	{	
		ret=lseek(f1, -buffer_size, SEEK_CUR);

		read(f1, file1, buffer_size); 
		read(f2, file2, buffer_size);

		for ( i=0 ; i<buffer_size; i++)
		{
			rev[buffer_size-1-i] = file1[i];
		}

		for ( i=0 ; i < buffer_size ; i++)
		{
			if (rev[i]>='A' && rev[i]<='Z')
				rev[i]+=32;
			else if(rev[i]>='a' && rev[i] <='z')
				rev[i]-=32;
		}

		for(i=0 ;i<buffer_size ;i++)
		{
			if(rev[i] != file2[i])
			{
				flag = 1; 
			}
		}

		ret=lseek(f1, -buffer_size, SEEK_CUR);

		if(ret < buffer_size)
		{
			break;
		}
	}


	long long p = z % buffer_size ;

	lseek(f1, 0, SEEK_SET);
	read(f1,file1,p);
	read(f2,file2,p);

	for ( i=0 ; i<p; ++i)
	{
		rev[p-1-i] = file1[i];
	}

	for ( i=0 ; i < p ; ++i)
	{
		if (rev[i]>='A' && rev[i]<='Z')
			rev[i]+=32;
		else if(rev[i]>='a' && rev[i] <='z')
			rev[i]-=32;
	}

	for(i=0 ;i<p ;++i)
	{
		if(rev[i] != file2[i])
		{
			flag = 1 ;
		}
	}	
	if (flag == 1)
		write(2, "No", sizeof("No")-1);
	else
		write(2, "Yes", sizeof("Yes")-1);
	//
	printf("FILE\n");
	printf("\nFile Permissions User\n");
	printf(access("Assignment/dump",R_OK) == 0 ? "r" :"-" );
	printf(access("Assignment/dump",X_OK) == 0 ? "x" :"-" );
	printf(access("Assignment/dump",W_OK) == 0 ? "w" :"-" );
	printf("\n");
	printf("\nFile Permissions Group\n");
	printf((checkFile.st_mode & S_IRGRP)? "r":"-");
	printf((checkFile.st_mode & S_IWGRP)? "w":"-");
	printf((checkFile.st_mode & S_IXGRP)? "x":"-");
	printf("\n");
	printf("\nFile Permissions Other\n");
	printf((checkFile.st_mode & S_IROTH)? "r":"-");
	printf((checkFile.st_mode & S_IWOTH)? "w":"-");
	printf((checkFile.st_mode & S_IXOTH)? "x":"-");
	printf("\n\n\n");

	printf("FOLDER\n");
	printf("\nFolder Permissions User\n");
	printf((checkFolder.st_mode & S_IRUSR)? "r":"-");
	printf((checkFolder.st_mode & S_IWUSR)? "w":"-");
	printf((checkFolder.st_mode & S_IXUSR)? "x":"-");
	printf("\nFolder Permissions Group\n");
	printf((checkFolder.st_mode & S_IRGRP)? "r":"-");
	printf((checkFolder.st_mode & S_IWGRP)? "w":"-");
	printf((checkFolder.st_mode & S_IXGRP)? "x":"-");
	printf("\n");
	printf("\nFolder Permissions Other\n");
	printf((checkFolder.st_mode & S_IROTH)? "r":"-");
	printf((checkFolder.st_mode & S_IWOTH)? "w":"-");
	printf((checkFolder.st_mode & S_IXOTH)? "x":"-");
	printf("\n");





	return 0;
}