/*
	Command Prompt using C++ with 15 CMD functions.To perform operations.
    Copyright (C) 2013  Shashank Chavan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.*/
    
/***************************************************************************
*  						Command Prompt Using C++       			           *
*   						by Shashank Chavan                             *
*                                                                          *
*  	  For queries,suggestion feel free to go at my site or e-mail me.      *
*                                                                          *
*     http://www.pcosmos.com/open-source-command-prompt-cpp-project	       *
*     					chavanshashank@outlook.com                         *
*                       	www.fb.com/cshas                               *
***************************************************************************/

#include "fstream.h"
#include "string.h"
#include "process.h"
#include "conio.h"
#include "iomanip.h"
#include "dir.h"
#include "dirent.h"
#include "stdio.h"
#define MAX 225
//#define MAXPATH 1000

//using namespace std;

char *memory=NULL;

class CMD               //class of CMD
{               		
	//Pvt data mem
	char dir[MAXPATH];
	char file[MAX];
	char dirtemp[MAXPATH];
  	char dirtemp2[MAXPATH];
	long double size; //long double var for copying n pasting

public:	
	//public mem fn
	void cd(char string[]);	//fns receving strings
	void cdn(char string[]);        
	void ChangeDir(char dir[]);
	void CleanUp();
	void Copy(char string[]);
	void Dir();
	void Delete(char string[]);		
	void Help(char string[]);
	void MakeDir(char string[]);
	void Move(char string[]);
	void Paste();
	void Rename(char string[]);
	void RemoveDir(char string[]);
	void ShowDir();
	void Type(char string[]);
};
void CMD::cd(char string[MAX])
{	
    getcwd(dir,MAXPATH);		//getting current working dir with MAXPATH
    int j=0,n,d;
    
    for(int c=0;c<(signed)strlen(string);c++) //counting dots for "cd" command
	{
       if(string[c]=='.')
        j++;
	}
    if(j%2==0)		//changing the directory as count of dots 
    {
        n=j/2;
        for(int i=n;i>0;i--)
        {
            strrev(dir);
            while(dir[j]!='\\')
            {
                dir[j];
                j++;
            }
 
            strrev(dir);

            for(d=(strlen(dir)-j);d<(signed)strlen(dir);d++)
            {
                dir[d]='\0';
            }
        }

        chdir(dir);		//changing the directory

    }
    else
        Help("cd..");	//calling to the Help fn
}
void CMD::cdn(char string[MAX])
{
	if(!strcmp("",string))		//if string is displaying incorrect syntax
	{
		cout<<endl<<"The syntax of the command is incorrect."<<endl;
		cout<<"Use \"HELP CD\" for the command help."<<endl;
		return;
	}
	getcwd(dir,MAXPATH);
	strcat(dir,"\\");
	strcat(dir,string);
	if (chdir(dir))     //changing directory
    {
        cout<<endl<<"The system can not find the specified path."<<endl;
        return;
    }
}
void CMD::ChangeDir(char dir[MAX])   //change directory fn
{
	if(!strcmp("",dir))		//if string is displaying incorrect syntax
	{
		cout<<endl<<"The syntax of the command is incorrect."<<endl;
		cout<<"Use \"HELP CHANGEDIR\" for the command help."<<endl;
		return;
	}
 
    if (chdir(dir))     //changing directory
    {
        cout<<endl<<"The system can not find the specified path."<<endl;
        return;
    }
  
}
void CMD::CleanUp()
{
        char dirn[MAXPATH]="\0";	
 		char dirn2[MAXPATH]="\0";
    	DIR *dirt=NULL;		
    	DIR *dirt2=NULL;
    	DIR *dirt3=NULL;
    	struct dirent *drnt=NULL;	
    	char *str="C:\\Users\\";	
        
        getcwd(dir,MAXPATH);
        strcpy(dirtemp,dir);	//copying current directory to return after oprn
        chdir(str);
        
        getcwd(dirn,MAXPATH);
        dirt=opendir(dirn);		//opening the dir
        if(dirt)
        {
                while((drnt=readdir(dirt))!=NULL)
                {
                	//by substring, accessing the only users of PC excluding other folders
                    if(!(strcmp(drnt->d_name,".") && strcmp(drnt->d_name,"..") && strcmp(drnt->d_name,"Public")&& strcmp(drnt->d_name,"Default User") && strcmp(drnt->d_name,"All Users") && strcmp(drnt->d_name,"Default")))
                    {
                    	continue;
                    }
                        strcat(str,drnt->d_name);	
                        strcat(str,"\\AppData\\Local\\Temp"); 
                        strcpy(dirn,str);
						if(chdir(str))
                        {
                        	strcpy(str,"C:\\Users\\");	
                        	continue;
                        }
                        cout<<endl<<"Cleaning up..... Please Wait....."<<endl;
                        
                        getcwd(dirtemp2,MAXPATH); 
						strcpy(dir,dirtemp2);
						dirt2=opendir(dir);		
						while((drnt=readdir(dirt2))!=NULL)
						{
        					if(!(strcmp(".",drnt->d_name) && strcmp("..",drnt->d_name)))
							{
								continue;		
							}
							strcat(dir,"\\");
        					strcat(dir,drnt->d_name);		

        					if(chdir(dir))		
        					{
								remove(drnt->d_name);	
								strcpy(dir,dirtemp2);
								strcat(dir,"\\");	
            					continue;	
        					}
							strcpy(file,drnt->d_name);	
        					getcwd(dirn2,MAXPATH);
        					dirt3=opendir(dirn2);
        					while((drnt=readdir(dirt3))!=NULL)
        					{
       		 					rmdir(drnt->d_name);	//removing the dirs
       		     				remove(drnt->d_name);	//removing the files
							}
							closedir(dirt3);	
        		    		cd("..");		
							rmdir(file);	
							

						}
                        closedir(dirt2);
                        
                        strcpy(str,"C:\\Users\\");
                        
                }
		//To cleanup following path you need to run your compiler as admin. so "Run As Administartor".
		char *dirtemp="C:\\Windows\\Temp\\";	//cleaning up temp path with same process as above
		DIR *dirt2=NULL;
        strcpy(dir,dirtemp);
        dirt3=opendir(dir);
        while((drnt=readdir(dirt3))!=NULL)
        {
        		if(!(strcmp(".",drnt->d_name) && strcmp("..",drnt->d_name)))
				{
					continue;
				}
        		strcat(dir,drnt->d_name);

        		if(chdir(dir))
        		{
        			remove(drnt->d_name);
        			strcpy(dir,"C:\\Windows\\Temp\\");
            		continue;
        		}
				strcpy(dirtemp2,drnt->d_name);
        		getcwd(dirn,MAXPATH);
        		dirt2=opendir(dirn);
        		while((drnt=readdir(dirt2))!=NULL)
        		{
        			rmdir(drnt->d_name);
            		remove(drnt->d_name);
        		}
            	cd("..");
            	rmdir(dirtemp2);
            	closedir(dirt2);

			}
			closedir(dirt3);

			cout<<endl<<"System is Cleaned Up Successfully.! ;)"<<endl;

        }
        else
        {
                cout<<endl<<"Can not open directory '%s'\n"<<dirn<<endl;
        }
        closedir(dirt);
        chdir(dirtemp);

}
void CMD::Copy(char string[MAX])
{
	if(!strcmp("",string))		//if string is displaying incorrect syntax
	{
		  	cout<<endl<<"The syntax of the command is incorrect."<<endl;
		  	cout<<"Use \"HELP COPY\" for the command help."<<endl;
		  	return;
	}
	ifstream fin2(string,ios::noreplace);
	fin2.close();
	if(!fin2)
	{
		cout<<endl<<"File does not exist."<<endl;
		return;
	}
	strcpy(file,string);
  	ifstream fin (file, ios::in|ios::binary|ios::ate);	//opening in binary read mode at the end

  	if (fin)
  	{
    	cout<<endl<<"Please Wait.. Copying File.."<<endl;
    	size = fin.tellg();
    	memory = new char [size];	//allocating size as returned from tellg
    	fin.seekg (0, ios::beg);	//seeking
    	fin.read (memory, size);	//reading and allocating
    	fin.close();

    	cout <<endl<< "The file is Copied."<<endl;

  	}
  	else 
		cout << endl<<"Unable to open file.";
}
void CMD::Delete(char string[MAX])  //string recve
{
	if(!strcmp("",string))		//if string is displaying incorrect syntax
	{
	  		cout<<endl<<"The syntax of the command is incorrect."<<endl;
		  	cout<<"Use \"HELP DELETE\" for the command help."<<endl;
		  	return;
	}
	ifstream fin2(string,ios::noreplace);
	fin2.close();
	if(!fin2)
	{
		cout<<endl<<"File does not exist."<<endl;
		return;
	}
    if (!remove(string))    //removing file
        cout<<endl<<"File Removed "<<string<<endl;
    else
        cout<<endl<<"File is Not removed!"<<endl;

}
void CMD::Dir()
{
	getcwd(dir,MAXPATH);	//current directory
	cout<<endl<<dir<<">";
}
void CMD::Help(char string[])	//help function using formatting manipulator setw and string cmprs
{
	cout<<endl;
    if(!strcmp("cd",string))
    {
        cout<<"CD\t"<<setw(60)<<"Changes the directory available in current directory."<<endl;
        cout<<"\nCD [DIR NAME]\n\nCD shas"<<endl;
        return;
    }
    else
    if(!strcmp("cd..",string))
    {
        cout<<"CD..\t"<<setw(42)<<"Changes directory to backward directory."<<endl;
        cout<<"\ncd.."<<endl;
        return;
    }
    else
    if(!strcmp("changedir",string))
    {
        cout<<"CHANGEDIR\t"<<setw(25)<<"Changes the current directory."<<endl;
        cout<<"\nchangedir [dir path]\n\nchangedir c:\\tc\\bin\\shas"<<endl;
        return;
    }
    else
    if(!strcmp("cleanup",string))
    {
        cout<<"CLEANUP\t"<<setw(49)<<"Cleans up the junk files from Windows7, Windows8."<<endl;
        cout<<"\ncleanup"<<endl;
        cout<<setw(0)<<"\n\nFor best result of Cleanup.Run CMD as Administrator."<<endl;
        return;
    }
    else
    if(!strcmp("clear",string))
    {
        cout<<"CLEAR\t"<<setw(38)<<"Clears the ouput on the screen"<<endl;
        cout<<"\nclear"<<endl;
        return;
    }
    else
    if(!strcmp("copy",string))
    {
        cout<<"COPY\t"<<setw(44)<<"Copies the file to another location."<<endl;
        cout<<"\ncopy [filename]\n\ncopy shas.exe"<<endl;
        cout<<setw(0)<<"\n\nIf you want to choose a specific directory then"<<endl;
        cout<<setw(0)<<"First change directory to source directory.\n";
        cout<<setw(0)<<"Then copy the specific File."<<endl;
        return;
    }
    else
    if(!strcmp("delete",string))
    {
        cout<<"DELETE\t"<<setw(25)<<"Deletes the file."<<endl;
        cout<<"\ndelete [filename]\n\ndelete shas.exe"<<endl;
        return;
    }
    else
    if(!strcmp("exit",string))
    {
        cout<<"EXIT\t"<<setw(29)<<"Exits from the S OS."<<endl;
        return;
    }
    else
    if(!strcmp("help",string))
    {
        cout<<"HELP\t"<<setw(47)<<"Provides help information for commands."<<endl;
        cout<<"\nhelp [command]\n\ncommand-displays help info on that command"<<endl;
        return;
    }
    else
    if(!strcmp("makedir",string))
    {
        cout<<"MAKEDIR\t"<<setw(30)<<"Creates the directory."<<endl;
        cout<<"\nmakedir [dir name]\n\nmakedir shas"<<endl;
        return;
    }
    else
    if(!strcmp("move",string))
    {
        cout<<"MOVE\t"<<setw(44)<<"Moves the files to another location."<<endl;
        cout<<"\nmove [filename]\n\nmove shas.obj"<<endl;
        cout<<setw(0)<<"\n\nIf you want to choose a specific directory then"<<endl;
        cout<<setw(0)<<"First change directory to source directory.\n";
        cout<<setw(0)<<"Then manipulate the specific File."<<endl;
        return;
    }
    else
    if(!strcmp("paste",string))
    {
        cout<<"PASTE\t"<<setw(51)<<"Pastes the copied file to another location."<<endl;
        cout<<"\npaste [file should be copied.]"<<endl;
        cout<<setw(0)<<"\n\nIf you want to choose a specific directory then"<<endl;
        cout<<setw(0)<<"First change directory to source directory.\n";
        cout<<setw(0)<<"Then paste the Copies File."<<endl;
        return;
    }
    else
    if(!strcmp("rename",string))
    {
        cout<<"RENAME\t"<<setw(26)<<"Renames the files."<<endl;
        cout<<"\nrename [oldfilename]\n\nrename shas.cpp"<<endl;
        return;
    }
    else
    if(!strcmp("removedir",string))
    {
        cout<<"REMOVEDIR\t"<<setw(22)<<"Removes the directory."<<endl;
        cout<<"\nremove [directory name]\n\nremove shas"<<endl;
        return;
    }
    else
    if(!strcmp("showdir",string))
    {
        cout<<"SHOWDIR\t"<<setw(35)<<"Shows the directory and files in current path."<<endl;
        return;
    }
    else
    if(!strcmp("type",string))
    {
    	cout<<"TYPE\t"<<setw(45)<<"Displays the contents of a text file."<<endl;
    	cout<<"\ntype [filename]\n\ntype cmds.cpp"<<endl;
    	return;
    }
    else
    if((strcmp("",string)||strcmp("\0",string)))
    {
        cout<<"This \'"<<string<<"\' command is not supported by help utility"<<endl;
        cout<<"Available commands are :\n"<<endl;
        //return;
    }

    cout<<"CD\t"<<setw(60)<<"Changes the directory available in current directory"<<endl;
	cout<<"CD..\t"<<setw(42)<<"Changes directory to backward one."<<endl;
	cout<<"CHANGEDIR\t"<<setw(25)<<"Changes the current directory."<<endl;
	cout<<"CLEANUP\t"<<setw(49)<<"Cleans up the temporary files from WinPC."<<endl;
	cout<<"CLEAR\t"<<setw(38)<<"Clears the ouput on the screen"<<endl;
	cout<<"COPY\t"<<setw(44)<<"Copies the file to another location."<<endl;
	cout<<"DELETE\t"<<setw(25)<<"Deletes the file."<<endl;
	cout<<"EXIT\t"<<setw(28)<<"Exits from the S OS."<<endl;
	cout<<"HELP\t"<<setw(47)<<"Provides help information for commands."<<endl;
	cout<<"MAKEDIR\t"<<setw(30)<<"Creates the directory."<<endl;
	cout<<"MOVE\t"<<setw(44)<<"Moves the files to another location."<<endl;
	cout<<"PASTE\t"<<setw(51)<<"Pastes the copied file to another location."<<endl;
	cout<<"RENAME\t"<<setw(26)<<"Renames the files."<<endl;
	cout<<"REMOVEDIR\t"<<setw(22)<<"Removes the directory."<<endl;
	cout<<"SHOWDIR\t"<<setw(35)<<"Shows the current directory"<<endl;
	cout<<"TYPE\t"<<setw(45)<<"Displays the contents of a text file."<<endl;
	cout<<endl<<setw(0)<<"To know more about commands use: HELP [command name]\n\nHELP COPY\n"<<endl;
}
void CMD::MakeDir(char string[])
{
	if(!strcmp("",string))		//if string is displaying incorrect syntax
	{
		cout<<endl<<"The syntax of the command is incorrect."<<endl;
 		cout<<"Use \"HELP MAKEDIR\" for the command help."<<endl;
  		return;
	}
    if(!mkdir(string))	//making dir
    {
        cout<<endl<<"\""<<string<<"\" directory is created."<<endl;
    }
    else
    {
        cout<<endl<<"Unable to create Directory."<<endl;
    }

}
void CMD::Move(char string[])
{
	if(!strcmp("",string))		//if string is displaying incorrect syntax
	{
		cout<<endl<<"The syntax of the command is incorrect."<<endl;
 		cout<<"Use \"HELP MOVE\" for the command help."<<endl;
 		return;
	}
	ifstream fin2(string,ios::noreplace);
	fin2.close();
	if(!fin2)
	{
		cout<<endl<<"File does not exist."<<endl;
		return;
	}
	fin2.close();
  	ifstream fin (string, ios::in | ios::ate |ios::binary );	//same as copy process
  	
  	if(fin)
  	{
    	cout<<"Please Wait.. Copying File.."<<endl;
    	getcwd(dir,MAXPATH);
    	strcpy(dirtemp,dir);
    	size = fin.tellg();
    	memory = new char [size];	//allocating
    	fin.seekg (0, ios::beg);
    	fin.read (memory, size);
    	fin.close();
    	
		cout <<endl<< "The file is Copied."<<endl;
    	cout<<"Enter the destination directory"<<endl;
    	cout<<endl;
		
		gets(file);
    	
		ChangeDir(file);		//chaning the destination dir for pasting file
		cout<<endl;
		ifstream fin2;
		fin2.open(string,ios::in | ios::noreplace | ios::nocreate);
		fin2.close();
		if(!fin2)
		{
    		ofstream fout;
			cout<<"Please Wait.. Pasting File.."<<endl;
    		fout.open(string,ios::out|ios::binary|ios::ate);
			fout.write(memory,size);
 			fout.close();
    		delete[] memory;	//deleting the allocated memory
		
    		getcwd(dir,MAXPATH);
    		chdir(dirtemp);
    		if(remove(string)!=0)
    		{
    			cout<<"Operation failed."<<endl;
				chdir(dir);
				return;
    		}
    		cout <<endl<< "The file is Pasted."<<endl;
    	}
		else
		{
			
			cout<<"File already exist."<<endl;
			char ch;
			cout<<"Do you want to overwrite?[Y/N] ";
			cin>>ch;
			cout<<endl;
			if(ch=='y'||ch=='Y')
			{
				
				ofstream fout;
				cout<<"Please Wait.. Pasting File.."<<endl;
    			fout.open(string,ios::out|ios::binary|ios::ate|ios::trunc);
				fout.write(memory,size);
 				fout.close();
    			delete[] memory;	//deleting the allocated memory
		
    			getcwd(dir,MAXPATH);
    			chdir(dirtemp);
    			if(remove(string)!=0)
    			{
    				cout<<"Operation failed."<<endl;
					chdir(dir);
					return;
    			}
    			cout <<endl<< "The file is Pasted."<<endl;	
			}
			else
				delete [] memory;
				memory=NULL;
			
			getcwd(dir,MAXPATH);
    		chdir(dirtemp);

		}
    	

  	}
  	else
	  	cout << "Unable to open file.";
}
void CMD::Paste()
{

	if(memory==NULL)
   	{
   		cout<<endl<<"Nothing is copied. Please Copy first.\n"<<endl;
   		Help("paste");
      	return;
   	}
   	else
   	{
   		ifstream fin2;
		fin2.open(file,ios::in | ios::noreplace |ios::nocreate);
		fin2.close();
		if(!fin2)
		{
    		ofstream fout;
			cout<<endl<<"Please Wait.. Pasting File.."<<endl;
    		fout.open(file,ios::out|ios::binary|ios::ate);
    		if(!fout)
   			{
   				cout<<"Not pasted succesfully!"<<endl;
   				return;
   			}
			fout.write(memory,size);
 			fout.close();
    		delete[] memory;	//deleting the allocated memory
		
    		getcwd(dir,MAXPATH);
    		chdir(dirtemp);
    		cout <<endl<< "The file is Pasted."<<endl;
    	}
		else
		{
			
			cout<<"File already exist."<<endl;
			char ch;
			cout<<"Do you want to overwrite?[Y/N] ";
			cin>>ch;
			if(ch=='y'||ch=='Y')
			{
				
				ofstream fout;
				cout<<"Please Wait.. Pasting File.."<<endl;
    			fout.open(file,ios::out|ios::binary|ios::ate|ios::trunc);
				fout.write(memory,size);
 				fout.close();
    			delete[] memory;	//deleting the allocated memory
		
    			getcwd(dir,MAXPATH);
    			chdir(dirtemp);
    			cout <<endl<< "The file is Pasted."<<endl;	
			}
			else
				delete [] memory;
				memory=NULL;
			
			getcwd(dir,MAXPATH);
    		chdir(dirtemp);

		}
   	}
}
void CMD::Rename(char string[])
{
	if(!strcmp("",string))		//if string is displaying incorrect syntax
	{
		cout<<endl<<"The syntax of the command is incorrect."<<endl;
		cout<<"Use \"HELP RENAME\" for the command help."<<endl;
		return;
	}
	ifstream fin2(string,ios::noreplace);
	fin2.close();
	if(!fin2)
	{
		cout<<endl<<"File does not exist"<<endl;
		return;
	}
    cout<<endl<<"Enter the new name."<<endl;
    gets(file);
    if(!rename(string,file))	//renaming the	old filename to new name
    {
        cout<<endl<<"Files is Renamed."<<endl;
    }
    else
    {
        cout<<endl<<"Unable to Rename."<<endl;
    }

}
void CMD::RemoveDir(char string[])//alomost same as cleanup it can just delte directory upto one inside dir
{
	if(!strcmp("",string))		//if string is displaying incorrect syntax
	{
		cout<<endl<<"The syntax of the command is incorrect."<<endl;
		cout<<"Use \"HELP REMOVEDIR\" for the command help."<<endl;
		return;
	}
   	struct dirent *drnt=NULL;
   	DIR *dirt=NULL;
   	char dirn[MAXPATH];
    if(!rmdir(string))
    {
        cout<<endl<<"\""<<string<<"\" directory is deleted."<<endl;
    }
    else
    if(rmdir(string))
    {
        getcwd(dirtemp,MAXPATH);
        strcpy(dir,dirtemp);
        strcat(dir,"\\");
        strcat(dir,string);

        if(chdir(dir))
        {
      		cout<<endl<<"Directory can not be accessed"<<endl;
            return;
        }
        getcwd(dirn,MAXPATH);
        dirt=opendir(dirn);
        while((drnt=readdir(dirt))!=NULL)
        {
        		rmdir(drnt->d_name);
            	remove(drnt->d_name);
        }
        closedir(dirt);
        chdir(dirtemp);
        if(!rmdir(string))
        {
        	cout<<endl<<"\""<<string<<"\" directory is deleted."<<endl;
        }
		
    }
    else
    {
        cout<<endl<<"Unable to delete Directory."<<endl;
    }
}

