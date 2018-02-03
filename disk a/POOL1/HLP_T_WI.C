/*************************************************************************
*  THIS FILE IS USED AS INPUT TO THE HELPMAKE PROGRAM TO CREATE THE      *
*  QC HELP SCREEN FOR THE FUNCTIONS OPEN_WINDOW() AND CLOSE_WINDOW().    *
**************************************************************************/
.context open_window
.context close_window
:l20
  extern void open_window  (1,2,3,4,5,6,7,8,9);  THE PARAMETERS ARE:

  1. INT ROW  2. INT COLUMN 3. INT WIDTH 4. INT LENGTH
  5. INT RECTANGLE TEXT COLOR  6. LONG RECTANGLE BACKGROUND COLOR
  7. CHARACTER TO USE FOR BOARDER (CAN BE ANY CHARACTER)
		 FOR SINGLE LINE USE ASCII 196
		 FOR DOUBLE LINE USE ASCII 205
  8. INT BOARDER TEXT COLOR  9. LONG BOARDER BACKGROUND COLOR

  THIS FUNCTION PLACES RECTANGLES WITH BOARDERS ONTO THE SCREEN AFTER
  STORING THE CONTENTS OF THE SCREEN TO BE COVERED UP. A WINDOW IS
  SET SO THE COORDINATES OF THE UPPER LEFT CORNER OF THE RECTANGLE
  WILL BE (ROW 1 ,COLUMN 1)
  TO CLOSE THE LAST WINDOW OPENED AND RESTORE THE SCREEN USE
		CLOSE_WINDOW(<1>)  FUNCTION
		1. int -- if = to (0) closes last window opened.
		  if = to (1) closes all windows.

   Index       Color      Index       Color
   0           Black      8           Dark gray
   1           Blue       9           Light blue
   2           Green      10          Light green
   3           Cyan       11          Light cyan
   4           Red        12          Light red
   5           Magenta    13          Light magenta
   6           Brown      14          Yellow
   7           White      15          Bright white


