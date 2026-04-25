cls

del main.obj Window.obj main.exe

cl.exe /c /EHsc main.c Window.c

rc.exe Window.rc

link.exe main.obj Window.obj Window.res User32.lib GDI32.lib /SUBSYSTEM:WINDOWS

main.exe