void CMD::ShowDir()
{
	char dirn[MAXPATH];
   	DIR *dirt = NULL;
   	struct dirent *drnt = NULL;
   	getcwd(dirn,MAXPATH);
	dirt=opendir(dirn);
   	ifstream fin;
	cout<<endl;
   	while((drnt=readdir(dirt))!=NULL)
   	{
		if(!(strcmp(".",drnt->d_name)&&strcmp("..",drnt->d_name)))
		{
			continue;
		}
		if(strstr(drnt->d_name,"."))
		{
			fin.open(drnt->d_name, ios::in|ios::binary|ios::ate);
			fin.seekg(0, ios::end);
			size=fin.tellg();
			
			int i;
			i=32-((signed)(strlen(drnt->d_name)));
			size=size/1024;		//to show in KB
			cout<<drnt->d_name<<setw(i)<<size<<" kB"<<endl;		//dynamic setw opt
			
			//Logic to show in MB and GB also
			/*
			if(size<=(1000000))
			{
				size=size/1024;
				cout<<drnt->d_name<<setw(i)<<size<<" kB"<<endl;
			}
			else
			if(size<=(10000000))
			{
				size=size/(1024*1024);
				cout<<drnt->d_name<<setw(i)<<size<<" MB"<<endl;
			}
			else
			{
				size=size/(1024*1024*1024);
				cout<<drnt->d_name<<setw(i)<<size<<" GB"<<endl;
			}*/

			fin.close();
		}
		else
		{
			int i;
			i=32-((signed)(strlen(drnt->d_name)));
			cout<<drnt->d_name<<setw(i)<<"<DIR>"<<endl;
		}

	}
   	closedir(dirt);
}

