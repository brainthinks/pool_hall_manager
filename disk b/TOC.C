#include<stdio.h>
FILE *dbase, *cfile;
char db[256];
char cf[256];
char cf2[256],str[81];
char row[4],col[4];
char *sptr;
char *ctab[16] =
{
	"n",  //blue
	"b",  //black
	"g",  //green
	"bg", //cyan
	"r",  //red
	"rb", //magenta
	"gr", //brown
	"w",  //white
	"n+", //gray
	"b+", //light blue
	"g+", //light green
	"bg+",//light cyan
	"r+", //light red
	"rb+",//light magenta
	"gr+", //yellow
	"w+"  //bright white
};
char hf[5];
char hb[5];
int x,y,h,t,num_row,temp,ptr;
int fcolor,bcolor,hfcolor=17,hbcolor=17,first_sw=1,color_sw=0,box;
int repl_sw,chr_sw;
main()
{
	sptr=db;
	open_dbase();
	open_cfile();
	strcpy(&cf[0],"#include<conio.h>\n");
	write_cfile();                       // write new C++ record
	strcpy(&cf[0],"#include<windows.h>\n");
	write_cfile();                       // write new C++ record

	strcpy(&cf[0],"main()\n");
	write_cfile();                       // write new C++ record
	strcpy(&cf[0],"{\n");
	write_cfile();                       // write new C++ record
	strcpy(&cf[0],"textbackground(0);    //NOTE: This controls primary background color.\n");
	write_cfile();                       // write new C++ record
	strcpy(&cf[0],"                       //It must be changed by the programmer, for desired effect.\n");
	write_cfile();                       // write new C++ record
	strcpy(&cf[0],"clrscr();\n");
	write_cfile();                       // write new C++ record
	strcpy(&cf[0],"prototype();\n");
	write_cfile();                       // write new C++ record
	strcpy(&cf[0],"getch();\n");
	write_cfile();                       // write new C++ record
	strcpy(&cf[0],"clrscr();\n");
	write_cfile();                       // write new C++ record

	strcpy(&cf[0],"return 0;\n");
	write_cfile();                       // write new C++ record

	strcpy(&cf[0],"}\n");
	write_cfile();                       // write new C++ record
	strcpy(&cf[0],"prototype()\n");
	write_cfile();                       // write new C++ record
	strcpy(&cf[0],"{\n");
	write_cfile();                       // write new C++ record
	strcpy(&cf[0],"struct text_info _video;\n");
	write_cfile();                       // write new C++ record
	strcpy(&cf[0],"gettextinfo(&_video);\n");
	write_cfile();                       // write new C++ record

	while(1)
	{
		box = 0;
		if(read_dbase())break;
		for(y=0;y<256;cf[y++]='\0');          // set output to nulls
			// check first 15 char for * or \n
		for(x=0;x<15&&db[x]!='*'&&db[x]!='\n';x++);
		if(x!=15)continue;                    // discard records without *
		for(x=0;x<15&&db[x]!='@';x++);        // check first 15 char for @
		if(x==15)continue;                    // discard records without @
		for(temp =x;db[temp+5]!='\n';temp++) // CHECK FOR (BOX)
		{
			ptr = memcmp(&db[temp],"TO",2);
			if(ptr== 0)
			{
				do_box();
				box =1;
				break;
			}
		}
		if(box)
		{
			box =0;
			continue;
		}
		for(x=0;db[x]!='@';cf[x]=db[x],x++);  // copy char's preceeding @
		strcpy(&cf[x],"gotoxy(");             // replace [@] with [gotoxy(']
		x++;                                  // increment input past @
		y=x+6;                                // set y for next output char
		for(;db[x]==' ';cf[y++]=db[x++]);     // copy spaces preceeding x,y

//****** this block of code reverses row,col to col,row ********************
//****** and adds 1 to row                              ********************

		for(h=0;db[x]!=',';row[h++]=db[x++]); // store row into row[]
		row[h]='\0';
		x++;                                  // increment input past ','
		for(;isdigit(db[x]);cf[y++]=db[x++]); // copy col to output
		cf[y++]=',';                          // move a ',' in output
		num_row =atoi(row);                   // convert row to int
		num_row+=1;							  // incrment row
		itoa(num_row,row, 10);                // convert answer to string
		for(h=0;row[h]!='\0';cf[y++]=row[h++]);    // copy row to output
//**************************************************************************

		for(;db[x]==' ';cf[y++]=db[x++]);    // copy spaces following x,y
		strcpy(&cf[y],"); cputs(");       // replace [say "] with [); cputs("]
		y+=9;                                // set y for next output char
		repl_sw =0;
		for(temp =x;db[temp+5]!='\n';temp++) // CHECK FOR replicate
		{
			ptr = memcmp(&db[temp],"REPLICATE",9);
			if(ptr== 0)
			{
				do_replicate();
				repl_sw = 1;
				break;
			}
		}
		if (!repl_sw)
		{
			chr_sw=0;
			for(temp =0;db[temp+5]!='\n';temp++) // char(?)
			{
				ptr = memcmp(&db[temp],"CHR(",4);
				if(ptr== 0)
				{
					x=temp;
					for(;!isdigit(db[x]);x++);                //increment x to first digit
					for(h=0;isdigit(db[x]);row[h++]=db[x++]); //copy char to row
					row[h]='\0';                              // make string end
					h =atoi(row);
					cf[y++]='"';
					cf[y++]=h;
					cf[y++]='"';
					chr_sw=1;
					break;
				}
			}
			if(!chr_sw)
			{
				for(;db[x]!='"';x++);                // increment x to first "
				cf[y++]=db[x++];                     // move it to output
				for(;db[x]!='"';cf[y++]=db[x++]);    // copy all char'a to ending "
				cf[y++]=db[x++];                     // move it to output
			}
		}
		strcpy(&cf[y],");");                 // move [);] to output
		y+=2;                                // set y for next output char

		for(temp =x;db[temp+5]!='\0';temp++) // CHECK FOR COLOR
		{
			ptr = memcmp(&db[temp],"COLOR",5);
			if(ptr== 0)
			{
				do_color(0);
				color_sw=1;
				break;
			}
		}
		if(ptr!=0)
		if(color_sw)
		{
			color_sw=0;


			sprintf(cf2,"textcolor(%2d);\n",15);
			fwrite(cf2,strlen(cf2),1,cfile);
			sprintf(cf2,"textbackground(%1d);\n",0);
			fwrite(cf2,strlen(cf2),1,cfile);
		}
		cf[y]='\n';
		write_cfile();                       // write new C++ record
	}
	return 0;
}
//***********************************************************************
do_replicate()
{
	int c;
	x=temp+9;
	for(;!isdigit(db[x]);x++);                //increment x to first digit
	for(h=0;isdigit(db[x]);row[h++]=db[x++]); //copy char to row
	row[h]='\0';                              // make string end
	c=atoi(row);                              // convert to int and store
	for(;!isdigit(db[x]);x++);                // incremnt to # of char's
	for(h=0;isdigit(db[x]);row[h++]=db[x++]); // copy to row
	h=atoi(row);                              // convert to int
	cf[y++]='"';                              // print a <">

	memset(&cf[y],c,h);                       // copy reiterated char"s out
	y+=h;

	cf[y++]='"';



return 0;
}
//************************************************************************
do_box()
{
	int st,n_row,n_col,boarder =0;
	int hattr;
	strcpy(&str,"open_window(");
	st+=12;
	for(;db[x]!=',';x++);
	x--;
	for(;isdigit(db[x]);x--);
	x++;
	for(h=0;db[x]!=',';row[h++]=db[x],x++); //move row
	row[h]='\0';
	num_row =(atoi(row))+1;                   // convert row to int
	itoa(num_row,row,10);
	for(h=0;row[h]!='\0';str[st++]=row[h++]);
	str[st++]=',';
	row[h]='\0';
	x++;
	for(h=0;isdigit(db[x]);str[st++]=db[x],col[h++]=db[x],x++);              // move column
	str[st++]=',';
	col[h]='\0';

	for(;db[x]!=',';x++);
	x--;
	for(;isdigit(db[x]);x--);
	x++;
	for(h=0;db[x]!=',';row[h++]=db[x],x++); //store row2

	n_row = ((atoi(row)+1)-num_row)+1;    //compute window depth
	itoa(n_row,row, 10);
	num_row =atoi(col);

	x++;
	for(h=0;isdigit(db[x]);col[h++]=db[x],x++);     // store column 2
	n_col = (atoi(col)-num_row)+1;               //compute window width
	itoa(n_col,col, 10);


	for(h=0;col[h]!='\0';str[st++]=col[h++]);
	str[st++]=',';
	for(h=0;row[h]!='\0';str[st++]=row[h++]);
	str[st++]=',';
	color_sw=0;
	for(temp =x;db[temp+5]!='\0';temp++) // CHECK FOR COLOR
	{
		ptr = memcmp(&db[temp],"COLOR",5);
		if(ptr== 0)
		{
			do_color(1);
			color_sw=1;
			break;
		}
	}
	if(color_sw)
		itoa(fcolor,col, 10);
	else
	{
		fcolor=15;               // temp
		strcpy(col,"15");
	}
	for(h=0;col[h]!='\0';str[st++]=col[h++]);  //text color
	str[st++]=',';
	if(color_sw)
		itoa(bcolor,col, 10);
	else
	{
		bcolor=0;
		strcpy(col,"0");
	}
	for(h=0;col[h]!='\0';str[st++]=col[h++]);  //background color
	str[st++]=',';
		boarder =196;
		for(temp =0;db[temp+5]!='\n';temp++) // CHECK FOR boarder
		{
			ptr = memcmp(&db[temp],"CHR(",4);
			if(ptr== 0)
			{
				x=temp;
				for(;!isdigit(db[x]);x++);                //increment x to first digit
				for(h=0;isdigit(db[x]);row[h++]=db[x++]); //copy char to row
				row[h]='\0';                              // make string end
				boarder =atoi(row);
				break;
			}


			ptr = memcmp(&db[temp],"DOUBLE",6);
			if(ptr== 0)
			{
				boarder =205;
				break;
			}
			ptr = memcmp(&db[temp],"SINGLE",6);
			if(ptr== 0)
			{
				boarder =196;
				break;
			}
			ptr = memcmp(&db[temp],"CHR(",4);
			if(ptr== 0)
			{
				x=temp;
				for(;!isdigit(db[x]);x++);                //increment x to first digit
				for(h=0;isdigit(db[x]);row[h++]=db[x++]); //copy char to row
				row[h]='\0';                              // make string end
				boarder =atoi(row);
				break;
			}

		}
		itoa(boarder,col, 10);
		for(h=0;col[h]!='\0';str[st++]=col[h++]);  //boarder
		str[st++]=',';
		if(color_sw)
			itoa(fcolor,col, 10);
		else
		{
			fcolor=15;			//temp
			strcpy(col,"15");
		}

		for(h=0;col[h]!='\0';str[st++]=col[h++]);  //text color
		str[st++]=',';
		if(color_sw)
		{
			itoa(bcolor,col, 10);

		}
		else
		{
			bcolor=0;
			strcpy(col,"0");
		}
		hfcolor = fcolor;
		hbcolor = bcolor;
		for(h=0;col[h]!='\0';str[st++]=col[h++]);  //background color
		strcpy(&str[st],");\n");
		fwrite(str,strlen(str),1,cfile);
		strcpy(str,"window(1,1,80,25);\n");
		fwrite(str,strlen(str),1,cfile);

return 0;
}
//*************************************************************************
do_color(int c_exit)

