cls

del main.obj Window.obj main.exe

cl.exe /c /EHsc /Isrc /Iresources src/core/main.c src/windows/Window.c

rc.exe /Isrc /Iresources src/windows/Window.rc

link.exe main.obj Window.obj src/windows/Window.res User32.lib GDI32.lib /SUBSYSTEM:WINDOWS

main.exe