void CMD::Type(char string[MAX])
{
	if(!strcmp("",string))		//if string is displaying incorrect syntax
	{
		cout<<endl<<"The syntax of the command is incorrect."<<endl;
		cout<<"Use \"HELP TYPE\" for the command help."<<endl;
		return;
	}
	ifstream fin2(string,ios::noreplace);
	fin2.close();
	if(!fin2)
	{
		cout<<endl<<"File does not exist"<<endl;
		return;
	}
	//allocating the memory and showing the memory
	ifstream fin(string,ios::in|ios::ate);
	if(fin)
	{
		size = fin.tellg();
		memory = new char [size];	//allocn
		fin.seekg(0,ios::beg);
		fin.read(memory,size);
	
		cout<<endl<<memory<<endl;
		fin.close();
		delete[] memory;	//deleting the memory alloc
	}
	else
		cout<<endl<<"Unable to open the file!"<<endl;
}

int main()
{
	CMD ash;		//creating the class Object
	char string[MAX],str1[MAX],str[MAX];
	int i,j,flag=0;
	clrscr();//system("cls");
	
	cout<<"S OS [Version 1.4.19]"<<endl;
	cout<<"(c) 2013 All GPL Rights @ Shashank."<<endl;
	cout<<"Enter the \"Help\" for Help Commands."<<endl;

	do
	{
   		flushall();		//flushing the char buffer and stream buffers
		ash.Dir();		//showing the current dir
		gets(string);
		strlwr(string);
		strcpy(str1,string);
		i=0;
		str[i]=str1[i];

								//Logic to cut the one string into two
		while(str1[i]!='\0')	
		{
            if(str1[i]==' ')
            {
                flag=1;			//flag
                break;
            }
            else
                flag=0;
            i++;
		}
						
            if(flag==1)
            {
                i=0;
                while(str1[i]!=' ')		//until space occurs copy
                {
					str[i]=str1[i];
					i++;
                }
                str[i]='\0';
                strcpy(string,str);
                //cout<<endl;

                j=0;
                while(str1[i]!='\0')	//second string op
                {
                    str[j]=str1[i+1];
                    i++;
                    j++;
                }
                str[j]='\0';
            }
            else
                strcpy(str,"");
		
						//calling all the member functions using object.
		if(strstr(string,"cd.."))
            ash.cd(string);			//calling string fn
		else					
		if(!strcmp("cd",string))
			ash.cdn(str);		//calling cdn fn
		else
		if(!strcmp("changedir",string))
			ash.ChangeDir(str);		//calling changedir fn
		else
		if(!strcmp("cleanup",string))
			ash.CleanUp();		//calling cleanup fn
		else
		if(!strcmp("clear",string))
			clrscr();//system("cls");	//clearing screen
		else
		if(!strcmp("copy",string))
			ash.Copy(str);		//copy fn
		else
		if(!strcmp("delete",string))
			ash.Delete(str);	//del fn
		else
		if(!strcmp("exit",string))
			exit(0);	//exit 0 to quit from do-while loop
		else
		if(!strcmp("help",string))
			ash.Help(str);	//help
		else
		if(!strcmp("makedir",string))
			ash.MakeDir(str);	//makedir
		else
		if(!strcmp("move",string))
			ash.Move(str);		//move
		else
		if(!strcmp("paste",string))
			ash.Paste();		//paste
		else
		if(!strcmp("rename",string))
			ash.Rename(str);		//rename
		else
		if(!strcmp("removedir",string))
			ash.RemoveDir(str);		//remove dir
		else
		if(!strcmp("showdir",string))
			ash.ShowDir();		//show dir
		else
		if(!strcmp("type",string))
			ash.Type(str);		//Type fn
		else
		if(!strcmp("",string));		//if not equal copying "" for help fn.
		else
		{
			cout<<"\'"<<string<<"\'"<<"is not a recongnized command."<<endl;
			cout<<"For command help please use \"HELP\" command"<<endl;
		}
	}while(1);		//end of infinite do-while
//return 0;
}
