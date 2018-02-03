/********************************************************
*   THIS INCLUDE FILE IS REQUIRED FOR THE FUNCTIONS:    *
*      OPEN_WINDOW()                                    *
*      CLOSE_WINDOW()                                   *
*********************************************************/


 extern void save_window(int wr1,int wc1,int wy,int wz,int wt,long wb);
 extern void close_window(int all);
 extern void open_window(int r,int c, int w,int l,int wt,long wb,int panel,int pt,int pb);
 unsigned ptr_no =0;
 void far *tmp;
 void far *buf_ptr[25];    /* up to 25 windows can be open at once */
