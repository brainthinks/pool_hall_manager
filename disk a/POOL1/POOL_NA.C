/*
		THIS MODULE MAINTAINS AND DISPLAYS THE EMPLOYOR NAME AND ADDRESS
*/
#include<stdio.h>
#include<graph.h>
FILE *na;
char na_buff[4][49];
	int centr;
	int extern fcolor;
/************************* RETRIEVE NAME AND ADDRESS ****************/
pool_nar()

{
	if(( na=fopen ("a:\\n_a.txt" ,"rb") ) != '\0')
	{
		fread(&na_buff,196,1,na);
		fclose(na);
	}
	else
	{
		memset(na_buff,' ',196);
		strcpy(&na_buff[0],"Business name");
		strcpy(&na_buff[1],"Street address");
		strcpy(&na_buff[2],"City & state");
		strcpy(&na_buff[3],"Phone no:");

		if(( na=fopen ("a:\\n_a.txt" ,"wb") ) != '\0')
		{
			fwrite(&na_buff,196,1,na);
			fclose(na);
		}
		else
		{
		_outtext("disk write error");
		exit(0);
		}
	}
}
/****************** UPDATE NAME AND ADDRESS ****************/
pool_naw()
{
	char c;
	char extern buf[80];
	int extern hcolor;
	c=' ';
	while(1)
	{
		_clearscreen(_GCLEARSCREEN);
		open_window(3,4,75,5,hcolor,7L,205,hcolor,7);
		_settextposition(2,20);
		_outtext("BUSINESS  NAME AND ADDRESS UPDATE");
		_settextwindow(1,1,24,80);
		_settextposition(19,4);
		_settextcolor(fcolor);
		_setbkcolor((long)hcolor);
		_outtext("Enter your business' name, address and phone number.");

		_settextposition(10,4);
		_outtext("Enter business name:      ");
		_settextcolor(hcolor);
		_setbkcolor((long)fcolor);
		pad(0);
		_outtext(na_buff[0]);
		_settextposition(10,30);
		reads(48,&na_buff[0],0,1,0,0);

		_settextcolor(fcolor);
		_setbkcolor((long)hcolor);
		_settextposition(12,4);
		_outtext("Enter street address:     ");
		_settextcolor(hcolor);
		_setbkcolor((long)fcolor);
		pad(1);
		_outtext(na_buff[1]);
		_settextposition(12,30);
		reads(48,&na_buff[1],0,1,0,0);

		_settextcolor(fcolor);
		_setbkcolor((long)hcolor);
		_settextposition(14,4);
		_outtext("Enter city & state:       ");
		_settextcolor(hcolor);
		_setbkcolor((long)fcolor);
		pad(2);
		_outtext(na_buff[2]);
		_settextposition(14,30);
		reads(48,&na_buff[2],0,1,0,0);

		_settextcolor(fcolor);
		_setbkcolor((long)hcolor);
		_settextposition(16,4);
		_outtext("Enter phone number:       ");
		_settextcolor(hcolor);
		_setbkcolor((long)fcolor);
		pad(3);
		_outtext(na_buff[3]);
		_settextposition(16,30);
		reads(48,&na_buff[3],0,1,0,0);

		open_window(19,20,40,4,7,(long)hcolor,205,7,hcolor);
		_outtext(" Is the above correct ?\n");
		_outtext(" Enter 'Y' for yes, 'N' for no.");
		c=getch();
		close_window(0);
		if(toupper(c)!='Y'){ close_window(1); continue;}
		break;
	}

	open_window(10,20,40,4,7,(long)hcolor,32,hcolor,7);
	_outtext("      Please wait -- updating file.");
	if(( na=fopen ("a:\\n_a.txt" ,"wb") ) != '\0')
	{
		fwrite(&na_buff,196,1,na);
		fclose(na);
	}
	else
	{
	_outtext("disk write error");
	exit(0);
	}
	close_window(1);
}
/********** pad blanks right on all n & a fields ***********************/
pad(int no)
{
	int y,x;
	x=48;
	y=strlen(na_buff[no]);
	na_buff[no][x--] = '\0';
	while(x-->y)
	na_buff[no][x] = ' ';
}





