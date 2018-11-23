# linux_paint
linux_paint

** You need GTK+ 3.0!. Please download GTK+ 3.0 library **

$ sudo apt-get install libgtk-3-dev

test compile 

$ cd app/

$ gcc `pkg-config --cflags gtk+-3.0` -o test main.c ../src/*.c -I../include `pkg-config --libs gtk+-3.0`
