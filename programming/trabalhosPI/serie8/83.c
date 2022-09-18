#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<time.h>
#include<sys/stat.h>

void
help()
{

  printf("Este programa tem como objetivo simular a função ls do unix.\n");
  printf("Se desejar saber além do nome dos ficheiros do diretório,\n");
  printf("também o seu tamanho e a data da última modificação introduza\n");
  printf(" algo do tipo:\n");
  printf("./83 -l pasta1/pasta2\n");
  printf("Se só desejar o nome, introduza igual, mas sem o -l.\n");
  exit(0);
}


int 
main(int argc, char **argv)
{

  int x=0;
  time_t c1 ;
  DIR *d;
  struct dirent *dinfo;
  struct stat info_file;
  struct tm *time;
  char str[128], *name, *namerec;

  if (argc==1)
    {
      //ls na pasta em qe tá
      name=(char*)malloc(2*sizeof(char)+2);
      strcpy(name,".");

     
    }

  //-l
  else if(strcmp(argv[1],"-l")==0)
    {
      x=1;
      if(argc==2)
	{
	  name=(char*)malloc(2*sizeof(char)+3);
	  strcpy(name,".");
     
	  //ls - l na pasta em que tá
	}
      else if(argc==3)
	{
	  //ls -l na pasta argv[2]
	  name= (char*)malloc(strlen(argv[2])+3);
	  strcpy(name,argv[2]);

	  
	}
    }
  else if (argc==2)
    {
      //ls na pasta argv[1]
      name= (char*)malloc(strlen(argv[1])+3);
      strcpy(name,argv[1]);

	 
    }
  else
    {
      help();
    }

  //ls
  d = opendir(name);
  if(d==NULL)
    {    
      printf("Erro nao há essa pasta.\n");
      return 0;
    }
#if defined(_WIN32)
  strcat(name,"\\");
#else
  strcat(name,"/");
#endif

  while((dinfo = readdir(d)) != NULL)
    {      
      printf("Nome\n");
      printf(" %s\t\n", dinfo->d_name);
      if (x==1)
	{

#if defined(_WIN32)
	  namerec=(char*)malloc(strlen(name)+strlen(dinfo->d_name)+2);
	  strcpy(namerec,name);
	  strcat(namerec,dinfo->d_name);
	  stat(namerec, &info_file);
	  free(namerec);
#else
	  namerec=(char*)malloc(strlen(name)+strlen(dinfo->d_name)+2);
	  strcpy(namerec,name);
	  strcat(namerec,dinfo->d_name);
	  lstat(namerec, &info_file);
	  free(namerec);
#endif

	  printf("Tamanho    Última vez modificado: \n");
	  if ((info_file.st_size)==4096)
	    {
	      printf("%lu (folder) \t", info_file.st_size);
	    }
	  else
	    {
	      printf("%lu\t", info_file.st_size);
	    }
	  time=localtime(&info_file.st_mtime);
  
	  strftime(str, 128,"%d/%m/%y - %H:%M" ,time);
	  printf("    %s\t\n\n", str);
	}
 
    }
  
  closedir(d);
  free(name);
  return 0;

}
