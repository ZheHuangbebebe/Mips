// myls.c ... my very own "ls" implementation

#include <stdlib.h>
#include <stdio.h>
#include <bsd/string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAXDIRNAME 100
#define MAXFNAME   200
#define MAXNAME    20

char *rwxmode(mode_t, char *);
char *username(uid_t, char *);
char *groupname(gid_t, char *);

int main(int argc, char *argv[])
{
   // string buffers for various names
   char dirname[MAXDIRNAME];
   char uname[MAXNAME+1]; // UNCOMMENT this line
   char gname[MAXNAME+1]; // UNCOMMENT this line
   char mode[MAXNAME+1]; // UNCOMMENT this line

   // collect the directory name, with "." as default
   if (argc < 2)
      strlcpy(dirname, ".", MAXDIRNAME);
   else
      strlcpy(dirname, argv[1], MAXDIRNAME);

   // check that the name really is a directory
   struct stat info;
   if (stat(dirname, &info) < 0)
      { perror(argv[0]); exit(EXIT_FAILURE); }
   if ((info.st_mode & S_IFMT) != S_IFDIR)
      { fprintf(stderr, "%s: Not a directory\n",argv[0]); exit(EXIT_FAILURE); }

   // open the directory to start reading
    DIR *df; // UNCOMMENT this line
   // ... TODO ...
	df = opendir(dirname);
   // read directory entries
   struct dirent *entry; // UNCOMMENT this line
   // ... TODO ...
	char *buf;
   if (df != NULL) {
	while((entry=readdir(df))!= NULL)
	{
		buf = dirname;
		if(argc < 2)
		snprintf(buf, MAXDIRNAME, "%s/%s", ".", entry->d_name);
		else
		snprintf(buf, MAXDIRNAME, "%s/%s", argv[1], entry->d_name);
		//printf("%s\n",buf);
		if(lstat(buf,&info) < 0)continue;
		if(entry->d_name[0] == '.')continue;
		printf("%s  ",rwxmode(info.st_mode, mode));
		printf("%-8.8s ",username(info.st_uid, uname));
		printf("%-8.8s ",groupname(info.st_gid, gname));
		printf("%8lld  %s\n",(long long)info.st_size, entry->d_name);
	
	}
    closedir(df); // UNCOMMENT this line
   }
   // finish up
   return EXIT_SUCCESS;
}

// convert octal mode to -rwxrwxrwx string
char *rwxmode(mode_t mode, char *str)
{
	strmode(mode, str);
   return str;
   // ... TODO ...
}

// convert user id to user name
char *username(uid_t uid, char *name)
{
   struct passwd *uinfo = getpwuid(uid);
   if (uinfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)uid);
   else
      snprintf(name, MAXNAME, "%s", uinfo->pw_name);
   return name;
}

// convert group id to group name
char *groupname(gid_t gid, char *name)
{
   struct group *ginfo = getgrgid(gid);
   if (ginfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)gid);
   else
      snprintf(name, MAXNAME, "%s", ginfo->gr_name);
   return name;
}