{
int i,ptr,tst,blink=0;

	for(;db[x]!='/';x++);
//***************************  SET COLORS FOR TEXT
	for(;db[x]!=' ';x--);
	x++;
	for(i=0;db[x]!='/';x++)
	{
		if(db[x]!='*')
		{
			hf[i++]=db[x];
			continue;
		}
		blink =1;
    }
	hf[i]='\0';
	i=0;
	while(i<16)          // be sure to add error check & * check
	{
		ptr=memcmp(hf,ctab[i++],strlen(hf));
		if (ptr==0) break;
	}
	if (ptr!=0)
		{
			cputs("error dbase color not in table");
			getch();
			exit (0);
		}
	fcolor = --i;
	if(blink)
	{
		fcolor +=128;
		blink=0;
	}
//*************************** SET COLORS FOR BACKGROUND
	x++;
	for(i=0;isgraph(db[x]);hb[i++]=db[x++]);
	hb[i]='\0';
	i=0;
	while(i<16)          // be sure to add error check & * check
	{
		ptr=memcmp(hb,ctab[i++],strlen(hb));
		if (ptr==0) break;
	}
	if (ptr!=0)
		{
			cputs("error dbase color not in table");
			getch();
			exit (0);
		}
	
	bcolor = --i;
	if(c_exit) return 0;
	if(fcolor!=hfcolor)
	{
		sprintf(cf2,"textcolor(%2d);\n",fcolor);
		fwrite(cf2,strlen(cf2),1,cfile);
		hfcolor=fcolor;
	}
	if(bcolor!=hbcolor)
	{
		sprintf(cf2,"textbackground(%1d);\n",bcolor);
		fwrite(cf2,strlen(cf2),1,cfile);
		hbcolor=bcolor;
	}
	first_sw =0;
	if(db[x]=='\n')return 0;
	for(;db[x]!=' ';x++);
	return 0;
}

read_dbase()
{
	char *xx;
	if( fgets(sptr,256,dbase)==0)
		{
		strcpy(&cf[0],"return 0;\n");
		write_cfile();                       // write new C++ record

		strcpy(&cf[0],"}\n");
		write_cfile();                       // write new C++ record

		fclose(dbase);
		fclose(cfile);
		exit(0);
	   }
return 0;
}
write_cfile()
{
	fwrite(cf,strlen(cf),1,cfile);
	return 0;
}
open_dbase()
{
	if(( dbase=fopen ("dbtoc.fmt" ,"r") ) != '\0');
	else
	{
		cputs("dbase input disk write error");
		{
		getch();
		exit(0);
		}
	}
		return 0;
}
open_cfile()
{
		if(( cfile=fopen ("dbtoc.c" ,"w") ) != '\0');

		else
		{
		cputs("c_file output disk write error");
		getch();
		exit(0);
		}
		return 0;
}